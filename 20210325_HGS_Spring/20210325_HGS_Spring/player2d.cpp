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
	CTexture *pTexture = GET_TEXTURE_PTR;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ���W
		pPlayer->SetSceneInfo(pos, size);
		pPlayer->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PLAYER_2D));

		// ����������
		pPlayer->Init();
	}

	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer2d::CPlayer2d(PRIORITY Priority)
{
	m_pScrollPolygon.clear();
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

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer2d::Uninit(void)
{
	// �I������
	CCharacter2d::Uninit();
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
					// �X�N���[���|���S�����̔j��
					m_pScrollPolygon.pop_back();

					CMapManager *pMapManager = CGame::GetMapManager();

					// ���̃}�b�v����
					pMapManager->CreateMap(InputType);
				}
				else
				{// �Փ˂̔���

				}
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

	if (pKeyboard->GetTrigger(DIK_W))
	{
		return INPUT_TYPE_UP;
	}
	if (pKeyboard->GetTrigger(DIK_A))
	{
		return INPUT_TYPE_LEFT;
	}
	if (pKeyboard->GetTrigger(DIK_S))
	{
		return INPUT_TYPE_DOWN;
	}
	if (pKeyboard->GetTrigger(DIK_D))
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
	DIJOYSTATE js = CInputJoypad::GetStick(0);								// �W���C�p�b�h�̎擾
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
