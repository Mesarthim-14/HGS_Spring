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
	CTexture *pTexture = GET_TEXTURE_PTR;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 座標
		pPlayer->SetSceneInfo(pos, size);
		pPlayer->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PLAYER_2D));

		// 初期化処理
		pPlayer->Init();
	}

	return pPlayer;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer2d::CPlayer2d(PRIORITY Priority)
{
	m_pScrollPolygon.clear();
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

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer2d::Uninit(void)
{
	// 終了処理
	CCharacter2d::Uninit();
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
					// スクロールポリゴン情報の破棄
					m_pScrollPolygon.pop_back();

					CMapManager *pMapManager = CGame::GetMapManager();

					// 次のマップ生成
					pMapManager->CreateMap(InputType);
				}
				else
				{// 衝突の判定

				}
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

	if (pKeyboard->GetTrigger(DIK_W))
	{
		return INPUT_TYPE_UP;
	}
	if (pKeyboard->GetTrigger(DIK_A))
	{
		return INPUT_TYPE_LEFT;
	}
	if (pKeyboard->GetTrigger(DIK_S))
	{
		return INPUT_TYPE_DOWN;
	}
	if (pKeyboard->GetTrigger(DIK_D))
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
	DIJOYSTATE js = CInputJoypad::GetStick(0);								// ジョイパッドの取得
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
