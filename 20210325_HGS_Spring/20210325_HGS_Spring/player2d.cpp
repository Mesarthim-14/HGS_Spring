//=============================================================================
//
// プレイヤー2dクラス [player2d.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "player2d.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "sound.h"
#include "collision.h"
#include "texture.h"
#include "resource_manager.h"
#include "map_manager.h"
#include "scroll_polygon.h"
#include "particle.h"
#include "time_limit.h"
#include "score.h"
#include "gauge.h"
#include "fade.h"
#include "number_2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED					(5.0f)				// プレイヤーの移動量
#define STICK_SENSITIVITY				(50.0f)				// スティック感度
#define PLAYER_ROT_SPEED				(0.1f)				// キャラクターの回転する速度
#define PLAYER_RADIUS					(50.0f)				// 半径の大きさ

//=============================================================================
// クリエイト
//=============================================================================
CPlayer2d * CPlayer2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CPlayer2d *pPlayer = new CPlayer2d;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 座標
		pPlayer->SetSceneInfo(pos, size);

		// 初期化処理
		pPlayer->Init();

		// テクスチャの設定
		CTexture *pTexture = GET_TEXTURE_PTR;
		pPlayer->BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_PLAYER_NEUTRAL));
		D3DXVECTOR2 TexInfo = pTexture->GetSparateTexInfo(CTexture::SEPARATE_TEX_PLAYER_NEUTRAL);
		bool bLoop = pTexture->GetSparateTexLoop(CTexture::SEPARATE_TEX_PLAYER_NEUTRAL);

		// アニメーションの設定
		pPlayer->InitAnimation((int)TexInfo.x, (int)TexInfo.y, bLoop);

	}

	return pPlayer;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer2d::CPlayer2d(PRIORITY Priority) : CCharacter2d(Priority)
{
	m_pScrollPolygon.clear();
	m_pTimeLimit = NULL;
	m_bDeath = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer2d::~CPlayer2d()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer2d::Init(void)
{
	CCharacter2d::Init();												// 座標　角度
	SetRadius(PLAYER_RADIUS);											// 半径の設定
	SetSpeed(PLAYER_SPEED);												// 速度の設定
	m_pTimeLimit = CTimeLimit::Create(); // 制限時間の生成
	m_bDeath = false;// 死亡フラグ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer2d::Uninit(void)
{
	if (m_pTimeLimit != NULL)
	{
		m_pTimeLimit->Uninit();
		m_pTimeLimit = NULL;
	}

	// 終了処理
	CCharacter2d::Uninit();

	// 終了処理
	if (m_pTimeLimit != nullptr)
	{
		m_pTimeLimit->Uninit();
		m_pTimeLimit = nullptr;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer2d::Update(void)
{
	// 座標代入
	D3DXVECTOR3 pos = GetPos();	// 現在の座標取得
	SetOldPos(pos);				// 古い座標保存

	// プレイヤーの状態
	UpdateState();

	// プレイヤーの制御
	PlayerControl();

	// 親クラスの更新処理
	CCharacter2d::Update();

	// 死亡チェック
	if (m_bDeath)
	{
		// リザルトに遷移処理
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_RESULT);

		//// コントローラー振動
		//CManager::GetJoypad()->SetVibration(0);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer2d::Draw(void)
{
	// 描画処理
	CCharacter2d::Draw();
}

//=============================================================================
// プレイヤーの状態
//=============================================================================
void CPlayer2d::UpdateState(void)
{
}

//=============================================================================
// プレイヤーの制御
//=============================================================================
void CPlayer2d::PlayerControl()
{
	// サイズが空じゃなかったら
	if (m_pScrollPolygon.size() != 0)
	{
		if (m_pScrollPolygon.at(0)->GetStop() == true)
		{
			// 制限時間クラスの更新
			if (!m_pTimeLimit->Update())
			{// 制限時間を過ぎたとき
				if (m_bDeath == false)
				{// 死亡フラグがfalseの時

				 // フラグをtrueに
					m_bDeath = true;
					// パーティクル生成
					CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_ALL);
					// コントローラー振動
					CManager::GetJoypad()->SetVibration(0);
				}
			}

			// 入力の種類
			INPUT_TYPE InputType = INPUT_TYPE_NONE;

			// 入力処理
			InputType = InputDirection();

			// 方向の入力
			if (InputType != INPUT_TYPE_NONE)
			{
				// 入力判定
				if (InputJudg(InputType) == true)
				{
					// スコア加算
					CScore::GetScorePointa()->AddScore(m_pTimeLimit->CheckEvaluation());
					
					// テクスチャの変更
					ChangeTexture(InputType);
				}
				else
				{// 衝突の判定
					if (m_bDeath == false)
					{// 死亡フラグがfalseの時
						
						// フラグをtrueに
						m_bDeath = true;

						// パーティクル生成
						if      (InputType == INPUT_TYPE_UP)    CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_UP);
						else if (InputType == INPUT_TYPE_DOWN)  CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_DOWN);
						else if (InputType == INPUT_TYPE_LEFT)  CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_LEFT);
						else if (InputType == INPUT_TYPE_RIGHT) CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_RIGHT);
						// コントローラー振動
						CManager::GetJoypad()->SetVibration(0);
					}
				}

				// スクロールポリゴン情報の破棄
				m_pScrollPolygon.pop_back();

				CMapManager *pMapManager = CGame::GetMapManager();

				// 次のマップ生成
				pMapManager->CreateMap(InputType);

				// ゲージ消す
				m_pTimeLimit->GetGauge()->Uninit();
				// 制限時間消す
				m_pTimeLimit->Uninit();
				m_pTimeLimit = NULL;

				m_pTimeLimit = CTimeLimit::Create(); // 制限時間の生成
			}
		}
	}
}

//=============================================================================
// 入力処理
//=============================================================================
INPUT_TYPE CPlayer2d::InputDirection(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// キーボード更新
	CInputJoypad *pJoyPad = CManager::GetJoypad();  // ジョイパッドの取得

	if (pKeyboard->GetTrigger(DIK_W) || pJoyPad->GetPushCross(CROSS_KEY_UP) || pJoyPad->GetStick().lY <= -600)
	{
		return INPUT_TYPE_UP;
	}
	else if (pKeyboard->GetTrigger(DIK_A) || pJoyPad->GetPushCross(CROSS_KEY_LEFT) || pJoyPad->GetStick().lX <= -600)
	{
		return INPUT_TYPE_LEFT;
	}
	else if (pKeyboard->GetTrigger(DIK_S) || pJoyPad->GetPushCross(CROSS_KEY_DOWN) || pJoyPad->GetStick().lY >= 600)
	{
		return INPUT_TYPE_DOWN;
	}
	else if (pKeyboard->GetTrigger(DIK_D) || pJoyPad->GetPushCross(CROSS_KEY_RIGHT) || pJoyPad->GetStick().lX >= 600)
	{
		return INPUT_TYPE_RIGHT;
	}

	return INPUT_TYPE_NONE;
}

//=============================================================================
// プレイヤー移動処理
//=============================================================================
void CPlayer2d::Move(void)
{
	// ローカル変数
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// キーボード更新
	DIJOYSTATE js = CManager::GetJoypad()->GetStick();						// ジョイパッドの取得
	float fSpeed = GetSpeed();												// スピード

	//入力が存在する
	if ((js.lX != 0.0f || js.lY != 0.0f))
	{
		float fAngle = atan2f((float)js.lX, (float)js.lY);	// コントローラの角度

		// 移動量設定
		GetPos().x += sinf(fAngle)* fSpeed;
		GetPos().y += cosf(fAngle)* fSpeed;
	}
}

//=============================================================================
// 入力の判定
//=============================================================================
bool CPlayer2d::InputJudg(INPUT_TYPE InputType)
{
	CScrollPolygon::SCROLL_INFO ScrollPolygon = m_pScrollPolygon[0]->GetScrollInfo();

	// 判定
	switch (InputType)
	{
	case INPUT_TYPE_UP:
		if (ScrollPolygon.Direcsion == CScrollPolygon::DIRECTION_TYPE_UP && ScrollPolygon.bFlag == true ||
			ScrollPolygon.Direcsion != CScrollPolygon::DIRECTION_TYPE_UP && ScrollPolygon.bFlag == false)
		{
			return true;
		}

		break;

	case INPUT_TYPE_DOWN:
		if (ScrollPolygon.Direcsion == CScrollPolygon::DIRECTION_TYPE_DOWN && ScrollPolygon.bFlag == true ||
			ScrollPolygon.Direcsion != CScrollPolygon::DIRECTION_TYPE_DOWN && ScrollPolygon.bFlag == false)
		{
			return true;
		}

		break;
	case INPUT_TYPE_RIGHT:
		if (ScrollPolygon.Direcsion == CScrollPolygon::DIRECTION_TYPE_RIGHT && ScrollPolygon.bFlag == true ||
			ScrollPolygon.Direcsion != CScrollPolygon::DIRECTION_TYPE_RIGHT && ScrollPolygon.bFlag == false)
		{
			return true;
		}

		break;
	case INPUT_TYPE_LEFT:
		if (ScrollPolygon.Direcsion == CScrollPolygon::DIRECTION_TYPE_LEFT && ScrollPolygon.bFlag == true ||
			ScrollPolygon.Direcsion != CScrollPolygon::DIRECTION_TYPE_LEFT && ScrollPolygon.bFlag == false)
		{
			return true;
		}

		break;
	}

	return false;
}

//=============================================================================
// スクロールポリゴンの情報取得
//=============================================================================
void CPlayer2d::SetScrollPolygon(CScrollPolygon * pScrollPolygon)
{
	// 空だったら
	if (m_pScrollPolygon.size() == 0)
	{
		// スクロールポリゴンの設定
		m_pScrollPolygon.push_back(pScrollPolygon);
	}
}

//=============================================================================
// テクスチャの変更
//=============================================================================
void CPlayer2d::ChangeTexture(INPUT_TYPE InputType)
{
	// ポインタ取得
	CTexture *pTexture = GET_TEXTURE_PTR;

	// 判定
	switch (InputType)
	{
	case INPUT_TYPE_UP:
		// テクスチャの設定
		BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_PLAYER_UP));
		break;

	case INPUT_TYPE_DOWN:
		// テクスチャの設定
		BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_PLAYER_DOWN));
		break;
	case INPUT_TYPE_RIGHT:
		// テクスチャの設定
		BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_PLAYER_RIGHT));
		break;
	case INPUT_TYPE_LEFT:
		// テクスチャの設定
		BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_PLAYER_LEFT));
		break;
	}
}