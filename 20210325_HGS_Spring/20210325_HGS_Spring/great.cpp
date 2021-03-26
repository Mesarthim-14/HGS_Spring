//=============================================================================
//
// �����L���O�N���X [ranking.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "great.h"
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
CGreat * CGreat::Create(void)
{
	// �������m��
	CGreat *pRanking = new CGreat;

	// ����������
	pRanking->Init();

	return pRanking;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGreat::CGreat():CScene(PRIORITY_UI)
{
	// 0�N���A
	memset(m_pGreat, 0, sizeof(m_pGreat));
	m_nGreat = 0;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGreat::~CGreat()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGreat::Init(void)
{
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �X�R�A�̎擾
	m_nGreat = CScore::GetScorePointa()->GetScoreData().nNumGreat;

	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			// �����̃������m��
			m_pGreat[nCount] =
				CNumber2d::Create(D3DXVECTOR3(GREAT_POS_X - nCount*RANKING_INTERVAL_X,
					GREAT_POS_Y + RANKING_INTERVAL_Y, 0.0f),
					D3DXVECTOR3(RANKING_SIZE_X, RANKING_SIZE_Y, 0.0f));

			if (m_pGreat[nCount] != NULL)
			{
				int nNum = (m_nGreat / (int)(pow(10, nCount))) % 10;

				// �����̐ݒ�
				m_pGreat[nCount]->SetNumber(nNum);
			}

			// �e�N�X�`���̐ݒ�
			m_pGreat[nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_1_2D));
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGreat::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pGreat[nCount] != NULL)
		{
			// �I������
			m_pGreat[nCount]->Uninit();
			//delete m_apRanking[nCntRank][nCount];
			m_pGreat[nCount] = NULL;
		}
	}

	// �������̊J������
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGreat::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGreat::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pGreat[nCount] != NULL)
		{
			// �`�揈��
			m_pGreat[nCount]->Draw();
		}
	}
}