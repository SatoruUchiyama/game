//==========================================================================-==
//
// Player処理 [bg.cpp]
// Author : Satoru Uchiyama
//
//==========================================================================-==
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "scene2d.h"
#include "player.h"
#include "bg.h"
#include "explosion.h"
#include "bullet.h"
#include "number.h"
#include "effect.h"
#include "title.h"
#include "fade.h"
#include "logo.h"
#include "sound.h"
//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
//LPDIRECT3DTEXTURE9 CTitle::m_pTexture[MAX_BG_TEXTURE] = {};

//-----------------------------------------------------------------------------
// デフォルトコンストラクタ
//-----------------------------------------------------------------------------
CTitle::CTitle()
{

}
//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CTitle::~CTitle()
{

}

//HRESULT CTitle::Lood(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	CManager Manager;
//	pDevice = Manager.GetRenderer()->GetDevice();
//	//テクスチャ読み込み
//	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_0.jpg", &m_pTexture[0]);
//	//テクスチャ読み込み
//	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_kumo_kage.png", &m_pTexture[1]);
//	//テクスチャ読み込み
//	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_kumo_kage_01.png", &m_pTexture[2]);
//	//テクスチャ読み込み
//	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\bg5.png", &m_pTexture[3]);
//
//	return S_OK;
//}
//void CTitle::Unlood(void)
//{
//	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
//	{
//		// テクスチャの破棄
//		if (m_pTexture[nCount] != NULL)
//		{
//			m_pTexture[nCount]->Release();
//			m_pTexture[nCount] = NULL;
//		}
//	}
//
//}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT CTitle::Init(void)
{
	CBg::Lood();
	//CPlayer::Lood();
	CLogo::Lood();
	m_nTimeTitle = 0;

	CLogo::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f),CLogo::LOGO_TYPE_00, D3DXVECTOR3(650.0f, 500.0f, 0.0f));
	CLogo::Create(D3DXVECTOR3(400.0f, 300.0f, 0.0f),CLogo::LOGO_TYPE_00, D3DXVECTOR3(650.0f, 500.0f, 0.0f));
	//CLogo::Create(D3DXVECTOR3(700.0f, 500.0f, 0.0f));
	CLogo::Create(D3DXVECTOR3(620.0f, 600.0f, 0.0f), CLogo::LOGO_TYPE_04, D3DXVECTOR3(400.0f, 300.0f, 0.0f));

	//CPlayer::Create(D3DXVECTOR3(600.0f, 600.0f, 0.0f));
	//CPlayer::Create(D3DXVECTOR3(500.0f, 600.0f, 0.0f));

	CBg::Create();
	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CTitle::Uninit(void)
{

	CLogo::Unlood();

	CBg::Unlood();

	CScene::ReleaseAll();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CTitle::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CInputJoystick *pJoystick = CManager::GetInputJoystick();
	CManager *psound = NULL;
	
	CFade *pFade = CManager::GetFade();

	m_nTimeTitle++;
	//
	if (pJoystick->GetPress(11) == true || pKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO4);
		pFade->Set(CManager::MODE_TUTORIAL);
	}
	else if (m_nTimeTitle % 600 == 0)
	{
		pFade->Set(CManager::MODE_RANKING);
	}
}

void CTitle::Draw(void)
{

}

CTitle *CTitle::Create(void)
{
	CTitle *pTitle;
	pTitle = new  CTitle;
	pTitle->Init();
		
	return pTitle;
}