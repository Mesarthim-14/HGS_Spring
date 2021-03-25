#ifndef _CHARACTER_3D_H_
#define _CHARACTER_3D_H_
//=============================================================================
//
// �L�����N�^�[����  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"
#include "character.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_CHARACTER_PARTS (22)	// �L�����N�^�[�̃p�[�c��
#define MAX_KEYFRAME		(10)	// �L�[�t���[���̍ő吔

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;

//=============================================================================
// �L�����N�^�[�̃N���X
//=============================================================================
class CCharacter3d : public CScene, public CCharacter
{
public:
	CCharacter3d(PRIORITY Priority = PRIORITY_CHARACTER);				// �R���X�g���N�^
	virtual ~CCharacter3d();											// �f�X�g���N�^

	virtual HRESULT Init(void);			// ����������
	virtual void Uninit();											// �I������
	virtual void Update();											// �X�V����
	virtual void Draw();											// �`�揈��

	void ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum);			// ���f���̐���
	void ModelAnimeUpdate(void);									// ���f���A�j���[�V����

	// �������z�֐�
	virtual void UpdateMotionState(void) = 0;						// ���[�V�����̏��

	// Set�֐�
	void SetPos(D3DXVECTOR3 pos);									// ���W�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);									// �p�x�̐ݒ�
	void SetMotion(int nMotion);									// ���[�V�����̐ݒ� 
	void SetStateCounter(int nStateCounter);						// ��ԃJ�E���^�[�̐ݒ�

	// Get�֐�
	D3DXVECTOR3 GetPos(void)				{ return m_pos; }						// ���݂̍��W���
	D3DXVECTOR3 GetRot(void)				{ return m_rot; }						// �p�x���
	int GetStateCounter(void)				{ return m_nStateCounter; }				// ��ԃJ�E���^�[�̏��
	CModelAnime *GetModelAnime(int nCount)	{ return m_apModelAnime[nCount]; }		// ���[�V�����̃J�E���g���
	CMotion *GetMotion(void)				{ return m_pMotion; }					// ���[�V�����̃|�C���^���

private:
	CModelAnime *m_apModelAnime[MAX_MODEL_PARTS];	// ���f���p�[�c�p�̃|�C���^
	CMotion *m_pMotion;								// ���[�V�����N���X�̃|�C���^
	D3DXVECTOR3 m_pos;				// ���W
	D3DXVECTOR3 m_rot;				// ���݂̉�]
	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	int m_nStateCounter;			// ��Ԃ̃J�E���^�[
	int m_nParts;					// �p�[�c��
	float m_fAngle;					// �p�x
};
#endif