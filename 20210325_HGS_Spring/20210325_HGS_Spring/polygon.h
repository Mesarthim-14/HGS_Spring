#ifndef _POLYGON_H_
#define _POLYGON_H_
//=============================================================================
//
// ポリゴン生成クラス処理 [polygon.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
//ライフクラス
//=============================================================================
class CPolygon
{
public:
	CPolygon();			// コンストラクタ
	~CPolygon();		// デストラクタ

	static CPolygon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// インスタンス生成

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);				// 初期化処理
	void Uninit(void);															// 終了処理
	void Update(void);															// 更新処理
	void Draw(void);															// 描画処理
	void SetColor(const D3DXCOLOR color);										// 色の設定

	void SetVertexPos(D3DXVECTOR3 pos[NUM_VERTEX]);                           // 頂点座標の設定
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }  // テクスチャの割り当て
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9        m_pTexture;  // テクスチャへのポインタ
	D3DXVECTOR3 m_Size;					// ポリゴンのサイズ
	D3DXVECTOR3 m_pos;					// ライフの位置
};
#endif 