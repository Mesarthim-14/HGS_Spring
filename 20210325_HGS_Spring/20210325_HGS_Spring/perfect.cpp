//=============================================================================
//
// �����L���O�N���X [ranking.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "perfect.h"
#include "manager.h"
#include "renderer.h"
#include "number_2d.h"
#include <stdio.h>
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
CPerfect * CPerfect::Create(void)
{
	// �������m��
	CPerfect *pRanking = new CPerfect;

	// ����������
	pRanking->Init();

	return pRanking;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPerfect::CPerfect() :CScene(PRIORITY_UI)
{
	// 0�N���A
	memset(m_pPerfect, 0, sizeof(m_pPerfect));
	m_nPerfect = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPerfect::~CPerfect()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPerfect::Init(void)
{
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �X�R�A�̎擾
	m_nPerfect = CScore::GetScorePointa()->GetScoreData().nNumParfect;

	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			// �����̃������m��
			m_pPerfect[nCount] =
				CNumber2d::Create(D3DXVECTOR3(PERFECT_POS_X - nCount*RANKING_INTERVAL_X,
					PERFECT_POS_Y + RANKING_INTERVAL_Y, 0.0f),
					D3DXVECTOR3(RANKING_SIZE_X, RANKING_SIZE_Y, 0.0f));

			if (m_pPerfect[nCount] != NULL)
			{
				int nNum = (m_nPerfect / (int)(pow(10, nCount))) % 10;

				// �����̐ݒ�
				m_pPerfect[nCount]->SetNumber(nNum);
			}

				// �e�N�X�`���̐ݒ�
			m_pPerfect[nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_1_2D));
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPerfect::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pPerfect[nCount] != NULL)
		{
			// �I������
			m_pPerfect[nCount]->Uninit();
			//delete m_apRanking[nCntRank][nCount];
			m_pPerfect[nCount] = NULL;
		}
	}

	// �������̊J������
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPerfect::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPerfect::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pPerfect[nCount] != NULL)
		{
			// �`�揈��
			m_pPerfect[nCount]->Draw();
		}
	}
}