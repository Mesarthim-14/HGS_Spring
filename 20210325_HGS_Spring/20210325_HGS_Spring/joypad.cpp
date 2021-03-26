//=============================================================================
//
// メイン処理 [inputcontroller.cpp]
// Author : Masuzawa Mirai
//
//=============================================================================
#include "joypad.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAN_RANGE 1000	//スティックの最大範囲
#define MIN_RANGE -1000	//スティックの最小範囲

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
LPDIRECTINPUTDEVICE8 CInputJoypad::m_pJoyDevice = NULL;
LPDIRECTINPUTEFFECT  CInputJoypad::m_lpDIEffect[JOYPAD_EFFECT_NUM] = {};             // エフェクト振動用
DWORD                CInputJoypad::m_dwNumForceFeedbackAxis[JOYPAD_EFFECT_NUM] = {}; // 

//=============================================================================
//ジョイスティッククラスのコンストラクタ
//=============================================================================
CInputJoypad::CInputJoypad()
{
	memset(&m_JoyState, 0, sizeof(m_JoyState));
}

//=============================================================================
//ジョイスティッククラスのデストラクタ
//=============================================================================
CInputJoypad::~CInputJoypad()
{
}

//=============================================================================
//ジョイスティッククラスの初期化処理
//=============================================================================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//入力処理の初期化
	CInput::Init(hInstance, hWnd);

	//ジョイスティックの列挙
	if (FAILED(m_pInput->EnumDevices(
		DI8DEVCLASS_GAMECTRL,	//列挙したいデバイスの種類
		DeviceFindCallBack,		//デバイスが列挙した際に実行される関数ポインタ(コールバック関数)
		NULL,					//第二引数実行時に引数として渡されるデータのポインタ
		DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY)))	//取得するデバイスを限定するかどうかのフラグ
	{
		return E_FAIL;
	}
	if (m_pJoyDevice == NULL)
	{
		//ジョイスティックの列挙
		if (FAILED(m_pInput->EnumDevices(
			DI8DEVCLASS_GAMECTRL,	//列挙したいデバイスの種類
			DeviceFindCallBack,		//デバイスが列挙した際に実行される関数ポインタ(コールバック関数)
			NULL,					//第二引数実行時に引数として渡されるデータのポインタ
			DIEDFL_ATTACHEDONLY)))	//取得するデバイスを限定するかどうかのフラグ
		{
			return E_FAIL;
		}

		//ジョイスティックが見つからなかった場合
		if (!m_pJoyDevice)
		{
			return E_FAIL;
		}

		if (m_pJoyDevice != NULL)
		{ // 振動なしコントローラー
		  //データフォーマットの設定
			if (FAILED(m_pJoyDevice->SetDataFormat(&c_dfDIJoystick)))
			{
				m_pJoyDevice->Release();
				return DIENUM_STOP;
			}

			//協調モードの設定
			if (FAILED(m_pJoyDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
			{
				m_pJoyDevice->Release();
				return DIENUM_STOP;
			}

			//入力範囲の設定
			DIPROPRANGE diprg;
			diprg.diph.dwSize = sizeof(diprg);	//ヘッダが保持している構造体のサイズ
			diprg.diph.dwHeaderSize = sizeof(diprg.diph);	//DIPROPHEADER構造体サイズ
			diprg.diph.dwHow = DIPH_BYOFFSET;	//オブジェクトの解釈方法
			diprg.lMax = MAN_RANGE;	//軸の値の最大範囲
			diprg.lMin = MIN_RANGE;	//軸の値の最小範囲

			//X軸の設定
			diprg.diph.dwObj = DIJOFS_X;
			m_pJoyDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

			//Y軸の設定
			diprg.diph.dwObj = DIJOFS_Y;
			m_pJoyDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

			//Z軸の設定
			diprg.diph.dwObj = DIJOFS_Z;
			m_pJoyDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

			//RX軸の設定
			diprg.diph.dwObj = DIJOFS_RX;
			m_pJoyDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

			//RY軸の設定
			diprg.diph.dwObj = DIJOFS_RY;
			m_pJoyDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

			//RZ軸の設定
			diprg.diph.dwObj = DIJOFS_RZ;
			m_pJoyDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

			//起動準備完了
			m_pJoyDevice->Poll();

			//制御開始
			if (m_pJoyDevice == NULL)
			{
				Uninit();
			}

			m_pJoyDevice->Acquire();

		}
	}
	else
	{ // 振動ありコントローラー
	  //データフォーマットの設定
		if (FAILED(m_pJoyDevice->SetDataFormat(&c_dfDIJoystick)))
		{
			m_pJoyDevice->Release();
			return DIENUM_STOP;
		}

		//協調モードの設定
		if (FAILED(m_pJoyDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		{
			m_pJoyDevice->Release();
			return DIENUM_STOP;
		}

		// 
		if (FAILED(m_pJoyDevice->EnumObjects(EnumAxesCallback, (VOID*)&m_dwNumForceFeedbackAxis[0], DIDFT_AXIS)))
		{
			m_pJoyDevice->Release();
			return DIENUM_STOP;
		}
		if (FAILED(m_pJoyDevice->EnumObjects(EnumAxesCallback, (VOID*)&m_dwNumForceFeedbackAxis[1], DIDFT_AXIS)))
		{
			m_pJoyDevice->Release();
			return DIENUM_STOP;
		}

		// 振動エフェクトの生成
		CreateEffect();
	}

	return S_OK;
}

//=============================================================================
//ジョイスティッククラスの終了処理
//=============================================================================
void CInputJoypad::Uninit(void)
{
	// 振動エフェクト
	for (int nCnt = 0; nCnt < JOYPAD_EFFECT_NUM; nCnt++)
	{
		if (m_lpDIEffect[nCnt] != NULL)
		{
			m_lpDIEffect[nCnt]->Release();
			m_lpDIEffect[nCnt] = NULL;
		}
	}

	//デバイス制御の停止
	if (m_pJoyDevice != NULL)
	{
		m_pJoyDevice->Unacquire();
		m_pJoyDevice->Release();
		m_pJoyDevice = NULL;
	}

	CInput::Uninit();
}

//=============================================================================
//ジョイスティッククラスの更新処理
//=============================================================================
void CInputJoypad::Update(void)
{
	DIJOYSTATE js;
	SecureZeroMemory(&js, sizeof(js));

	if (m_pJoyDevice != NULL)
	{
		//1フレーム前の情報を保存
		m_JoyState.Old.rgdwPOV[0] = m_JoyState.Press.rgdwPOV[0];

		m_pJoyDevice->Poll();

		if (SUCCEEDED(m_pJoyDevice->GetDeviceState(sizeof(DIJOYSTATE), &js)))
		{
			//十字キーの情報を保存
			m_JoyState.Press.rgdwPOV[0] = js.rgdwPOV[0];

			//ボタン情報
			for (int nCntButton = 0; nCntButton < JOY_BUTTON_MAX; nCntButton++)
			{
				//トリガー情報を保存
				m_JoyState.Trigger.rgbButtons[nCntButton] = (m_JoyState.Press.rgbButtons[nCntButton] ^ js.rgbButtons[nCntButton])&js.rgbButtons[nCntButton];

				//リリース情報を保存
				m_JoyState.Release.rgbButtons[nCntButton] = (m_JoyState.Press.rgbButtons[nCntButton] ^ js.rgbButtons[nCntButton])&~js.rgbButtons[nCntButton];

				//プレス保存
				m_JoyState.Press.rgbButtons[nCntButton] = js.rgbButtons[nCntButton];
			}
		}
		else
		{
			//失敗した場合再度接続を試みる
			m_pJoyDevice->Acquire();
		}
	}
}

//=============================================================================
//ジョイスティッククラスのプレス情報の取得
//=============================================================================
bool CInputJoypad::GetJoyStickPress(int nButton)
{
	return (m_JoyState.Press.rgbButtons[nButton] & 0x80) ? true : false;
}

//=============================================================================
//ジョイスティッククラスのトリガー情報の取得
//=============================================================================
bool CInputJoypad::GetJoyStickTrigger(int nButton)
{
	return (m_JoyState.Trigger.rgbButtons[nButton] & 0x80) ? true : false;
}

//=============================================================================
//ジョイスティッククラスのリリース情報の取得
//=============================================================================
bool CInputJoypad::GetJoyStickReleas(int nButton)
{
	return (m_JoyState.Release.rgbButtons[nButton] & 0x80) ? true : false;
}

//=============================================================================
//ジョイスティッククラスの十字キーが押された瞬間の判定処理
//=============================================================================
bool CInputJoypad::GetPushCross(int nButton)
{
	//前回が何も押されていないかつ、現在が押されていたら
	if (m_JoyState.Old.rgdwPOV[0] == 0xFFFFFFFF &&
		m_JoyState.Press.rgdwPOV[0] == nButton)
	{
		return true;
	}
	return false;
}

//=============================================================================
//ジョイスティッククラスの十字キーが離した瞬間の判定処理
//=============================================================================
bool CInputJoypad::GetPushRelease(int nButtond)
{
	//前回が押されているかつ、現在が押されていない
	if (m_JoyState.Old.rgdwPOV[0] == nButtond &&
		m_JoyState.Press.rgdwPOV[0] == 0xFFFFFFFF)
	{
		return true;
	}
	return false;
}

//=============================================================================
// 振動のセット
//=============================================================================
void CInputJoypad::SetVibration(int nNum)
{
	if (m_lpDIEffect[nNum] != NULL)
	{
		m_lpDIEffect[nNum]->Start(1, 0);
	}
}

//=============================================================================
//ジョイスティッククラスのスティック情報の取得
//=============================================================================
DIJOYSTATE CInputJoypad::GetStick(void)
{
	DIJOYSTATE js;
	SecureZeroMemory(&js, sizeof(js));

	if (m_pJoyDevice != NULL)
	{
		m_pJoyDevice->Poll();
		m_pJoyDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);

	}

	return js;
}


//=============================================================================
//ジョイスティッククラスのデバイス列挙コールバック関数
//=============================================================================
BOOL CALLBACK CInputJoypad::DeviceFindCallBack(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext)
{
	//ジョイスティックの作成
	if (FAILED(m_pInput->CreateDevice(
		pdidInstance->guidInstance,
		&m_pJoyDevice,
		NULL)))
	{
		return DIENUM_CONTINUE;
	}

	//検索を終了する
	return DIENUM_STOP;
}

//=============================================================================
// 　軸列挙コールバック関数
//=============================================================================
BOOL CInputJoypad::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE * pdidoi, VOID * pContext)
{
	HRESULT     hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = 0 - 1000;
	diprg.lMax = 0 + 1000;
	hr = m_pJoyDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr)) return DIENUM_STOP;

	DWORD *pdwNumForceFeedbackAxis = (DWORD*)pContext;
	if ((pdidoi->dwFlags & DIDOI_FFACTUATOR) != 0) (*pdwNumForceFeedbackAxis)++;

	return DIENUM_CONTINUE;
}

//=============================================================================
// 振動エフェクトの生成
//=============================================================================
void CInputJoypad::CreateEffect(void)
{
	DWORD rgdwAxes[2] = { DIJOFS_X , DIJOFS_Y };
	LONG  rglDirection[2] = { 1 , 1 };

	DICONSTANTFORCE cf;
	DIEFFECT        eff;

	// 振動強さの調整
	DIENVELOPE lpEnvelope;
	lpEnvelope.dwSize = sizeof(DIENVELOPE);
	lpEnvelope.dwAttackLevel = 10;
	lpEnvelope.dwAttackTime = (DWORD)(0.01f * DI_SECONDS);
	lpEnvelope.dwFadeLevel = 10;
	lpEnvelope.dwFadeTime = (DWORD)(0.0f* DI_SECONDS);

	ZeroMemory(&eff, sizeof(eff));
	eff.dwSize = sizeof(DIEFFECT);
	eff.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	eff.dwDuration = (DWORD)(0.5f * DI_SECONDS);
	eff.dwSamplePeriod = 0;
	eff.dwGain = DI_FFNOMINALMAX;
	eff.dwTriggerButton = DIEB_NOTRIGGER;
	eff.dwTriggerRepeatInterval = 0;
	eff.cAxes = m_dwNumForceFeedbackAxis[0];
	eff.rgdwAxes = rgdwAxes;
	eff.rglDirection = rglDirection;
	eff.lpEnvelope = 0;
	eff.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
	eff.lpvTypeSpecificParams = &cf;
	eff.dwStartDelay = 0;

	m_pJoyDevice->CreateEffect(GUID_ConstantForce, &eff, &m_lpDIEffect[0], NULL);

	// 振動強さの調整
	lpEnvelope.dwAttackLevel = 0;
	lpEnvelope.dwAttackTime = (DWORD)(0.01f * DI_SECONDS);
	lpEnvelope.dwFadeLevel = 10;
	lpEnvelope.dwFadeTime = (DWORD)(0.0f* DI_SECONDS);


	ZeroMemory(&eff, sizeof(eff));
	eff.dwSize = sizeof(DIEFFECT);
	eff.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	eff.dwDuration = (DWORD)(0.15f * DI_SECONDS);
	eff.dwSamplePeriod = 0;
	eff.dwGain = 1;
	eff.dwTriggerButton = DIEB_NOTRIGGER;
	eff.dwTriggerRepeatInterval = 0;
	eff.cAxes = m_dwNumForceFeedbackAxis[1];
	eff.rgdwAxes = rgdwAxes;
	eff.rglDirection = rglDirection;
	eff.lpEnvelope = &lpEnvelope;
	eff.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
	eff.lpvTypeSpecificParams = &cf;
	eff.dwStartDelay = 0;

	m_pJoyDevice->CreateEffect(GUID_ConstantForce, &eff, &m_lpDIEffect[1], NULL);
	int n = 0;
}



