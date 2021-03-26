#ifndef _SCROLL_POLYGON_H_
#define _SCROLL_POLYGON_H_
//=======================================================================================
// 
// �X�N���[���|���S���N���X���� [scroll_polygon.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "scene2d.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define SCROLL_FRAME	(30)		// �ړ�����t���[����

//=======================================================================================
// �X�N���[���|���S���N���X��`
//=======================================================================================
class CScrollPolygon: public CScene2D
{
public:
	// �����̎�ނ̗񋓌^
	enum DIRECTION_TYPE
	{
		DIRECTION_TYPE_NONE = -1,	// �����l
		DIRECTION_TYPE_UP,			// ��
		DIRECTION_TYPE_DOWN,		// ��
		DIRECTION_TYPE_RIGHT,		// �E
		DIRECTION_TYPE_LEFT,		// ��
		DIRECTION_TYPE_MAX			// �ő�l
	};

	// �X�N���[�����̍\����
	struct SCROLL_INFO
	{

		DIRECTION_TYPE Direcsion;
		bool bFlag;
	};

	CScrollPolygon(PRIORITY Priority = PRIORITY_0);	// �R���X�g���N�^
	~CScrollPolygon();								// �f�X�g���N�^

	static CScrollPolygon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, SCROLL_INFO ScrollInfo);			// �C���X�^���X����
	HRESULT Init(void);						// ����������
	void Update(void);						// �X�V����

	// Set�֐�
	void SetSecondMove(bool bSecondMove, D3DXVECTOR3 move);

	// Get�֐�
	bool GetEnd(void)				{ return m_bEnd ; }	// �I���t���O
	SCROLL_INFO GetScrollInfo(void) { return m_ScrollInfo; }
	bool GetStop(void)				{ return m_bStop; }
private:
	int m_nCounter;						// �J�E���^�[
	SCROLL_INFO m_ScrollInfo;			// �X�N���[�����
	D3DXVECTOR3 m_move;					// �ړ���
	bool m_bSecondMove;					// ��x�ڂ̈ړ�
	bool m_bEnd;						// �I���t���O
	bool m_bStop;						// �~�܂����t���O
};

#endif