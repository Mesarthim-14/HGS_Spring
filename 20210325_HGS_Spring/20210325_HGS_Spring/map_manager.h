#ifndef _MAP_H_
#define _MAP_H_
//=============================================================================
//
// �}�b�v�N���X�w�b�_�[ [map.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "player2d.h"
#include "scroll_polygon.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCROLL_POLYGON_APPEAR_POS_X	()
#define SCROLL_POLYGON_APPEAR_POS	()

//=============================================================================
// �O���錾
//=============================================================================
class CScrollPolygon;


//=============================================================================
// �G�t�F�N�g����
//=============================================================================
class CMapManager
{
public:
	~CMapManager();								// �f�X�g���N�^

	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void CreateMap(INPUT_TYPE InputType);		// �}�b�v�̐���
	D3DXVECTOR3 SetPos(INPUT_TYPE InputType);	// �ړ��ʂ̐ݒ�
	D3DXVECTOR3 SetMove(INPUT_TYPE InputType);	// �ړ��ʂ̐ݒ�
	CScrollPolygon::SCROLL_INFO SetScrollInfo(void);		// �X�N���[�����
	static CMapManager *GetInstance(void);				// �C���X�^���X�擾�֐�
	
private:
	CMapManager();								// �R���X�g���N�^
	static CMapManager *m_pMap;					// ���g�̃N���X�̃|�C���^
	std::vector<CScrollPolygon*> m_pScroll;		// �A�C�e���{�b�N�X�̃|�C���^
};
#endif
