#ifndef _SCORE_2D_H_
#define _SCORE_2D_H_
//=============================================================================
//
// �X�R�A�N���X����  [score.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "evaluation_ui.h"

//=============================================================================
// �L�����N�^�[�̃N���X
//=============================================================================
class CScore
{
public:
	// �X�R�A�\����
	typedef struct
	{
		int nScore;
		int nNumNice;    // �i�C�X��
		int nNumGreat;   // �O���[�g��
		int nNumParfect; // �p�[�t�F�N�g��
	}Score;

	CScore();	// �R���X�g���N�^
	virtual ~CScore();								// �f�X�g���N�^
	static CScore * Create(void); // �N���X����
	static void Release(void); // �N���X����

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void AddScore(CEvaluation::EVALUATION_TYPE type);

	static CScore *GetScorePointa(void) { return m_pScore; }
	Score GetScoreData(void) { return m_score; }
private:
	static CScore * m_pScore;
	Score m_score; // �X�R�A�\����
};
#endif