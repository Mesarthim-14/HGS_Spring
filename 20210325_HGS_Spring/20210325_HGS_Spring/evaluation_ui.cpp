//=============================================================================
//
// 評価UIクラス処理  [evaluation_ui.cpp]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "evaluation_ui.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POS  D3DXVECTOR3(200.0f, 200.0f, 0.0f) // 座標
#define SIZE D3DXVECTOR3(120.0f,40.0f,0.0f) // サイズ*画像サイズに合わせる
#define ROT D3DXToRadian(170)
#define MINUS_ALPHA 0.02f

//=============================================================================
// クリエイト
//=============================================================================
CEvaluation * CEvaluation::Create(void)
{
	// 初期化処理
	CEvaluation *pParticlre = new CEvaluation;

	// !nullcheck
	if (pParticlre != nullptr)
	{
		// 座標
		pParticlre->SetSceneInfo(POS, SIZE);


		// 初期化処理
		pParticlre->Init();
	}

	return pParticlre;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CEvaluation::CEvaluation(PRIORITY Priority) :CScene2D(Priority)
{
	m_fAlpha = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEvaluation::~CEvaluation()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEvaluation::Init(void)
{
	// 初期化処理
	CScene2D::Init();
	m_fAlpha = 0.0f;

	D3DXCOLOR col = GetColor();
	col.a = m_fAlpha;
	SetCol(col);

	SetRotation(ROT);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEvaluation::Uninit(void)
{
	// 終了処理
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEvaluation::Update(void)
{

	if (m_fAlpha > 0)
	{
		m_fAlpha -= MINUS_ALPHA;
		D3DXCOLOR col = GetColor();
		col.a = m_fAlpha;
		SetCol(col);
	}
	

	// 親クラスの更新処理
	CScene2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CEvaluation::Draw(void)
{
	// 描画処理
	CScene2D::Draw();
}

//=============================================================================
// 評価のセット
//=============================================================================
void CEvaluation::SetEvaluation(EVALUATION_TYPE type)
{
	// アルファ値のセット
	m_fAlpha = 1.5f;


	// テクスチャの切り替え
	CTexture *pTexture = GET_TEXTURE_PTR;

	switch (type)
	{
	case EVALUATION_TYPE_NICE:
		// ナイス
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NICE));
		break;
	case EVALUATION_TYPE_GREAT:
		// グレート
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_GREAT));
		break;
	case EVALUATION_TYPE_PARFECT:
		// パーフェクト
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARFECT));
		break;
	default:
		break;
	}

}
