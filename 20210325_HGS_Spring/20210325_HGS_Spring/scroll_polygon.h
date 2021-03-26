#ifndef _SCROLL_POLYGON_H_
#define _SCROLL_POLYGON_H_
//=======================================================================================
// 
// スクロールポリゴンクラス処理 [scroll_polygon.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "scene2d.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define SCROLL_FRAME	(30)		// 移動するフレーム数

//=======================================================================================
// スクロールポリゴンクラス定義
//=======================================================================================
class CScrollPolygon: public CScene2D
{
public:
	// 方向の種類の列挙型
	enum DIRECTION_TYPE
	{
		DIRECTION_TYPE_NONE = -1,	// 初期値
		DIRECTION_TYPE_UP,			// 上
		DIRECTION_TYPE_DOWN,		// 下
		DIRECTION_TYPE_RIGHT,		// 右
		DIRECTION_TYPE_LEFT,		// 左
		DIRECTION_TYPE_MAX			// 最大値
	};

	// スクロール情報の構造体
	struct SCROLL_INFO
	{

		DIRECTION_TYPE Direcsion;
		bool bFlag;
	};

	CScrollPolygon(PRIORITY Priority = PRIORITY_0);	// コンストラクタ
	~CScrollPolygon();								// デストラクタ

	static CScrollPolygon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, SCROLL_INFO ScrollInfo);			// インスタンス生成
	HRESULT Init(void);						// 初期化処理
	void Update(void);						// 更新処理

	// Set関数
	void SetSecondMove(bool bSecondMove, D3DXVECTOR3 move);

	// Get関数
	bool GetEnd(void)				{ return m_bEnd ; }	// 終了フラグ
	SCROLL_INFO GetScrollInfo(void) { return m_ScrollInfo; }
	bool GetStop(void)				{ return m_bStop; }
private:
	int m_nCounter;						// カウンター
	SCROLL_INFO m_ScrollInfo;			// スクロール情報
	D3DXVECTOR3 m_move;					// 移動量
	bool m_bSecondMove;					// 二度目の移動
	bool m_bEnd;						// 終了フラグ
	bool m_bStop;						// 止まったフラグ
};

#endif