//=============================================================================
//
// キャラクタークラス [character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character3d.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "game.h"
#include "player3d.h"
#include "texture.h"
#include "sound.h"
#include "resource_manager.h"
#include "motion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GRAVITY_POWAR			(0.7f)						// 重力の強さ
#define GROUND_RIMIT			(0.0f)						// 地面の制限

//=============================================================================
// コンストラクタ
//=============================================================================
CCharacter3d::CCharacter3d(PRIORITY Priority) : CScene(Priority)
{
	 m_pos = ZeroVector3;
	 m_rot = ZeroVector3;
	 m_fAngle = 0.0f;
	 memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	 m_nStateCounter = 0;
	 m_pMotion = nullptr;
	 m_nParts = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCharacter3d::~CCharacter3d()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCharacter3d::Init(void)
{

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCharacter3d::Uninit()
{
	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		// !nullcheck
		if (m_apModelAnime[nCntModelNum] != nullptr)
		{
			//メモリの削除
			delete m_apModelAnime[nCntModelNum];

			//メモリのクリア
			m_apModelAnime[nCntModelNum] = nullptr;
		}
	}

	// !nullcheck
	if (m_pMotion != nullptr)
	{
		//メモリの削除
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCharacter3d::Update()
{
	//アニメーションの更新処理
	ModelAnimeUpdate();

	// 移動量加算
	m_pos += GetMove();
}

//=============================================================================
// 描画処理
//=============================================================================
void CCharacter3d::Draw()
{
	// 描画処理
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// 裏面を（左回り）をカリング

	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != nullptr)
		{
			//階層モデルクラスの描画処理
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// 裏面を（左回り）をカリング
}

//=============================================================================
// モデルの生成
//=============================================================================
void CCharacter3d::ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum)
{
	// XFileのポインタ取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデルパーツの設定
		m_nParts = pXfile->GetModelParts(FileNum);

		//モデルパーツ数分繰り返す
		for (int nCntModel = 0; nCntModel < m_nParts; nCntModel++)
		{
			CXfile::MODELFILE ModelFile = pXfile->GetModelFile(nCntModel, FileNum);

			if (m_apModelAnime[nCntModel] == nullptr)
			{
				// 初期化処理
				m_apModelAnime[nCntModel] = CModelAnime::Create(ModelFile.offsetPos, ModelFile.offsetRot);

				// モデルの情報取得
				std::vector<CXfile::MODEL> model = pXfile->GetHierarchyXfile(FileNum);

				// モデルの生成
				m_apModelAnime[nCntModel]->SetModel(model.at(nCntModel));
			}

			//親子構造の設定
			if (m_apModelAnime[nCntModel] != nullptr)
			{
				//親モデルの場合
				if (nCntModel == 0)
				{
					m_apModelAnime[nCntModel]->SetParent(nullptr);
				}
				//子モデルの場合
				else
				{
					//自分の親情報を設定する
					m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[ModelFile.nParent]);
				}
			}
		}

		// nullcheck
		if (m_pMotion == nullptr)
		{
			// インスタンス生成
			m_pMotion = CMotion::Create(pXfile->GetModelFileName(FileNum));
		}
	}
}

//=============================================================================
// モデルアニメーション
//=============================================================================
void CCharacter3d::ModelAnimeUpdate(void)
{
	// モーションの更新処理
	if (m_pMotion != nullptr)
	{
		// モーションの更新
		m_pMotion->UpdateMotion(m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// モーションの設定
//=============================================================================
void CCharacter3d::SetMotion(int nMotionState)
{
	// !nullcheck
	if (m_pMotion != nullptr)
	{
		// モーションの更新
		m_pMotion->SetMotion(nMotionState, m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// 座標の設定
//=============================================================================
void CCharacter3d::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 角度の設定
//=============================================================================
void CCharacter3d::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 状態カウンターの設定
//=============================================================================
void CCharacter3d::SetStateCounter(int nStateCounter)
{
	m_nStateCounter = nStateCounter;
}