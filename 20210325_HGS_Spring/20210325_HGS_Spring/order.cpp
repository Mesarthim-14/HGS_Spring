//=======================================================================================
//
// 命令Uiクラス [order.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "order.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define ORDER_UI_SIZE (D3DXVECTOR3(100.0f, 100.0f, 0.0f))

//=======================================================================================
// コンストラクタ
//=======================================================================================
COrder::COrder(PRIORITY Priority) : CScene2D(Priority)
{

}

//=======================================================================================
// デストラクタ
//=======================================================================================
COrder::~COrder()
{

}

//=======================================================================================
// Sceneクラスの生成
//=======================================================================================
COrder* COrder::Create(const D3DXVECTOR3 pos, CScrollPolygon::SCROLL_INFO ScrollInfo)
{
	// オブジェクトを生成
	COrder* pScene = new COrder;

	// !nullcheck
	if (pScene != nullptr)
	{
		pScene->SetSceneInfo(pos, ORDER_UI_SIZE);
		pScene->SetTexture(ScrollInfo);
		// 初期化処理
		pScene->Init();
	}

	return pScene;
}

//=======================================================================================
// ポリゴンの初期化
//=======================================================================================
HRESULT COrder::Init(void)
{
	// 初期化処理
	CScene2D::Init();

	return S_OK;
}

//=======================================================================================
// ポリゴンの終了処理
//=======================================================================================
void COrder::Uninit(void)
{
	// 初期化処理
	CScene2D::Uninit();
}

//=======================================================================================
// ポリゴンの更新処理
//=======================================================================================
void COrder::Update(void)
{

}

//=======================================================================================
// ポリゴンの描画処理
//=======================================================================================
void COrder::Draw(void)
{
	// 初期化処理
	CScene2D::Draw();
}

//=======================================================================================
// テクスチャの設定
//=======================================================================================
void COrder::SetTexture(CScrollPolygon::SCROLL_INFO ScrollInfo)
{
	CTexture *pTexture = GET_TEXTURE_PTR;
	int nNum = rand() % 3;

	// テクスチャ種類分け
	switch (ScrollInfo.Direcsion)
	{
	case CScrollPolygon::DIRECTION_TYPE_UP:
		if (ScrollInfo.bFlag == true)
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_UP_E + nNum)));
		}
		else
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_NOT_UP_E + nNum)));
		}
		break;

	case CScrollPolygon::DIRECTION_TYPE_DOWN:
		if (ScrollInfo.bFlag == true)
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_DOWN_E + nNum)));
		}
		else
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_NOT_DOWN_E + nNum)));

		}
		break;

	case CScrollPolygon::DIRECTION_TYPE_RIGHT:
		if (ScrollInfo.bFlag == true)
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_RIGHT_E + nNum)));
		}
		else
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_NOT_RIGHT_E + nNum)));

		}
		break;

	case CScrollPolygon::DIRECTION_TYPE_LEFT:
		if (ScrollInfo.bFlag == true)
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_LEFT_E + nNum)));
		}
		else
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_NOT_LEFT_E + nNum)));

		}
		break;
	}
}