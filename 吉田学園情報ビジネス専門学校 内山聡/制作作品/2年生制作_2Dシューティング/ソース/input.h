//=============================================================================
//
// メイン処理 [input.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"

//#define STRICT
//#define DIRECTINPUT_VERSION 0x0800
//#define _CRT_SECURE_NO_DEPRECATE
//#ifndef _WIN32_DCOM
//#define _WIN32_DCOM
//#endif
//
//#include <windows.h>
//#include <commctrl.h>
//#include <basetsd.h>
//#include <dinput.h>
//#include <dinputd.h>
//#include <assert.h>
//#include <oleauto.h>
//#include <shellapi.h>
//-----------------------------------------------------------------------------
// Joypad情報用マクロ
//-----------------------------------------------------------------------------
//#define BUTTON_UP		0x00000001l		//方向キー上(dijs.IY<0)
//#define BUTTON_DOWN		0x00000002l		//方向キー下(dijs.IY>0)
//#define BUTTON_LEFT		0x00000004l		//方向キー左(dijs.IX<0)
//#define BUTTON_RIGHT	0x00000008l		//方向キー右(dijs.IX>0)
//#define BUTTON_A		0x00000010l		//Ａボタン(dijs.rgbButtons[0]&0x80)
//#define BUTTON_B		0x00000020l		//Ｂボタン(dijs.rgbButtons[1]&0x80)
//#define BUTTON_C		0x00000040l		//Ｃボタン(dijs.rgbButtons[2]&0x80)
//#define BUTTON_X		0x00000080l		//Ｘボタン(dijs.rgbButtons[3]&0x80)
//#define BUTTON_Y		0x00000100l		//Ｙボタン(dijs.rgbButtons[4]&0x80)
//#define BUTTON_Z		0x00000200l		//Ｚボタン(dijs.rgbButtons[5]&0x80)
//#define BUTTON_L		0x00000400l		//Ｌボタン(dijs.rgbButtons[6]&0x80)
//#define BUTTON_R		0x00000800l		//Ｒボタン(dijs.rgbButtons[7]&0x80)
//#define BUTTON_START	0x00001000l		//ＳＴＡＲＴボタン(dijs.rgbButtons[8]&0x80)
//#define BUTTON_M		0x00002000l		//Ｍボタン(dijs.rgbButtons[9]&0x80)

//=====================================
//	マクロ定義
//=====================================
#define	MAX_KEY			(256)			//キーの最大出力数
//-----------------------------------------------------------------------------
// Joypad用設定値
//-----------------------------------------------------------------------------
#define DEADZONE		2500			// 各軸の25%を無効ゾーンとする
#define RANGE_MAX		1000			// 有効範囲の最大値
#define RANGE_MIN		-1000			// 有効範囲の最小値
#define MAX_BUTTAN		(32)			//ボタンの数
#define MAX_STICK		(2)
//=====================================
//	Input(操作)クラス
//=====================================
class CInput
{
public:
	CInput();
	virtual ~CInput();
	//操作の初期化処理
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	//操作の終了処理
	virtual void Uninit(void);
	//操作の更新処理
	virtual void Update(void) = 0;
protected:
	//操作のポインタ
	static LPDIRECTINPUT8				m_pInput;
	//デバイスポインタ
	LPDIRECTINPUTDEVICE8				m_pDevice;
};

//=====================================
//	InputKeyboard(キーボード)クラス
//=====================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	//キーボードの初期化処理
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	//キーボードの終了処理
	void Uninit(void);
	//キーボードの更新処理
	void Update(void);
	//キーボードの取得(プレス)
	bool GetPress(int nKey);
	//キーボードの取得(トリガー)
	bool GetTrigger(int Key);
	
private:

	//
	BYTE m_aKeyState[MAX_KEY];
	//
	BYTE m_aKeyStateTrigger[MAX_KEY];
};
//=====================================
//	InputJoystick(コントローラ)クラス
//=====================================
class CInputJoystick : public CInput
{
public:
	CInputJoystick();
	~CInputJoystick();

	HRESULT Init(HINSTANCE hInstance,HWND hDlg);

	//BOOL CALLBACK GetJoystickCallback(LPDIDEVICEINSTANCE lpddi, LPVOID /*pvRef*/);
	//キーボードの終了処理
	//void Uninit(void);
	//キーボードの更新処理
	void Update(void);
	//キーボードの取得(プレス)
	bool GetPress(int nButton);
	//キーボードの取得(トリガー)
	bool GetTrigger(int nButton);
	//
	bool GetJoystick(int nStick);
	//void GetJoypadState(void);
	float GetLeftAxiz(void);
	float GetRightAxiz(void);
	float GetRadian(void);
private:
	DWORD					diJoyState = 0x00000000L;	// ジョイパッド情報
														//

	float m_LeftAxizX;
	float m_LeftAxizY;
	float m_RightAxizX;
	float m_RightAxizY;
	float m_Radian;

	BYTE m_aKeyState[MAX_KEY];
	//
	BYTE m_aKeyStateTrigger[MAX_KEY];
	//
	BYTE m_aJoystickState[MAX_STICK];
};
#endif
