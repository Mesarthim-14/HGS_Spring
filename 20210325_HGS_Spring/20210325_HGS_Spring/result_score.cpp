//=============================================================================
//
// ランキングクラス [ranking.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "result_score.h"
#include "manager.h"
#include "renderer.h"
#include "number_2d.h"
#include "texture.h"
#include "resource_manager.h"
#include "score.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define RANKING_INTERVAL_X	(45.0f)					// 数字の間隔
#define RANKING_INTERVAL_Y	(83.0f)					// 数字の間隔

#define MY_RANKING_INTERVAL_X	(80.0f)				// 数字の間隔
#define MY_RANKING_INTERVAL_Y	(88.0f)				// 数字の間隔

#define RANKING_FLASH_NUM	(3)						// ランキング点滅フレーム

//=============================================================================
// マクロ定義
//=============================================================================


//=============================================================================
// ランキング生成
//=============================================================================
CResultScore * CResultScore::Create(void)
{
	// メモリ確保
	CResultScore *pRanking = new CResultScore;

	// 初期化処理
	pRanking->Init();

	return pRanking;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CResultScore::CResultScore()
{
	// 0クリア
	m_nScore = 0;
	m_nScoreCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResultScore::~CResultScore()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResultScore::Init(void)
{
	CTexture *pTexture = GET_TEXTURE_PTR;

	// スコアの取得
	m_nScore = CScore::GetScorePointa()->GetScoreData().nScore;
	//m_nScore = 99;

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		// 数字のメモリ確保
		m_pScore[nCount] = CNumber2d::Create(D3DXVECTOR3(RESULT_SCORE_POS_X - nCount * RANKING_INTERVAL_X,
											RESULT_SCORE_POS_Y + RANKING_INTERVAL_Y, 0.0f),
											D3DXVECTOR3(RESULT_SCORE_SIZE_X, RESULT_SCORE_SIZE_Y, 0.0f));

		if (m_pScore[nCount] != NULL)
		{
			// 数字の設定
			m_pScore[nCount]->SetNumber(0);
		}

		// テクスチャの設定
		m_pScore[nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_1_2D));
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResultScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pScore[nCount] != NULL)
		{
			// 終了処理
			m_pScore[nCount]->Uninit();
			//delete m_pScore[nCntRank][nCount];
			m_pScore[nCount] = NULL;
		}
	}

	// メモリの開放処理
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CResultScore::Update(void)
{
	if (m_nScoreCount <= m_nScore)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			if (m_pScore[nCount] != NULL)
			{
				int nNum = (m_nScoreCount / (int)(pow(10, nCount))) % 10;

				// 数字の設定
				m_pScore[nCount]->SetNumber(nNum);
			}
		}

		m_nScoreCount++;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CResultScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pScore[nCount] != NULL)
		{
			// 描画処理
			m_pScore[nCount]->Draw();
		}
	}
}