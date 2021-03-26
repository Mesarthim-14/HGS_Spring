//=============================================================================
//
// �e�N�X�`���̊Ǘ��N���X [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));

	// �ʏ�e�N�X�`���̖��O�̐ݒ�
	m_aTexFileName =
	{
		{ "data/Texture/player.png" },
		{ "data/Texture/number_1.png" },
		{ "data/Texture/number_2.png" },
		{ "data/Texture/particle001.png" },	// �p�[�e�B�N��
		{ "data/Texture/Nice.png" },		// nice
		{ "data/Texture/Great.png" },		// great
		{ "data/Texture/Parfect.png" },		// parfect
		{ "data/Texture/game_BG.png" },		// �Q�[���w�i
		{ "data/Texture/Up_E.png" },		// ��
		{ "data/Texture/Up_J.png" },		// ��
		{ "data/Texture/Up_M.png" },		// ��
		{ "data/Texture/Down_E.png" },		// ��
		{ "data/Texture/Down_J.png" },		// ��
		{ "data/Texture/Down_M.png" },		// ��
		{ "data/Texture/Right_E.png" },		// �E
		{ "data/Texture/Right_J.png" },		// �E
		{ "data/Texture/Right_M.png" },		// �E
		{ "data/Texture/Left_E.png" },		// ��
		{ "data/Texture/Left_J.png" },		// ��
		{ "data/Texture/Left_M.png" },		// ��
		{ "data/Texture/Not_Up_E.png" },	// �ザ��Ȃ�
		{ "data/Texture/Not_Up_J.png" },	// �ザ��Ȃ�
		{ "data/Texture/Not_Up_M.png" },	// �ザ��Ȃ�
		{ "data/Texture/Not_Down_E.png" },	// ������Ȃ�
		{ "data/Texture/Not_Down_J.png" },	// ������Ȃ�
		{ "data/Texture/Not_Down_M.png" },	// ������Ȃ�
		{ "data/Texture/Not_Right_E.png" },	// �E����Ȃ�
		{ "data/Texture/Not_Right_J.png" },	// �E����Ȃ�
		{ "data/Texture/Not_Right_M.png" },	// �E����Ȃ�
		{ "data/Texture/Not_Left_E.png" },	// ������Ȃ�
		{ "data/Texture/Not_Left_J.png" },	// ������Ȃ�
		{ "data/Texture/Not_Left_M.png" },	// ������Ȃ�
		{ "data/Texture/tutorial.png" },	//
		{ "data/Texture/Title.png" },       // 
	}; 

	// �����e�N�X�`���̖��O�̐ݒ�
	m_aSparateTexFileName =
	{
		{ "data/Texture/U1.png" },				// ��
		{ "data/Texture/D1.png" },				// ��
		{ "data/Texture/R1.png" },				// �E
		{ "data/Texture/L1.png" },				// ��
		{ "data/Texture/N1.png" },				// �j���[�g����
	};
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
	// �ʏ�e�N�X�`���N���A
	m_aTexFileName.clear();

	// �����e�N�X�`���N���A
	m_aSparateTexFileName.clear();
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CTexture * CTexture::Create(void)
{
	// �������m��
	CTexture *pTexture = new CTexture;

	return pTexture;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < m_aTexFileName.size(); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[nCount].data(), &m_apTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CTexture::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != nullptr)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// �����e�N�X�`���̃��[�h
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �����e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < m_aSparateTexFileName.size(); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aSparateTexFileName.at(nCount).data(), &m_apSeparateTexture[nCount].pSeparateTexture);
	}

	return S_OK;
}

//=============================================================================
// �����e�N�X�`���̃A�����[�h
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// �e�N�X�`���̉��
	for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
	{
		if (m_apSeparateTexture[nCount].pSeparateTexture != nullptr)
		{
			m_apSeparateTexture[nCount].pSeparateTexture->Release();
			m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
		}
	}
}

//=============================================================================
// �e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE Tex_Num)
{
	if (Tex_Num < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[Tex_Num] != nullptr)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != nullptr)
		{
			// �e�N�X�`�����
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`���̏��
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}