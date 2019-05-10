//=============================================================================
//
// ���C������ [input.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=====================================
//�w�b�_�[�ǂݍ���
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
// Joypad���p�}�N��
//-----------------------------------------------------------------------------
//#define BUTTON_UP		0x00000001l		//�����L�[��(dijs.IY<0)
//#define BUTTON_DOWN		0x00000002l		//�����L�[��(dijs.IY>0)
//#define BUTTON_LEFT		0x00000004l		//�����L�[��(dijs.IX<0)
//#define BUTTON_RIGHT	0x00000008l		//�����L�[�E(dijs.IX>0)
//#define BUTTON_A		0x00000010l		//�`�{�^��(dijs.rgbButtons[0]&0x80)
//#define BUTTON_B		0x00000020l		//�a�{�^��(dijs.rgbButtons[1]&0x80)
//#define BUTTON_C		0x00000040l		//�b�{�^��(dijs.rgbButtons[2]&0x80)
//#define BUTTON_X		0x00000080l		//�w�{�^��(dijs.rgbButtons[3]&0x80)
//#define BUTTON_Y		0x00000100l		//�x�{�^��(dijs.rgbButtons[4]&0x80)
//#define BUTTON_Z		0x00000200l		//�y�{�^��(dijs.rgbButtons[5]&0x80)
//#define BUTTON_L		0x00000400l		//�k�{�^��(dijs.rgbButtons[6]&0x80)
//#define BUTTON_R		0x00000800l		//�q�{�^��(dijs.rgbButtons[7]&0x80)
//#define BUTTON_START	0x00001000l		//�r�s�`�q�s�{�^��(dijs.rgbButtons[8]&0x80)
//#define BUTTON_M		0x00002000l		//�l�{�^��(dijs.rgbButtons[9]&0x80)

//=====================================
//	�}�N����`
//=====================================
#define	MAX_KEY			(256)			//�L�[�̍ő�o�͐�
//-----------------------------------------------------------------------------
// Joypad�p�ݒ�l
//-----------------------------------------------------------------------------
#define DEADZONE		2500			// �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX		1000			// �L���͈͂̍ő�l
#define RANGE_MIN		-1000			// �L���͈͂̍ŏ��l
#define MAX_BUTTAN		(32)			//�{�^���̐�
#define MAX_STICK		(2)
//=====================================
//	Input(����)�N���X
//=====================================
class CInput
{
public:
	CInput();
	virtual ~CInput();
	//����̏���������
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	//����̏I������
	virtual void Uninit(void);
	//����̍X�V����
	virtual void Update(void) = 0;
protected:
	//����̃|�C���^
	static LPDIRECTINPUT8				m_pInput;
	//�f�o�C�X�|�C���^
	LPDIRECTINPUTDEVICE8				m_pDevice;
};

//=====================================
//	InputKeyboard(�L�[�{�[�h)�N���X
//=====================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	//�L�[�{�[�h�̏���������
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	//�L�[�{�[�h�̏I������
	void Uninit(void);
	//�L�[�{�[�h�̍X�V����
	void Update(void);
	//�L�[�{�[�h�̎擾(�v���X)
	bool GetPress(int nKey);
	//�L�[�{�[�h�̎擾(�g���K�[)
	bool GetTrigger(int Key);
	
private:

	//
	BYTE m_aKeyState[MAX_KEY];
	//
	BYTE m_aKeyStateTrigger[MAX_KEY];
};
//=====================================
//	InputJoystick(�R���g���[��)�N���X
//=====================================
class CInputJoystick : public CInput
{
public:
	CInputJoystick();
	~CInputJoystick();

	HRESULT Init(HINSTANCE hInstance,HWND hDlg);

	//BOOL CALLBACK GetJoystickCallback(LPDIDEVICEINSTANCE lpddi, LPVOID /*pvRef*/);
	//�L�[�{�[�h�̏I������
	//void Uninit(void);
	//�L�[�{�[�h�̍X�V����
	void Update(void);
	//�L�[�{�[�h�̎擾(�v���X)
	bool GetPress(int nButton);
	//�L�[�{�[�h�̎擾(�g���K�[)
	bool GetTrigger(int nButton);
	//
	bool GetJoystick(int nStick);
	//void GetJoypadState(void);
	float GetLeftAxiz(void);
	float GetRightAxiz(void);
	float GetRadian(void);
private:
	DWORD					diJoyState = 0x00000000L;	// �W���C�p�b�h���
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
