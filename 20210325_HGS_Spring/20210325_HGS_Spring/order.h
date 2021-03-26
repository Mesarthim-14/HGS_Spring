#ifndef _ORDER_H_
#define _ORDER_H_
//=============================================================================
//
// 命令テクスチャクラスヘッダー [order.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene2d.h"
#include "scroll_polygon.h"

//=============================================================================
// オーダークラス
//=============================================================================
class COrder : public CScene2D
{
public:
	COrder(PRIORITY Priority = PRIORITY_1);			// コンストラクタ
	~COrder();											// デストラクタ

	static COrder*Create(D3DXVECTOR3 pos, CScrollPolygon::SCROLL_INFO ScrollInfo);	// クリエイト

	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理

	void SetTexture(CScrollPolygon::SCROLL_INFO ScrollInfo);
private:
};
#endif