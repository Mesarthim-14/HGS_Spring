//=======================================================================================
//
//  [tutorial.cpp]
// Author : 佐藤颯紀
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "tutorial.h"
#include "scene2d.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "texture.h"

//=======================================================================================
//静的メンバ変数宣言
//=======================================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture[1] = {};

//=======================================================================================
// タイトルクラスのコンストラクタ
//=======================================================================================
CTutorial::CTutorial(PRIORITY Priority) : CScene(Priority)
{
	m_pScene = nullptr;
}

//=======================================================================================
// タイトルクラスのデストラクタ
//=======================================================================================
CTutorial::~CTutorial()
{

}

//=======================================================================================
// タイトルクラスのクリエイト処理
//=======================================================================================
CTutorial* CTutorial::Create(void)
{
	CTutorial* pTutorial = new CTutorial();

	// 初期化処理
	pTutorial->Init();

	return pTutorial;
}


//=======================================================================================
// タイトルクラスの初期化処理
//=======================================================================================
HRESULT CTutorial::Init(void)
{
	if (m_pScene == nullptr)
	{
		m_pScene = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

		// テクスチャ割り当て
		CTexture *pTexture = GET_TEXTURE_PTR;
		m_pScene->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TUTOTIRAL));
	}
	
	// サウンドのポインタ
	CSound *pSound = GET_SOUND_PTR;
	//pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=======================================================================================
// タイトルクラスの終了処理
//=======================================================================================
void CTutorial::Uninit(void)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
	}


	//オブジェクトの破棄
	Release();
}

//=======================================================================================
// タイトルクラスの更新処理
//=======================================================================================
void CTutorial::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// コントローラのstartを押したとき
	if (CManager::GetJoypad()->GetJoyStickTrigger(CInputJoypad::JOY_BUTTON_START) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

	//エンターキーを押したとき
	if (pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

}

//=======================================================================================
// タイトルクラスの描画処理
//=======================================================================================
void CTutorial::Draw(void)
{

}
