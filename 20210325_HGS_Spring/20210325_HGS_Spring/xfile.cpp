//=============================================================================
//
// Xファイルの管理クラス [xfile.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "xfile.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CXfile::CXfile()
{
	memset(m_aXfile, 0, sizeof(m_aXfile));
	memset(m_aModelFile, 0, sizeof(m_aModelFile));
	memset(m_pFileName, 0, sizeof(m_pFileName));
	memset(m_nMaxParts, 0, sizeof(m_nMaxParts));
//	memset(m_aHierarchyModel, 0, sizeof(m_aHierarchyModel));

	for (int nCount = 0; nCount < HIERARCHY_XFILE_NUM_MAX; nCount++)
	{
		// 初期化処理
		m_apHierarchyModel[nCount].clear();
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CXfile::~CXfile()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CXfile * CXfile::Create(void)
{
	// メモリ確保
	CXfile *pXfile = new CXfile;

	return pXfile;
}

//=============================================================================
// Xファイルロード
//=============================================================================
HRESULT CXfile::ModelLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

//	// Xファイルの読み込み
//	D3DXLoadMeshFromX(XFILE_NAME_BG,
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		nullptr,
//		&m_aXfile[XFILE_NUM_BG].pBuffMat,
//		nullptr,
//		&m_aXfile[XFILE_NUM_BG].dwNumMat,
//		&m_aXfile[XFILE_NUM_BG].pMesh);
//
//	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
//	{
//		//マテリアル情報の解析
//		D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[nCount].pBuffMat->GetBufferPointer();
//
//		for (int nCntMat = 0; nCntMat < (int)m_aXfile[nCount].dwNumMat; nCntMat++)
//		{
//			// ファイルネームの取得
//			char cData[128] = {};
//
//			sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);
//
//			// テクスチャの読み込み
//			D3DXCreateTextureFromFile(pDevice, cData, &m_aXfile[nCount].apTexture[nCntMat]);
//		}
//	}

	return S_OK;
}

//=============================================================================
// Xファイルアンロード
//=============================================================================
void CXfile::ModelUnLoad(void)
{
	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		//メッシュの破棄
		if (m_aXfile[nCount].pMesh != nullptr)
		{
			m_aXfile[nCount].pMesh->Release();
			m_aXfile[nCount].pMesh = nullptr;
		}
		//マテリアルの破棄
		if (m_aXfile[nCount].pBuffMat != nullptr)
		{
			m_aXfile[nCount].pBuffMat->Release();
			m_aXfile[nCount].pBuffMat = nullptr;
		}

		// テクスチャの破棄
		for (int nCntTexture = 0; nCntTexture < MAX_XFILE_TEXTURE; nCntTexture++)
		{
			if (m_aXfile[nCount].apTexture[nCntTexture] != nullptr)
			{
				m_aXfile[nCount].apTexture[nCntTexture]->Release();
				m_aXfile[nCount].apTexture[nCntTexture] = nullptr;
			}
		}
	}
}

//=============================================================================
// 階層構造のモデルファイル読み込み
//=============================================================================
HRESULT CXfile::HierarchyReadFile(void)
{
	FILE *pFile = nullptr;		//FILEポインタ

	// ファイルの名前を設定
	SetHierarchyFileName();

	for (int nModelCnt = 0; nModelCnt < HIERARCHY_XFILE_NUM_MAX; nModelCnt++)
	{
		// ファイルオープン
		pFile = fopen(m_pFileName[nModelCnt], "r");

		char aHeadData[1024];
		char aModeName[1024];
		int nModelIndex = 0;	// モデルのインデックス
		int nMotionType = 0;	// モーションのタイプ
		int nKeyNum = 0;		// キー番号
		int nMotionNum = 0;		// モーション番号

		if (pFile != nullptr)
		{
			do
			{
				//一列読み込んでモード情報を抽出
				fgets(aHeadData, sizeof(aHeadData), pFile);
				sscanf(aHeadData, "%s", aModeName);

				if (strcmp(aModeName, "MODEL_FILENAME") == 0)
				{
					//Xファイルの名前
					sscanf(aHeadData, "%*s %*s %s %*s %*s", m_aModelFile[nModelIndex][nModelCnt].xFileName);

					//インデックスを１つ進める
					nModelIndex++;
				}

				if (strcmp(aModeName, "CHARACTERSET") == 0)
				{
					//インデックスを最初に戻す
					nModelIndex = 0;

					//END_MOTIONSETを読み込むまで繰り返す
					while (strcmp(aModeName, "END_CHARACTERSET") != 0)
					{
						//一列読み込んでモード情報を抽出
						fgets(aHeadData, sizeof(aHeadData), pFile);
						sscanf(aHeadData, "%s", aModeName);

						if (strcmp(aModeName, "PARTSSET") == 0)
						{
							//END_PARTSSETを読み込むまで繰り返す
							while (strcmp(aModeName, "END_PARTSSET") != 0)
							{
								//一列読み込んでモード情報を抽出
								fgets(aHeadData, sizeof(aHeadData), pFile);
								sscanf(aHeadData, "%s", aModeName);

								if (strcmp(aModeName, "PARENT") == 0)
								{
									//親子情報の設定
									sscanf(aHeadData, "%*s %*s %d", &m_aModelFile[nModelIndex][nModelCnt].nParent);
								}
								if (strcmp(aModeName, "POS") == 0)
								{
									//位置の設定
									sscanf(aHeadData, "%*s %*s %f %f %f", &m_aModelFile[nModelIndex][nModelCnt].offsetPos.x,
										&m_aModelFile[nModelIndex][nModelCnt].offsetPos.y, &m_aModelFile[nModelIndex][nModelCnt].offsetPos.z);
								}
								if (strcmp(aModeName, "ROT") == 0)
								{
									//向きの設定
									sscanf(aHeadData, "%*s %*s %f %f %f", &m_aModelFile[nModelIndex][nModelCnt].offsetRot.x,
										&m_aModelFile[nModelIndex][nModelCnt].offsetRot.y, &m_aModelFile[nModelIndex][nModelCnt].offsetRot.z);
								}
							}

							//インデックスを１つ進める
							nModelIndex++;

							// パーツ数を数える
							m_nMaxParts[nModelCnt]++;

						}
					}
				}

			} while (strcmp(aModeName, "END_SCRIPT") != 0);

			//ファイルクローズ
			fclose(pFile);
		}
		else
		{
			//失敗した場合メッセージボックスを表示
			MessageBox(nullptr, "モーションファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);

			return	E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// 階層構造のモデルロード
//=============================================================================
HRESULT CXfile::HierarchyModelLoad(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (int nCount = 0; nCount < m_nMaxParts[nXFileNumCnt]; nCount++)
		{
			MODEL Hierarchy = {nullptr, nullptr, 0, nullptr};

			//モデルの読み込み
			D3DXLoadMeshFromX(m_aModelFile[nCount][nXFileNumCnt].xFileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				nullptr,
				&Hierarchy.pBuffMat,
				nullptr,
				&Hierarchy.dwNumMat,
				&Hierarchy.pMesh);

			//マテリアル情報の解析
			D3DXMATERIAL *materials = (D3DXMATERIAL*)Hierarchy.pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)Hierarchy.dwNumMat; nCntMat++)
			{
				if (materials[nCntMat].pTextureFilename != nullptr)
				{
					// ファイルネームの取得
					char cData[256] = {};

					sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

					// テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice, cData, &Hierarchy.apTexture[nCntMat]);
				}
			}

			// モデル情報を取得
			m_apHierarchyModel[nXFileNumCnt].push_back(Hierarchy);
		}
	}

	return S_OK;
}

//=============================================================================
// 階層構造のアンモデルロード
//=============================================================================
void CXfile::HierarchyModelUnLoad(void)
{
	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (unsigned nCount = 0; nCount < m_apHierarchyModel[nXFileNumCnt].size(); nCount++)
		{
			//マテリアル情報の破棄
			if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat != nullptr)
			{
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat->Release();
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat = nullptr;
			}

			//メッシュ情報の破棄
			if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh != nullptr)
			{
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh->Release();
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh = nullptr;
			}

			// テクスチャの開放
			for (int nCntTexture = 0; nCntTexture < MAX_XFILE_TEXTURE; nCntTexture++)
			{
				if (m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture[nCntTexture] != nullptr)
				{
					m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture[nCntTexture]->Release();
					m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture[nCntTexture] = nullptr;
				}
			}
		}

		m_apHierarchyModel[nXFileNumCnt].clear();
	}
}

//=============================================================================
// ファイルの名前を設定
//=============================================================================
void CXfile::SetHierarchyFileName(void)
{
//	m_pFileName[HIERARCHY_XFILE_NUM_PLAYER] = HIERARCHY_FILENAME_PLAYER;
}

//=============================================================================
// モデルの情報
//=============================================================================
CXfile::MODEL CXfile::GetXfile(XFILE_NUM Tex_Num)
{
	return m_aXfile[Tex_Num];
}

//=============================================================================
// モデルに使用するテクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 *CXfile::GetXfileTexture(XFILE_NUM TexNum)
{
	if (TexNum < XFILE_NUM_MAX)
	{
		if (m_aXfile[TexNum].apTexture != nullptr)
		{
			return m_aXfile[TexNum].apTexture;
		}
	}

	return nullptr;
}
