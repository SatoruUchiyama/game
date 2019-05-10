//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// ���C������ [main.cpp]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "main.h"
#include "input.h"
#include "Gamepad.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "object.h"

#if _DEBUG
#include "Debug_Log.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"					// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"�ꐡ��͑�"				// �E�C���h�E�̃L���v�V������
#define UPDATE_FRAME	(60)						// �P�b�ԂɍX�V�����
#define WINDOW_MODE		(true)						// �E�B���h�E���[�h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D			= NULL;				// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice	= NULL;				// �f�o�C�X�I�u�W�F�N�g(�`��ɕK�v)
MODE				g_mode			= MODE_TITLE;		// ���[�h�̐ݒ�
int					g_nCountFPS		= 0;				// FPS�J�E���^

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���C���֐�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
							CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							(rect.right - rect.left),
							(rect.bottom - rect.top),
							NULL,
							NULL,
							hInstance,
							NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, WINDOW_MODE)))
	{
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �e�J�E���^�[��������
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();		// �V�X�e���������擾(�~���b�P��)
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();		// �V�X�e���������擾(�~���b�P��)

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// �V�X�e���������擾
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��
			 // FPS�𑪒�
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;		// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;					// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / UPDATE_FRAME))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;		// ���������s����������ۑ�

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;		// �J�E���g�����Z
			}
		}
	}

	// �I������
	Uninit();

	// ����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���V�[�W��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount			 = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil	 = true;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬	[Z�e�X�g�Ŏg��]
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed					 = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�e�B���O���[�h�L��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	//++++++++++++++++++++++++++++++++++++++++
	// �t�@�C���ǂݍ���
	//++++++++++++++++++++++++++++++++++++++++

	// �L�[�{�[�h
	InitKeyboard(hInstance, hWnd);

	// �Q�[���p�b�h
	InitGamapad(hInstance, hWnd);

	// �T�E���h
	InitSound(hWnd);

	// �t�F�[�h
	InitFade(g_mode);

	// ���[�h
	SetMode(g_mode);

#if _DEBUG
	// �f�o�b�O���O
	InitDebug_Log();
#endif

	// rand�̒l���X�V����
	srand((unsigned int)time(0));

	return S_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Uninit(void)
{
	//++++++++++++++++++++++++++++++++++++++++
	// �t�@�C���ǂݍ��ݏ��̔j��
	//++++++++++++++++++++++++++++++++++++++++

	// �L�[�{�[�h
	UninitKeyboard();

	// �Q�[���p�b�h
	UninitGamapad();

	// �t�F�[�h
	UninitFade();

	// �T�E���h
	UninitSound();

#if _DEBUG
	// �f�o�b�O���O
	UninitDebug_Log();
#endif

	if(g_pD3DDevice != NULL)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Update(void)
{
	// �L�[�{�[�h
	UpdateKeyboard();

	// �Q�[���p�b�h
	UpdateGamapad();

	// �e��ʂ̍X�V����
	switch (g_mode)
	{
	case MODE_TITLE:		// �^�C�g��
		UpdateTitle();
		break;

	case MODE_TUTORIAL:		// �`���[�g���A��
		UpdateTutorial();
		break;

	case MODE_GAME:			// �Q�[���{��
		UpdateGame();
		break;

	case MODE_RESULT:		// ���U���g
		UpdateResult();
		break;
	}

	// �t�F�[�h
	UpdateFade();

#if _DEBUG
	// �f�o�b�O���O
	UpdateDebug_Log();
#endif
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.0f) , 1.0f, 0);		//D3DCOLOR_RGBA(0, 0, 0, 0)

	// �`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		// �e��ʂ̕`�揈��
		switch (g_mode)
		{
		case MODE_TITLE:		// �^�C�g��
			DrawTitle();
			break;

		case MODE_TUTORIAL:		// �`���[�g���A��
			DrawTutorial();
			break;

		case MODE_GAME:			// �Q�[���{��
			DrawGame();
			break;

		case MODE_RESULT:		// ���U���g
			DrawResult();
			break;
		}

		// �t�F�[�h
		DrawFade();

#if _DEBUG
		// �f�o�b�O���O
		DrawDebug_Log();
#endif

		// �`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �f�o�C�X�̎擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}


//=============================================================================
// ���[�h�ݒ菈��
//=============================================================================
void SetMode(MODE mode)
{
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// �e��ʂ̏I������  -----  ���݂̏�� [���[�h]  -----
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	switch (g_mode)
	{
	case MODE_TITLE:		// �^�C�g��
		UninitTitle();
		// ������~
		StopSound();
		break;

	case MODE_TUTORIAL:		// �`���[�g���A��
		UninitTutorial();
		// ������~
		StopSound();
		break;

	case MODE_GAME:			// �Q�[���{��
		UninitGame();
		// ������~
		StopSound();
		break;
	case MODE_RESULT:		// ���U���g
		UninitResult();
		// ������~
		StopSound();
		break;
	}

	// ���̃��[�h��ݒ肷��
	g_mode = mode;

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// �e��ʂ̏���������  -----  ���̏�� [���[�h]  -----
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	switch (mode)
	{
	case MODE_TITLE:		// �^�C�g��
		InitTitle();
		// BGM [�^�C�g��]
		PlaySound(SOUND_LABEL_BGM000);
		break;

	case MODE_TUTORIAL:		// �`���[�g���A��
		InitTutorial();
		PlaySound(SOUND_LABEL_BGM000);

		break;

	case MODE_GAME:			// �Q�[���{��
		InitGame();
		// BGM [�Q�[��]
		PlaySound(SOUND_LABEL_BGM005);
		PlaySound(SOUND_LABEL_BGM_WATER);		// ��̉�
		break;

	case MODE_RESULT:		// ���U���g
		InitResult();
		// BGM [���U���g]
		PlaySound(SOUND_LABEL_BGM002);
		break;
	}
	// ���̃��[�h��ݒ肷��
	g_mode = mode;
}

//=============================================================================
// ���[�h�擾����
//=============================================================================
MODE GetMode(void)
{
	return g_mode;		// ���݂̏�� [���[�h] ��Ԃ�
}

//=============================================================================
// FPS�擾����
//=============================================================================
int GetFPS(void)
{
	return g_nCountFPS;		// FPS��Ԃ�
}