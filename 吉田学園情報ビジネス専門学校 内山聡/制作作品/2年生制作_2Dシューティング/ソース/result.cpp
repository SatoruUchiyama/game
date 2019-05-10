//==========================================================================-==
//
// Player���� [bg.cpp]
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
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
//LPDIRECT3DTEXTURE9 CTitle::m_pTexture[MAX_BG_TEXTURE] = {};

//-----------------------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-----------------------------------------------------------------------------
CResult::CResult()
{

}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CResult::~CResult()
{

}

//HRESULT CResult::Lood(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	CManager Manager;
//	pDevice = Manager.GetRenderer()->GetDevice();
//	//�e�N�X�`���ǂݍ���
//	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_0.jpg", &m_pTexture[0]);
//	//�e�N�X�`���ǂݍ���
//	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_kumo_kage.png", &m_pTexture[1]);
//	//�e�N�X�`���ǂݍ���
//	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_kumo_kage_01.png", &m_pTexture[2]);
//	//�e�N�X�`���ǂݍ���
//	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\bg5.png", &m_pTexture[3]);
//
//	return S_OK;
//}
//void CResult::Unlood(void)
//{
//	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
//	{
//		// �e�N�X�`���̔j��
//		if (m_pTexture[nCount] != NULL)
//		{
//			m_pTexture[nCount]->Release();
//			m_pTexture[nCount] = NULL;
//		}
//	}
//
//}

//-----------------------------------------------------------------------------
// ����������
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
// �I������
//-----------------------------------------------------------------------------
void CResult::Uninit(void)
{
	CBg::Unlood();
	CLogo::Unlood();
	CScene::ReleaseAll();
}

//-----------------------------------------------------------------------------
// �X�V����
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