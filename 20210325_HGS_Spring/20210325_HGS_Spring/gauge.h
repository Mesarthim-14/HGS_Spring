//=============================================================================
//
// gauge�w�b�_ [gauge.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _GAUGE_H_
#define _GAUGE_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//�O���錾
//*****************************
class CPolygon;

//*****************************
// �}�N����`
//*****************************

//*****************************
//�N���X��`
//*****************************

//�Q�[�W�N���X
class CGauge : public CScene
{
public:

	//============
	// �񋓒�`
	//============
	// HP�o�[�̃p�[�c��
	typedef enum
	{
		BAR_WHILTE = 0, // �Q�[�W�w�i
		BAR_FRONT,      // �Q�[�W�{��
		BAR_PARTS_MAX,  // �p�[�c�̍ő吔
	}BAR_PARTS;

	//============
	// �����o�֐�
	//============

	CGauge();
	~CGauge();

	// static
	static CGauge *Create(float* pData, D3DXVECTOR3 leftPos, float fBarWidht, float m_fBarHeight,
		int m_nMaxNum, D3DXCOLOR frontCol); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;   // �e�N�X�`���ւ̃|�C���^
	CPolygon*   m_apPolygon[BAR_PARTS_MAX]; // ���C�t�`��p�̃|���S��
	D3DXVECTOR3 m_leftPos;                  // �Q�[�W�̍��[
	float       m_fBarWidht;                // ��
	float       m_fBarHeight;               // ����
	int         m_nMaxNum;                  // �Q�[�W�������l�̍ő吔
	float *     m_pData;                    // �Q�[�W�ƕR�Â��鐔�l�̃|�C���^
	D3DXCOLOR   m_frontCol;                 // �t�����g�̃J���[
};

#endif