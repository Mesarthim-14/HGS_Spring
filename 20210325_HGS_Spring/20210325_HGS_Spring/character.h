#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// キャラクター2Dクラス処理  [character_2d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene_base.h"
#include "modelanime.h"

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CCharacter
{
public:
	CCharacter();				// コンストラクタ
	virtual ~CCharacter() {}											// デストラクタ

	virtual HRESULT Init(void) = 0;			// 初期化処理
	virtual void Uninit(void) = 0;											// 終了処理
	virtual void Update(void) = 0;											// 更新処理
	virtual void Draw(void) = 0;											// 描画処理

	// 純粋仮想関数
	virtual void UpdateState(void) = 0;								// キャラクター状態

	// Set関数
	void SetMove(const D3DXVECTOR3 &move)		{ m_move = move; }			// 移動量の設定
	void SetOldPos(const D3DXVECTOR3 &OldPos)	{ m_OldPos = OldPos; }		// 古い座標
	void SetRadius(const float fRadius)			{ m_fRadius = fRadius; }	// 半径の設定
	void SetSpeed(const float fSpeed)			{ m_fSpeed = fSpeed; }		// 速度の設定

	// Get関数
	D3DXVECTOR3 &GetMove(void)	{ return m_move; }			// 移動量の情報
	D3DXVECTOR3 &GetOldPos(void)	{ return m_OldPos; }		// 古い座標情報
	float GetSpeed(void)		{ return m_fSpeed; }		// スピードの情報
	float GetRadius(void)		{ return m_fRadius; }		// 半径の情報
	
private:
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_OldPos;	// 古い座標
	float m_fSpeed;			// 移動量
	float m_fRadius;		// 半径
};
#endif