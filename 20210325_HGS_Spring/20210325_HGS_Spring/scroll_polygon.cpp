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
#include "order.h"
#include "game.h"
#include "player2d.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define SCROLL_POLYGON_SIZE	(D3DXVECTOR3(SCREEN_WIDTH /2 -50.0f, SCREEN_HEIGHT /2 -50.0f, 0.0f))	// �|���S���̃T�C�Y

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CScrollPolygon::CScrollPolygon(PRIORITY Priority) : CScene2D(Priority)
{
	m_pOrder = nullptr;
	m_ScrollInfo = { DIRECTION_TYPE_NONE , false };
	m_nCounter = 0;
	m_move = ZeroVector3;					// �ړ���
	m_bSecondMove = false;					// ��x�ڂ̈ړ�
	m_bEnd = false;
	m_bStop = false;
	m_nEndCounter = 0;
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
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_GAME_BG));

	// nullcheck
	if (m_pOrder == nullptr)
	{
		// ���W
		m_pOrder = COrder::Create(GetPos(), m_ScrollInfo);
	}

	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CScrollPolygon::Uninit(void)
{
	// �I������
	CScene2D::Uninit();

	// !nullcheck
	if (m_pOrder != nullptr)
	{
		// �I�[�_�[�̏I������
		m_pOrder->Uninit();
		m_pOrder = nullptr;
	}
}

//=======================================================================================
// �|���S���̍X�V����
//=======================================================================================
void CScrollPolygon::Update(void)
{
	if (CGame::GetPlayer2d()->GetDeath() == true)
	{
		m_nEndCounter++;
	}

	if (m_nEndCounter <= 10)
	{
		m_nCounter++;

		// ���W
		GetPos() += m_move;

		// ���_�̈ړ�
		UpdateVertex();

		// !nullcheck
		if (m_pOrder != nullptr)
		{
			D3DXVECTOR3 pos = GetPos();
			// ���W�̍X�V
			m_pOrder->GetPos() = D3DXVECTOR3(pos.x, pos.y - 85.0f, 0.0f);
			m_pOrder->UpdateVertex();
		}

		// ��x�ڂ̈ړ�
		if (m_bSecondMove == true)
		{
			// �X�N���[������J�E���^
			if (m_nCounter >= SCROLL_FRAME)
			{
				// �ړ����~�߂�
				m_bEnd = true;
			}
		}
		else
		{
			// �X�N���[������J�E���^
			if (m_nCounter >= SCROLL_FRAME)
			{
				// �ړ����~�߂�
				m_move = ZeroVector3;
				m_bStop = true;
			}
		}


	}
}


//=======================================================================================
// 
//=======================================================================================
void CScrollPolygon::SetSecondMove(bool bSecondMove, D3DXVECTOR3 move)
{
	m_bSecondMove = bSecondMove;
	m_nCounter = 0;
	m_move = move;
}