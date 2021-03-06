//=============================================================================
//
// ナンバー2Dクラス [number.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "number_2d.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SCORE_ANIM_PATTERN	(8)			// アニメーションのパターン
#define NUMBER_NUM			(10)		// ナンバーの数

//=============================================================================
// インスタンス生成
//=============================================================================
CNumber2d * CNumber2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// インスタンス生成
	CNumber2d *pNumber = new CNumber2d;

	// !nullcheck
	if (pNumber != nullptr)
	{
		pNumber->SetSceneInfo(pos, size);

		// 初期化処理
		pNumber->Init();
	}

	return pNumber;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CNumber2d::CNumber2d(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CNumber2d::~CNumber2d()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNumber2d::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNumber2d::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CNumber2d::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CNumber2d::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ナンバーの加算
//=============================================================================
void CNumber2d::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber + (1.0f / NUMBER_NUM), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber + (1.0f / NUMBER_NUM), 1.0f);

	// 頂点バッファをアンロックする
	GetVtxBuff()->Unlock();
}