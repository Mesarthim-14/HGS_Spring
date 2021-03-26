//=============================================================================
//
// �]��UI�N���X����  [evaluation_ui.cpp]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "evaluation_ui.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POS  D3DXVECTOR3(200.0f, 200.0f, 0.0f) // ���W
#define SIZE D3DXVECTOR3(120.0f,40.0f,0.0f) // �T�C�Y*�摜�T�C�Y�ɍ��킹��
#define ROT D3DXToRadian(170)
#define MINUS_ALPHA 0.02f

//=============================================================================
// �N���G�C�g
//=============================================================================
CEvaluation * CEvaluation::Create(void)
{
	// ����������
	CEvaluation *pParticlre = new CEvaluation;

	// !nullcheck
	if (pParticlre != nullptr)
	{
		// ���W
		pParticlre->SetSceneInfo(POS, SIZE);


		// ����������
		pParticlre->Init();
	}

	return pParticlre;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEvaluation::CEvaluation(PRIORITY Priority) :CScene2D(Priority)
{
	m_fAlpha = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEvaluation::~CEvaluation()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEvaluation::Init(void)
{
	// ����������
	CScene2D::Init();
	m_fAlpha = 0.0f;

	D3DXCOLOR col = GetColor();
	col.a = m_fAlpha;
	SetCol(col);

	SetRotation(ROT);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEvaluation::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEvaluation::Update(void)
{

	if (m_fAlpha > 0)
	{
		m_fAlpha -= MINUS_ALPHA;
		D3DXCOLOR col = GetColor();
		col.a = m_fAlpha;
		SetCol(col);
	}
	

	// �e�N���X�̍X�V����
	CScene2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEvaluation::Draw(void)
{
	// �`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �]���̃Z�b�g
//=============================================================================
void CEvaluation::SetEvaluation(EVALUATION_TYPE type)
{
	// �A���t�@�l�̃Z�b�g
	m_fAlpha = 1.5f;


	// �e�N�X�`���̐؂�ւ�
	CTexture *pTexture = GET_TEXTURE_PTR;

	switch (type)
	{
	case EVALUATION_TYPE_NICE:
		// �i�C�X
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NICE));
		break;
	case EVALUATION_TYPE_GREAT:
		// �O���[�g
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_GREAT));
		break;
	case EVALUATION_TYPE_PARFECT:
		// �p�[�t�F�N�g
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARFECT));
		break;
	default:
		break;
	}

}
