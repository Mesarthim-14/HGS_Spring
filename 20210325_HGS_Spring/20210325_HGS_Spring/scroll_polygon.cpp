//=======================================================================================
//
// スクロールポリゴンクラス [scroll_polygon.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "scroll_polygon.h"
#include "keyboard.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define SCROLL_POLYGON_SIZE	(D3DXVECTOR3(SCREEN_WIDTH /2 -50.0f, SCREEN_HEIGHT /2 -50.0f, 0.0f))	// ポリゴンのサイズ

//=======================================================================================
// コンストラクタ
//=======================================================================================
CScrollPolygon::CScrollPolygon(PRIORITY Priority) : CScene2D(Priority)
{
	m_ScrollInfo = { DIRECTION_TYPE_NONE , false };
	m_nCounter = 0;
	m_DefaultMove = ZeroVector3;			// 元の移動量
	m_move = ZeroVector3;					// 移動量
	m_bSecondMove = false;					// 二度目の移動
	m_bEnd = false;
	m_bStop = false;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CScrollPolygon::~CScrollPolygon()
{

}

//=======================================================================================
// Sceneクラスの生成
//=======================================================================================
CScrollPolygon* CScrollPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, SCROLL_INFO ScrollInfo)
{
	// オブジェクトを生成
	CScrollPolygon* pScrollPolygon = new CScrollPolygon;

	// !nullcheck
	if (pScrollPolygon != nullptr)
	{
		// 情報設定
		pScrollPolygon->SetSceneInfo(pos, SCROLL_POLYGON_SIZE);

		// 移動量
		pScrollPolygon->m_move = move;
		pScrollPolygon->m_DefaultMove = move;

		// 構造体情報代入
		pScrollPolygon->m_ScrollInfo = ScrollInfo;

		// 初期化処理
		pScrollPolygon->Init();
	}

	return pScrollPolygon;
}

//=======================================================================================
// ポリゴンの初期化
//=======================================================================================
HRESULT CScrollPolygon::Init(void)
{
	// 初期化処理
	CScene2D::Init();

	// テクスチャのポインタ取得
	CTexture *pTexture = GET_TEXTURE_PTR;

	// テクスチャの設定
	BindTexture(nullptr);

	return S_OK;
}

//=======================================================================================
// ポリゴンの更新処理
//=======================================================================================
void CScrollPolygon::Update(void)
{
	m_nCounter++;


	// 二度目の移動
	if (m_bSecondMove == true)
	{
		GetPos() += m_DefaultMove;

		// スクロールするカウンタ
		if (m_nCounter >= SCROLL_FRAME)
		{
			// 移動を止める
			m_bEnd = true;
		}
	}
	else
	{
		// 座標
		GetPos() += m_move;

		// スクロールするカウンタ
		if (m_nCounter >= SCROLL_FRAME)
		{
			// 移動を止める
			m_move = ZeroVector3;
			m_bStop = true;
		}
	}

	// 頂点の移動
	UpdateVertex();
}

//=======================================================================================
// 
//=======================================================================================
void CScrollPolygon::SetSecondMove(bool bSecondMove)
{
	m_bSecondMove = bSecondMove;
	m_nCounter = 0;
	m_move = ZeroVector3;
//	m_move = m_DefaultMove;
}