#ifndef _EVALUATION_H_
#define _EVALUATION_H_
//=============================================================================
//
// �]��UI�N���X����  [evaluation.h]
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
class CEvaluation : public CScene2D
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

	CEvaluation(PRIORITY Priority = PRIORITY_UI);	// �R���X�g���N�^
	virtual ~CEvaluation();							// �f�X�g���N�^

	static CEvaluation* Create(void); // �N���X����

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetEvaluation(EVALUATION_TYPE type);
private:

	float m_fAlpha; //�A���t�@�l
};
#endif