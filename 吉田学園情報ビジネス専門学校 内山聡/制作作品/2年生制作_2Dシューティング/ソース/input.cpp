//=============================================================================
//
// メイン処理 [manager.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//	コンストラクタ
CInput::CInput()
{
	m_pDevice = NULL;
}

//	デストラクタ
CInput::~CInput()
{

}

//	初期化処理
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}

	return S_OK;
}

//	終了処理
void CInput::Uninit(void)
{
	// 入力デバイス(キーボード)の開放
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//-------------------------------------------------------------------------
//	キーボード
//-------------------------------------------------------------------------

//<><><><><><><><><><><><><><><>
//	コンストラクタ
//<><><><><><><><><><><><><><><>
CInputKeyboard::CInputKeyboard()
{
}

//<><><><><><><><><><><><><><><>
//	デストラクタ
//<><><><><><><><><><><><><><><>
CInputKeyboard::~CInputKeyboard()
{
}

//<><><><><><><><><><><><><><><>
//	初期化処理
//<><><><><><><><><><><><><><><>
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{

	// DirectInputオブジェクトの生成
	CInput::Init(hInstance, hWnd);
	

	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}


	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}


	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}


	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();


	return S_OK;
}


//<><><><><><><><><><><><><><><>
//	終了処理
//<><><><><><><><><><><><><><><>
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}


//<><><><><><><><><><><><><><><>
//	更新処理
//<><><><><><><><><><><><><><><>
void CInputKeyboard::Update(void)
{

	BYTE aKeyState[MAX_KEY];

	int nCntKey;


	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}


bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}


bool  CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}



//-------------------------------------------------------------------------
//	ジョイスティック
//-------------------------------------------------------------------------

//<><><><><><><><><><><><><><><>
//	コンストラクタ
//<><><><><><><><><><><><><><><>
CInputJoystick::CInputJoystick()
{
}


//<><><><><><><><><><><><><><><>
//	デストラクタ
//<><><><><><><><><><><><><><><>
CInputJoystick::~CInputJoystick()
{
}


//<><><><><><><><><><><><><><><>
//	初期化処理
//<><><><><><><><><><><><><><><>
HRESULT CInputJoystick::Init(HINSTANCE hInstance,HWND hWnd)
{
	// DirectInputオブジェクトの生成
	CInput::Init(hInstance, hWnd);
	

	// 入力デバイス()の生成
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}


	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}


	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}


	if (m_pDevice != NULL)
	{// 生成できた
		DIPROPRANGE diprg;

		// 軸の値の範囲を設定
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = RANGE_MIN;
		diprg.lMax = RANGE_MAX;

		// 軸の設定
		// 左アナログスティック
		diprg.diph.dwObj = DIJOFS_X;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 右アナログスティック
		diprg.diph.dwObj = DIJOFS_RX;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 十字キー(上を0度とし時計回りに角度 * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ジョイスティックへのアクセス権を獲得(入力制御開始)
		m_pDevice->Acquire();
	}

	return S_OK;
}

//<><><><><><><><><><><><><><><>
//	更新処理
//<><><><><><><><><><><><><><><>
void CInputJoystick::Update(void)
{
	DIJOYSTATE joystate;
	// ジョイスティックにポールをかける
	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();

		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIJOYSTATE), &joystate)))
		{
			m_LeftAxizX = (float)joystate.lX;
			m_LeftAxizY = (float)joystate.lY;
			m_RightAxizX = (float)joystate.lZ;
			m_RightAxizY = (float)joystate.lRz;

			//
			if (joystate.lX <= -100 || joystate.lX >= 100 || joystate.lY <= -100 || joystate.lY >= 100)
			{
				//倒れた時
				m_aJoystickState[0] = 0x80;
			}
			else
			{
				//倒れてないとき
				m_aJoystickState[0] = 0;
			}

			if (joystate.lZ <= -100 || joystate.lZ >= 100 || joystate.lRz <= -100 || joystate.lRz >= 100)
			{
				//倒れた時
				m_aJoystickState[1] = 0x80;
			}
			else
			{
				//倒れてないとき
				m_aJoystickState[1] = 0;
			}

			for (int nCunButn = 0; nCunButn < MAX_BUTTAN; nCunButn++)
			{
				m_aKeyStateTrigger[nCunButn] = (m_aKeyState[nCunButn] ^ joystate.rgbButtons[nCunButn])&joystate.rgbButtons[nCunButn];
				m_aKeyState[nCunButn] = joystate.rgbButtons[nCunButn];
			}
		}
		else
		{
			// キーボードへのアクセス権を獲得(入力制御開始)
			m_pDevice->Acquire();
		}
	}
}

bool CInputJoystick::GetPress(int nButton)
{
	return (m_aKeyState[nButton] & 0x80) ? true : false;
}
bool  CInputJoystick::GetTrigger(int nButton)
{
	return (m_aKeyStateTrigger[nButton] & 0x80) ? true : false;
}
bool CInputJoystick::GetJoystick(int nStick)
{
	return (m_aJoystickState[nStick] & 0x80) ? true : false;
}
float CInputJoystick::GetLeftAxiz(void)
{
	float Axiz = atan2f(m_LeftAxizX, m_LeftAxizY);
	return Axiz;
}
float CInputJoystick::GetRightAxiz(void)
{
	float Axiz = atan2f(m_RightAxizX, m_RightAxizY);
	return Axiz;
}
float CInputJoystick::GetRadian(void)
{
	return m_Radian;
}

//BOOL CALLBACK CInputJoystick::GetJoystickCallback(LPDIDEVICEINSTANCE lpddi, LPVOID /*pvRef*/)
//{
//	HRESULT hr;
//
//	hr = m_pInput->CreateDeviceEx(lpddi->guidInstance, IID_IDirectInputDevice7, (void**)&m_pDevice, NULL);
//	if (FAILED(hr))
//		return DIENUM_CONTINUE;	// 次のデバイスを列挙
//
//	return DIENUM_STOP;	// デバイスの列挙を中止
//
//}
//-----------------------------------------------------------------------------
// 関数名　：　GetJoypadState()
// 機能概要：　ジョイパッドの状態を取得
//-----------------------------------------------------------------------------
//void CInputJoystick::GetJoypadState(void)
//{
//	HRESULT			hr;
//	DIJOYSTATE		dijs;
//
//	diJoyState = 0x00000000l;	// 初期化
//
//	m_pDevice->Poll();	// ジョイスティックにポールをかける
//	hr = m_pDevice->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
//	if (hr == DIERR_INPUTLOST)
//		m_pDevice->Acquire();
//}
////<><><><><><><><><><><><><><><>
////	終了処理
////<><><><><><><><><><><><><><><>
//void CInputJoystick::UninitDirectInput(void)
//{
//	CInput::Uninit();
//}