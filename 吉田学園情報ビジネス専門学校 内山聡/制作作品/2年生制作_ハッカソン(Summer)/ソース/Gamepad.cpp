//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �R���g���[���[���� [Gamepad.cpp]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "Gamepad.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECTINPUT8		 g_pGamepadInput = NULL;		// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDeviceGamepad = NULL;		// �f�o�C�X�̃|�C���^ (�R�[���o�b�N�֐��̊֌W�� [static] ��)
DIDEVCAPS			 g_GamepadCaps;					// �Q�[���p�b�h�̋@�\���
Gamepad				 g_GamePad;						// �Q�[���p�b�h�̏��

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGamapad(HINSTANCE hInstance, HWND hWnd)
{
	// ���[�J���ϐ�
	HRESULT hr;		// ���s���ʊm�F�p

	// �l���N���A
	for (int nCntKey = 0; nCntKey < GAMEPAD_NUM_KEY_MAX; nCntKey++)
	{
		g_GamePad.aKeyState[nCntKey] = 0;				// �{�^�����͏��(�v���X���)
		g_GamePad.aKeyStateTrigger[nCntKey] = 0;		// �{�^�����͏��(�g���K�[���)
		g_GamePad.aKeyStateRelease[nCntKey] = 0;		// �{�^�����͏��(�����[�X���)
	}
	for (int nCntDirection = 0; nCntDirection < DIRECTION_MAX; nCntDirection++)
	{
		g_GamePad.aCrossKeyState[nCntDirection] = 0;			// �\���L�[���͏��(�v���X���)
		g_GamePad.aCrossKeyStateTrigger[nCntDirection] = 0;		// �\���L�[���͏��(�g���K�[���)
		g_GamePad.aCrossKeyStateRelease[nCntDirection] = 0;		// �\���L�[���A���(�����[�X���)
		g_GamePad.aStickLeftState[nCntDirection] = 0;			// ���X�e�B�b�N���͏��(�v���X���)
		g_GamePad.aStickLeftStateTrigger[nCntDirection] = 0;	// ���X�e�B�b�N���͏��(�g���K�[���)
		g_GamePad.aStickLeftStateRelease[nCntDirection] = 0;	// ���X�e�B�b�N���͏��(�����[�X)
		g_GamePad.aStickRightState[nCntDirection] = 0;			// �E�X�e�B�b�N���͏��(�v���X���)
		g_GamePad.aStickRightStateTrigger[nCntDirection] = 0;	// �E�X�e�B�b�N���͏��(�g���K�[���)
		g_GamePad.aStickRightStateRelease[nCntDirection] = 0;	// �E�X�e�B�b�N���͏��(�����[�X)
	}


	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pGamepadInput, NULL)))
	{
		MessageBox(NULL, "DirectInput8�I�u�W�F�N�g�̍쐬�Ɏ��s", "Direct Input Error", MB_OK);
		return E_FAIL;
	}

	// ���̓f�o�C�X(�R���g���[���[)�̐���
	if (FAILED(hr = g_pGamepadInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)))		// ��4���� (ATTACHEDONLY = ���ݐڑ�����Ă���W���C�X�e�B�b�N�̂݌��o����)
	{
		return FALSE;
	}

	if (hr == S_OK && g_pDeviceGamepad != NULL)
	{// �R���g���[���[�������ł����ꍇ
		// �f�o�C�X�Ƀf�[�^�t�H�[�}�b�g��ݒ�
		if (FAILED(hr = g_pDeviceGamepad->SetDataFormat(&c_dfDIJoystick2)))
		{
			return FALSE;
		}

		// �������[�h��ݒ�
		if (FAILED(hr = g_pDeviceGamepad->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			return FALSE;
		}

		// �Q�[���p�b�h�̋@�\�̏������W
		g_GamepadCaps.dwSize = sizeof(DIDEVCAPS);

		if (FAILED(hr = g_pDeviceGamepad->GetCapabilities(&g_GamepadCaps)))
		{
			g_pDeviceGamepad->Release();
			return FALSE;
		}

		// �e���̃��[�h�ݒ�
		if (FAILED(hr = g_pDeviceGamepad->EnumObjects(EnumAxesCallback, (void*)g_pDeviceGamepad, DIDFT_AXIS)))
		{
			return FALSE;
		}

		// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
		hr = g_pDeviceGamepad->Poll();

		if (FAILED(hr))
		{
			hr = g_pDeviceGamepad->Acquire();

			while (hr == DIERR_INPUTLOST)
			{
				hr = g_pDeviceGamepad->Acquire();
			}
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGamapad(void)
{
	// DirectInput�̊J������
	if (g_pGamepadInput != NULL)
	{
		g_pGamepadInput->Release();
		g_pGamepadInput = NULL;
	}

	// �Q�[���p�b�h�̃|�C���^�����
	if (g_pDeviceGamepad != NULL)
	{
		g_pDeviceGamepad->Release();
		g_pDeviceGamepad = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGamapad(void)
{
	if (g_pDeviceGamepad != NULL)
	{// �R���g���[���[���q�����Ă��Ȃ��Ƃ��������Ȃ�

		DIJOYSTATE2 GamepadState;							// �R���g���[���[�̏��
		BYTE aCrossKeyState[DIRECTION_MAX] = { 0,0,0,0 };	// �\���L�[�̏��
		BYTE aLeftStickState[DIRECTION_MAX] = { 0,0,0,0 };	// ���X�e�B�b�N�̏��
		BYTE aRightStickState[DIRECTION_MAX] = { 0,0,0,0 };	// �E�X�e�B�b�N�̏��
		HRESULT hr;

		hr = g_pDeviceGamepad->Poll();

		// ���̓f�o�C�X����f�[�^���擾
		if (SUCCEEDED(hr = g_pDeviceGamepad->GetDeviceState(sizeof(DIJOYSTATE2), &GamepadState)))
		{
			//--- �\���L�[ ---//
			if (GamepadState.rgdwPOV[0] == 0)
			{// ��
				aCrossKeyState[DIRECTION_UP] = 128;
			}
			if (GamepadState.rgdwPOV[0] == 9000)
			{// ��
				aCrossKeyState[DIRECTION_DOWN] = 128;
			}
			if (GamepadState.rgdwPOV[0] == 18000)
			{// �E
				aCrossKeyState[DIRECTION_RIGHT] = 128;
			}
			if (GamepadState.rgdwPOV[0] == 27000)
			{// ��
				aCrossKeyState[DIRECTION_LEFT] = 128;
			}

			//--- ���X�e�B�b�N ---//
			if (GamepadState.lY < -GAMEPAD_DEADZONE)
			{// ��
				aLeftStickState[DIRECTION_UP] = 128;
			}
			if (GamepadState.lY > GAMEPAD_DEADZONE)
			{// ��
				aLeftStickState[DIRECTION_DOWN] = 128;
			}
			if (GamepadState.lX > GAMEPAD_DEADZONE)
			{// �E
				aLeftStickState[DIRECTION_RIGHT] = 128;
			}
			if (GamepadState.lX < -GAMEPAD_DEADZONE)
			{// ��
				aLeftStickState[DIRECTION_LEFT] = 128;
			}

			//--- �E�X�e�B�b�N ---//
			if (GamepadState.lRz < -GAMEPAD_DEADZONE)
			{// ��
				aRightStickState[DIRECTION_UP] = 128;
			}
			if (GamepadState.lRz > GAMEPAD_DEADZONE)
			{// ��
				aRightStickState[DIRECTION_DOWN] = 128;
			}
			if (GamepadState.lZ > GAMEPAD_DEADZONE)
			{// �E
				aRightStickState[DIRECTION_RIGHT] = 128;
			}
			if (GamepadState.lZ < -GAMEPAD_DEADZONE)
			{// ��
				aRightStickState[DIRECTION_LEFT] = 128;
			}

			// �X�e�B�b�N & �\���L�[
			for (int nCntDirection = 0; nCntDirection < DIRECTION_MAX; nCntDirection++)
			{
				// �\���L�[���͏�� [�g���K�[] = (���� ^ �ߋ�) & ����
				g_GamePad.aCrossKeyStateTrigger[nCntDirection] = (aCrossKeyState[nCntDirection] ^ g_GamePad.aCrossKeyState[nCntDirection]) & aCrossKeyState[nCntDirection];
				// �\���L�[���͏�� [�����[�X = (���� ^ �ߋ�) & �ߋ�
				g_GamePad.aCrossKeyStateRelease[nCntDirection] = (aCrossKeyState[nCntDirection] ^ g_GamePad.aCrossKeyState[nCntDirection]) & g_GamePad.aCrossKeyState[nCntDirection];
				// �\���L�[���͏�� [�v���X] �� �O��̓��͏�����ɔ��f���邽�߁A�Ō�ɍX�V���邱�ƁI
				g_GamePad.aCrossKeyState[nCntDirection] = aCrossKeyState[nCntDirection];
				// ���X�e�B�b�N���͏�� [�g���K�[] = (���� ^ �ߋ�) & ����
				g_GamePad.aStickLeftStateTrigger[nCntDirection] = (aLeftStickState[nCntDirection] ^ g_GamePad.aStickLeftState[nCntDirection]) & aLeftStickState[nCntDirection];
				// ���X�e�B�b�N���͏�� [�����[�X = (���� ^ �ߋ�) & �ߋ�
				g_GamePad.aStickLeftStateRelease[nCntDirection] = (aLeftStickState[nCntDirection] ^ g_GamePad.aStickLeftState[nCntDirection]) & g_GamePad.aStickLeftState[nCntDirection];
				// ���X�e�B�b�N���͏�� [�v���X] �� �O��̓��͏�����ɔ��f���邽�߁A�Ō�ɍX�V���邱�ƁI
				g_GamePad.aStickLeftState[nCntDirection] = aLeftStickState[nCntDirection];
				// �E�X�e�B�b�N���͏�� [�g���K�[] = (���� ^ �ߋ�) & ����
				g_GamePad.aStickRightStateTrigger[nCntDirection] = (aRightStickState[nCntDirection] ^ g_GamePad.aStickRightState[nCntDirection]) & aRightStickState[nCntDirection];
				// �E�X�e�B�b�N���͏�� [�����[�X = (���� ^ �ߋ�) & �ߋ�
				g_GamePad.aStickRightStateRelease[nCntDirection] = (aRightStickState[nCntDirection] ^ g_GamePad.aStickRightState[nCntDirection]) & g_GamePad.aStickRightState[nCntDirection];
				// �E�X�e�B�b�N���͏�� [�v���X] �� �O��̓��͏�����ɔ��f���邽�߁A�Ō�ɍX�V���邱�ƁI
				g_GamePad.aStickRightState[nCntDirection] = aRightStickState[nCntDirection];
			}

			// �{�^��
			for (int nCntKey = 0; nCntKey < GAMEPAD_NUM_KEY_MAX; nCntKey++)
			{
				// �{�^�����͏��(�g���K�[���) = (���� ^ �ߋ�) & ����
				g_GamePad.aKeyStateTrigger[nCntKey] = (GamepadState.rgbButtons[nCntKey] ^ g_GamePad.aKeyState[nCntKey]) & GamepadState.rgbButtons[nCntKey];
				// �{�^�����͏��(�����[�X���) = (���� ^ �ߋ�) & �ߋ�
				g_GamePad.aKeyStateRelease[nCntKey] = (GamepadState.rgbButtons[nCntKey] ^ g_GamePad.aKeyState[nCntKey]) & g_GamePad.aKeyState[nCntKey];
				// �{�^�����͏��(�v���X���) �� �O��̓��͏�����ɔ��f���邽�߁A�Ō�ɍX�V���邱�ƁI
				g_GamePad.aKeyState[nCntKey] = GamepadState.rgbButtons[nCntKey];

			}
		}
		else
		{
			g_pDeviceGamepad->Acquire();		// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �{�^�� [�v���X]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetGamapadKeyPress(int nKey)
{
	return(g_GamePad.aKeyState[nKey] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �{�^�� [�g���K�[]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetGamapadKeyTrigger(int nKey)
{
	return(g_GamePad.aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �{�^�� [�����[�X]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetGamapadKeyRelease(int nKey)
{
	return(g_GamePad.aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���X�e�B�b�N [�v���X]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetStickLeftPress(DIRECTION direction)
{
	return(g_GamePad.aStickLeftState[(int)direction] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���X�e�B�b�N [�g���K�[]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetStickLeftTrigger(DIRECTION direction)
{
	return(g_GamePad.aStickLeftStateTrigger[(int)direction] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���X�e�B�b�N [�����[�X]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetStickLeftRelease(DIRECTION direction)
{
	return(g_GamePad.aStickLeftStateRelease[(int)direction] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �E�X�e�B�b�N [�v���X]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetStickRightPress(DIRECTION direction)
{
	return(g_GamePad.aStickRightState[(int)direction] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �E�X�e�B�b�N [�g���K�[]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetStickRightTrigger(DIRECTION direction)
{
	return(g_GamePad.aStickRightStateTrigger[(int)direction] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �E�X�e�B�b�N [�����[�X]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetStickRightRelease(DIRECTION direction)
{
	return(g_GamePad.aStickRightStateRelease[(int)direction] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �\���L�[ [�v���X]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetCrossKeyPress(DIRECTION direction)
{
	return(g_GamePad.aCrossKeyState[(int)direction] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �\���L�[ [�g���K�[]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetCrossKeyTrigger(DIRECTION direction)
{
	return(g_GamePad.aCrossKeyStateTrigger[(int)direction] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �\���L�[ [�����[�X]
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetCrossKeyRelease(DIRECTION direction)
{
	return(g_GamePad.aCrossKeyStateRelease[(int)direction] & 0x80) ? true : false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �R���g���[���[�����擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
DIJOYSTATE2 *GetGamepadState(void)
{
	return(&g_GamePad.GamepadState);
}

//*****************************************************************************
// joystick�p�R�[���o�b�N�֐�
//*****************************************************************************
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidinstance, VOID* pContext)
{
	HRESULT hr;

	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾
	hr = g_pGamepadInput->CreateDevice(pdidinstance->guidInstance, &g_pDeviceGamepad, NULL);

	// �f�o�C�X�����o�o���Ȃ������ꍇ
	if (FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}

	return DIENUM_STOP;
}

//*****************************************************************************
// joystick�̋@�\�R�[���o�b�N�֐�
//*****************************************************************************
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	HRESULT hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = -(GAMEPAD_STICK_SENSITIVITY);		// �\���L�[�̍ŏ��l [��] [��]	�}�C�i�X
	diprg.lMax = GAMEPAD_STICK_SENSITIVITY;			// �\���L�[�̍ő�l [��] [�E]	�v���X

	// �f�o�C�X�ɐݒ�
	hr = g_pDeviceGamepad->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}