//=============================================================================
//
// �i�C�X�N���X [nice.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "nice.h"
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
#define RANKING_INTERVAL_X	(50.0f)					// �����̊Ԋu
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
CNice * CNice::Create(void)
{
	// �������m��
	CNice *pRanking = new CNice;

	// ����������
	pRanking->Init();

	return pRanking;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNice::CNice()
{
	// 0�N���A
	memset(m_pNice, 0, sizeof(m_pNice));
	m_nNice = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNice::~CNice()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CNice::Init(void)
{
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �X�R�A�̎擾
	m_nNice = CScore::GetScorePointa()->GetScoreData().nNumNice;

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		// �����̃������m��
		m_pNice[nCount] =
			CNumber2d::Create(D3DXVECTOR3(NICE_POS_X - nCount*RANKING_INTERVAL_X,
				NICE_POS_Y + RANKING_INTERVAL_Y, 0.0f),
				D3DXVECTOR3(NICE_SIZE_X, NICE_SIZE_Y, 0.0f));

		if (m_pNice[nCount] != NULL)
		{
			int nNum = (m_nNice / (int)(pow(10, nCount))) % 10;

			// �����̐ݒ�
			m_pNice[nCount]->SetNumber(nNum);
		}

		// �e�N�X�`���̐ݒ�
		m_pNice[nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_1_2D));
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CNice::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pNice[nCount] != NULL)
		{
			// �I������
			m_pNice[nCount]->Uninit();
			//delete m_apRanking[nCntRank][nCount];
			m_pNice[nCount] = NULL;
		}
	}

	// �������̊J������
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CNice::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CNice::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_pNice[nCount] != NULL)
		{
			// �`�揈��
			m_pNice[nCount]->Draw();
		}
	}
}