#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// �e�N�X�`���̊Ǘ��w�b�_�[ [texture.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
//�N���X�錾
//=============================================================================
class CTexture
{
public:
	// �e�N�X�`���̔ԍ��̗񋓌^
	typedef enum
	{
		TEXTURE_NUM_NONE = -1,		// �����l
		TEXTURE_NUM_PLAYER_2D,		// 2D�v���C���[
		TEXTURE_NUM_NUMBER_1_2D,	// �����P
		TEXTURE_NUM_NUMBER_2_2D,	// �����Q
		TEXTURE_NUM_PARTICLE,		// �p�[�e�B�N��
		TEXTURE_NUM_NICE,
		TEXTURE_NUM_GREAT,
		TEXTURE_NUM_PARFECT,
		TEXTURE_NUM_GAME_BG,		// �Q�[���w�i
		TEXTURE_NUM_UP_E,			// ��
		TEXTURE_NUM_UP_J,			// ��
		TEXTURE_NUM_UP_M,			// ��
		TEXTURE_NUM_DOWN_E,			// ��
		TEXTURE_NUM_DOWN_J,			// ��
		TEXTURE_NUM_DOWN_M,			// ��
		TEXTURE_NUM_RIGHT_E,		// �E
		TEXTURE_NUM_RIGHT_J,		// �E
		TEXTURE_NUM_RIGHT_M,		// �E
		TEXTURE_NUM_LEFT_E,			// ��
		TEXTURE_NUM_LEFT_J,			// ��
		TEXTURE_NUM_LEFT_M,			// ��
		TEXTURE_NUM_NOT_UP_E,		// �ザ��Ȃ�
		TEXTURE_NUM_NOT_UP_J,		// �ザ��Ȃ�
		TEXTURE_NUM_NOT_UP_M,		// �ザ��Ȃ�
		TEXTURE_NUM_NOT_DOWN_E,		// ������Ȃ�
		TEXTURE_NUM_NOT_DOWN_J,		// ������Ȃ�
		TEXTURE_NUM_NOT_DOWN_M,		// ������Ȃ�
		TEXTURE_NUM_NOT_RIGHT_E,	// �E����Ȃ�
		TEXTURE_NUM_NOT_RIGHT_J,	// �E����Ȃ�
		TEXTURE_NUM_NOT_RIGHT_M,	// �E����Ȃ�
		TEXTURE_NUM_NOT_LEFT_E,		// ������Ȃ�
		TEXTURE_NUM_NOT_LEFT_J,		// ������Ȃ�
		TEXTURE_NUM_NOT_LEFT_M,		// ������Ȃ�
		TEXTURE_NUM_TUTOTIRAL,		// ������Ȃ�
		TEXTURE_NUM_MAX
	}TEXTURE_TYPE;

	// �A�j���[�V�������s���e�N�X�`���̗񋓌^
	typedef enum
	{
		SEPARATE_TEX_NONE = -1,			// �����l
		SEPARATE_TEX_PLAYER_UP,			// ��
		SEPARATE_TEX_PLAYER_DOWN,		// ��
		SEPARATE_TEX_PLAYER_RIGHT,		// �E
		SEPARATE_TEX_PLAYER_LEFT,		// ��
		SEPARATE_TEX_PLAYER_NEUTRAL,	// �j���[�g����
		SEPARATE_TEX_MAX				// �ő�l
	}SEPARATE_TEX_TYPE;

	// �A�j���[�V�������s���e�N�X�`���̍\���̏��
	typedef struct
	{
		LPDIRECT3DTEXTURE9 pSeparateTexture;		// �����e�N�X�`���ւ̃|�C���^
		SEPARATE_TEX_TYPE type;						// �e�N�X�`���̎��
		D3DXVECTOR2 m_TexInfo;						// �e�N�X�`���̕������A����
		bool bLoop;									// ���[�v���邩
	}SEPARATE_TEX_INFO;

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	static CTexture *Create(void);												// �C���X�^���X����

	 HRESULT Load(void);														// �e�N�X�`�����[�h
	 void UnLoad(void);															// �e�N�X�`���A�����[�h
	 HRESULT SeparateTexLoad(void);												// �����e�N�X�`�����[�h
	 void SeparateTexUnLoad(void);												// �����e�N�X�`���A�����[�h

	 LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);						// �e�N�X�`���̏��

	 LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type);		// �����e�N�X�`�����
	 D3DXVECTOR2 GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type);				// �����e�N�X�`���@UV�̖����擾
	 bool GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type);					// ���[�v���邩
private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];							// �e�N�X�`���̃|�C���^
	std::vector<std::string> m_aTexFileName;									// �ʏ�e�N�X�`���̃t�@�C����

	// �����e�N�X�`���p�ϐ�
	std::vector<std::string> m_aSparateTexFileName;								// �����e�N�X�`���̃t�@�C����

	// �����e�N�X�`���̍\����
	SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
	{
		nullptr, SEPARATE_TEX_PLAYER_UP, D3DXVECTOR2(2, 16), true,		 // ��
		nullptr, SEPARATE_TEX_PLAYER_DOWN, D3DXVECTOR2(2, 16), true,		 // ��
		nullptr, SEPARATE_TEX_PLAYER_RIGHT, D3DXVECTOR2(2, 16), true,		 // �E
		nullptr, SEPARATE_TEX_PLAYER_LEFT, D3DXVECTOR2(2, 16), true,		 // ��
		nullptr, SEPARATE_TEX_PLAYER_NEUTRAL, D3DXVECTOR2(2, 16), true,	 // �j���[�g����
	};
	// �����e�N�X�`���̃|�C���^
};
#endif
