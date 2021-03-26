#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// テクスチャの管理ヘッダー [texture.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
//クラス宣言
//=============================================================================
class CTexture
{
public:
	// テクスチャの番号の列挙型
	typedef enum
	{
		TEXTURE_NUM_NONE = -1,		// 初期値
		TEXTURE_NUM_PLAYER_2D,		// 2Dプレイヤー
		TEXTURE_NUM_NUMBER_1_2D,	// 数字１
		TEXTURE_NUM_NUMBER_2_2D,	// 数字２
		TEXTURE_NUM_PLAYER_2D,		// 2Dプレイヤー
		TEXTURE_NUM_PARTICLE,		// パーティクル
		TEXTURE_NUM_MAX
	}TEXTURE_TYPE;

	// アニメーションを行うテクスチャの列挙型
	typedef enum
	{
		SEPARATE_TEX_NONE = -1,			// 初期値
		SEPARATE_TEX_SHARP,				// 鋭いエフェクト
		SEPARATE_TEX_MAX				// 最大値
	}SEPARATE_TEX_TYPE;

	// アニメーションを行うテクスチャの構造体情報
	typedef struct
	{
		LPDIRECT3DTEXTURE9 pSeparateTexture;		// 分割テクスチャへのポインタ
		SEPARATE_TEX_TYPE type;						// テクスチャの種類
		D3DXVECTOR2 m_TexInfo;						// テクスチャの分割数、速さ
		bool bLoop;									// ループするか
	}SEPARATE_TEX_INFO;

	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

	static CTexture *Create(void);												// インスタンス生成

	 HRESULT Load(void);														// テクスチャロード
	 void UnLoad(void);															// テクスチャアンロード
	 HRESULT SeparateTexLoad(void);												// 分割テクスチャロード
	 void SeparateTexUnLoad(void);												// 分割テクスチャアンロード

	 LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);						// テクスチャの情報

	 LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type);		// 分割テクスチャ情報
	 D3DXVECTOR2 GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type);				// 分割テクスチャ　UVの枚数取得
	 bool GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type);					// ループするか
private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];							// テクスチャのポインタ
	std::vector<std::string> m_aTexFileName;									// 通常テクスチャのファイル名

	// 分割テクスチャ用変数
	std::vector<std::string> m_aSparateTexFileName;								// 分割テクスチャのファイル名

	// 分割テクスチャの構造体
	SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
	{
		nullptr, CTexture::SEPARATE_TEX_SHARP, D3DXVECTOR2(5, 5), false,
	};
	// 分割テクスチャのポインタ
};
#endif
