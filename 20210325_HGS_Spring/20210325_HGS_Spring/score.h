#ifndef _SCORE_2D_H_
#define _SCORE_2D_H_
//=============================================================================
//
// スコアクラス処理  [score.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "evaluation_ui.h"

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CScore
{
public:
	// スコア構造体
	typedef struct
	{
		int nScore;
		int nNumNice;    // ナイス数
		int nNumGreat;   // グレート数
		int nNumParfect; // パーフェクト数
	}Score;

	CScore();	// コンストラクタ
	virtual ~CScore();								// デストラクタ
	static CScore * Create(void); // クラス生成
	static void Release(void); // クラス生成

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	void AddScore(CEvaluation::EVALUATION_TYPE type);

	static CScore *GetScorePointa(void) { return m_pScore; }
	Score GetScoreData(void) { return m_score; }
private:
	static CScore * m_pScore;
	Score m_score; // スコア構造体
};
#endif