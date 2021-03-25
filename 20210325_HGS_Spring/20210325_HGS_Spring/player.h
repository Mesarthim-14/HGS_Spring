#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"

//=============================================================================
// プレイヤー2Dクラス
//=============================================================================
class CPlayer
{
public:
	enum PLAYER_STATE
	{
		PLAYER_STATE_NONE = 0,		// 初期置
		PLAYER_STATE_NORMAL,		// 通常状態
		PLAYER_STATE_DAMAGE,		// ダメージ
		PLAYER_STATE_MAX			// 最大数
	};

	CPlayer();		// コンストラクタ
	virtual ~CPlayer() {}		// デストラクタ

	virtual HRESULT Init(void) = 0;			// 初期化処理
	virtual void Uninit(void) = 0;			// 終了処理
	virtual void Update(void) = 0;			// 更新処理
	virtual void Draw(void) = 0;			// 描画処理

	// 純粋仮想関数
	virtual void UpdateState(void) = 0;			// プレイヤーの状態
	virtual void PlayerControl(void) = 0;		// プレイヤーの制御
	virtual void Move(void) = 0;				// プレイヤーの歩く処理

	// Set関数
	void SetArmor(const bool bArmor)			{ m_bArmor = bArmor; }	// 無敵時間の設定
	void SetState(const PLAYER_STATE &state)	{ m_state = state; }	// 状態

	// Get関数
	bool GetArmor(void) { return m_bArmor; }			// 無敵時間の情報
	PLAYER_STATE GetState(void) { return m_state; }		// 状態

private:
	bool m_bArmor;
	PLAYER_STATE m_state;
};
#endif