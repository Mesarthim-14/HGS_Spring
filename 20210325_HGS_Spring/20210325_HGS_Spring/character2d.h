#ifndef _CHARACTER_2D_H_
#define _CHARACTER_2D_H_
//=============================================================================
//
// �L�����N�^�[�N���X����  [character_2d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "modelanime.h"
#include "character.h"

//=============================================================================
// �L�����N�^�[�̃N���X
//=============================================================================
class CCharacter2d : public CScene2D, public CCharacter
{
public:
	CCharacter2d(PRIORITY Priority = PRIORITY_CHARACTER);	// �R���X�g���N�^
	virtual ~CCharacter2d();								// �f�X�g���N�^

	virtual HRESULT Init(void);								// ����������
	virtual void Uninit(void);									// �I������
	virtual void Update(void);									// �X�V����
	virtual void Draw(void);									// �`�揈��

private:
};
#endif