//=============================================================================
//
// �����L���O�N���X [ranking.cpp]
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
#define RANKING_INTERVAL_X	(45.0f)					// �����̊Ԋu
#define RANKING_INTERVAL_Y	(83.0f)					// �����̊Ԋu

#define MY_RANKING_INTERVAL_X	(80.0f)				// �����̊Ԋu
#define MY_RANKING_INTERVAL_Y	(88.0f)				// �����̊Ԋu

#define RANKING_FLASH_NUM	(3)						// �����L���O�_�Ńt���[��

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
	m_nScore = 0;
	m_nScoreCount = 0;
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
	m_nScore = CScore::GetScorePointa()->GetScoreData().nScore;
	//m_nScore = 99;

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
	if (m_nScoreCount <= m_nScore)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			if (m_pScore[nCount] != NULL)
			{
				int nNum = (m_nScoreCount / (int)(pow(10, nCount))) % 10;

				// �����̐ݒ�
				m_pScore[nCount]->SetNumber(nNum);
			}
		}

		m_nScoreCount++;
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