//=============================================================================
//
// ランキングクラス [ranking.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "number_2d.h"
#include <stdio.h>
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SAVE_FILENAME "data/Text/Ranking.txt"		// ファイル名
#define RANKING_INTERVAL_X	(70.0f)					// 数字の間隔
#define RANKING_INTERVAL_Y	(100.0f)					// 数字の間隔

#define MY_RANKING_INTERVAL_X	(80.0f)				// 数字の間隔
#define MY_RANKING_INTERVAL_Y	(88.0f)				// 数字の間隔

#define RANKING_FLASH_NUM	(30)					// ランキング点滅フレーム

//=============================================================================
// マクロ定義
//=============================================================================
int CRanking::m_nRanking[MAX_RANKING] = {};
int CRanking::m_nCurrentNum = -1;
int CRanking::m_nMyRank = 0;

//=============================================================================
// ランキング生成
//=============================================================================
CRanking * CRanking::Create(void)
{
	// メモリ確保
	CRanking *pRanking = new CRanking;

	// 初期化処理
	pRanking->Init();

	return pRanking;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking()
{
	// 0クリア
	memset(m_apRanking, 0, sizeof(m_apRanking));
	memset(m_apMyRanking, 0, sizeof(m_apMyRanking));
	m_nNumRanking = 0;
	m_nFlashFlame = 0;
	m_nSubNumber = 0;
	m_nSubNum = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{
	m_nCurrentNum = -1;
	m_nMyRank = 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRanking::Init(void)
{
	CTexture *pTexture = GET_TEXTURE_PTR;

	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			// 数字のメモリ確保
			m_apRanking[nCntRank][nCount] =
				CNumber2d::Create(D3DXVECTOR3(RANKING_POS_X - nCount*RANKING_INTERVAL_X,
									RANKING_POS_Y + nCntRank*RANKING_INTERVAL_Y, 0.0f),
									D3DXVECTOR3(RANKING_SIZE_X, RANKING_SIZE_Y, 0.0f));

			if (m_apRanking[nCntRank][nCount] != NULL)
			{
				int nNum = (m_nRanking[nCntRank] / (int)(pow(10, nCount))) % 10;

				// 数字の設定
				m_apRanking[nCntRank][nCount]->SetNumber(nNum);
			}

			// 現在の番号だったら
			if (nCntRank == m_nCurrentNum)
			{
				// テクスチャの設定
				m_apRanking[nCntRank][nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_2_2D));
			}
			else
			{
				// テクスチャの設定
				m_apRanking[nCntRank][nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_1_2D));
			}
		}
	}

	//for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	//{
	//	// 数字のメモリ確保
	//	m_apMyRanking[nCount] =
	//		CNumber2d::Create(D3DXVECTOR3(470.0f - nCount*MY_RANKING_INTERVAL_X, 370.0f, 0.0f),
	//							D3DXVECTOR3(MY_RANKING_SIZE_X, MY_RANKING_SIZE_Y, 0.0f));

	//	if (m_apMyRanking[nCount] != NULL)
	//	{
	//		int nNum = (m_nMyRank / (int)(pow(10, nCount))) % 10;

	//		// 数字の設定
	//		m_apMyRanking[nCount]->SetNumber(nNum);
	//	}
	//}

	// ファイル入力
	Save();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	// ファイル入力
	Save();

	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			if (m_apRanking[nCntRank][nCount] != NULL)
			{
				// 終了処理
				m_apRanking[nCntRank][nCount]->Uninit();
				//delete m_apRanking[nCntRank][nCount];
				m_apRanking[nCntRank][nCount] = NULL;
			}
		}
	}

	//for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	//{
	//	if (m_apMyRanking[nCount] != NULL)
	//	{
	//		// 数字のメモリ確保
	//		m_apMyRanking[nCount]->Uninit();
	//		//delete m_apMyRanking[nCount];
	//		m_apMyRanking[nCount] = NULL;
	//	}
	//}

	// メモリの開放処理
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRanking::Update(void)
{
	// ポリゴンの点滅
	FlashPolygon();
}

//=============================================================================
// 描画処理
//=============================================================================
void CRanking::Draw(void)
{
	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			if (m_apRanking[nCntRank][nCount] != NULL)
			{
				// 描画処理
				m_apRanking[nCntRank][nCount]->Draw();
			}
		}
	}
	//for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	//{
	//	if (m_apMyRanking[nCount] != NULL)
	//	{
	//		// 数字のメモリ確保
	//		m_apMyRanking[nCount]->Draw();

	//	}
	//}
}

//=============================================================================
// ファイル入力
//=============================================================================
void CRanking::Save(void)
{
	FILE *pFile;

	// ファイルを開く
	pFile = fopen(SAVE_FILENAME, "w");

	// ポインタが正しいか確認
	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			// 体力をファイルに出力
			fprintf(pFile, "%d\n", m_nRanking[nCount]);

			// 改行
			printf("\n");

		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{	// 開けなかった場合
		printf("開けませんでした");
	}
}

//=============================================================================
// ファイル出力
//=============================================================================
void CRanking::Load(void)
{
	FILE *pFile;

	// テキストファイルを開く
	pFile = fopen(SAVE_FILENAME, "r");

	// ファイルが開けた時の処理
	if (pFile != NULL)
	{
		// プレイヤー情報の初期化
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			// 初期化
			m_nRanking[nCount] = 0;

			// スコアを出力
			fscanf(pFile, "%d\n", &m_nRanking[nCount]);
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{	// ファイルが開けないとき
		printf("開けませんでした\n");
	}
}

//=============================================================================
// ランキングへスコアを代入
//=============================================================================
void CRanking::SetRanking(int nNumber)
{
	// ファイル出力
	Load();

	m_nMyRank = nNumber;
	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		// ランキング圏外か判定
		if (m_nRanking[nCount] < nNumber)
		{
			for (int nCntRank = MAX_RANKING - 1; nCntRank > nCount; nCntRank--)
			{
				int nSort = m_nRanking[nCntRank];
				m_nRanking[nCntRank] = m_nRanking[nCntRank - 1];
				m_nRanking[nCntRank - 1] = nSort;
			}
			// ランキング最下位の上書き
			m_nRanking[nCount] = nNumber;

			// 現在の番号取得
			m_nCurrentNum = nCount;
			break;
		}
	}
}

//=============================================================================
// ポリゴンの生成
//=============================================================================
void CRanking::FlashPolygon(void)
{
	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			if (nCntRank == m_nCurrentNum)
			{
				if (m_nCurrentNum != -1)
				{
					// フレームを加算
					m_nFlashFlame++;

					if (m_nFlashFlame >= RANKING_FLASH_NUM)
					{
						m_nFlashFlame = 0;

						if (m_nSubNumber == 0)
						{
							// 0になったら切り替え
							m_nSubNumber = 255;
						}
						else if (m_nSubNumber == 255)
						{
							// 255になったら切り替え
							m_nSubNumber = 0;
						}

						for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
						{
							m_apRanking[nCntRank][nCount]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, (float)m_nSubNumber));
						}
					}
				}
			}
		}
	}
}