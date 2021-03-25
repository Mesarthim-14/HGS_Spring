#ifndef _CHARACTER_3D_H_
#define _CHARACTER_3D_H_
//=============================================================================
//
// キャラクター処理  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"
#include "character.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_CHARACTER_PARTS (22)	// キャラクターのパーツ数
#define MAX_KEYFRAME		(10)	// キーフレームの最大数

//=============================================================================
// 前方宣言
//=============================================================================
class CMotion;

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CCharacter3d : public CScene, public CCharacter
{
public:
	CCharacter3d(PRIORITY Priority = PRIORITY_CHARACTER);				// コンストラクタ
	virtual ~CCharacter3d();											// デストラクタ

	virtual HRESULT Init(void);			// 初期化処理
	virtual void Uninit();											// 終了処理
	virtual void Update();											// 更新処理
	virtual void Draw();											// 描画処理

	void ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum);			// モデルの生成
	void ModelAnimeUpdate(void);									// モデルアニメーション

	// 純粋仮想関数
	virtual void UpdateMotionState(void) = 0;						// モーションの状態

	// Set関数
	void SetPos(D3DXVECTOR3 pos);									// 座標の設定
	void SetRot(D3DXVECTOR3 rot);									// 角度の設定
	void SetMotion(int nMotion);									// モーションの設定 
	void SetStateCounter(int nStateCounter);						// 状態カウンターの設定

	// Get関数
	D3DXVECTOR3 GetPos(void)				{ return m_pos; }						// 現在の座標情報
	D3DXVECTOR3 GetRot(void)				{ return m_rot; }						// 角度情報
	int GetStateCounter(void)				{ return m_nStateCounter; }				// 状態カウンターの情報
	CModelAnime *GetModelAnime(int nCount)	{ return m_apModelAnime[nCount]; }		// モーションのカウント情報
	CMotion *GetMotion(void)				{ return m_pMotion; }					// モーションのポインタ情報

private:
	CModelAnime *m_apModelAnime[MAX_MODEL_PARTS];	// モデルパーツ用のポインタ
	CMotion *m_pMotion;								// モーションクラスのポインタ
	D3DXVECTOR3 m_pos;				// 座標
	D3DXVECTOR3 m_rot;				// 現在の回転
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
	int m_nStateCounter;			// 状態のカウンター
	int m_nParts;					// パーツ数
	float m_fAngle;					// 角度
};
#endif