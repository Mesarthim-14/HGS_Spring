#ifndef _NICE_H_
#define _NICE_H_
//=============================================================================
//
// ナイスヘッダー [nice.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_NUMBER		(2)				// ナンバーの桁数
#define NICE_POS_X		(152.0f)		// ナイスの横の座標
#define NICE_POS_Y		(525.0f)		// ナイスの縦の座標
#define NICE_SIZE_X		(35.0f)			// ナイスの横のサイズ
#define NICE_SIZE_Y		(40.0f)			// ナイスの縦のサイズ

//=============================================================================
// 前置宣言
//=============================================================================
class CNumber2d;

//=============================================================================
// レンダラークラス
//=============================================================================
class CNice : public CScene
{
public:
	CNice();				// コンストラクタ
	~CNice();			// デストラクタ

							// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	static CNice *Create(void);								// 生成

private:
	CNumber2d *m_pNice[MAX_NUMBER];	// 桁数分
	int m_nNice;									// スコア
};

#endif