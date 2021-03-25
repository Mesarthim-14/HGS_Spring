//=============================================================================
//
// �L�����N�^�[�N���X [character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character3d.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "game.h"
#include "player3d.h"
#include "texture.h"
#include "sound.h"
#include "resource_manager.h"
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GRAVITY_POWAR			(0.7f)						// �d�͂̋���
#define GROUND_RIMIT			(0.0f)						// �n�ʂ̐���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacter3d::CCharacter3d(PRIORITY Priority) : CScene(Priority)
{
	 m_pos = ZeroVector3;
	 m_rot = ZeroVector3;
	 m_fAngle = 0.0f;
	 memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	 m_nStateCounter = 0;
	 m_pMotion = nullptr;
	 m_nParts = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacter3d::~CCharacter3d()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCharacter3d::Init(void)
{

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCharacter3d::Uninit()
{
	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		// !nullcheck
		if (m_apModelAnime[nCntModelNum] != nullptr)
		{
			//�������̍폜
			delete m_apModelAnime[nCntModelNum];

			//�������̃N���A
			m_apModelAnime[nCntModelNum] = nullptr;
		}
	}

	// !nullcheck
	if (m_pMotion != nullptr)
	{
		//�������̍폜
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCharacter3d::Update()
{
	//�A�j���[�V�����̍X�V����
	ModelAnimeUpdate();

	// �ړ��ʉ��Z
	m_pos += GetMove();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCharacter3d::Draw()
{
	// �`�揈��
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// ���ʂ��i�����j���J�����O

	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != nullptr)
		{
			//�K�w���f���N���X�̕`�揈��
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// ���ʂ��i�����j���J�����O
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CCharacter3d::ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum)
{
	// XFile�̃|�C���^�擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f���p�[�c�̐ݒ�
		m_nParts = pXfile->GetModelParts(FileNum);

		//���f���p�[�c�����J��Ԃ�
		for (int nCntModel = 0; nCntModel < m_nParts; nCntModel++)
		{
			CXfile::MODELFILE ModelFile = pXfile->GetModelFile(nCntModel, FileNum);

			if (m_apModelAnime[nCntModel] == nullptr)
			{
				// ����������
				m_apModelAnime[nCntModel] = CModelAnime::Create(ModelFile.offsetPos, ModelFile.offsetRot);

				// ���f���̏��擾
				std::vector<CXfile::MODEL> model = pXfile->GetHierarchyXfile(FileNum);

				// ���f���̐���
				m_apModelAnime[nCntModel]->SetModel(model.at(nCntModel));
			}

			//�e�q�\���̐ݒ�
			if (m_apModelAnime[nCntModel] != nullptr)
			{
				//�e���f���̏ꍇ
				if (nCntModel == 0)
				{
					m_apModelAnime[nCntModel]->SetParent(nullptr);
				}
				//�q���f���̏ꍇ
				else
				{
					//�����̐e����ݒ肷��
					m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[ModelFile.nParent]);
				}
			}
		}

		// nullcheck
		if (m_pMotion == nullptr)
		{
			// �C���X�^���X����
			m_pMotion = CMotion::Create(pXfile->GetModelFileName(FileNum));
		}
	}
}

//=============================================================================
// ���f���A�j���[�V����
//=============================================================================
void CCharacter3d::ModelAnimeUpdate(void)
{
	// ���[�V�����̍X�V����
	if (m_pMotion != nullptr)
	{
		// ���[�V�����̍X�V
		m_pMotion->UpdateMotion(m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// ���[�V�����̐ݒ�
//=============================================================================
void CCharacter3d::SetMotion(int nMotionState)
{
	// !nullcheck
	if (m_pMotion != nullptr)
	{
		// ���[�V�����̍X�V
		m_pMotion->SetMotion(nMotionState, m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// ���W�̐ݒ�
//=============================================================================
void CCharacter3d::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �p�x�̐ݒ�
//=============================================================================
void CCharacter3d::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// ��ԃJ�E���^�[�̐ݒ�
//=============================================================================
void CCharacter3d::SetStateCounter(int nStateCounter)
{
	m_nStateCounter = nStateCounter;
}