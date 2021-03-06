//=======================================================================================
//
// シーン2Dクラス [scene2d.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "keyboard.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"

//=======================================================================================
// コンストラクタ
//=======================================================================================
CScene2D::CScene2D(PRIORITY Priority) : CSceneBase(Priority)
{
	m_nCountAnim = 0;								// アニメーションテクスチャ
	m_nCountAnimPattern = 0;						// アニメーションのパターン
	m_nCounterAnim= 0;								// アニメーションのカウンター
	m_nPatternAnim= 0;								// アニメーションのパターン数
	m_nSpeedTexture = 0;							// テクスチャの移動速度
	m_nLoop = -1;									// ループするかどうか
	m_fDivisionCounter = 0.0f;						// スクロールのカウンター
	m_fDivisionBaseNum = 0.0f;						// スクロールの移動量
	m_fRotasion = 0.0f;
	m_fScaleNum = 0.0f;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CScene2D::~CScene2D()
{

}

//=======================================================================================
// Sceneクラスの生成
//=======================================================================================
CScene2D* CScene2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// オブジェクトを生成
	CScene2D* pScene = new CScene2D;

	// !nullcheck
	if (pScene != nullptr)
	{
		pScene->SetSceneInfo(pos, size);

		// 初期化処理
		pScene->Init();
	}

	return pScene;
}

//=======================================================================================
// ポリゴンの初期化
//=======================================================================================
HRESULT CScene2D::Init(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;		// バッファ

	// 頂点バッファの生成
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点データをロックする
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 座標
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x -size.x, pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x +size.x, pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x -size.x, pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x +size.x, pos.y + size.y, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = WhiteColor;
	pVtx[1].col = WhiteColor;
	pVtx[2].col = WhiteColor;
	pVtx[3].col = WhiteColor;

	// 頂点データをアンロックする
	pVtxBuff->Unlock();

	// 頂点バッファの設定
	BindVtxBuff(pVtxBuff);

	return S_OK;
}

//=======================================================================================
// ポリゴンの終了処理
//=======================================================================================
void CScene2D::Uninit(void)
{
	// 削除フラグを持たせる
	Release();
}

//=======================================================================================
// ポリゴンの更新処理
//=======================================================================================
void CScene2D::Update(void)
{
	// アニメーションパターンが設定されていたら
	if (m_nPatternAnim != 0)
	{
		// アニメーションの更新
		UpdateAnimation();
	}
}

//=======================================================================================
// ポリゴンの描画処理
//=======================================================================================
void CScene2D::Draw(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//アルファテストを有効化
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//アルファテスト基準値の設定
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファテストの比較方法の設定(GREATERは基準値より大きい場合)
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pD3DDevice->SetTexture(0, GetTexture());

	// ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	//アルファテストを無効化
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// テクスチャの設定
	pD3DDevice->SetTexture(0, nullptr);
}


//======================================================
//色の取得
//======================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	// 色の設定
	SetColor(col);

	//頂点データ範囲をロックし、頂点バッファへのポインタを所得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定(0~255の数値で設定)
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r,g,b,aは0~255の範囲で決めること
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r:レッド g:グリーン　b:ブルー
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //aは、透明度を表している
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//頂点データをアンロック
	GetVtxBuff()->Unlock();
}

//=============================================
// アニメーション情報取得
//=============================================
void CScene2D::InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop)
{
	m_nCounterAnim = nCounterAnim;
	m_nPatternAnim = nPatternAnim;
	m_nLoop = nLoop;

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

	// 頂点バッファをアンロックする
	GetVtxBuff()->Unlock();
}

//=============================================
// アニメーション更新関数
//=============================================
void CScene2D::UpdateAnimation(void)
{
	// 爆発のアニメーションカウントを進めて、パターンを切り替える
	m_nCountAnim++;
	// 頂点情報(テクスチャ座標)の更新
	if (m_nCountAnim >= m_nCounterAnim)	// 爆発の速さ
	{
		// アニメーションのカウントを0にする
		m_nCountAnim = 0;

		// アニメーションのパターンをカウントさせる
		m_nCountAnimPattern++;
	}

	// アニメーションが終わったら
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		// 数値を戻しておく
		m_nCountAnimPattern = 0;

		if (m_nLoop == 0)
		{
			// 終了処理
			Uninit();
		}
	}
	else
	{
		// 頂点情報を設定
		VERTEX_2D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標を更新
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// 頂点バッファをアンロックする
		GetVtxBuff()->Unlock();
	}
}

//=============================================
// テクスチャのスクロール情報を取得
//=============================================
void CScene2D::InitScroll(int nSpeed, float fDivision)
{
	m_nSpeedTexture = nSpeed;
	m_fDivisionBaseNum = fDivision;
}

//=============================================
// テクスチャのスクロール情報を更新
//=============================================
void CScene2D::UpdateScroll(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// カウンターを進める
	m_nCounterAnim++;

	// 頂点情報(テクスチャ座標)の更新
	if (m_nCounterAnim >= m_nSpeedTexture)		// 爆発の速さ
	{
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標を更新
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - m_fDivisionCounter);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - m_fDivisionCounter);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - m_fDivisionCounter);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - m_fDivisionCounter);

		// 頂点バッファをアンロックする
		GetVtxBuff()->Unlock();

		// アニメーションのパターンをカウントさせる
		m_fDivisionCounter += m_fDivisionBaseNum;
		m_nCounterAnim = 0;
	}
}

//======================================================
// 拡大関数
//======================================================
void CScene2D::ScaleUp(float fScaleUp)
{
	// 情報取得
	D3DXVECTOR3 pos = GetPos();	// 座標
	D3DXVECTOR3 size = GetSize();	// 座標
	m_fScaleNum += fScaleUp;

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点データ範囲をロックし、頂点バッファへのポインタを所得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - (size.x * m_fScaleNum), pos.y - (size.y * m_fScaleNum), 0.0f);	
	pVtx[1].pos = D3DXVECTOR3(pos.x + (size.x * m_fScaleNum), pos.y - (size.y * m_fScaleNum), 0.0f);	
	pVtx[2].pos = D3DXVECTOR3(pos.x - (size.x * m_fScaleNum), pos.y + (size.y * m_fScaleNum), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (size.x * m_fScaleNum), pos.y + (size.y * m_fScaleNum), 0.0f);

	//頂点データをアンロック
	GetVtxBuff()->Unlock();
}

//======================================================
// 頂点座標の更新
//======================================================
void CScene2D::UpdateVertex(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// バッファ
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点データ範囲をロックし、頂点バッファへのポインタを所得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	//頂点データをアンロック
	pVtxBuff->Unlock();
}

//======================================================
// ローテーションの取得
//======================================================
void CScene2D::SetRotation(float rotasion)
{
	// 情報取得
	D3DXVECTOR3 pos = GetPos();	// 座標
	D3DXVECTOR3 size = GetSize();	// 座標

	// 回転の値を加算
	 m_fRotasion += rotasion;

	float r = sqrtf(powf(size.x , 2.0) + powf(size.y , 2.0));	//半径
	float fTheta = atan2(size.x , size.x );					//シータ

	float XAngle = r*cos(fTheta + m_fRotasion);	//Xの角度
	float YAngle = r*sin(fTheta + m_fRotasion);	//Yの角度

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点データ範囲をロックし、頂点バッファへのポインタを所得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r*cos(fTheta + D3DXToRadian(90) + m_fRotasion);
	YAngle = r*sin(fTheta + D3DXToRadian(90) + m_fRotasion);
	pVtx[1].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r*cos(fTheta + D3DXToRadian(-90) + m_fRotasion);
	YAngle = r*sin(fTheta + D3DXToRadian(-90) + m_fRotasion);
	pVtx[2].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r*cos(fTheta + D3DXToRadian(180) + m_fRotasion);
	YAngle = r*sin(fTheta + D3DXToRadian(180) + m_fRotasion);
	pVtx[3].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);

	//頂点データをアンロック
	GetVtxBuff()->Unlock();

}

//=============================================
// 拡大の値設定
//=============================================
void CScene2D::SetScale(const float &fScale)
{
	m_fScaleNum = fScale;
}