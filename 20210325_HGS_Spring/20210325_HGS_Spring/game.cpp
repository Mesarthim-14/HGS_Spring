//=======================================================================================
//
// ゲーム処理 [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player2d.h"
#include "player3d.h"
#include "joypad.h"
#include "time.h"
#include "sound.h"
#include "keyboard.h"
#include "mesh_3d.h"
#include "resource_manager.h"
#include "fade.h"
#include "map_manager.h"
#include "score.h"



#include "particle.h"
#include "time_limit.h"

//=======================================================================================
// static初期化
//=======================================================================================
CCamera *CGame::m_pCamera = nullptr;
CLight *CGame::m_pLight = nullptr;
CPlayer3d *CGame::m_pPlayer3d = nullptr;
CMapManager *CGame::m_pMapManager = nullptr;
CPlayer2d *CGame::m_pPlayer2d = nullptr;

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame(PRIORITY Priority) : CScene(Priority)
{
	m_bGameEnd = false;
	m_nTimeCounter = 0;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGame::~CGame()
{

}

//=======================================================================================
// クリエイト
//=======================================================================================
CGame* CGame::Create(void)
{
	// メモリ確保
	CGame* pGame = new CGame();

	// 初期化処理
	pGame->Init();

	return pGame;
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGame::Init()
{
	// nullcheck
	if (m_pPlayer2d == nullptr)
	{
		m_pPlayer2d = CPlayer2d::Create(ZeroVector3, D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	}

	// nullcheck
	if (m_pMapManager == nullptr)
	{
		// マップマネージャのインスタンス生成
		m_pMapManager = CMapManager::GetInstance();
	}

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//フォントの生成
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	//サウンドの再生
	GET_SOUND_PTR->Play(CSound::SOUND_LABEL_BGM_GAME);
	// スコアクラスの生成
	CScore::Create();

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit(void)
{
	//サウンドの停止
	GET_SOUND_PTR->Stop(CSound::SOUND_LABEL_BGM_GAME);

	// !nullcheck
	if (m_pPlayer2d != nullptr)
	{
		// 終了処理
		m_pPlayer2d->Uninit();
		m_pPlayer2d = nullptr;
	}

	// nullcheck
	if (m_pMapManager != nullptr)
	{
		// マップマネージャのインスタンス生成
		delete m_pMapManager;
		m_pMapManager = nullptr;
	}

	//オブジェクトの破棄
	Release();

	CScore::Release();
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update(void)
{
	// nullcheck
	if (m_pMapManager != nullptr)
	{
		// マップマネージャのインスタンス生成
		m_pMapManager->Update();
	}

	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// コントローラのstartを押したときか、エンターキーを押したとき
	if (CManager::GetJoypad()->GetJoyStickTrigger(CInputJoypad::JOY_BUTTON_START) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_RESULT);
	}


	/////////////////////////////////////////////////////////////////////////////////
	// 仮置き////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	if (pKey->GetTrigger(DIK_SPACE)) CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_ALL);
	if (pKey->GetTrigger(DIK_UP)) CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_UP);
	if (pKey->GetTrigger(DIK_DOWN)) CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_DOWN);
	if (pKey->GetTrigger(DIK_LEFT)) CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_LEFT);
	if (pKey->GetTrigger(DIK_RIGHT)) CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_RIGHT);
#endif
	/////////////////////////////////////////////////////////////////////////////////
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw(void)
{
}

//=======================================================================================
// ゲームの設定
//=======================================================================================
void CGame::SetGame(void)
{
	// ゲームのタイムカウンター
	m_nTimeCounter++;
}

//=======================================================================================
// カメラの情報
//=======================================================================================
CCamera * CGame::GetCamera(void)
{
	return m_pCamera;
}

//=======================================================================================
// ライトの情報
//=======================================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}
