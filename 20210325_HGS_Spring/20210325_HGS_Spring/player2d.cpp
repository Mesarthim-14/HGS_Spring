//=============================================================================
//
// �v���C���[2d�N���X [player2d.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player2d.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "sound.h"
#include "collision.h"
#include "texture.h"
#include "resource_manager.h"
#include "map_manager.h"
#include "scroll_polygon.h"
#include "particle.h"
#include "time_limit.h"
#include "score.h"
#include "gauge.h"
#include "fade.h"
#include "number_2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED					(5.0f)				// �v���C���[�̈ړ���
#define STICK_SENSITIVITY				(50.0f)				// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED				(0.1f)				// �L�����N�^�[�̉�]���鑬�x
#define PLAYER_RADIUS					(50.0f)				// ���a�̑傫��

//=============================================================================
// �N���G�C�g
//=============================================================================
CPlayer2d * CPlayer2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CPlayer2d *pPlayer = new CPlayer2d;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ���W
		pPlayer->SetSceneInfo(pos, size);

		// ����������
		pPlayer->Init();

		// �e�N�X�`���̐ݒ�
		CTexture *pTexture = GET_TEXTURE_PTR;
		pPlayer->BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_PLAYER_NEUTRAL));
		D3DXVECTOR2 TexInfo = pTexture->GetSparateTexInfo(CTexture::SEPARATE_TEX_PLAYER_NEUTRAL);
		bool bLoop = pTexture->GetSparateTexLoop(CTexture::SEPARATE_TEX_PLAYER_NEUTRAL);

		// �A�j���[�V�����̐ݒ�
		pPlayer->InitAnimation((int)TexInfo.x, (int)TexInfo.y, bLoop);

	}

	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer2d::CPlayer2d(PRIORITY Priority) : CCharacter2d(Priority)
{
	m_pScrollPolygon.clear();
	m_pTimeLimit = NULL;
	m_bDeath = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer2d::~CPlayer2d()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer2d::Init(void)
{
	CCharacter2d::Init();												// ���W�@�p�x
	SetRadius(PLAYER_RADIUS);											// ���a�̐ݒ�
	SetSpeed(PLAYER_SPEED);												// ���x�̐ݒ�
	m_pTimeLimit = CTimeLimit::Create(); // �������Ԃ̐���
	m_bDeath = false;// ���S�t���O

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer2d::Uninit(void)
{
	if (m_pTimeLimit != NULL)
	{
		m_pTimeLimit->Uninit();
		m_pTimeLimit = NULL;
	}

	// �I������
	CCharacter2d::Uninit();

	// �I������
	if (m_pTimeLimit != nullptr)
	{
		m_pTimeLimit->Uninit();
		m_pTimeLimit = nullptr;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer2d::Update(void)
{
	// ���W���
	D3DXVECTOR3 pos = GetPos();	// ���݂̍��W�擾
	SetOldPos(pos);				// �Â����W�ۑ�

	// �v���C���[�̏��
	UpdateState();

	// �v���C���[�̐���
	PlayerControl();

	// �e�N���X�̍X�V����
	CCharacter2d::Update();

	// ���S�`�F�b�N
	if (m_bDeath)
	{
		// ���U���g�ɑJ�ڏ���
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_RESULT);

		//// �R���g���[���[�U��
		//CManager::GetJoypad()->SetVibration(0);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer2d::Draw(void)
{
	// �`�揈��
	CCharacter2d::Draw();
}

//=============================================================================
// �v���C���[�̏��
//=============================================================================
void CPlayer2d::UpdateState(void)
{
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
void CPlayer2d::PlayerControl()
{
	// �T�C�Y���󂶂�Ȃ�������
	if (m_pScrollPolygon.size() != 0)
	{
		if (m_pScrollPolygon.at(0)->GetStop() == true)
		{
			// �������ԃN���X�̍X�V
			if (!m_pTimeLimit->Update())
			{// �������Ԃ��߂����Ƃ�
				if (m_bDeath == false)
				{// ���S�t���O��false�̎�

				 // �t���O��true��
					m_bDeath = true;
					// �p�[�e�B�N������
					CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_ALL);
					// �R���g���[���[�U��
					CManager::GetJoypad()->SetVibration(0);
				}
			}

			// ���͂̎��
			INPUT_TYPE InputType = INPUT_TYPE_NONE;

			// ���͏���
			InputType = InputDirection();

			// �����̓���
			if (InputType != INPUT_TYPE_NONE)
			{
				// ���͔���
				if (InputJudg(InputType) == true)
				{
					// �X�R�A���Z
					CScore::GetScorePointa()->AddScore(m_pTimeLimit->CheckEvaluation());
					
					// �e�N�X�`���̕ύX
					ChangeTexture(InputType);
				}
				else
				{// �Փ˂̔���
					if (m_bDeath == false)
					{// ���S�t���O��false�̎�
						
						// �t���O��true��
						m_bDeath = true;

						// �p�[�e�B�N������
						if      (InputType == INPUT_TYPE_UP)    CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_UP);
						else if (InputType == INPUT_TYPE_DOWN)  CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_DOWN);
						else if (InputType == INPUT_TYPE_LEFT)  CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_LEFT);
						else if (InputType == INPUT_TYPE_RIGHT) CParticlre::CreateDeath(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CParticlre::DEATH_PART_TYPE_RIGHT);
						// �R���g���[���[�U��
						CManager::GetJoypad()->SetVibration(0);
					}
				}

				// �X�N���[���|���S�����̔j��
				m_pScrollPolygon.pop_back();

				CMapManager *pMapManager = CGame::GetMapManager();

				// ���̃}�b�v����
				pMapManager->CreateMap(InputType);

				// �Q�[�W����
				m_pTimeLimit->GetGauge()->Uninit();
				// �������ԏ���
				m_pTimeLimit->Uninit();
				m_pTimeLimit = NULL;

				m_pTimeLimit = CTimeLimit::Create(); // �������Ԃ̐���
			}
		}
	}
}

//=============================================================================
// ���͏���
//=============================================================================
INPUT_TYPE CPlayer2d::InputDirection(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// �L�[�{�[�h�X�V
	CInputJoypad *pJoyPad = CManager::GetJoypad();  // �W���C�p�b�h�̎擾

	if (pKeyboard->GetTrigger(DIK_W) || pJoyPad->GetPushCross(CROSS_KEY_UP) || pJoyPad->GetStick().lY <= -600)
	{
		return INPUT_TYPE_UP;
	}
	else if (pKeyboard->GetTrigger(DIK_A) || pJoyPad->GetPushCross(CROSS_KEY_LEFT) || pJoyPad->GetStick().lX <= -600)
	{
		return INPUT_TYPE_LEFT;
	}
	else if (pKeyboard->GetTrigger(DIK_S) || pJoyPad->GetPushCross(CROSS_KEY_DOWN) || pJoyPad->GetStick().lY >= 600)
	{
		return INPUT_TYPE_DOWN;
	}
	else if (pKeyboard->GetTrigger(DIK_D) || pJoyPad->GetPushCross(CROSS_KEY_RIGHT) || pJoyPad->GetStick().lX >= 600)
	{
		return INPUT_TYPE_RIGHT;
	}

	return INPUT_TYPE_NONE;
}

//=============================================================================
// �v���C���[�ړ�����
//=============================================================================
void CPlayer2d::Move(void)
{
	// ���[�J���ϐ�
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// �L�[�{�[�h�X�V
	DIJOYSTATE js = CManager::GetJoypad()->GetStick();						// �W���C�p�b�h�̎擾
	float fSpeed = GetSpeed();												// �X�s�[�h

	//���͂����݂���
	if ((js.lX != 0.0f || js.lY != 0.0f))
	{
		float fAngle = atan2f((float)js.lX, (float)js.lY);	// �R���g���[���̊p�x

		// �ړ��ʐݒ�
		GetPos().x += sinf(fAngle)* fSpeed;
		GetPos().y += cosf(fAngle)* fSpeed;
	}
}

//=============================================================================
// ���͂̔���
//=============================================================================
bool CPlayer2d::InputJudg(INPUT_TYPE InputType)
{
	CScrollPolygon::SCROLL_INFO ScrollPolygon = m_pScrollPolygon[0]->GetScrollInfo();

	// ����
	switch (InputType)
	{
	case INPUT_TYPE_UP:
		if (ScrollPolygon.Direcsion == CScrollPolygon::DIRECTION_TYPE_UP && ScrollPolygon.bFlag == true ||
			ScrollPolygon.Direcsion != CScrollPolygon::DIRECTION_TYPE_UP && ScrollPolygon.bFlag == false)
		{
			return true;
		}

		break;

	case INPUT_TYPE_DOWN:
		if (ScrollPolygon.Direcsion == CScrollPolygon::DIRECTION_TYPE_DOWN && ScrollPolygon.bFlag == true ||
			ScrollPolygon.Direcsion != CScrollPolygon::DIRECTION_TYPE_DOWN && ScrollPolygon.bFlag == false)
		{
			return true;
		}

		break;
	case INPUT_TYPE_RIGHT:
		if (ScrollPolygon.Direcsion == CScrollPolygon::DIRECTION_TYPE_RIGHT && ScrollPolygon.bFlag == true ||
			ScrollPolygon.Direcsion != CScrollPolygon::DIRECTION_TYPE_RIGHT && ScrollPolygon.bFlag == false)
		{
			return true;
		}

		break;
	case INPUT_TYPE_LEFT:
		if (ScrollPolygon.Direcsion == CScrollPolygon::DIRECTION_TYPE_LEFT && ScrollPolygon.bFlag == true ||
			ScrollPolygon.Direcsion != CScrollPolygon::DIRECTION_TYPE_LEFT && ScrollPolygon.bFlag == false)
		{
			return true;
		}

		break;
	}

	return false;
}

//=============================================================================
// �X�N���[���|���S���̏��擾
//=============================================================================
void CPlayer2d::SetScrollPolygon(CScrollPolygon * pScrollPolygon)
{
	// �󂾂�����
	if (m_pScrollPolygon.size() == 0)
	{
		// �X�N���[���|���S���̐ݒ�
		m_pScrollPolygon.push_back(pScrollPolygon);
	}
}

//=============================================================================
// �e�N�X�`���̕ύX
//=============================================================================
void CPlayer2d::ChangeTexture(INPUT_TYPE InputType)
{
	// �|�C���^�擾
	CTexture *pTexture = GET_TEXTURE_PTR;

	// ����
	switch (InputType)
	{
	case INPUT_TYPE_UP:
		// �e�N�X�`���̐ݒ�
		BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_PLAYER_UP));
		break;

	case INPUT_TYPE_DOWN:
		// �e�N�X�`���̐ݒ�
		BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_PLAYER_DOWN));
		break;
	case INPUT_TYPE_RIGHT:
		// �e�N�X�`���̐ݒ�
		BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_PLAYER_RIGHT));
		break;
	case INPUT_TYPE_LEFT:
		// �e�N�X�`���̐ݒ�
		BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_PLAYER_LEFT));
		break;
	}
}