#ifndef _MAP_H_
#define _MAP_H_
//=============================================================================
//
// マップクラスヘッダー [map.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "player2d.h"
#include "scroll_polygon.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SCROLL_POLYGON_APPEAR_POS_X	()
#define SCROLL_POLYGON_APPEAR_POS	()

//=============================================================================
// 前方宣言
//=============================================================================
class CScrollPolygon;


//=============================================================================
// エフェクト生成
//=============================================================================
class CMapManager
{
public:
	~CMapManager();								// デストラクタ

	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void CreateMap(INPUT_TYPE InputType);		// マップの生成
	D3DXVECTOR3 SetPos(INPUT_TYPE InputType);	// 移動量の設定
	D3DXVECTOR3 SetMove(INPUT_TYPE InputType);	// 移動量の設定
	CScrollPolygon::SCROLL_INFO SetScrollInfo(void);		// スクロール情報
	static CMapManager *GetInstance(void);				// インスタンス取得関数
	
private:
	CMapManager();								// コンストラクタ
	static CMapManager *m_pMap;					// 自身のクラスのポインタ
	std::vector<CScrollPolygon*> m_pScroll;		// アイテムボックスのポインタ
};
#endif
