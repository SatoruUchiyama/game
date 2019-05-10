//=============================================================================
//
// ポーズメニュー処理 [pauseselect.cpp]
// Author : 
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "Player.h"
#include "pauselogo.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

LPDIRECT3DTEXTURE9 CPauselogo::m_pTexture[MAX_PAUSEMENU] = {};
CPauselogo::SELECTMODE CPauselogo::m_Mode = SELECTMODE_CONTINUE;
//-----------------------------------------------------------------------------
// デフォルトコンストラクタ
//-----------------------------------------------------------------------------
CPauselogo::CPauselogo(int nPriority) :CScene(nPriority)
{
	for (int nCount = 0; nCount < MAX_PAUSEMENU; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	m_fMenuPosY = 0;
}
//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CPauselogo::~CPauselogo()
{

}

HRESULT CPauselogo::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\ちゅ4.jpg", &m_pTexture[0]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\ちゅ5.jpg", &m_pTexture[1]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\ちゅ6.jpg", &m_pTexture[2]);

	return S_OK;
}

void CPauselogo::Unlood(void)
{
	for (int nCount = 0; nCount < MAX_PAUSEMENU; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPauselogo::Init(void)
{
	float fMenuPosY = 150.0;

	m_Mode = SELECTMODE_CONTINUE;

	m_nSelect = 0;

	m_color[0] = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);

	for (int nCnt = 1; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		m_color[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//fMenuPosY += 150;
	}
	
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2d(7);
		m_apScene2D[nCnt]->Init();
		m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(150.0f, 50.0f, 50.0f));
		m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(650.0f, (250.0f+ m_fMenuPosY), 0.0f));
		m_apScene2D[nCnt]->SetColor(D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f));
		m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
		m_fMenuPosY += 150;
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPauselogo::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}
	
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPauselogo::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CInputJoystick *pJoystick = CManager::GetInputJoystick();
	CFade *pFade = CManager::GetFade();

	if (pKeyboard->GetTrigger(DIK_DOWN) == true || pJoystick->GetTrigger(2) == true)
	{
		m_nSelect = (m_nSelect + 1) % 3;
	}
	if (pKeyboard->GetTrigger(DIK_UP) == true || pJoystick->GetTrigger(1) == true)
	{
		m_nSelect = (m_nSelect + 2) % 3;
	}

	if (pKeyboard->GetTrigger(DIK_S) == true)
	{
		m_nSelect = (m_nSelect + 1) % 3;
	}
	if (pKeyboard->GetTrigger(DIK_W) == true)
	{
		m_nSelect = (m_nSelect + 2) % 3;
	}

	for (int nCount = 0; nCount < MAX_PAUSEMENU; nCount++)
	{
		if (m_nSelect == nCount)
		{
			m_color[m_nSelect] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		}
		else
		{
			m_color[m_nSelect] = D3DXCOLOR(1.0f, 1.0f, 0.5f, 0.5);
		}
		m_apScene2D[nCount]->SetColor(m_color[m_nSelect]);
	}
	
}

//=============================================================================
// 描画処理
//=============================================================================
void CPauselogo::Draw(void)
{

}

CPauselogo::SELECTMODE CPauselogo::GetMode(void)
{
	return m_Mode;
}
int CPauselogo::GetSelect(void)
{
	return m_nSelect;
}
//=============================================================================
// セレクトモードの取得
//=============================================================================
CPauselogo *CPauselogo::Create(D3DXVECTOR3 pos, float fwidth, float fheight)
{
	CPauselogo *pPauselogo;
	pPauselogo = new  CPauselogo;
	pPauselogo->m_pos = pos;
	pPauselogo->m_fwidth = fwidth;
	pPauselogo->m_fheight = fheight;
	pPauselogo->Init();

	return pPauselogo;
}