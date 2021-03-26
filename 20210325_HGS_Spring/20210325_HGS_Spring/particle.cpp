//=============================================================================
//
// �p�[�e�B�N���N���X����  [particle.cpp]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DEFAULT_SIZE D3DXVECTOR3(20.0f,20.0f,10.0f)

// ���S���̃p�[�e�B�N��
#define DEATH_PARTICLE_NUM 70              // �p�[�e�B�N��
#define DEATH_PARTICLE_SPEED_MIN 15        // �p�[�e�B�N���X�s�[�h �Œ�l
#define DEATH_PARTICLE_SPEED_AMPLITUDE 10  // �p�[�e�B�N���X�s�[�h �ӂ蕝
#define DEATH_PARTICLE_SPEED_RATE 0.98f    // �ړ��ʏ�Z�l
#define DEATH_PARTICLE_COLOR D3DXCOLOR(1.0f, (float)(rand() % 50) / 100.0f, (float)(rand() % 50) / 100.0f, (float)(rand()%20) / 10.0f) // �Ԃ��ۂ��F�����_��
#define DEATH_PARTICLE_LIFE 70                 // ����
#define DEATH_PARTICLE_ALPHA_MINUSVALU  2.0f / DEATH_PARTICLE_LIFE; // �A���t�@�l���Z�l
#define DEATH_PARTICLE_SIZE_MIN 10        // �p�[�e�B�N���X�s�[�h �Œ�l
#define DEATH_PARTICLE_SIZE_AMPLITUDE 10  // �p�[�e�B�N���X�s�[�h �ӂ蕝

void CParticlre::CreateDeath(D3DXVECTOR3 pos , DEATH_PART_TYPE type)
{

	for (int nCnt = 0; nCnt < DEATH_PARTICLE_NUM; nCnt++)
	{

		int nRandAngle = rand() % 180;
		// �����_���Ȉړ��ʂ̎擾
		// ����
		switch (type)
		{
		case DEATH_PART_TYPE_ALL:
			//Z
			nRandAngle = rand() % 360;
			break;
		case DEATH_PART_TYPE_UP:
			// ��ʏ�
			nRandAngle = rand() % 180;
			break;
		case DEATH_PART_TYPE_DOWN:
			// ��ʉ�
			nRandAngle = (rand() % 180) + 180;
			break;
		case DEATH_PART_TYPE_LEFT:
			// ��ʍ�
			nRandAngle = (rand() % 180) - 90;
			break;
		case DEATH_PART_TYPE_RIGHT:
			// ��ʉE
			nRandAngle = (rand() % 180) + 90;
			break;
		default:
			break;
		}

		D3DXVECTOR3 randMove;
		randMove.x = cosf(D3DXToRadian(nRandAngle));
		randMove.y = sinf(D3DXToRadian(nRandAngle));
		randMove.z = 0.0f;
		// ���x
		int nRandSpeed = rand() % DEATH_PARTICLE_SPEED_AMPLITUDE + DEATH_PARTICLE_SPEED_MIN;

		// �N���X����
		CParticlre *pParticlre = CParticlre::Create(pos, randMove * (float)nRandSpeed , DEATH_PARTICLE_LIFE);
		
		// �J���[�̐ݒ�
		pParticlre->SetColor(DEATH_PARTICLE_COLOR);
		pParticlre->SetCol(pParticlre->GetColor());

		// �T�C�Y�̐ݒ�
		int nRandSize = rand() % DEATH_PARTICLE_SPEED_AMPLITUDE + DEATH_PARTICLE_SPEED_MIN;
		pParticlre->SetSize(D3DXVECTOR3((float)nRandSize, (float)nRandSize, 0.0f));

		// �e�N�X�`�����蓖��
		CTexture *pTexture = GET_TEXTURE_PTR;
		pParticlre->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
	}
}

//=============================================================================
// �N���G�C�g
//=============================================================================
CParticlre * CParticlre::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move , int nLife)
{
	// ����������
	CParticlre *pParticlre = new CParticlre;

	// !nullcheck
	if (pParticlre != nullptr)
	{
		// ���W
		pParticlre->SetSceneInfo(pos, DEFAULT_SIZE);
		// �ړ���
		pParticlre->m_move = move;
		pParticlre->m_nLife = nLife;

		// ����������
		pParticlre->Init();
		// �p�x�����_��
		pParticlre->SetRotation(D3DXToRadian(rand() % 360));
	}

	return pParticlre;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CParticlre::CParticlre(PRIORITY Priority) :CScene2D(Priority)
{
	m_move = ZeroVector3; // �ړ���
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �J���[
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CParticlre::~CParticlre()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CParticlre::Init(void)
{
	// ����������
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CParticlre::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CParticlre::Update(void)
{
	// �ړ��ʂ̊Ǘ�
	ManageMoveValue();

	// �ړ�����
	GetPos() += m_move;

	// �i�X�A���t�@�l�����炷
	D3DXCOLOR col = GetColor();
	col.a -= DEATH_PARTICLE_ALPHA_MINUSVALU;
	// 0�ȉ��ɂȂ��������
	if (col.a < 0)
	{
		Uninit();
		return;
	}
	// �Z�b�g����\
	SetCol(col);

	// �����̏���
	m_nLife--;
	if (m_nLife < 0)
	{
		Uninit();
		return;
	}

	// ���_���W�̍X�V
	UpdateVertex();

	// �p�x���Z
	SetRotation(D3DXToRadian(1));

	// �e�N���X�̍X�V����
	CScene2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CParticlre::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//// ���Z����
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`�揈��
	CScene2D::Draw();

	// �ʏ퍇���ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void CParticlre::ManageMoveValue(void)
{
	m_move *= DEATH_PARTICLE_SPEED_RATE;

	D3DXVECTOR3 pos = GetPos();

	// ��ʒ[�̏���
	if (pos.x >= SCREEN_WIDTH || pos.x <= 0)
	{
		// �ړ��ʂ̔��]
		m_move.x *= -1;
		// �ړ��ʂ𔼕��ɂ���
		m_move *= 0.5f;
		GetPos() += m_move;
	}
	if (pos.y >= SCREEN_HEIGHT || pos.y <= 0)
	{
		// �ړ��ʂ̔��]
		m_move.y *= -1;
		// �ړ��ʂ𔼕��ɂ���
		m_move *= 0.5f;
		GetPos() += m_move;
	}
}
