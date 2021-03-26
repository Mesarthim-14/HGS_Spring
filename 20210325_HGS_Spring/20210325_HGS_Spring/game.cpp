//=======================================================================================
//
// �Q�[������ [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
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
// static������
//=======================================================================================
CCamera *CGame::m_pCamera = nullptr;
CLight *CGame::m_pLight = nullptr;
CPlayer3d *CGame::m_pPlayer3d = nullptr;
CMapManager *CGame::m_pMapManager = nullptr;
CPlayer2d *CGame::m_pPlayer2d = nullptr;

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame(PRIORITY Priority) : CScene(Priority)
{
	m_bGameEnd = false;
	m_nTimeCounter = 0;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{

}

//=======================================================================================
// �N���G�C�g
//=======================================================================================
CGame* CGame::Create(void)
{
	// �������m��
	CGame* pGame = new CGame();

	// ����������
	pGame->Init();

	return pGame;
}

//=======================================================================================
// ����������
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
		// �}�b�v�}�l�[�W���̃C���X�^���X����
		m_pMapManager = CMapManager::GetInstance();
	}

	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�t�H���g�̐���
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	//�T�E���h�̍Đ�
	GET_SOUND_PTR->Play(CSound::SOUND_LABEL_BGM_GAME);
	// �X�R�A�N���X�̐���
	CScore::Create();

	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CGame::Uninit(void)
{
	//�T�E���h�̒�~
	GET_SOUND_PTR->Stop(CSound::SOUND_LABEL_BGM_GAME);

	// !nullcheck
	if (m_pPlayer2d != nullptr)
	{
		// �I������
		m_pPlayer2d->Uninit();
		m_pPlayer2d = nullptr;
	}

	// nullcheck
	if (m_pMapManager != nullptr)
	{
		// �}�b�v�}�l�[�W���̃C���X�^���X����
		delete m_pMapManager;
		m_pMapManager = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();

	CScore::Release();
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update(void)
{
	// nullcheck
	if (m_pMapManager != nullptr)
	{
		// �}�b�v�}�l�[�W���̃C���X�^���X����
		m_pMapManager->Update();
	}

	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (CManager::GetJoypad()->GetJoyStickTrigger(CInputJoypad::JOY_BUTTON_START) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_RESULT);
	}


	/////////////////////////////////////////////////////////////////////////////////
	// ���u��////////////////////////////////////////////////////////////////////////
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
// �`�揈��
//=======================================================================================
void CGame::Draw(void)
{
}

//=======================================================================================
// �Q�[���̐ݒ�
//=======================================================================================
void CGame::SetGame(void)
{
	// �Q�[���̃^�C���J�E���^�[
	m_nTimeCounter++;
}

//=======================================================================================
// �J�����̏��
//=======================================================================================
CCamera * CGame::GetCamera(void)
{
	return m_pCamera;
}

//=======================================================================================
// ���C�g�̏��
//=======================================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}
