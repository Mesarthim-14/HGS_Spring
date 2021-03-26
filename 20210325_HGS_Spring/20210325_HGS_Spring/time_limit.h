#ifndef _TIME_LIMIT_H_
#define _TIME_LIMIT_H_
//=============================================================================
//
// 制限時間 [time_limit.h]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CGauge;

//=============================================================================
// プレイヤー2Dクラス
//=============================================================================
class CTimeLimit
{
public:
	// スコアタイプ列挙
	typedef enum
	{
		EVALUATION_TYPE_NICE = 0,
		EVALUATION_TYPE_GREAT,
		EVALUATION_TYPE_PARFECT,
		EVALUATION_TYPE_MAX
	}EVALUATION_TYPE;

	CTimeLimit();			// コンストラクタ
	~CTimeLimit();												// デストラクタ

	static CTimeLimit*Create(float fTime);	// クリエイト

	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	bool Update(void);				// 更新処理*返り値*制限時間いないか
	void Draw(void);				// 描画処理
	
	EVALUATION_TYPE CheckEvaluation(void); // 評価のチェック
private:
	float m_fTime;     // 時間
	float m_fMaxTime;  // 最大時間
	CGauge * m_pGauge; // ゲージクラス
};
#endif