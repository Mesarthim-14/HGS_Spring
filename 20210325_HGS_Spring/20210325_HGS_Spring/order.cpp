//=======================================================================================
//
// ����Ui�N���X [order.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "order.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define ORDER_UI_SIZE (D3DXVECTOR3(100.0f, 100.0f, 0.0f))

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
COrder::COrder(PRIORITY Priority) : CScene2D(Priority)
{

}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
COrder::~COrder()
{

}

//=======================================================================================
// Scene�N���X�̐���
//=======================================================================================
COrder* COrder::Create(const D3DXVECTOR3 pos, CScrollPolygon::SCROLL_INFO ScrollInfo)
{
	// �I�u�W�F�N�g�𐶐�
	COrder* pScene = new COrder;

	// !nullcheck
	if (pScene != nullptr)
	{
		pScene->SetSceneInfo(pos, ORDER_UI_SIZE);
		pScene->SetTexture(ScrollInfo);
		// ����������
		pScene->Init();
	}

	return pScene;
}

//=======================================================================================
// �|���S���̏�����
//=======================================================================================
HRESULT COrder::Init(void)
{
	// ����������
	CScene2D::Init();

	return S_OK;
}

//=======================================================================================
// �|���S���̏I������
//=======================================================================================
void COrder::Uninit(void)
{
	// ����������
	CScene2D::Uninit();
}

//=======================================================================================
// �|���S���̍X�V����
//=======================================================================================
void COrder::Update(void)
{

}

//=======================================================================================
// �|���S���̕`�揈��
//=======================================================================================
void COrder::Draw(void)
{
	// ����������
	CScene2D::Draw();
}

//=======================================================================================
// �e�N�X�`���̐ݒ�
//=======================================================================================
void COrder::SetTexture(CScrollPolygon::SCROLL_INFO ScrollInfo)
{
	CTexture *pTexture = GET_TEXTURE_PTR;
	int nNum = rand() % 3;

	// �e�N�X�`����ޕ���
	switch (ScrollInfo.Direcsion)
	{
	case CScrollPolygon::DIRECTION_TYPE_UP:
		if (ScrollInfo.bFlag == true)
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_UP_E + nNum)));
		}
		else
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_NOT_UP_E + nNum)));
		}
		break;

	case CScrollPolygon::DIRECTION_TYPE_DOWN:
		if (ScrollInfo.bFlag == true)
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_DOWN_E + nNum)));
		}
		else
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_NOT_DOWN_E + nNum)));

		}
		break;

	case CScrollPolygon::DIRECTION_TYPE_RIGHT:
		if (ScrollInfo.bFlag == true)
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_RIGHT_E + nNum)));
		}
		else
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_NOT_RIGHT_E + nNum)));

		}
		break;

	case CScrollPolygon::DIRECTION_TYPE_LEFT:
		if (ScrollInfo.bFlag == true)
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_LEFT_E + nNum)));
		}
		else
		{
			BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_NOT_LEFT_E + nNum)));

		}
		break;
	}
}