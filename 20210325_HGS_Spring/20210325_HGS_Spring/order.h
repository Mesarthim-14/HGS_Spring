#ifndef _ORDER_H_
#define _ORDER_H_
//=============================================================================
//
// ���߃e�N�X�`���N���X�w�b�_�[ [order.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene2d.h"
#include "scroll_polygon.h"

//=============================================================================
// �I�[�_�[�N���X
//=============================================================================
class COrder : public CScene2D
{
public:
	COrder(PRIORITY Priority = PRIORITY_1);			// �R���X�g���N�^
	~COrder();											// �f�X�g���N�^

	static COrder*Create(D3DXVECTOR3 pos, CScrollPolygon::SCROLL_INFO ScrollInfo);	// �N���G�C�g

	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��

	void SetTexture(CScrollPolygon::SCROLL_INFO ScrollInfo);
private:
};
#endif