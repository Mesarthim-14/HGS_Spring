#ifndef _RANKING_H_
#define _RANKING_H_
//=============================================================================
//
// ランキングクラスヘッダー [ranking.h]
// Author : Konishi Yuuto
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
#define MAX_RANKING		(5)				// ランキングの数
#define RANKING_POS_X	(1000.0f)		// ランキングの横の座標
#define RANKING_POS_Y	(150.0f)		// ランキングの縦の座標
#define RANKING_SIZE_X	(55.0f)			// ランキングの横のサイズ
#define RANKING_SIZE_Y	(60.0f)			// ランキングの縦のサイズ

#define MY_RANKING_SIZE_X	(55.0f)		// ランキングの横のサイズ
#define MY_RANKING_SIZE_Y	(60.0f)		// ランキングの縦のサイズ

//=============================================================================
// 前置宣言
//=============================================================================
class CNumber2d;

//=============================================================================
// レンダラークラス
//=============================================================================
class CRanking : public CScene
{
public:
	CRanking();				// コンストラクタ
	~CRanking();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	static CRanking *Create(void);								// 生成
	void Save(void);											// ファイル出力
	static void Load(void);										// ファイル入力
	static void SetRanking(int nNumber);						// ランキングにスコアを与える
	void FlashPolygon(void);									// ポリゴンの点滅

private:
	CNumber2d *m_apRanking[MAX_RANKING][MAX_NUMBER];	// 桁数分
	CNumber2d *m_apMyRanking[MAX_NUMBER];				// 自分のスコア表示
	static int m_nRanking[MAX_RANKING];					// スコア
	int m_nNumRanking;									// ランキングの数
	static int m_nCurrentNum;							// 現在プレイしたスコア
	int m_nFlashFlame = 0;								// ランキングの点滅フレーム
	int m_nSubNumber;									// 点滅用変数
	int m_nSubNum;										// 点滅用変数
	static int m_nMyRank;								// 自分自身のスコア
};

#endif