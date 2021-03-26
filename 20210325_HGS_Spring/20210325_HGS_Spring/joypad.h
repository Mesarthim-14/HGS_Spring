//=============================================================================
//
// メイン処理 [inputcontroller.h]
// Author : Masuzawa Mirai
//
//=============================================================================
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "input.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_CONTROLLER_NUM		(1)		//コントローラーの接続最大数
#define CROSS_KEY_UP			(0)		//十字キー上
#define CROSS_KEY_TOP_RIGHT		(4500)	//十字キー右上
#define CROSS_KEY_RIGHT			(9000)	//十字キー右
#define CROSS_KEY_BOTTOM_RIGHT	(13500)	//十字キー右下
#define CROSS_KEY_DOWN			(18000)	//十字キー下
#define CROSS_KEY_BOTTOM_LEFT	(22500)	//十字キー左下
#define CROSS_KEY_LEFT			(27000)	//十字キー左
#define CROSS_KEY_TOP_LEFT		(31500)	//十字キー左上
#define JOYPAD_EFFECT_NUM 2

//=============================================================================
//ジョイスティッククラス
//=============================================================================
class CInputJoypad :public CInput
{
public:
	//=============================================================================
	//ジョイスティックのボタン用の列挙型定義
	//=============================================================================
	typedef enum
	{
		JOY_BUTTON_X = 0,		//Xボタン
		JOY_BUTTON_Y,			//Yボタン
		JOY_BUTTON_A,			//Aボタン
		JOY_BUTTON_B,			//Bボタン
		JOY_BUTTON_L_TRIGGER,	//Lトリガーボタン
		JOY_BUTTON_R_TRIGGER,	//Rトリガーボタン
		JOY_BUTTON_L_TRIGGER2,	//Lトリガーボタン2
		JOY_BUTTON_R_TRIGGER2,	//Rトリガーボタン2
		JOY_BUTTON_L3,			//Lボタン
		JOY_BUTTON_R3,			//Rボタン
		JOY_BUTTON_SELECT,		//SELECTボタン
		JOY_BUTTON_START,		//STARTボタン
		JOY_BUTTON_HOME,		//HOMEボタン
		JOY_BUTTON_MAX,			//最大ボタン数
	}JOY_BUTTON;

	//=============================================================================
	//ジョイスティック状態判別用の構造体定義
	//=============================================================================
	typedef struct
	{
		DIJOYSTATE	Old;		//パッドボタンの前回情報
		DIJOYSTATE	Press;		//パッドボタンのプレス情報
		DIJOYSTATE	Trigger;	//パッドボタンのトリガー情報
		DIJOYSTATE	Release;	//パッドボタンのリリース情報
	}JoyStickState;

	//=============================================================================
	//メンバ関数宣言
	//=============================================================================
	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void	Uninit(void);
	void	Update(void);

	bool GetJoyStickPress(int nButton);		//ジョイスティッククラスのプレス情報の取得
	bool GetJoyStickTrigger(int nButton);	//ジョイスティッククラスのトリガー情報の取得Z
	bool GetJoyStickReleas(int nButton);	//ジョイスティッククラスのリリース情報の取得

	bool GetPushCross(int nButtond);		//ジョイスティッククラスの十字キーが押された瞬間の判定処理
	bool GetPushRelease(int nButtond);		//ジョイスティッククラスの十字キーが離した瞬間の判定処理

	void SetVibration(int nNum);             // 振動セット処理 0* 大きい 1*小さい

	DIJOYSTATE	GetStick(void);			//ジョイスティッククラスのスティック情報の取得
	static BOOL CALLBACK DeviceFindCallBack(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
private:

	void CreateEffect(void); // 振動エフェクトの生成
							 //=============================================================================
							 //メンバ変数宣言
							 //=============================================================================
	static LPDIRECTINPUTDEVICE8 m_pJoyDevice;	          //ジョイスティックのデバイス情報
	JoyStickState				m_JoyState;		          //ジョイスティックの状態
	static LPDIRECTINPUTEFFECT  m_lpDIEffect[JOYPAD_EFFECT_NUM];             // エフェクト振動用
	static DWORD                m_dwNumForceFeedbackAxis[JOYPAD_EFFECT_NUM]; // 
};


#endif
