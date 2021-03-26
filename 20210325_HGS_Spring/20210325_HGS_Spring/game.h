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
class CMapManager;
class CEvaluation;
// ���͂̎�ނ̗񋓌^
enum INPUT_TYPE
{
	INPUT_TYPE_NONE = -1,		// �����l
	INPUT_TYPE_UP,				// ��
	INPUT_TYPE_DOWN,			// ��
	INPUT_TYPE_RIGHT,			// �E
	INPUT_TYPE_LEFT,			// ��
	INPUT_TYPE_MAX				// �ő�l
};

//***************************************************************************************
// �Q�[���N���X
//***************************************************************************************
class CGame : public CScene
{
public:
	CGame(PRIORITY Priority = PRIORITY_0);				// �R���X�g���N�^
	~CGame();											// �f�X�g���N�^

	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��
	void SetGame(void);				// �Q�[���̐ݒ�

	static CGame* Create(void);									// �Q�[���������
	static CCamera *GetCamera(void);							// �J�����̃|�C���^���
	static CLight *GetLight(void);								// ���C�g�̃|�C���^���
	static CPlayer2d *GetPlayer2d(void) { return m_pPlayer2d; }		// �v���C���[�̃|�C���^���
	static CPlayer3d *GetPlayer3d(void) { return m_pPlayer3d; }	// �v���C���[�̃|�C���^
	static CMapManager *GetMapManager(void) { return m_pMapManager; }	// �}�b�v�}�l�[�W���̃|�C���^���
	static CEvaluation *GetEvaluation(void) { return m_pEvaluation; }	// �}�b�v�}�l�[�W���̃|�C���^���

private:	
	static CCamera *m_pCamera;			// �J�����̃|�C���^	
	static CLight *m_pLight;			// ���C�g�̃|�C���^
	static CPlayer2d *m_pPlayer2d;				// �v���C���[2D�̃|�C���^
	static CPlayer3d *m_pPlayer3d;		// �v���C���[3D�̃|�C���^
	static CMapManager *m_pMapManager;			// �}�b�v�}�l�[�W���[�̃|�C���^
	static CEvaluation *m_pEvaluation;  // �]��UI�N���X
	LPD3DXFONT m_pFont;					// �f�o�b�N�p�t�H���g
	int m_nTimeCounter;					// �Q�[���̃J�E���^�[
	bool m_bGameEnd;					// �Q�[���̃G���h�t���O
};
#endif