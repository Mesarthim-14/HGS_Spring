//=============================================================================
//
// �}�b�v�N���X [map.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "map_manager.h"
#include "manager.h"
#include "renderer.h"
#include "scroll_polygon.h"
#include "player2d.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCROLL_SPEED_X		((SCREEN_WIDTH)/(float)SCROLL_FRAME)										// �ړ���
#define SCROLL_SPEED_Y		((SCREEN_HEIGHT)/(float)SCROLL_FRAME)										// �ړ���

#define SCROLL_POS_UP		(D3DXVECTOR3((SCREEN_WIDTH/2), -(SCREEN_HEIGHT/2), 0.0f))				// ���W
#define SCROLL_POS_DOWN		(D3DXVECTOR3((SCREEN_WIDTH/2), SCREEN_HEIGHT+(SCREEN_HEIGHT/2), 0.0f))	// ���W
#define SCROLL_POS_RIGHT	(D3DXVECTOR3(SCREEN_WIDTH+(SCREEN_WIDTH/2), (SCREEN_HEIGHT/2), 0.0f))	// ���W
#define SCROLL_POS_LEFT		(D3DXVECTOR3(-(SCREEN_WIDTH/2), (SCREEN_HEIGHT/2), 0.0f))				// ���W

#define SCROLL_MOVE_UP		(D3DXVECTOR3(0.0f, SCROLL_SPEED_Y, 0.0f))	// �ړ���
#define SCROLL_MOVE_DOWN	(D3DXVECTOR3(0.0f, -SCROLL_SPEED_Y, 0.0f))	// �ړ���
#define SCROLL_MOVE_RIGHT	(D3DXVECTOR3(-SCROLL_SPEED_X, 0.0f, 0.0f))	// �ړ���
#define SCROLL_MOVE_LEFT	(D3DXVECTOR3(SCROLL_SPEED_X, 0.0f, 0.0f))	// �ړ���

//=============================================================================
// static�������錾
//=============================================================================
CMapManager *CMapManager::m_pMap = nullptr;		// ���g�̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapManager::CMapManager()
{
	CreateMap(INPUT_TYPE_NONE);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapManager::~CMapManager()
{
}

//=============================================================================
// �I������
//=============================================================================
void CMapManager::Uninit(void)
{
	// �������m��
	for (unsigned nCount = 0; nCount < m_pScroll.size(); nCount++)
	{
		// !nullcheck
		if (m_pScroll[nCount] != nullptr)
		{
			// �I������
			m_pScroll[nCount]->Uninit();
			m_pScroll[nCount] = nullptr;
		}
	}
		// �z��̃N���A
		m_pScroll.clear();
	

	// !nullcheck
	if (m_pMap != nullptr)
	{
		// �|�C���^�̊J��
		delete m_pMap;
		m_pMap = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CMapManager::Update(void)
{
	// �T�C�Y��
	for (size_t nCount = 0; nCount < m_pScroll.size(); nCount++)
	{
		// �I���t���O�������
		if (m_pScroll.at(nCount)->GetEnd() == true)
		{
			// �I������
			m_pScroll.at(nCount)->Uninit();

			// ��ɂ���
			m_pScroll.erase(m_pScroll.begin() + nCount);
		}
	}
}

//=============================================================================
// �A�C�e���{�b�N�X�̐���
//=============================================================================
void CMapManager::CreateMap(INPUT_TYPE InputType)
{
	// ���W�ݒ�
	D3DXVECTOR3 pos = ZeroVector3;

	// �ړ��ʂ̐ݒ�
	D3DXVECTOR3 move = ZeroVector3;

	// �T�C�Y�������
	if (m_pScroll.size() != 0)
	{
		// ���W�ݒ�
		pos = SetPos(InputType);

		// �ړ��ʂ̐ݒ�
		move = SetMove(InputType);

		// ��x�ڂ̈ړ���ݒ�
		m_pScroll.at(0)->SetSecondMove(true, move);

	}
	else
	{
		INPUT_TYPE ElseInputType = (INPUT_TYPE)(rand() % (int)INPUT_TYPE_MAX);
	
		// ���W�ݒ�
		pos = SetPos(ElseInputType);

		// �ړ��ʂ̐ݒ�
		move = SetMove(ElseInputType);
	}

	// �X�N���[���|���S�����
	CScrollPolygon::SCROLL_INFO DirectionType = SetScrollInfo();

	CScrollPolygon *pScrollPolygon = CScrollPolygon::Create(pos, move, DirectionType);
	
	// �Q�[���̃v���C���[
	CPlayer2d *pPlayer = CGame::GetPlayer2d();

	// �X�N���[���|���S���̏����v���C���[�Ɏ�������
	pPlayer->SetScrollPolygon(pScrollPolygon);

	// �C���X�^���X���m��
	m_pScroll.push_back(pScrollPolygon);
}

//=============================================================================
// �������W�ݒ�
//=============================================================================
D3DXVECTOR3 CMapManager::SetPos(INPUT_TYPE InputType)
{
	// �^�C�v����
	switch (InputType)
	{
		// �����
	case INPUT_TYPE_UP:
		return SCROLL_POS_UP;
		break;

		// ������
	case INPUT_TYPE_DOWN:
		return SCROLL_POS_DOWN;
		break;

		// �E����
	case INPUT_TYPE_RIGHT:
		return SCROLL_POS_RIGHT;
		break;

		// ������
	case INPUT_TYPE_LEFT:
		return SCROLL_POS_LEFT;
		break;

	default:
		break;
	}

	return ZeroVector3;
}

//=============================================================================
// �ړ��ʂ̐ݒ�
//=============================================================================
D3DXVECTOR3 CMapManager::SetMove(INPUT_TYPE InputType)
{
	// �^�C�v����
	switch (InputType)
	{
		// �����
	case INPUT_TYPE_UP:
		return SCROLL_MOVE_UP;
		break;

		// ������
	case INPUT_TYPE_DOWN:
		return SCROLL_MOVE_DOWN;
		break;

		// �E����
	case INPUT_TYPE_RIGHT:
		return SCROLL_MOVE_RIGHT;
		break;

		// ������
	case INPUT_TYPE_LEFT:
		return SCROLL_MOVE_LEFT;
		break;

	default:
		break;
	}

	return ZeroVector3;
}

//=============================================================================
// �X�N���[���|���S���̏���ݒ�
//=============================================================================
CScrollPolygon::SCROLL_INFO CMapManager::SetScrollInfo(void)
{
	// �^�C�v�𗐐��Őݒ�
	CScrollPolygon::DIRECTION_TYPE DirectionType =
		(CScrollPolygon::DIRECTION_TYPE)(rand() % (int)CScrollPolygon::DIRECTION_TYPE_MAX);

	// bool�^�̗����ݒ�
	int nFlag = rand() % 2;
	bool bFlag = false;

	switch (nFlag)
	{
	case 0:
		bFlag = false;
		break;
	case 1:
		bFlag = true;
		break;
	}

	return { DirectionType, bFlag };
}

//=============================================================================
// �C���X�^���X�擾�֐�
//=============================================================================
CMapManager * CMapManager::GetInstance(void)
{
	// nullcheck
	if (m_pMap == nullptr)
	{
		// �������m��
		m_pMap = new CMapManager;
	}

	return m_pMap;
}