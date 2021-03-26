//=============================================================================
//
// ランキングクラス [ranking.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "perfect.h"
#include "manager.h"
#include "renderer.h"
#include "number_2d.h"
#include <stdio.h>
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
CPerfect * CPerfect::Create(void)
{
	// メモリ確保
	CPerfect *pRanking = new CPerfect;

	// 初期化処理
	pRanking->Init();

	return pRanking;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPerfect::CPerfect() :CScene(PRIORITY_UI)
{
	// 0クリア
	memset(m_pPerfect, 0, sizeof(m_pPerfect));
	m_nPerfect = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPerfect::~CPerfect()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPerfect::Init(void)
{
	CTexture *pTexture = GET_TEXTURE_PTR;

	// スコアの取得
	m_nPerfect = CScore::GetScorePointa()->GetScoreData().nNumParfect;

	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			// 数字のメモリ確保
			m_pPerfect[nCount] =
				CNumber2d::Create(D3DXVECTOR3(PERFECT_POS_X - nCount*RANKING_INTERVAL_X,
					PERFECT_POS_Y + RANKING_INTERVAL_Y, 0.0f),
					D3DXVECTOR3(RANKING_SIZE_X, RANKING_SIZE_Y, 0.0f));

			if (m_pPerfect[nCount] != NULL)
			{
				int nNum = (m_nPerfect / (int)(pow(10, nCount))) % 10;

				// 数字の設定
				m_pPerfect[nCount]->SetNumber(nNum);
			}

				// テクスチャの設定
			m_pPerfect[nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_1_2D));
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPerfect::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pPerfect[nCount] != NULL)
		{
			// 終了処理
			m_pPerfect[nCount]->Uninit();
			//delete m_apRanking[nCntRank][nCount];
			m_pPerfect[nCount] = NULL;
		}
	}

	// メモリの開放処理
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPerfect::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CPerfect::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pPerfect[nCount] != NULL)
		{
			// 描画処理
			m_pPerfect[nCount]->Draw();
		}
	}
}