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
#include "order.h"
#include "game.h"
#include "player2d.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define SCROLL_POLYGON_SIZE	(D3DXVECTOR3(SCREEN_WIDTH /2 -50.0f, SCREEN_HEIGHT /2 -50.0f, 0.0f))	// ポリゴンのサイズ

//=======================================================================================
// コンストラクタ
//=======================================================================================
CScrollPolygon::CScrollPolygon(PRIORITY Priority) : CScene2D(Priority)
{
	m_pOrder = nullptr;
	m_ScrollInfo = { DIRECTION_TYPE_NONE , false };
	m_nCounter = 0;
	m_move = ZeroVector3;					// 移動量
	m_bSecondMove = false;					// 二度目の移動
	m_bEnd = false;
	m_bStop = false;
	m_nEndCounter = 0;
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
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_GAME_BG));

	// nullcheck
	if (m_pOrder == nullptr)
	{
		// 座標
		m_pOrder = COrder::Create(GetPos(), m_ScrollInfo);
	}

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CScrollPolygon::Uninit(void)
{
	// 終了処理
	CScene2D::Uninit();

	// !nullcheck
	if (m_pOrder != nullptr)
	{
		// オーダーの終了処理
		m_pOrder->Uninit();
		m_pOrder = nullptr;
	}
}

//=======================================================================================
// ポリゴンの更新処理
//=======================================================================================
void CScrollPolygon::Update(void)
{
	if (CGame::GetPlayer2d()->GetDeath() == true)
	{
		m_nEndCounter++;
	}

	if (m_nEndCounter <= 10)
	{
		m_nCounter++;

		// 座標
		GetPos() += m_move;

		// 頂点の移動
		UpdateVertex();

		// !nullcheck
		if (m_pOrder != nullptr)
		{
			D3DXVECTOR3 pos = GetPos();
			// 座標の更新
			m_pOrder->GetPos() = D3DXVECTOR3(pos.x, pos.y - 85.0f, 0.0f);
			m_pOrder->UpdateVertex();
		}

		// 二度目の移動
		if (m_bSecondMove == true)
		{
			// スクロールするカウンタ
			if (m_nCounter >= SCROLL_FRAME)
			{
				// 移動を止める
				m_bEnd = true;
			}
		}
		else
		{
			// スクロールするカウンタ
			if (m_nCounter >= SCROLL_FRAME)
			{
				// 移動を止める
				m_move = ZeroVector3;
				m_bStop = true;
			}
		}


	}
}


//=======================================================================================
// 
//=======================================================================================
void CScrollPolygon::SetSecondMove(bool bSecondMove, D3DXVECTOR3 move)
{
	m_bSecondMove = bSecondMove;
	m_nCounter = 0;
	m_move = move;
}