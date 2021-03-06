//=============================================================================
//
// プレイヤー2dクラス [player2d.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "time_limit.h"
#include "gauge.h"
#include "score.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define GAUGE_WIDGHT 800.0f
#define GAUGE_HEIGHT 10.0f
#define GAUGE_COLOR D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)
//#define GAUGE_COLOR D3DXCOLOR(1.0f,1.0f,0.0f,1.0f)
#define GAUGE_LEFT_POS D3DXVECTOR3((SCREEN_WIDTH/2) - GAUGE_WIDGHT / 2 ,150.0f,0.0f)

//=============================================================================
// クリエイト
//=============================================================================
CTimeLimit * CTimeLimit::Create(void)
{
	// 初期化処理
	CTimeLimit *pTimeLimit = new CTimeLimit;

	int nTimeRate = CScore::GetScorePointa()->GetScoreData().nScore;
	if (nTimeRate > 80)nTimeRate = 80;
	pTimeLimit->m_fTime = DEFAULT_TIME + ((25 - DEFAULT_TIME)*1/MAX_TIME_SCORE)* nTimeRate;
	pTimeLimit->m_fMaxTime = pTimeLimit->m_fTime;
	pTimeLimit->Init();

	return pTimeLimit;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CTimeLimit::CTimeLimit()
{
	m_fTime = 0.0f;
	m_fMaxTime = 0.0f;
	m_pGauge = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTimeLimit::~CTimeLimit()
{
	
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTimeLimit::Init(void)
{
	m_pGauge = CGauge::Create(&m_fTime, GAUGE_LEFT_POS, GAUGE_WIDGHT, GAUGE_HEIGHT, (int)m_fTime, GAUGE_COLOR);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTimeLimit::Uninit(void)
{
	delete this;
}

//=============================================================================
// 更新処理
//=============================================================================
bool CTimeLimit::Update(void)
{
	m_fTime--;
	if (m_fTime <= 0.0f)
	{
		m_fTime = 0.0f;
		return false;
	}
	return true;
}

//=============================================================================
// 描画処理
//=============================================================================
void CTimeLimit::Draw(void)
{

}

//=============================================================================
// 評価チェック
//=============================================================================
CEvaluation::EVALUATION_TYPE CTimeLimit::CheckEvaluation(void)
{
	// 割合の計算
	float fEvaluatin = m_fTime / m_fMaxTime;

	if (fEvaluatin >= 0.7f)
	{// パーフェクト
		return CEvaluation::EVALUATION_TYPE_PARFECT;
	}
	else if (fEvaluatin >= 0.4f)
	{// グレート
		return CEvaluation::EVALUATION_TYPE_GREAT;
	}

	// ナイス
	return CEvaluation::EVALUATION_TYPE_NICE;
}
