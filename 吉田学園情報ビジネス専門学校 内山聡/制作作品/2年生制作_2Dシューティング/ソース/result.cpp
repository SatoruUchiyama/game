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
#include "result.h"
#include "fade.h"
#include "bg.h"
#include "logo.h"
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
CResult::CResult()
{

}
//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CResult::~CResult()
{

}

//HRESULT CResult::Lood(void)
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
//void CResult::Unlood(void)
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
HRESULT CResult::Init(void)
{
	CBg::Lood();
	CLogo::Lood();
	CBg::Create();

	CLogo::Create(D3DXVECTOR3(620.0f, 300.0f, 0.0f), CLogo::LOGO_TYPE_03, D3DXVECTOR3(400.0f, 300.0f, 0.0f));
	CLogo::Create(D3DXVECTOR3(620.0f, 600.0f, 0.0f), CLogo::LOGO_TYPE_04, D3DXVECTOR3(400.0f, 300.0f, 0.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CResult::Uninit(void)
{
	CBg::Unlood();
	CLogo::Unlood();
	CScene::ReleaseAll();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CResult::Update(void)
{
		CFade *pFade = CManager::GetFade();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CInputJoystick *pJoystick = CManager::GetInputJoystick();

	if (pJoystick->GetPress(11) == true)
	{
		pFade->Set(CManager::MODE_RANKING);
	}
}

void CResult::Draw(void)
{

}

CResult *CResult::Create(void)
{
	CResult *pResult;
	pResult = new  CResult;
	pResult->Init();

	return pResult;
}