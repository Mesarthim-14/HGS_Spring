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
		TEXTURE_NUM_PARTICLE,		// パーティクル
		TEXTURE_NUM_NICE,
		TEXTURE_NUM_GREAT,
		TEXTURE_NUM_PARFECT,
		TEXTURE_NUM_GAME_BG,		// ゲーム背景
		TEXTURE_NUM_UP_E,			// 上
		TEXTURE_NUM_UP_J,			// 上
		TEXTURE_NUM_UP_M,			// 上
		TEXTURE_NUM_DOWN_E,			// 下
		TEXTURE_NUM_DOWN_J,			// 下
		TEXTURE_NUM_DOWN_M,			// 下
		TEXTURE_NUM_RIGHT_E,		// 右
		TEXTURE_NUM_RIGHT_J,		// 右
		TEXTURE_NUM_RIGHT_M,		// 右
		TEXTURE_NUM_LEFT_E,			// 左
		TEXTURE_NUM_LEFT_J,			// 左
		TEXTURE_NUM_LEFT_M,			// 左
		TEXTURE_NUM_NOT_UP_E,		// 上じゃない
		TEXTURE_NUM_NOT_UP_J,		// 上じゃない
		TEXTURE_NUM_NOT_UP_M,		// 上じゃない
		TEXTURE_NUM_NOT_DOWN_E,		// 下じゃない
		TEXTURE_NUM_NOT_DOWN_J,		// 下じゃない
		TEXTURE_NUM_NOT_DOWN_M,		// 下じゃない
		TEXTURE_NUM_NOT_RIGHT_E,	// 右じゃない
		TEXTURE_NUM_NOT_RIGHT_J,	// 右じゃない
		TEXTURE_NUM_NOT_RIGHT_M,	// 右じゃない
		TEXTURE_NUM_NOT_LEFT_E,		// 左じゃない
		TEXTURE_NUM_NOT_LEFT_J,		// 左じゃない
		TEXTURE_NUM_NOT_LEFT_M,		// 左じゃない
		TEXTURE_NUM_TUTOTIRAL,		// 左じゃない
		TEXTURE_NUM_MAX
	}TEXTURE_TYPE;

	// アニメーションを行うテクスチャの列挙型
	typedef enum
	{
		SEPARATE_TEX_NONE = -1,			// 初期値
		SEPARATE_TEX_PLAYER_UP,			// 上
		SEPARATE_TEX_PLAYER_DOWN,		// 下
		SEPARATE_TEX_PLAYER_RIGHT,		// 右
		SEPARATE_TEX_PLAYER_LEFT,		// 左
		SEPARATE_TEX_PLAYER_NEUTRAL,	// ニュートラル
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
		nullptr, SEPARATE_TEX_PLAYER_UP, D3DXVECTOR2(2, 16), true,		 // 上
		nullptr, SEPARATE_TEX_PLAYER_DOWN, D3DXVECTOR2(2, 16), true,		 // 下
		nullptr, SEPARATE_TEX_PLAYER_RIGHT, D3DXVECTOR2(2, 16), true,		 // 右
		nullptr, SEPARATE_TEX_PLAYER_LEFT, D3DXVECTOR2(2, 16), true,		 // 左
		nullptr, SEPARATE_TEX_PLAYER_NEUTRAL, D3DXVECTOR2(2, 16), true,	 // ニュートラル
	};
	// 分割テクスチャのポインタ
};
#endif
