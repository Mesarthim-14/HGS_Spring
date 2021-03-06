//=============================================================================
//
// キャラクター2Dクラス [character2d.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character2d.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "game.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GRAVITY_POWAR			(0.7f)						// 重力の強さ
#define GROUND_RIMIT			(0.0f)						// 地面の制限

//=============================================================================
// コンストラクタ
//=============================================================================
CCharacter2d::CCharacter2d(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CCharacter2d::~CCharacter2d()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCharacter2d::Init(void)
{
	// 初期化処理
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCharacter2d::Uninit(void)
{
	// 終了処理
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCharacter2d::Update(void)
{
	// 更新処理
	CScene2D::Update();

	// 移動量加算
	GetPos() += GetMove();

	// 頂点座標の更新
	UpdateVertex();
}

//=============================================================================
// 描画処理
//=============================================================================
void CCharacter2d::Draw(void)
{
	// 描画処理
	CScene2D::Draw();
}