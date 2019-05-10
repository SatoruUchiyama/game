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
#include "player.h"
#include "bg.h"
#include "explosion.h"
#include "bullet.h"
#include "number.h"
#include "effect.h"
#include "tutorial.h"
#include "fade.h"
#include "logo.h"
#include "enemy.h"
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
CTutorial::CTutorial()
{

}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CTutorial::~CTutorial()
{

}

//HRESULT CTitle::Lood(void)
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
//void CTitle::Unlood(void)
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
HRESULT CTutorial::Init(void)
{
	CBg::Lood();
	//CPlayer::Lood();
	CLogo::Lood();
	CPlayer::Lood();
	CEffect::Lood();
	CBullet::Lood();		//�e�̃e�N�X�`�������[�h
	CExplosion::Lood();
	CEnemy::Lood();
	//CLogo::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	//CLogo::Create(D3DXVECTOR3(400.0f, 300.0f, 0.0f));

	//�v���C���[�̍��W���N���G�C�g
	CPlayer::Create(D3DXVECTOR3(1050.0f, 600.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), CPlayer::OBJTYPE_PLAYER_01);
	CPlayer::Create(D3DXVECTOR3(1100.0f, 600.0f, 0.0f), D3DXVECTOR3(50.0f, 30.0f, 0.0f), CPlayer::OBJTYPE_PLAYER_02);


	CEnemy::Create(D3DXVECTOR3(1000.0f, 200.0f, 0.0f), CEnemy::ENEMY_TARGET_04,100, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	//CPlayer::Create(D3DXVECTOR3(600.0f, 600.0f, 0.0f));
	//CPlayer::Create(D3DXVECTOR3(500.0f, 600.0f, 0.0f));
	CLogo::Create(D3DXVECTOR3(450.0f, 300.0f, 0.0f), CLogo::LOGO_TYPE_02, D3DXVECTOR3(450.0f, 300.0f, 0.0f));
	CLogo::Create(D3DXVECTOR3(620.0f, 650.0f, 0.0f), CLogo::LOGO_TYPE_04, D3DXVECTOR3(400.0f, 300.0f, 0.0f));
	CBg::Create();
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CTutorial::Uninit(void)
{
	CEffect::Unlood();
	CBullet::Unlood();		//�e�̃e�N�X�`�������[�h
	CExplosion::Unlood();
	CEnemy::Unlood();
	CPlayer::Unlood();
	CLogo::Unlood();

	CBg::Unlood();

	CScene::ReleaseAll();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CTutorial::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CInputJoystick *pJoystick = CManager::GetInputJoystick();

	CFade *pFade = CManager::GetFade();

	//
	if (pKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		//CManager::SetMode(CManager::MODE_GAME);
		pFade->Set(CManager::MODE_GAME);
	}

	//
	if (pJoystick->GetPress(11) == true)
	{
		pFade->Set(CManager::MODE_GAME);
	}
}

void CTutorial::Draw(void)
{

}

CTutorial *CTutorial::Create(void)
{
	CTutorial *pTitle;
	pTitle = new  CTutorial;
	pTitle->Init();

	return pTitle;
}