//=============================================================================
//
// ���C������ [manager.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//	�R���X�g���N�^
CInput::CInput()
{
	m_pDevice = NULL;
}

//	�f�X�g���N�^
CInput::~CInput()
{

}

//	����������
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}

	return S_OK;
}

//	�I������
void CInput::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//-------------------------------------------------------------------------
//	�L�[�{�[�h
//-------------------------------------------------------------------------

//<><><><><><><><><><><><><><><>
//	�R���X�g���N�^
//<><><><><><><><><><><><><><><>
CInputKeyboard::CInputKeyboard()
{
}

//<><><><><><><><><><><><><><><>
//	�f�X�g���N�^
//<><><><><><><><><><><><><><><>
CInputKeyboard::~CInputKeyboard()
{
}

//<><><><><><><><><><><><><><><>
//	����������
//<><><><><><><><><><><><><><><>
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{

	// DirectInput�I�u�W�F�N�g�̐���
	CInput::Init(hInstance, hWnd);
	

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}


	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}


	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}


	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();


	return S_OK;
}


//<><><><><><><><><><><><><><><>
//	�I������
//<><><><><><><><><><><><><><><>
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}


//<><><><><><><><><><><><><><><>
//	�X�V����
//<><><><><><><><><><><><><><><>
void CInputKeyboard::Update(void)
{

	BYTE aKeyState[MAX_KEY];

	int nCntKey;


	// ���̓f�o�C�X����f�[�^���擾
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
//	�W���C�X�e�B�b�N
//-------------------------------------------------------------------------

//<><><><><><><><><><><><><><><>
//	�R���X�g���N�^
//<><><><><><><><><><><><><><><>
CInputJoystick::CInputJoystick()
{
}


//<><><><><><><><><><><><><><><>
//	�f�X�g���N�^
//<><><><><><><><><><><><><><><>
CInputJoystick::~CInputJoystick()
{
}


//<><><><><><><><><><><><><><><>
//	����������
//<><><><><><><><><><><><><><><>
HRESULT CInputJoystick::Init(HINSTANCE hInstance,HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	CInput::Init(hInstance, hWnd);
	

	// ���̓f�o�C�X()�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}


	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}


	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}


	if (m_pDevice != NULL)
	{// �����ł���
		DIPROPRANGE diprg;

		// ���̒l�͈̔͂�ݒ�
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = RANGE_MIN;
		diprg.lMax = RANGE_MAX;

		// ���̐ݒ�
		// ���A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_X;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �E�A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_RX;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �\���L�[(���0�x�Ƃ����v���Ɋp�x * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �W���C�X�e�B�b�N�ւ̃A�N�Z�X�����l��(���͐���J�n)
		m_pDevice->Acquire();
	}

	return S_OK;
}

//<><><><><><><><><><><><><><><>
//	�X�V����
//<><><><><><><><><><><><><><><>
void CInputJoystick::Update(void)
{
	DIJOYSTATE joystate;
	// �W���C�X�e�B�b�N�Ƀ|�[����������
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
				//�|�ꂽ��
				m_aJoystickState[0] = 0x80;
			}
			else
			{
				//�|��ĂȂ��Ƃ�
				m_aJoystickState[0] = 0;
			}

			if (joystate.lZ <= -100 || joystate.lZ >= 100 || joystate.lRz <= -100 || joystate.lRz >= 100)
			{
				//�|�ꂽ��
				m_aJoystickState[1] = 0x80;
			}
			else
			{
				//�|��ĂȂ��Ƃ�
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
			// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
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
//		return DIENUM_CONTINUE;	// ���̃f�o�C�X���
//
//	return DIENUM_STOP;	// �f�o�C�X�̗񋓂𒆎~
//
//}
//-----------------------------------------------------------------------------
// �֐����@�F�@GetJoypadState()
// �@�\�T�v�F�@�W���C�p�b�h�̏�Ԃ��擾
//-----------------------------------------------------------------------------
//void CInputJoystick::GetJoypadState(void)
//{
//	HRESULT			hr;
//	DIJOYSTATE		dijs;
//
//	diJoyState = 0x00000000l;	// ������
//
//	m_pDevice->Poll();	// �W���C�X�e�B�b�N�Ƀ|�[����������
//	hr = m_pDevice->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// �f�o�C�X��Ԃ�ǂݎ��
//	if (hr == DIERR_INPUTLOST)
//		m_pDevice->Acquire();
//}
////<><><><><><><><><><><><><><><>
////	�I������
////<><><><><><><><><><><><><><><>
//void CInputJoystick::UninitDirectInput(void)
//{
//	CInput::Uninit();
//}