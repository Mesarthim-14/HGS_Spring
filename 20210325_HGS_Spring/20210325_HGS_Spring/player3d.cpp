//=============================================================================
//
// プレイヤークラス [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "player3d.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
#include "character.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED					(20.0f)				// プレイヤーの移動量
#define STICK_SENSITIVITY				(50.0f)				// スティック感度
#define PLAYER_ROT_SPEED				(0.1f)				// キャラクターの回転する速度
#define PLAYER_RADIUS					(50.0f)				// 半径の大きさ

//=============================================================================
// クリエイト
//=============================================================================
CPlayer3d * CPlayer3d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CPlayer3d *pPlayer = new CPlayer3d;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 座標
		pPlayer->SetPos(pos);
		pPlayer->SetRot(size);

		// 初期化処理
		pPlayer->Init();
	}

	return pPlayer;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer3d::CPlayer3d(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
	m_bArmor = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer3d::~CPlayer3d()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer3d::Init(void)
{
	// モデル情報取得
	CXfile *pXfile = GET_XFILE_PTR;

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデルの情報を渡す
	//	ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	CCharacter3d::Init();												// 座標　角度
	SetRadius(PLAYER_RADIUS);											// 半径の設定
	SetSpeed(PLAYER_SPEED);												// 速度の設定

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer3d::Uninit(void)
{	
	// 終了処理
	CCharacter3d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer3d::Update(void)
{
	// 座標代入
	D3DXVECTOR3 pos = GetPos();	// 現在の座標取得
	SetOldPos(pos);				// 古い座標保存

	// プレイヤーの状態
	UpdateState();

	// モーション状態
	UpdateMotionState();

	// プレイヤーの制御
	PlayerControl();

	// 角度の更新処理
	UpdateRot();

	// 親クラスの更新処理
	CCharacter3d::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer3d::Draw(void)
{
	// 描画処理
	CCharacter3d::Draw();
}

//=============================================================================
// プレイヤーの状態
//=============================================================================
void CPlayer3d::UpdateState(void)
{
}

//=============================================================================
// モーション状態
//=============================================================================
void CPlayer3d::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();
	int nKey = GetMotion()->GetKey();
	int nCountMotion = GetMotion()->GetCountMotion();

	// モーション情報
	switch (MotionState)
	{
	case MOTION_IDOL:
		break;
	}
}

//=============================================================================
// プレイヤーの制御
//=============================================================================
void CPlayer3d::PlayerControl()
{
	// プレイヤーの移動処理
	Move();
}

//=============================================================================
// 角度の更新処理
//=============================================================================
void CPlayer3d::UpdateRot(void)
{
	// 角度の取得
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// キャラクター回転の速度
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// 角度の設定
	SetRot(rot);
}

//=============================================================================
// プレイヤー移動処理
//=============================================================================
void CPlayer3d::Move(void)
{
	// ローカル変数
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// キーボード更新
	DIJOYSTATE js = CInputJoypad::GetStick(0);								// ジョイパッドの取得
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();		// サウンドのポインタ
	float fAngle = CGame::GetCamera()->Getφ();								// カメラの角度
	D3DXVECTOR3 pos = GetPos();												// 座標
	D3DXVECTOR3 rot = GetRot();												// 角度
	float fSpeed = GetSpeed();												// スピード
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();	// モーションの状態

		//入力が存在する
	if ((js.lX != 0.0f || js.lY != 0.0f))
	{
		// 歩き状態にする
		m_bMove = true;

		//歩行モーションの再生
		SetMotion(MOTION_WALK);

		float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// コントローラの角度
		float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// コントローラの角度

		// 移動量設定
		pos.x += sinf(fAngle + (fAngle2))* fSpeed;
		pos.z += cosf(fAngle + (fAngle2))* fSpeed;

		// 角度の設定
		m_rotDest.y = fAngle + (fAngle3);
	}
}