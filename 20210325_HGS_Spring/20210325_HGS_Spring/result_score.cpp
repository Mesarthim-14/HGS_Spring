//=============================================================================
//
// ���U���g�X�R�A���� [result_score.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "result_score.h"
#include "manager.h"
#include "renderer.h"
#include "number_2d.h"
#include "texture.h"
#include "resource_manager.h"
#include "score.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define RANKING_INTERVAL_X	(130.0f)					// �����̊Ԋu
#define RANKING_INTERVAL_Y	(83.0f)					// �����̊Ԋu

#define MY_RANKING_INTERVAL_X	(80.0f)				// �����̊Ԋu
#define MY_RANKING_INTERVAL_Y	(88.0f)				// �����̊Ԋu

#define RANKING_FLASH_NUM	(3)						// �����L���O�_�Ńt���[��

#define RESULT_SCORE_COUNT_SPEED	(60)			//���U���g�X�R�A�̃J�E���g���I���܂ł̕b��

//=============================================================================
// �}�N����`
//=============================================================================


//=============================================================================
// �����L���O����
//=============================================================================
CResultScore * CResultScore::Create(void)
{
	// �������m��
	CResultScore *pRanking = new CResultScore;

	// ����������
	pRanking->Init();

	return pRanking;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResultScore::CResultScore()
{
	// 0�N���A
	m_fScore = 0;
	m_fScoreCount = 0;
	m_fScoreCntSpeed = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResultScore::~CResultScore()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResultScore::Init(void)
{
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �X�R�A�̎擾
	m_fScore = (float)CScore::GetScorePointa()->GetScoreData().nScore;

	//���t���[�����Z����l���Z�o
	m_fScoreCntSpeed = m_fScore / RESULT_SCORE_COUNT_SPEED;

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		// �����̃������m��
		m_pScore[nCount] = CNumber2d::Create(D3DXVECTOR3(RESULT_SCORE_POS_X - nCount * RANKING_INTERVAL_X,
											RESULT_SCORE_POS_Y + RANKING_INTERVAL_Y, 0.0f),
											D3DXVECTOR3(RESULT_SCORE_SIZE_X, RESULT_SCORE_SIZE_Y, 0.0f));

		if (m_pScore[nCount] != NULL)
		{
			// �����̐ݒ�
			m_pScore[nCount]->SetNumber(0);
		}

		// �e�N�X�`���̐ݒ�
		m_pScore[nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_1_2D));
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResultScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pScore[nCount] != NULL)
		{
			// �I������
			m_pScore[nCount]->Uninit();
			//delete m_pScore[nCntRank][nCount];
			m_pScore[nCount] = NULL;
		}
	}

	// �������̊J������
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResultScore::Update(void)
{
	if (m_fScoreCount <= m_fScore)
	{
		m_fScoreCount += m_fScoreCntSpeed;

		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			if (m_pScore[nCount] != NULL)
			{
				int nNum = ((int)m_fScoreCount / (int)(pow(10, nCount))) % 10;

				// �����̐ݒ�
				m_pScore[nCount]->SetNumber(nNum);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResultScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pScore[nCount] != NULL)
		{
			// �`�揈��
			m_pScore[nCount]->Draw();
		}
	}
}