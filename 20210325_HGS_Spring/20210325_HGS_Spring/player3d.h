#ifndef _PLAYER_3D_H_
#define _PLAYER_3D_H_
//=============================================================================
//
// �v���C���[3D�N���X�w�b�_�[ [player3d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character3d.h"
#include "modelanime.h"
#include "player.h"

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer3d : public CCharacter3d, public CPlayer
{
public:
	//=============================================================================
	//�@���[�V������Ԃ̗񋓌^
	//=============================================================================
	enum MOTION_STATE
	{
		MOTION_NONE = -1,
		MOTION_IDOL,				// �A�C�h�����[�V����
		MOTION_WALK,				// ���s���[�V����
		MOTION_MAX,					// ���[�V�����ő吔
	};

	//=============================================================================
	//�@���[�V������Ԃ̗񋓌^
	//=============================================================================
	enum PARTS_NUM
	{
		PARTS_NUM_NONE = -1,
		PARTS_NUM_MAX,				// ���[�V�����ő吔
	};

	CPlayer3d(PRIORITY Priority = PRIORITY_CHARACTER);			// �R���X�g���N�^
	~CPlayer3d();												// �f�X�g���N�^

	static CPlayer3d*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �N���G�C�g

	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��
	void UpdateState(void);			// �v���C���[�̏��
	void UpdateMotionState(void);	// ���[�V�������
	void PlayerControl(void);		// �v���C���[�̐���
	void UpdateRot(void);			// �p�x�̍X�V����
	void Move(void);				// �v���C���[�̕�������

private:
	D3DXVECTOR3 m_rotDest;			// ��](�ڕW�l)
	bool m_bMove;					// �����Ă���t���O
	bool m_bArmor;					// ���G���Ԃ̃t���O
};
#endif