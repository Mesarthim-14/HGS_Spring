#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : Konishi Yuuto
//
//=============================================================================

//***************************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// �}�N����`
//***************************************************************************************
#define MAX_PLAYER (1)			// �v���C���[�̐�

//***************************************************************************************
// �O���錾
//***************************************************************************************
class CCamera;
class CLight;
class CMeshField;
class CPlayer2d;
class CPlayer3d;

//***************************************************************************************
// �Q�[���N���X
//***************************************************************************************
class CGame : public CScene
{
public:
	CGame(PRIORITY Priority = PRIORITY_0);				// �R���X�g���N�^
	~CGame();											// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
	void SetGame(void);										// �Q�[���̐ݒ�

	static CGame* Create(void);									// �Q�[���������
	static CCamera *GetCamera(void);						// �J�����̃|�C���^���
	static CLight *GetLight(void);							// ���C�g�̃|�C���^���
	CPlayer2d *GetPlayer2d(void) { return m_pPlayer2d; }	// �v���C���[�̃|�C���^���
	static CPlayer3d *GetPlayer3d(void) { return m_pPlayer3d; }	// �v���C���[�̃|�C���^
private:	
	static CCamera *m_pCamera;			// �J�����̃|�C���^	
	static CLight *m_pLight;			// ���C�g�̃|�C���^
	CPlayer2d *m_pPlayer2d;				// �v���C���[2D�̃|�C���^
	static CPlayer3d *m_pPlayer3d;		// �v���C���[3D�̃|�C���^
	LPD3DXFONT m_pFont;					// �f�o�b�N�p�t�H���g
	int m_nTimeCounter;					// �Q�[���̃J�E���^�[
	bool m_bGameEnd;					// �Q�[���̃G���h�t���O
};
#endif