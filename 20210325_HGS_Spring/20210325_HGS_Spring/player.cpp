//=============================================================================
//
// プレイヤークラスヘッダー [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	m_bArmor = false;
	m_state = PLAYER_STATE_NONE;
}