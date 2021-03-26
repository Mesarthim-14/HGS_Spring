//=======================================================================================
//
//  [tutorial.cpp]
// Author : �����D�I
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
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
//�ÓI�����o�ϐ��錾
//=======================================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture[1] = {};

//=======================================================================================
// �^�C�g���N���X�̃R���X�g���N�^
//=======================================================================================
CTutorial::CTutorial(PRIORITY Priority) : CScene(Priority)
{
	m_pScene = nullptr;
}

//=======================================================================================
// �^�C�g���N���X�̃f�X�g���N�^
//=======================================================================================
CTutorial::~CTutorial()
{

}

//=======================================================================================
// �^�C�g���N���X�̃N���G�C�g����
//=======================================================================================
CTutorial* CTutorial::Create(void)
{
	CTutorial* pTutorial = new CTutorial();

	// ����������
	pTutorial->Init();

	return pTutorial;
}


//=======================================================================================
// �^�C�g���N���X�̏���������
//=======================================================================================
HRESULT CTutorial::Init(void)
{
	if (m_pScene == nullptr)
	{
		m_pScene = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

		// �e�N�X�`�����蓖��
		CTexture *pTexture = GET_TEXTURE_PTR;
		m_pScene->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TUTOTIRAL));
	}
	
	// �T�E���h�̃|�C���^
	CSound *pSound = GET_SOUND_PTR;
	//pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=======================================================================================
// �^�C�g���N���X�̏I������
//=======================================================================================
void CTutorial::Uninit(void)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
	}


	//�I�u�W�F�N�g�̔j��
	Release();
}

//=======================================================================================
// �^�C�g���N���X�̍X�V����
//=======================================================================================
void CTutorial::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// �R���g���[����start���������Ƃ�
	if (CManager::GetJoypad()->GetJoyStickTrigger(CInputJoypad::JOY_BUTTON_START) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

	//�G���^�[�L�[���������Ƃ�
	if (pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

}

//=======================================================================================
// �^�C�g���N���X�̕`�揈��
//=======================================================================================
void CTutorial::Draw(void)
{

}
