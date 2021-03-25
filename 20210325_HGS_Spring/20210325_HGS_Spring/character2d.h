#ifndef _CHARACTER_2D_H_
#define _CHARACTER_2D_H_
//=============================================================================
//
// キャラクタークラス処理  [character_2d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "modelanime.h"
#include "character.h"

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CCharacter2d : public CScene2D, public CCharacter
{
public:
	CCharacter2d(PRIORITY Priority = PRIORITY_CHARACTER);	// コンストラクタ
	virtual ~CCharacter2d();								// デストラクタ

	virtual HRESULT Init(void);								// 初期化処理
	virtual void Uninit(void);									// 終了処理
	virtual void Update(void);									// 更新処理
	virtual void Draw(void);									// 描画処理

private:
};
#endif