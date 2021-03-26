//=============================================================================
//
// パーティクルクラス処理  [particle.cpp]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define DEFAULT_SIZE D3DXVECTOR3(20.0f,20.0f,10.0f)

// 死亡時のパーティクル
#define DEATH_PARTICLE_NUM 70              // パーティクル
#define DEATH_PARTICLE_SPEED_MIN 15        // パーティクルスピード 最低値
#define DEATH_PARTICLE_SPEED_AMPLITUDE 10  // パーティクルスピード ふり幅
#define DEATH_PARTICLE_SPEED_RATE 0.98f    // 移動量乗算値
#define DEATH_PARTICLE_COLOR D3DXCOLOR(1.0f, (float)(rand() % 50) / 100.0f, (float)(rand() % 50) / 100.0f, (float)(rand()%20) / 10.0f) // 赤っぽい色ランダム
#define DEATH_PARTICLE_LIFE 70                 // 寿命
#define DEATH_PARTICLE_ALPHA_MINUSVALU  2.0f / DEATH_PARTICLE_LIFE; // アルファ値減算値
#define DEATH_PARTICLE_SIZE_MIN 10        // パーティクルスピード 最低値
#define DEATH_PARTICLE_SIZE_AMPLITUDE 10  // パーティクルスピード ふり幅

void CParticlre::CreateDeath(D3DXVECTOR3 pos , DEATH_PART_TYPE type)
{

	for (int nCnt = 0; nCnt < DEATH_PARTICLE_NUM; nCnt++)
	{

		int nRandAngle = rand() % 180;
		// ランダムな移動量の取得
		// 方向
		switch (type)
		{
		case DEATH_PART_TYPE_ALL:
			//Z
			nRandAngle = rand() % 360;
			break;
		case DEATH_PART_TYPE_UP:
			// 画面上
			nRandAngle = rand() % 180;
			break;
		case DEATH_PART_TYPE_DOWN:
			// 画面下
			nRandAngle = (rand() % 180) + 180;
			break;
		case DEATH_PART_TYPE_LEFT:
			// 画面左
			nRandAngle = (rand() % 180) - 90;
			break;
		case DEATH_PART_TYPE_RIGHT:
			// 画面右
			nRandAngle = (rand() % 180) + 90;
			break;
		default:
			break;
		}

		D3DXVECTOR3 randMove;
		randMove.x = cosf(D3DXToRadian(nRandAngle));
		randMove.y = sinf(D3DXToRadian(nRandAngle));
		randMove.z = 0.0f;
		// 速度
		int nRandSpeed = rand() % DEATH_PARTICLE_SPEED_AMPLITUDE + DEATH_PARTICLE_SPEED_MIN;

		// クラス生成
		CParticlre *pParticlre = CParticlre::Create(pos, randMove * (float)nRandSpeed , DEATH_PARTICLE_LIFE);
		
		// カラーの設定
		pParticlre->SetColor(DEATH_PARTICLE_COLOR);
		pParticlre->SetCol(pParticlre->GetColor());

		// サイズの設定
		int nRandSize = rand() % DEATH_PARTICLE_SPEED_AMPLITUDE + DEATH_PARTICLE_SPEED_MIN;
		pParticlre->SetSize(D3DXVECTOR3((float)nRandSize, (float)nRandSize, 0.0f));

		// テクスチャ割り当て
		CTexture *pTexture = GET_TEXTURE_PTR;
		pParticlre->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
	}
}

//=============================================================================
// クリエイト
//=============================================================================
CParticlre * CParticlre::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move , int nLife)
{
	// 初期化処理
	CParticlre *pParticlre = new CParticlre;

	// !nullcheck
	if (pParticlre != nullptr)
	{
		// 座標
		pParticlre->SetSceneInfo(pos, DEFAULT_SIZE);
		// 移動量
		pParticlre->m_move = move;
		pParticlre->m_nLife = nLife;

		// 初期化処理
		pParticlre->Init();
		// 角度ランダム
		pParticlre->SetRotation(D3DXToRadian(rand() % 360));
	}

	return pParticlre;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CParticlre::CParticlre(PRIORITY Priority) :CScene2D(Priority)
{
	m_move = ZeroVector3; // 移動量
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // カラー
}

//=============================================================================
// デストラクタ
//=============================================================================
CParticlre::~CParticlre()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CParticlre::Init(void)
{
	// 初期化処理
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CParticlre::Uninit(void)
{
	// 終了処理
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CParticlre::Update(void)
{
	// 移動量の管理
	ManageMoveValue();

	// 移動処理
	GetPos() += m_move;

	// 段々アルファ値を減らす
	D3DXCOLOR col = GetColor();
	col.a -= DEATH_PARTICLE_ALPHA_MINUSVALU;
	// 0以下になったら消す
	if (col.a < 0)
	{
		Uninit();
		return;
	}
	// セットから―
	SetCol(col);

	// 寿命の処理
	m_nLife--;
	if (m_nLife < 0)
	{
		Uninit();
		return;
	}

	// 頂点座標の更新
	UpdateVertex();

	// 角度加算
	SetRotation(D3DXToRadian(1));

	// 親クラスの更新処理
	CScene2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CParticlre::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//// 加算合成
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画処理
	CScene2D::Draw();

	// 通常合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void CParticlre::ManageMoveValue(void)
{
	m_move *= DEATH_PARTICLE_SPEED_RATE;

	D3DXVECTOR3 pos = GetPos();

	// 画面端の処理
	if (pos.x >= SCREEN_WIDTH || pos.x <= 0)
	{
		// 移動量の反転
		m_move.x *= -1;
		// 移動量を半分にする
		m_move *= 0.5f;
		GetPos() += m_move;
	}
	if (pos.y >= SCREEN_HEIGHT || pos.y <= 0)
	{
		// 移動量の反転
		m_move.y *= -1;
		// 移動量を半分にする
		m_move *= 0.5f;
		GetPos() += m_move;
	}
}
