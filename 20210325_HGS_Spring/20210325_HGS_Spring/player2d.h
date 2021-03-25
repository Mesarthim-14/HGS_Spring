#ifndef _PLAYER_2D_H_
#define _PLAYER_2D_H_
//=============================================================================
//
// �v���C���[2D�N���X�w�b�_�[ [player2d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character2d.h"
#include "player.h"

//=============================================================================
// �v���C���[2D�N���X
//=============================================================================
class CPlayer2d : public CCharacter2d, public CPlayer
{
public:
	CPlayer2d(PRIORITY Priority = PRIORITY_CHARACTER);			// �R���X�g���N�^
	~CPlayer2d();												// �f�X�g���N�^

	static CPlayer2d*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �N���G�C�g

	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��

	void UpdateState(void);			// �v���C���[�̏��
	void PlayerControl(void);		// �v���C���[�̐���
	void Move(void);				// �v���C���[�̕�������

private:
};
#endif