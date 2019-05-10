//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �R���g���[���[���� [Gamepad.h]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	GAMEPAD_NUM_KEY_MAX			(128)		// �L�[�̍ő吔(128�Œ�)
#define GAMEPAD_STICK_SENSITIVITY	(1000)		// �X�e�B�b�N�̊��x�̈�
#define DEADRATE					(0.2f)		// �������x��
#define GAMEPAD_DEADZONE			(GAMEPAD_STICK_SENSITIVITY * DEADRATE)			// �������x�̈�

//*****************************************************************************
// �N���X��`
//*****************************************************************************
	//--- ELECOM [JC-U3613] ---//
typedef enum
{
	ELECOM_X = 0,
	ELECOM_Y,
	ELECOM_A,
	ELECOM_B,
	ELECOM_LB,
	ELECOM_RB,
	ELECOM_LT,
	ELECOM_RT,
	ELECOM_LS,
	ELECOM_RS,
	ELECOM_BACK,
	ELECOM_START,
	ELECOM_MAX
}ELECOM_CTRL;

//--- ���� ---//
typedef enum
{
	DIRECTION_UP = 0,	// ��
	DIRECTION_DOWN,		// ��
	DIRECTION_RIGHT,	// �E
	DIRECTION_LEFT,		// ��
	DIRECTION_MAX
}DIRECTION;

typedef struct
{// �Q�[���p�b�h�̏��
	DIJOYSTATE2 GamepadState;							// �R���g���[���[��� [�S�Ă̓��͏��]
	BYTE aKeyState[GAMEPAD_NUM_KEY_MAX];				// �{�^�����͏��(�v���X���)
	BYTE aKeyStateTrigger[GAMEPAD_NUM_KEY_MAX];		// �{�^�����͏��(�g���K�[���)
	BYTE aKeyStateRelease[GAMEPAD_NUM_KEY_MAX];		// �{�^�����͏��(�����[�X���)
	BYTE aCrossKeyState[DIRECTION_MAX];				// �\���L�[���͏��(�v���X���)
	BYTE aCrossKeyStateTrigger[DIRECTION_MAX];		// �\���L�[���͏��(�g���K�[���)
	BYTE aCrossKeyStateRelease[DIRECTION_MAX];		// �\���L�[���͏��(�����[�X)
	BYTE aStickLeftState[DIRECTION_MAX];				// ���X�e�B�b�N���͏��(�v���X���)
	BYTE aStickLeftStateTrigger[DIRECTION_MAX];		// ���X�e�B�b�N���͏��(�g���K�[���)
	BYTE aStickLeftStateRelease[DIRECTION_MAX];		// ���X�e�B�b�N���͏��(�����[�X)
	BYTE aStickRightState[DIRECTION_MAX];				// �E�X�e�B�b�N���͏��(�v���X���)
	BYTE aStickRightStateTrigger[DIRECTION_MAX];		// �E�X�e�B�b�N���͏��(�g���K�[���)
	BYTE aStickRightStateRelease[DIRECTION_MAX];		// �E�X�e�B�b�N���͏��(�����[�X)

}Gamepad;

BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidinstance, VOID* pContext);
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);
HRESULT InitGamapad(HINSTANCE hInstance, HWND hWnd);
void UninitGamapad(void);
void UpdateGamapad(void);
/* �擾�֐� */
DIJOYSTATE2 *GetGamepadState(void);		// �R���g���[���[�����擾
										/* ���͊֐� */
bool GetGamapadKeyPress(int nKey);							// �{�^�� [�v���X]
bool GetGamapadKeyTrigger(int nKey);						// �{�^�� [�g���K�[]
bool GetGamapadKeyRelease(int nKey);						// �{�^�� [�����[�X]
bool GetCrossKeyPress(DIRECTION direction);			// �\���L�[ [�v���X]
bool GetCrossKeyTrigger(DIRECTION direction);		// �\���L�[ [�g���K�[]
bool GetCrossKeyRelease(DIRECTION direction);		// �\���L�[ [�����[�X]
bool GetStickLeftPress(DIRECTION direction);		// ���X�e�B�b�N [�v���X]
bool GetStickLeftTrigger(DIRECTION direction);		// ���X�e�B�b�N [�g���K�[]
bool GetStickLeftRelease(DIRECTION direction);		// ���X�e�B�b�N [�����[�X]
bool GetStickRightPress(DIRECTION direction);		// �E�X�e�B�b�N [�v���X]
bool GetStickRightTrigger(DIRECTION direction);		// �E�X�e�B�b�N [�g���K�[]
bool GetStickRightRelease(DIRECTION direction);		// �E�X�e�B�b�N [�����[�X]

#endif