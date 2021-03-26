#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//=============================================================================
//
// パーティクルクラス処理  [particle.h]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CParticlre : public CScene2D
{
public:
	typedef enum
	{
		DEATH_PART_TYPE_ALL = 0, // 全方向
		DEATH_PART_TYPE_UP,      // 画面上
		DEATH_PART_TYPE_DOWN ,   // 画面下
		DEATH_PART_TYPE_LEFT ,   // 画面左
		DEATH_PART_TYPE_RIGHT,   // 画面右
		DEATH_PART_TYPE_MAX,
	}DEATH_PART_TYPE;

	CParticlre(PRIORITY Priority = PRIORITY_PARTICLE);	// コンストラクタ
	virtual ~CParticlre();								// デストラクタ

	static void CreateDeath(D3DXVECTOR3 pos, DEATH_PART_TYPE type);              // クラス生成
	static CParticlre* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move , int nLife); // クラス生成

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

private:

	void ManageMoveValue(void); // 移動量の管理

	D3DXVECTOR3 m_move; // 移動量
	D3DXCOLOR   m_col;  // カラー
	int m_nLife;        // 寿命
};
#endif