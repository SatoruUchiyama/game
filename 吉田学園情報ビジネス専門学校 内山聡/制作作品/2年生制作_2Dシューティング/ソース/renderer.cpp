//==========================================================================-==
//
// �����_���[���� [renderer.cpp]
// Author : satoru uchiyama
//
//==========================================================================-==
#include"main.h"
#include"renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "fade.h"
#include "pause.h"
#include "pauselogo.h"
#include "input.h"
#include "ranking.h"
//CPause *CRenderer::m_pPause = NULL;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;			     // Direct3D�I�u�W�F�N�g
	m_pD3DDevice = NULL;	    // Device�I�u�W�F�N�g(�`��ɕK�v)
	m_FpsCount = NULL;	       //FPS�̃J�E���g�����炤
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));									  // ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;											 // �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							    // �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							   // �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				              // �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		                 // �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;					    	// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					   // �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;						              // �E�B���h�E���[�hbWindow
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;  // ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}
	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				    // ���ʂ��J�����O
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						   // Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				  // ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		 // ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	   // �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	  // �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	 // �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif

	m_bPause = false;
	return S_OK;
}

//*============================================================================
// �I������
//*============================================================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//*============================================================================
// �X�V����
//*============================================================================
void CRenderer::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CInputJoystick *pJoystick = CManager::GetInputJoystick();
	CFade *pFade = CManager::GetFade();
	CManager::MODE mode;
	mode = CManager::GetMode();

	CPauselogo::SELECTMODE SelsectMode;
	SelsectMode = CPauselogo::GetMode();

	if (mode == CManager::MODE_GAME)
	{
		if (pKeyboard->GetTrigger(DIK_P) == true || pJoystick->GetTrigger(11) == true)
		{
			m_bPause = m_bPause ? false : true;

			if (m_bPause == true)
			{
				m_pPauseLogo = CPauselogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 150.0f, 50.0f);

			}
			else
			{
				if (m_pPauseLogo != NULL)
				{
					m_pPauseLogo->Uninit();
					m_pPauseLogo = NULL;
				}
				
			}
		}
		
		if (m_bPause == false)
		{
			CScene::UpdateAll();
		}
		else
		{
			if (m_pPauseLogo != NULL)
			{
				m_pPauseLogo->Update();
			}
			if (pKeyboard->GetTrigger(DIK_RETURN) == true || pJoystick->GetPress(3) == true)
			{
				int nSelect;
				nSelect = m_pPauseLogo->GetSelect();
				if (nSelect == 0)
				{
					SelsectMode = CPauselogo::SELECTMODE_CONTINUE;
				}
				else if (nSelect == 1)
				{
					SelsectMode = CPauselogo::SELECTMODE_RETRY;
				}
				else if (nSelect == 2)
				{
					SelsectMode = CPauselogo::SELECTMODE_QUIT;
				}

				switch (SelsectMode)
				{
				case CPauselogo::SELECTMODE_CONTINUE:
					break;
				case CPauselogo::SELECTMODE_RETRY:
					pFade->Set(CManager::MODE_GAME);
					break;
				case CPauselogo::SELECTMODE_QUIT:
					pFade->Set(CManager::MODE_TITLE);
					break;
				}
				m_bPause = m_bPause ? false : true;
				m_pPauseLogo->Uninit();
				m_pPauseLogo = NULL;
			}
		}
	}
	else
	{
		CScene::UpdateAll();
	}

	//CScene::UpdateAll();
}

//*============================================================================
// �`�揈��
//*============================================================================
void CRenderer::Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 100), 1.0f, 0);

	CFade *pFade = CManager::GetFade();
	CRanking *pRanking = CManager::GetRaning();

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene::DrawAll();

		if (pRanking != NULL)
		{
			pRanking->Draw();
		}
		if (pFade != NULL)
		{
			pFade->Draw();
		}
		
#ifdef _DEBUG
		// FPS�\��
		DrawFPS();
#endif
		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
#ifdef _DEBUG
//*============================================================================
// FPS�\��
//*============================================================================
void CRenderer::DrawFPS(void)
{
	//return�Ŏ����Ă���FPS����
	m_FpsCount = GetFps();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", m_FpsCount);
	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

//LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
//{
//	return m_pD3DDevice;
//}