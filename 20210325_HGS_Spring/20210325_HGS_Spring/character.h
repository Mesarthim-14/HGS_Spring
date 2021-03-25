#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// �L�����N�^�[2D�N���X����  [character_2d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "scene_base.h"
#include "modelanime.h"

//=============================================================================
// �L�����N�^�[�̃N���X
//=============================================================================
class CCharacter
{
public:
	CCharacter();				// �R���X�g���N�^
	virtual ~CCharacter() {}											// �f�X�g���N�^

	virtual HRESULT Init(void) = 0;			// ����������
	virtual void Uninit(void) = 0;											// �I������
	virtual void Update(void) = 0;											// �X�V����
	virtual void Draw(void) = 0;											// �`�揈��

	// �������z�֐�
	virtual void UpdateState(void) = 0;								// �L�����N�^�[���

	// Set�֐�
	void SetMove(const D3DXVECTOR3 &move)		{ m_move = move; }			// �ړ��ʂ̐ݒ�
	void SetOldPos(const D3DXVECTOR3 &OldPos)	{ m_OldPos = OldPos; }		// �Â����W
	void SetRadius(const float fRadius)			{ m_fRadius = fRadius; }	// ���a�̐ݒ�
	void SetSpeed(const float fSpeed)			{ m_fSpeed = fSpeed; }		// ���x�̐ݒ�

	// Get�֐�
	D3DXVECTOR3 &GetMove(void)	{ return m_move; }			// �ړ��ʂ̏��
	D3DXVECTOR3 &GetOldPos(void)	{ return m_OldPos; }		// �Â����W���
	float GetSpeed(void)		{ return m_fSpeed; }		// �X�s�[�h�̏��
	float GetRadius(void)		{ return m_fRadius; }		// ���a�̏��
	
private:
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_OldPos;	// �Â����W
	float m_fSpeed;			// �ړ���
	float m_fRadius;		// ���a
};
#endif