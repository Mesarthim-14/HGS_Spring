//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
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
// �}�N����`
//=============================================================================
#define ROTATION_NUM		(0.1f)		// ��]�̑���

//=============================================================================
//���U���g�N���X�̃R���X�g���N�^
//=============================================================================
CTitle::CTitle(PRIORITY Priority) : CScene(Priority)
{
	//�����o�ϐ��̃N���A
	m_pScene2D = nullptr;
	m_pPress = nullptr;
	m_pTitleName = nullptr;
}

//=============================================================================
//���U���g�N���X�̃f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
//���U���g�N���X�̃N���G�C�g����
//=============================================================================
CTitle * CTitle::Create(void)
{
	//���U���g�N���X�̃|�C���^�ϐ�
	CTitle *pTitle = new CTitle;

	//���������m�ۂł��Ă�����
	if (pTitle != nullptr)
	{
		//�����������Ăяo��
		pTitle->Init();
	}

	return pTitle;
}

//=============================================================================
//���U���g�N���X�̏���������
//=============================================================================
HRESULT CTitle::Init()
{
	if (m_pScene2D == nullptr)
	{
		//2D�I�u�W�F�N�g�̐���
		m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

		if (m_pScene2D != nullptr)
		{
			m_pScene2D->BindTexture(nullptr);
		}
	}

	//�T�E���h�̍Đ�
	GET_SOUND_PTR->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=============================================================================
//���U���g�N���X�̏I������
//=============================================================================
void CTitle::Uninit(void)
{
	//�T�E���h�̒�~
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

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
//���U���g�N���X�̍X�V����
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);

		//�T�E���h�̍Đ�
		GET_SOUND_PTR->Play(CSound::SOUND_LABEL_SE_DECISION);
	}

	if (m_pPress != nullptr)
	{
	//	m_pPress->SetRotation(ROTATION_NUM);
	}

}

//=============================================================================
//���U���g�N���X�̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{
}
