#ifndef _PLAYER_3D_H_
#define _PLAYER_3D_H_
//=============================================================================
//
// プレイヤー3Dクラスヘッダー [player3d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character3d.h"
#include "modelanime.h"
#include "player.h"

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer3d : public CCharacter3d, public CPlayer
{
public:
	//=============================================================================
	//　モーション状態の列挙型
	//=============================================================================
	enum MOTION_STATE
	{
		MOTION_NONE = -1,
		MOTION_IDOL,				// アイドルモーション
		MOTION_WALK,				// 歩行モーション
		MOTION_MAX,					// モーション最大数
	};

	//=============================================================================
	//　モーション状態の列挙型
	//=============================================================================
	enum PARTS_NUM
	{
		PARTS_NUM_NONE = -1,
		PARTS_NUM_MAX,				// モーション最大数
	};

	CPlayer3d(PRIORITY Priority = PRIORITY_CHARACTER);			// コンストラクタ
	~CPlayer3d();												// デストラクタ

	static CPlayer3d*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// クリエイト

	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理
	void UpdateState(void);			// プレイヤーの状態
	void UpdateMotionState(void);	// モーション状態
	void PlayerControl(void);		// プレイヤーの制御
	void UpdateRot(void);			// 角度の更新処理
	void Move(void);				// プレイヤーの歩く処理

private:
	D3DXVECTOR3 m_rotDest;			// 回転(目標値)
	bool m_bMove;					// 歩いているフラグ
	bool m_bArmor;					// 無敵時間のフラグ
};
#endif