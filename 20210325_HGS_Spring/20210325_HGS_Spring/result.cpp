//=============================================================================
//
// ���U���g�N���X���� [result.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"
#include "ranking.h"
#include "sound.h"
#include "score.h"
#include "result_score.h"
#include "perfect.h"
#include "great.h"
#include "nice.h"

//=============================================================================
//���U���g�N���X�̃R���X�g���N�^
//=============================================================================
CResult::CResult(PRIORITY Priority) : CScene(Priority)
{
	//�����o�ϐ��̃N���A
	m_pScene2D = nullptr;
}

//=============================================================================
//���U���g�N���X�̃f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
//���U���g�N���X�̃N���G�C�g����
//=============================================================================
CResult * CResult::Create(void)
{
	//���U���g�N���X�̃|�C���^�ϐ�
	CResult *pResult = new CResult;

	//���������m�ۂł��Ă�����
	if (pResult != nullptr)
	{
		//�����������Ăяo��
		pResult->Init();
	}

	return pResult;
}

//=============================================================================
//���U���g�N���X�̏���������
//=============================================================================
HRESULT CResult::Init(void)
{
	if (m_pScene2D == nullptr)
	{
		//2D�I�u�W�F�N�g�̐���
		m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

		if (m_pScene2D != nullptr)
		{
			m_pScene2D->BindTexture(nullptr);
		}
	}

	// �����L���O�̐���
	CRanking::Create();

	//���U���g�X�R�A�̐���
	CResultScore::Create();

	//�p�[�t�F�N�g�񐔂̐���
	CPerfect::Create();

	//�O���[�g�񐔂̐���
	CGreat::Create();

	//�i�C�X�񐔂̐���
	CNice::Create();

	//�T�E���h�̍Đ�
	GET_SOUND_PTR->Play(CSound::SOUND_LABEL_BGM_RESULT);

	return E_NOTIMPL;
}

//=============================================================================
//���U���g�N���X�̏I������
//=============================================================================
void CResult::Uninit(void)
{
	//�T�E���h�̒�~
	GET_SOUND_PTR->Stop(CSound::SOUND_LABEL_BGM_RESULT);

	if (m_pScene2D != nullptr)
	{
		m_pScene2D->Uninit();
		m_pScene2D = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();

	CScore::Release();
}

//=============================================================================
//���U���g�N���X�̍X�V����
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (CManager::GetJoypad()->GetJoyStickTrigger(CInputJoypad::JOY_BUTTON_START) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE);

		//�T�E���h�̍Đ�
		GET_SOUND_PTR->Play(CSound::SOUND_LABEL_SE_DECISION);
	}
}

//=============================================================================
//���U���g�N���X�̕`�揈��
//=============================================================================
void CResult::Draw(void)
{
}
