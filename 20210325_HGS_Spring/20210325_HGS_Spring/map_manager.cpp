//=============================================================================
//
// マップクラス [map.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "map_manager.h"
#include "manager.h"
#include "renderer.h"
#include "scroll_polygon.h"
#include "player2d.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SCROLL_SPEED_X		((SCREEN_WIDTH)/(float)SCROLL_FRAME)										// 移動量
#define SCROLL_SPEED_Y		((SCREEN_HEIGHT)/(float)SCROLL_FRAME)										// 移動量

#define SCROLL_POS_UP		(D3DXVECTOR3((SCREEN_WIDTH/2), -(SCREEN_HEIGHT/2), 0.0f))				// 座標
#define SCROLL_POS_DOWN		(D3DXVECTOR3((SCREEN_WIDTH/2), SCREEN_HEIGHT+(SCREEN_HEIGHT/2), 0.0f))	// 座標
#define SCROLL_POS_RIGHT	(D3DXVECTOR3(SCREEN_WIDTH+(SCREEN_WIDTH/2), (SCREEN_HEIGHT/2), 0.0f))	// 座標
#define SCROLL_POS_LEFT		(D3DXVECTOR3(-(SCREEN_WIDTH/2), (SCREEN_HEIGHT/2), 0.0f))				// 座標

#define SCROLL_MOVE_UP		(D3DXVECTOR3(0.0f, SCROLL_SPEED_Y, 0.0f))	// 移動量
#define SCROLL_MOVE_DOWN	(D3DXVECTOR3(0.0f, -SCROLL_SPEED_Y, 0.0f))	// 移動量
#define SCROLL_MOVE_RIGHT	(D3DXVECTOR3(-SCROLL_SPEED_X, 0.0f, 0.0f))	// 移動量
#define SCROLL_MOVE_LEFT	(D3DXVECTOR3(SCROLL_SPEED_X, 0.0f, 0.0f))	// 移動量

//=============================================================================
// static初期化宣言
//=============================================================================
CMapManager *CMapManager::m_pMap = nullptr;		// 自身のポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CMapManager::CMapManager()
{
	CreateMap(INPUT_TYPE_NONE);
}

//=============================================================================
// デストラクタ
//=============================================================================
CMapManager::~CMapManager()
{
}

//=============================================================================
// 終了処理
//=============================================================================
void CMapManager::Uninit(void)
{
	// メモリ確保
	for (unsigned nCount = 0; nCount < m_pScroll.size(); nCount++)
	{
		// !nullcheck
		if (m_pScroll[nCount] != nullptr)
		{
			// 終了処理
			m_pScroll[nCount]->Uninit();
			m_pScroll[nCount] = nullptr;
		}
	}
		// 配列のクリア
		m_pScroll.clear();
	

	// !nullcheck
	if (m_pMap != nullptr)
	{
		// ポインタの開放
		delete m_pMap;
		m_pMap = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CMapManager::Update(void)
{
	// サイズ分
	for (size_t nCount = 0; nCount < m_pScroll.size(); nCount++)
	{
		// 終了フラグがあれば
		if (m_pScroll.at(nCount)->GetEnd() == true)
		{
			// 終了処理
			m_pScroll.at(nCount)->Uninit();

			// 空にする
			m_pScroll.erase(m_pScroll.begin() + nCount);
		}
	}
}

//=============================================================================
// アイテムボックスの生成
//=============================================================================
void CMapManager::CreateMap(INPUT_TYPE InputType)
{
	// 座標設定
	D3DXVECTOR3 pos = ZeroVector3;

	// 移動量の設定
	D3DXVECTOR3 move = ZeroVector3;

	// サイズがあれば
	if (m_pScroll.size() != 0)
	{
		// 座標設定
		pos = SetPos(InputType);

		// 移動量の設定
		move = SetMove(InputType);

		// 二度目の移動を設定
		m_pScroll.at(0)->SetSecondMove(true, move);

	}
	else
	{
		INPUT_TYPE ElseInputType = (INPUT_TYPE)(rand() % (int)INPUT_TYPE_MAX);
	
		// 座標設定
		pos = SetPos(ElseInputType);

		// 移動量の設定
		move = SetMove(ElseInputType);
	}

	// スクロールポリゴン情報
	CScrollPolygon::SCROLL_INFO DirectionType = SetScrollInfo();

	CScrollPolygon *pScrollPolygon = CScrollPolygon::Create(pos, move, DirectionType);
	
	// ゲームのプレイヤー
	CPlayer2d *pPlayer = CGame::GetPlayer2d();

	// スクロールポリゴンの情報をプレイヤーに持たせる
	pPlayer->SetScrollPolygon(pScrollPolygon);

	// インスタンスを確保
	m_pScroll.push_back(pScrollPolygon);
}

//=============================================================================
// 初期座標設定
//=============================================================================
D3DXVECTOR3 CMapManager::SetPos(INPUT_TYPE InputType)
{
	// タイプ分け
	switch (InputType)
	{
		// 上入力
	case INPUT_TYPE_UP:
		return SCROLL_POS_UP;
		break;

		// 下入力
	case INPUT_TYPE_DOWN:
		return SCROLL_POS_DOWN;
		break;

		// 右入力
	case INPUT_TYPE_RIGHT:
		return SCROLL_POS_RIGHT;
		break;

		// 左入力
	case INPUT_TYPE_LEFT:
		return SCROLL_POS_LEFT;
		break;

	default:
		break;
	}

	return ZeroVector3;
}

//=============================================================================
// 移動量の設定
//=============================================================================
D3DXVECTOR3 CMapManager::SetMove(INPUT_TYPE InputType)
{
	// タイプ分け
	switch (InputType)
	{
		// 上入力
	case INPUT_TYPE_UP:
		return SCROLL_MOVE_UP;
		break;

		// 下入力
	case INPUT_TYPE_DOWN:
		return SCROLL_MOVE_DOWN;
		break;

		// 右入力
	case INPUT_TYPE_RIGHT:
		return SCROLL_MOVE_RIGHT;
		break;

		// 左入力
	case INPUT_TYPE_LEFT:
		return SCROLL_MOVE_LEFT;
		break;

	default:
		break;
	}

	return ZeroVector3;
}

//=============================================================================
// スクロールポリゴンの情報を設定
//=============================================================================
CScrollPolygon::SCROLL_INFO CMapManager::SetScrollInfo(void)
{
	// タイプを乱数で設定
	CScrollPolygon::DIRECTION_TYPE DirectionType =
		(CScrollPolygon::DIRECTION_TYPE)(rand() % (int)CScrollPolygon::DIRECTION_TYPE_MAX);

	// bool型の乱数設定
	int nFlag = rand() % 2;
	bool bFlag = false;

	switch (nFlag)
	{
	case 0:
		bFlag = false;
		break;
	case 1:
		bFlag = true;
		break;
	}

	return { DirectionType, bFlag };
}

//=============================================================================
// インスタンス取得関数
//=============================================================================
CMapManager * CMapManager::GetInstance(void)
{
	// nullcheck
	if (m_pMap == nullptr)
	{
		// メモリ確保
		m_pMap = new CMapManager;
	}

	return m_pMap;
}