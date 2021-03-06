#ifndef _RESULT_SCORE_H_
#define _RESULT_SCORE_H_
//=============================================================================
//
// リザルトスコア処理 [result_score.h]
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
#define MAX_NUMBER		(2)					// ナンバーの桁数
#define RESULT_SCORE_POS_X	(390.0f)		// ランキングの横の座標
#define RESULT_SCORE_POS_Y	(200.0f)		// ランキングの縦の座標
#define RESULT_SCORE_SIZE_X	(105.0f)			// ランキングの横のサイズ
#define RESULT_SCORE_SIZE_Y	(110.0f)			// ランキングの縦のサイズ

//=============================================================================
// 前置宣言
//=============================================================================
class CNumber2d;

//=============================================================================
// レンダラークラス
//=============================================================================
class CResultScore : public CScene
{
public:
	CResultScore();				// コンストラクタ
	~CResultScore();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);											// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	static CResultScore *Create(void);							// 生成

private:
	CNumber2d *m_pScore[MAX_NUMBER];		// スコアポインタ
	float m_fScore;							// スコア
	float m_fScoreCount;						// スコアのカウント
	float m_fScoreCntSpeed;					// スコアのカウントスピード
};

#endif