//=============================================================================
//
// �v���C���[�N���X [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player3d.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
#include "character.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED					(20.0f)				// �v���C���[�̈ړ���
#define STICK_SENSITIVITY				(50.0f)				// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED				(0.1f)				// �L�����N�^�[�̉�]���鑬�x
#define PLAYER_RADIUS					(50.0f)				// ���a�̑傫��

//=============================================================================
// �N���G�C�g
//=============================================================================
CPlayer3d * CPlayer3d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CPlayer3d *pPlayer = new CPlayer3d;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ���W
		pPlayer->SetPos(pos);
		pPlayer->SetRot(size);

		// ����������
		pPlayer->Init();
	}

	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer3d::CPlayer3d(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
	m_bArmor = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer3d::~CPlayer3d()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer3d::Init(void)
{
	// ���f�����擾
	CXfile *pXfile = GET_XFILE_PTR;

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f���̏���n��
	//	ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	CCharacter3d::Init();												// ���W�@�p�x
	SetRadius(PLAYER_RADIUS);											// ���a�̐ݒ�
	SetSpeed(PLAYER_SPEED);												// ���x�̐ݒ�

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer3d::Uninit(void)
{	
	// �I������
	CCharacter3d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer3d::Update(void)
{
	// ���W���
	D3DXVECTOR3 pos = GetPos();	// ���݂̍��W�擾
	SetOldPos(pos);				// �Â����W�ۑ�

	// �v���C���[�̏��
	UpdateState();

	// ���[�V�������
	UpdateMotionState();

	// �v���C���[�̐���
	PlayerControl();

	// �p�x�̍X�V����
	UpdateRot();

	// �e�N���X�̍X�V����
	CCharacter3d::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer3d::Draw(void)
{
	// �`�揈��
	CCharacter3d::Draw();
}

//=============================================================================
// �v���C���[�̏��
//=============================================================================
void CPlayer3d::UpdateState(void)
{
}

//=============================================================================
// ���[�V�������
//=============================================================================
void CPlayer3d::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();
	int nKey = GetMotion()->GetKey();
	int nCountMotion = GetMotion()->GetCountMotion();

	// ���[�V�������
	switch (MotionState)
	{
	case MOTION_IDOL:
		break;
	}
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
void CPlayer3d::PlayerControl()
{
	// �v���C���[�̈ړ�����
	Move();
}

//=============================================================================
// �p�x�̍X�V����
//=============================================================================
void CPlayer3d::UpdateRot(void)
{
	// �p�x�̎擾
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// �L�����N�^�[��]�̑��x
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// �p�x�̐ݒ�
	SetRot(rot);
}

//=============================================================================
// �v���C���[�ړ�����
//=============================================================================
void CPlayer3d::Move(void)
{
	// ���[�J���ϐ�
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// �L�[�{�[�h�X�V
	DIJOYSTATE js = CInputJoypad::GetStick(0);								// �W���C�p�b�h�̎擾
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();		// �T�E���h�̃|�C���^
	float fAngle = CGame::GetCamera()->Get��();								// �J�����̊p�x
	D3DXVECTOR3 pos = GetPos();												// ���W
	D3DXVECTOR3 rot = GetRot();												// �p�x
	float fSpeed = GetSpeed();												// �X�s�[�h
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();	// ���[�V�����̏��

		//���͂����݂���
	if ((js.lX != 0.0f || js.lY != 0.0f))
	{
		// ������Ԃɂ���
		m_bMove = true;

		//���s���[�V�����̍Đ�
		SetMotion(MOTION_WALK);

		float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// �R���g���[���̊p�x
		float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// �R���g���[���̊p�x

		// �ړ��ʐݒ�
		pos.x += sinf(fAngle + (fAngle2))* fSpeed;
		pos.z += cosf(fAngle + (fAngle2))* fSpeed;

		// �p�x�̐ݒ�
		m_rotDest.y = fAngle + (fAngle3);
	}
}