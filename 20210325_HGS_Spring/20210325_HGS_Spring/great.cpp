//=============================================================================
//
// ランキングクラス [ranking.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "great.h"
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
CGreat * CGreat::Create(void)
{
	// メモリ確保
	CGreat *pRanking = new CGreat;

	// 初期化処理
	pRanking->Init();

	return pRanking;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CGreat::CGreat():CScene(PRIORITY_UI)
{
	// 0クリア
	memset(m_pGreat, 0, sizeof(m_pGreat));
	m_nGreat = 0;

}

//=============================================================================
// デストラクタ
//=============================================================================
CGreat::~CGreat()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGreat::Init(void)
{
	CTexture *pTexture = GET_TEXTURE_PTR;

	// スコアの取得
	m_nGreat = CScore::GetScorePointa()->GetScoreData().nNumGreat;

	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			// 数字のメモリ確保
			m_pGreat[nCount] =
				CNumber2d::Create(D3DXVECTOR3(GREAT_POS_X - nCount*RANKING_INTERVAL_X,
					GREAT_POS_Y + RANKING_INTERVAL_Y, 0.0f),
					D3DXVECTOR3(RANKING_SIZE_X, RANKING_SIZE_Y, 0.0f));

			if (m_pGreat[nCount] != NULL)
			{
				int nNum = (m_nGreat / (int)(pow(10, nCount))) % 10;

				// 数字の設定
				m_pGreat[nCount]->SetNumber(nNum);
			}

			// テクスチャの設定
			m_pGreat[nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_1_2D));
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGreat::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pGreat[nCount] != NULL)
		{
			// 終了処理
			m_pGreat[nCount]->Uninit();
			//delete m_apRanking[nCntRank][nCount];
			m_pGreat[nCount] = NULL;
		}
	}

	// メモリの開放処理
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGreat::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CGreat::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pGreat[nCount] != NULL)
		{
			// 描画処理
			m_pGreat[nCount]->Draw();
		}
	}
}