//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ROTATION_NUM		(0.1f)		// 回転の速さ

//=============================================================================
//リザルトクラスのコンストラクタ
//=============================================================================
CTitle::CTitle(PRIORITY Priority) : CScene(Priority)
{
	//メンバ変数のクリア
	m_pScene2D = nullptr;
	m_pPress = nullptr;
	m_pTitleName = nullptr;
}

//=============================================================================
//リザルトクラスのデストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
//リザルトクラスのクリエイト処理
//=============================================================================
CTitle * CTitle::Create(void)
{
	//リザルトクラスのポインタ変数
	CTitle *pTitle = new CTitle;

	//メモリが確保できていたら
	if (pTitle != nullptr)
	{
		//初期化処理呼び出し
		pTitle->Init();
	}

	return pTitle;
}

//=============================================================================
//リザルトクラスの初期化処理
//=============================================================================
HRESULT CTitle::Init()
{
	if (m_pScene2D == nullptr)
	{
		//2Dオブジェクトの生成
		m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

		if (m_pScene2D != nullptr)
		{
			m_pScene2D->BindTexture(nullptr);
		}
	}

	//サウンドの再生
	GET_SOUND_PTR->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=============================================================================
//リザルトクラスの終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	//サウンドの停止
	GET_SOUND_PTR->Stop(CSound::SOUND_LABEL_BGM_TITLE);

	if (m_pScene2D != nullptr)
	{
		m_pScene2D->Uninit();
		m_pScene2D = nullptr;
	}

	if (m_pTitleName != nullptr)
	{
		m_pTitleName->Uninit();
		m_pTitleName = nullptr;
	}
	
	if (m_pPress != nullptr)
	{
		m_pPress->Uninit();
		m_pPress = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
//リザルトクラスの更新処理
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// コントローラのstartを押したときか、エンターキーを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);

		//サウンドの再生
		GET_SOUND_PTR->Play(CSound::SOUND_LABEL_SE_DECISION);
	}

	if (m_pPress != nullptr)
	{
	//	m_pPress->SetRotation(ROTATION_NUM);
	}

}

//=============================================================================
//リザルトクラスの描画処理
//=============================================================================
void CTitle::Draw(void)
{
}
