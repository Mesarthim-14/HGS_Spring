#ifndef _POLYGON_H_
#define _POLYGON_H_
//=============================================================================
//
// �|���S�������N���X���� [polygon.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//���C�t�N���X
//=============================================================================
class CPolygon
{
public:
	CPolygon();			// �R���X�g���N�^
	~CPolygon();		// �f�X�g���N�^

	static CPolygon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// �C���X�^���X����

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);				// ����������
	void Uninit(void);															// �I������
	void Update(void);															// �X�V����
	void Draw(void);															// �`�揈��
	void SetColor(const D3DXCOLOR color);										// �F�̐ݒ�

	void SetVertexPos(D3DXVECTOR3 pos[NUM_VERTEX]);                           // ���_���W�̐ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }  // �e�N�X�`���̊��蓖��
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9        m_pTexture;  // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_Size;					// �|���S���̃T�C�Y
	D3DXVECTOR3 m_pos;					// ���C�t�̈ʒu
};
#endif 