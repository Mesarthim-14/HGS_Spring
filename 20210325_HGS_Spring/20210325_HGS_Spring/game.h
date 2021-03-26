#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//
// ゲームの処理 [game.h]
// Author : Konishi Yuuto
//
//=============================================================================

//***************************************************************************************
// インクルードファイル
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// マクロ定義
//***************************************************************************************
#define MAX_PLAYER (1)			// プレイヤーの数

//***************************************************************************************
// 前方宣言
//***************************************************************************************
class CCamera;
class CLight;
class CMeshField;
class CPlayer2d;
class CPlayer3d;
class CMapManager;
class CEvaluation;
// 入力の種類の列挙型
enum INPUT_TYPE
{
	INPUT_TYPE_NONE = -1,		// 初期値
	INPUT_TYPE_UP,				// 上
	INPUT_TYPE_DOWN,			// 下
	INPUT_TYPE_RIGHT,			// 右
	INPUT_TYPE_LEFT,			// 左
	INPUT_TYPE_MAX				// 最大値
};

//***************************************************************************************
// ゲームクラス
//***************************************************************************************
class CGame : public CScene
{
public:
	CGame(PRIORITY Priority = PRIORITY_0);				// コンストラクタ
	~CGame();											// デストラクタ

	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理
	void SetGame(void);				// ゲームの設定

	static CGame* Create(void);									// ゲーム生成情報
	static CCamera *GetCamera(void);							// カメラのポインタ情報
	static CLight *GetLight(void);								// ライトのポインタ情報
	static CPlayer2d *GetPlayer2d(void) { return m_pPlayer2d; }		// プレイヤーのポインタ情報
	static CPlayer3d *GetPlayer3d(void) { return m_pPlayer3d; }	// プレイヤーのポインタ
	static CMapManager *GetMapManager(void) { return m_pMapManager; }	// マップマネージャのポインタ情報
	static CEvaluation *GetEvaluation(void) { return m_pEvaluation; }	// マップマネージャのポインタ情報

private:	
	static CCamera *m_pCamera;			// カメラのポインタ	
	static CLight *m_pLight;			// ライトのポインタ
	static CPlayer2d *m_pPlayer2d;				// プレイヤー2Dのポインタ
	static CPlayer3d *m_pPlayer3d;		// プレイヤー3Dのポインタ
	static CMapManager *m_pMapManager;			// マップマネージャーのポインタ
	static CEvaluation *m_pEvaluation;  // 評価UIクラス
	LPD3DXFONT m_pFont;					// デバック用フォント
	int m_nTimeCounter;					// ゲームのカウンター
	bool m_bGameEnd;					// ゲームのエンドフラグ
};
#endif