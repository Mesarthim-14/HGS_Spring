#ifndef _TIME_LIMIT_H_
#define _TIME_LIMIT_H_
//=============================================================================
//
// �������� [time_limit.h]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CGauge;

//=============================================================================
// �v���C���[2D�N���X
//=============================================================================
class CTimeLimit
{
public:
	// �X�R�A�^�C�v��
	typedef enum
	{
		EVALUATION_TYPE_NICE = 0,
		EVALUATION_TYPE_GREAT,
		EVALUATION_TYPE_PARFECT,
		EVALUATION_TYPE_MAX
	}EVALUATION_TYPE;

	CTimeLimit();			// �R���X�g���N�^
	~CTimeLimit();												// �f�X�g���N�^

	static CTimeLimit*Create(float fTime);	// �N���G�C�g

	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	bool Update(void);				// �X�V����*�Ԃ�l*�������Ԃ��Ȃ���
	void Draw(void);				// �`�揈��
	
	EVALUATION_TYPE CheckEvaluation(void); // �]���̃`�F�b�N
private:
	float m_fTime;     // ����
	float m_fMaxTime;  // �ő厞��
	CGauge * m_pGauge; // �Q�[�W�N���X
};
#endif