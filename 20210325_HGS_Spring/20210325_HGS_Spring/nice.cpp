//=============================================================================
//
// ナイスクラス [nice.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "nice.h"
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
#define RANKING_INTERVAL_X	(50.0f)					// 数字の間隔
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
CNice * CNice::Create(void)
{
	// メモリ確保
	CNice *pRanking = new CNice;

	// 初期化処理
	pRanking->Init();

	return pRanking;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CNice::CNice()
{
	// 0クリア
	memset(m_pNice, 0, sizeof(m_pNice));
	m_nNice = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CNice::~CNice()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNice::Init(void)
{
	CTexture *pTexture = GET_TEXTURE_PTR;

	// スコアの取得
	m_nNice = CScore::GetScorePointa()->GetScoreData().nNumNice;

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		// 数字のメモリ確保
		m_pNice[nCount] =
			CNumber2d::Create(D3DXVECTOR3(NICE_POS_X - nCount*RANKING_INTERVAL_X,
				NICE_POS_Y + RANKING_INTERVAL_Y, 0.0f),
				D3DXVECTOR3(NICE_SIZE_X, NICE_SIZE_Y, 0.0f));

		if (m_pNice[nCount] != NULL)
		{
			int nNum = (m_nNice / (int)(pow(10, nCount))) % 10;

			// 数字の設定
			m_pNice[nCount]->SetNumber(nNum);
		}

		// テクスチャの設定
		m_pNice[nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_1_2D));
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNice::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pNice[nCount] != NULL)
		{
			// 終了処理
			m_pNice[nCount]->Uninit();
			//delete m_apRanking[nCntRank][nCount];
			m_pNice[nCount] = NULL;
		}
	}

	// メモリの開放処理
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CNice::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CNice::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pNice[nCount] != NULL)
		{
			// 描画処理
			m_pNice[nCount]->Draw();
		}
	}
}