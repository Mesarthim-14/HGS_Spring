#ifndef _EVALUATION_H_
#define _EVALUATION_H_
//=============================================================================
//
// 評価UIクラス処理  [evaluation.h]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CEvaluation : public CScene2D
{
public:
	// スコアタイプ列挙
	typedef enum
	{
		EVALUATION_TYPE_NICE = 0,
		EVALUATION_TYPE_GREAT,
		EVALUATION_TYPE_PARFECT,
		EVALUATION_TYPE_MAX
	}EVALUATION_TYPE;

	CEvaluation(PRIORITY Priority = PRIORITY_UI);	// コンストラクタ
	virtual ~CEvaluation();							// デストラクタ

	static CEvaluation* Create(void); // クラス生成

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	void SetEvaluation(EVALUATION_TYPE type);
private:

	float m_fAlpha; //アルファ値
};
#endif