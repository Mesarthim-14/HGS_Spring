#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"

//=============================================================================
// �v���C���[2D�N���X
//=============================================================================
class CPlayer
{
public:
	enum PLAYER_STATE
	{
		PLAYER_STATE_NONE = 0,		// �����u
		PLAYER_STATE_NORMAL,		// �ʏ���
		PLAYER_STATE_DAMAGE,		// �_���[�W
		PLAYER_STATE_MAX			// �ő吔
	};

	CPlayer();		// �R���X�g���N�^
	virtual ~CPlayer() {}		// �f�X�g���N�^

	virtual HRESULT Init(void) = 0;			// ����������
	virtual void Uninit(void) = 0;			// �I������
	virtual void Update(void) = 0;			// �X�V����
	virtual void Draw(void) = 0;			// �`�揈��

	// �������z�֐�
	virtual void UpdateState(void) = 0;			// �v���C���[�̏��
	virtual void PlayerControl(void) = 0;		// �v���C���[�̐���
	virtual void Move(void) = 0;				// �v���C���[�̕�������

	// Set�֐�
	void SetArmor(const bool bArmor)			{ m_bArmor = bArmor; }	// ���G���Ԃ̐ݒ�
	void SetState(const PLAYER_STATE &state)	{ m_state = state; }	// ���

	// Get�֐�
	bool GetArmor(void) { return m_bArmor; }			// ���G���Ԃ̏��
	PLAYER_STATE GetState(void) { return m_state; }		// ���

private:
	bool m_bArmor;
	PLAYER_STATE m_state;
};
#endif