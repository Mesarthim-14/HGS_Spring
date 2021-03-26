//=============================================================================
//
// テクスチャの管理クラス [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));

	// 通常テクスチャの名前の設定
	m_aTexFileName =
	{
		{ "data/Texture/player.png" },
		{ "data/Texture/number_1.png" },
		{ "data/Texture/number_2.png" },
		{ "data/Texture/particle001.png" },	// パーティクル
		{ "data/Texture/Nice.png" },		// nice
		{ "data/Texture/Great.png" },		// great
		{ "data/Texture/Parfect.png" },		// parfect
		{ "data/Texture/game_BG.png" },		// ゲーム背景
		{ "data/Texture/Up_E.png" },		// 上
		{ "data/Texture/Up_J.png" },		// 上
		{ "data/Texture/Up_M.png" },		// 上
		{ "data/Texture/Down_E.png" },		// 下
		{ "data/Texture/Down_J.png" },		// 下
		{ "data/Texture/Down_M.png" },		// 下
		{ "data/Texture/Right_E.png" },		// 右
		{ "data/Texture/Right_J.png" },		// 右
		{ "data/Texture/Right_M.png" },		// 右
		{ "data/Texture/Left_E.png" },		// 左
		{ "data/Texture/Left_J.png" },		// 左
		{ "data/Texture/Left_M.png" },		// 左
		{ "data/Texture/Not_Up_E.png" },	// 上じゃない
		{ "data/Texture/Not_Up_J.png" },	// 上じゃない
		{ "data/Texture/Not_Up_M.png" },	// 上じゃない
		{ "data/Texture/Not_Down_E.png" },	// 下じゃない
		{ "data/Texture/Not_Down_J.png" },	// 下じゃない
		{ "data/Texture/Not_Down_M.png" },	// 下じゃない
		{ "data/Texture/Not_Right_E.png" },	// 右じゃない
		{ "data/Texture/Not_Right_J.png" },	// 右じゃない
		{ "data/Texture/Not_Right_M.png" },	// 右じゃない
		{ "data/Texture/Not_Left_E.png" },	// 左じゃない
		{ "data/Texture/Not_Left_J.png" },	// 左じゃない
		{ "data/Texture/Not_Left_M.png" },	// 左じゃない
		{ "data/Texture/tutorial.png" },	//
		{ "data/Texture/Title.png" },       // 
	}; 

	// 分割テクスチャの名前の設定
	m_aSparateTexFileName =
	{
		{ "data/Texture/U1.png" },				// 上
		{ "data/Texture/D1.png" },				// 下
		{ "data/Texture/R1.png" },				// 右
		{ "data/Texture/L1.png" },				// 左
		{ "data/Texture/N1.png" },				// ニュートラル
	};
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
	// 通常テクスチャクリア
	m_aTexFileName.clear();

	// 分割テクスチャクリア
	m_aSparateTexFileName.clear();
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTexture * CTexture::Create(void)
{
	// メモリ確保
	CTexture *pTexture = new CTexture;

	return pTexture;
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CTexture::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	for (size_t nCount = 0; nCount < m_aTexFileName.size(); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[nCount].data(), &m_apTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
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
// 分割テクスチャのロード
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 分割テクスチャの読み込み
	for (size_t nCount = 0; nCount < m_aSparateTexFileName.size(); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aSparateTexFileName.at(nCount).data(), &m_apSeparateTexture[nCount].pSeparateTexture);
	}

	return S_OK;
}

//=============================================================================
// 分割テクスチャのアンロード
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// テクスチャの解放
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
// テクスチャ情報
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
// 分割テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != nullptr)
		{
			// テクスチャ情報
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// 分割テクスチャの情報
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}