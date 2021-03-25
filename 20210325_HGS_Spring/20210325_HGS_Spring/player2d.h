#ifndef _PLAYER_2D_H_
#define _PLAYER_2D_H_
//=============================================================================
//
// プレイヤー2Dクラスヘッダー [player2d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character2d.h"
#include "player.h"

//=============================================================================
// プレイヤー2Dクラス
//=============================================================================
class CPlayer2d : public CCharacter2d, public CPlayer
{
public:
	CPlayer2d(PRIORITY Priority = PRIORITY_CHARACTER);			// コンストラクタ
	~CPlayer2d();												// デストラクタ

	static CPlayer2d*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// クリエイト

	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理

	void UpdateState(void);			// プレイヤーの状態
	void PlayerControl(void);		// プレイヤーの制御
	void Move(void);				// プレイヤーの歩く処理

private:
};
#endif