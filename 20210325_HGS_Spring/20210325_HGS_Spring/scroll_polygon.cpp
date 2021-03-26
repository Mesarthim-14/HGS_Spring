//=======================================================================================
//
// �X�N���[���|���S���N���X [scroll_polygon.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "scroll_polygon.h"
#include "keyboard.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define SCROLL_POLYGON_SIZE	(D3DXVECTOR3(SCREEN_WIDTH /2 -50.0f, SCREEN_HEIGHT /2 -50.0f, 0.0f))	// �|���S���̃T�C�Y

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CScrollPolygon::CScrollPolygon(PRIORITY Priority) : CScene2D(Priority)
{
	m_ScrollInfo = { DIRECTION_TYPE_NONE , false };
	m_nCounter = 0;
	m_DefaultMove = ZeroVector3;			// ���̈ړ���
	m_move = ZeroVector3;					// �ړ���
	m_bSecondMove = false;					// ��x�ڂ̈ړ�
	m_bEnd = false;
	m_bStop = false;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CScrollPolygon::~CScrollPolygon()
{

}

//=======================================================================================
// Scene�N���X�̐���
//=======================================================================================
CScrollPolygon* CScrollPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, SCROLL_INFO ScrollInfo)
{
	// �I�u�W�F�N�g�𐶐�
	CScrollPolygon* pScrollPolygon = new CScrollPolygon;

	// !nullcheck
	if (pScrollPolygon != nullptr)
	{
		// ���ݒ�
		pScrollPolygon->SetSceneInfo(pos, SCROLL_POLYGON_SIZE);

		// �ړ���
		pScrollPolygon->m_move = move;
		pScrollPolygon->m_DefaultMove = move;

		// �\���̏����
		pScrollPolygon->m_ScrollInfo = ScrollInfo;

		// ����������
		pScrollPolygon->Init();
	}

	return pScrollPolygon;
}

//=======================================================================================
// �|���S���̏�����
//=======================================================================================
HRESULT CScrollPolygon::Init(void)
{
	// ����������
	CScene2D::Init();

	// �e�N�X�`���̃|�C���^�擾
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �e�N�X�`���̐ݒ�
	BindTexture(nullptr);

	return S_OK;
}

//=======================================================================================
// �|���S���̍X�V����
//=======================================================================================
void CScrollPolygon::Update(void)
{
	m_nCounter++;


	// ��x�ڂ̈ړ�
	if (m_bSecondMove == true)
	{
		GetPos() += m_DefaultMove;

		// �X�N���[������J�E���^
		if (m_nCounter >= SCROLL_FRAME)
		{
			// �ړ����~�߂�
			m_bEnd = true;
		}
	}
	else
	{
		// ���W
		GetPos() += m_move;

		// �X�N���[������J�E���^
		if (m_nCounter >= SCROLL_FRAME)
		{
			// �ړ����~�߂�
			m_move = ZeroVector3;
			m_bStop = true;
		}
	}

	// ���_�̈ړ�
	UpdateVertex();
}

//=======================================================================================
// 
//=======================================================================================
void CScrollPolygon::SetSecondMove(bool bSecondMove)
{
	m_bSecondMove = bSecondMove;
	m_nCounter = 0;
	m_move = ZeroVector3;
//	m_move = m_DefaultMove;
}