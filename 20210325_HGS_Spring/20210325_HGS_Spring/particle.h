#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//=============================================================================
//
// �p�[�e�B�N���N���X����  [particle.h]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �L�����N�^�[�̃N���X
//=============================================================================
class CParticlre : public CScene2D
{
public:
	typedef enum
	{
		DEATH_PART_TYPE_ALL = 0, // �S����
		DEATH_PART_TYPE_UP,      // ��ʏ�
		DEATH_PART_TYPE_DOWN ,   // ��ʉ�
		DEATH_PART_TYPE_LEFT ,   // ��ʍ�
		DEATH_PART_TYPE_RIGHT,   // ��ʉE
		DEATH_PART_TYPE_MAX,
	}DEATH_PART_TYPE;

	CParticlre(PRIORITY Priority = PRIORITY_PARTICLE);	// �R���X�g���N�^
	virtual ~CParticlre();								// �f�X�g���N�^

	static void CreateDeath(D3DXVECTOR3 pos, DEATH_PART_TYPE type);              // �N���X����
	static CParticlre* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move , int nLife); // �N���X����

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

private:

	void ManageMoveValue(void); // �ړ��ʂ̊Ǘ�

	D3DXVECTOR3 m_move; // �ړ���
	D3DXCOLOR   m_col;  // �J���[
	int m_nLife;        // ����
};
#endif