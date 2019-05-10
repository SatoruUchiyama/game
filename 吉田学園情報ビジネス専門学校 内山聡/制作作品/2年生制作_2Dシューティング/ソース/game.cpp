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
#include "title.h"
#include "game.h"
#include "player.h"
#include "bg.h"
#include "explosion.h"
#include "bullet.h"
#include "score.h"
#include "number.h"
#include "enemy.h"
#include "effect.h"
#include "fade.h"
#include "item.h"
#include "pause.h"
#include "pauselogo.h"
#include "ranking.h"
//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
//LPDIRECT3DTEXTURE9 CTitle::m_pTexture[MAX_BG_TEXTURE] = {};

CScore * CGame::m_score = NULL;
//-----------------------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-----------------------------------------------------------------------------
CGame::CGame()
{

}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CGame::~CGame()
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
HRESULT CGame::Init(void)
{
	CBullet::Lood();		//�e�̃e�N�X�`�������[�h
	CPlayer::Lood();		//�v���C���[�̃e�N�X�`�������[�h
	CExplosion::Lood();
	CBg::Lood();
	//CPause::Lood();
	CEnemy::Lood();
	CItem::Lood();
	CNumber::Lood();
	CEffect::Lood();
	CPauselogo::Lood();
	//
	//�w�i�̃N���G�C�g
	CBg::Create();
	//�v���C���[�̍��W���N���G�C�g
	CPlayer::Create(D3DXVECTOR3(550.0f, 600.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), CPlayer::OBJTYPE_PLAYER_01);
	CPlayer::Create(D3DXVECTOR3(600.0f, 600.0f, 0.0f), D3DXVECTOR3(50.0f, 30.0f, 0.0f), CPlayer::OBJTYPE_PLAYER_02);
	
	//CPause::Create(D3DXVECTOR3(300.0f, 300.0f, 0.0f));

	//
	m_score = CScore::Create(D3DXVECTOR3(950.0f, 500.0f, 0.0f));

	//CEnemy::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	//1��ڂ̓G
	for (int nCount = 1; nCount < 4; nCount++)
	{
		//����
		CEnemy::Create(D3DXVECTOR3(100.0f*nCount, -300.0f, 0.0f), CEnemy::ENEMY_TARGET_01,1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	}
	//2��ڂ̓G
	for (int nCount = 1; nCount < 4; nCount++)
	{
		//����
		CEnemy::Create(D3DXVECTOR3(1300.0f+(nCount*100), 400.0f, 0.0f),CEnemy::ENEMY_TARGET_02,1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	}
	//2��ڂ̓G
	for (int nCount = 1; nCount < 4; nCount++)
	{
		//�E��
		CEnemy::Create(D3DXVECTOR3(-1200.0f+(nCount*100), 100.0f, 0.0f),CEnemy::ENEMY_TARGET_03,1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	}
	//���ɍs��5�̖�
	CEnemy::Create(D3DXVECTOR3(2000.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1,D3DXVECTOR3(30.0f,30.0f,0.0f));
	CEnemy::Create(D3DXVECTOR3(2000.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(2100.0f, 200.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));

	CEnemy::Create(D3DXVECTOR3(2200.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(2200.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));

	//�E�ɍs��5�̖�
	CEnemy::Create(D3DXVECTOR3(-2000.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-2000.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-2100.0f, 200.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-2200.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-2200.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));

	//3�A�P
	CEnemy::Create(D3DXVECTOR3(2900.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(3300.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(3700.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));

	//���ɍs��
	CEnemy::Create(D3DXVECTOR3(100.0f, -900.0f, 0.0f), CEnemy::ENEMY_TARGET_01, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(500.0f, -900.0f, 0.0f), CEnemy::ENEMY_TARGET_01, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(900.0f, -900.0f, 0.0f), CEnemy::ENEMY_TARGET_01, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));

	//�E�ɍs��
	CEnemy::Create(D3DXVECTOR3(-2500.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-2500.0f, 400.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-2600.0f, 500.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));

	//���ɍs��5�̖�
	CEnemy::Create(D3DXVECTOR3(3900.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(3900.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(4000.0f, 200.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(4100.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(4100.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_02, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));

	//3�A�P
	CEnemy::Create(D3DXVECTOR3(-4000.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-4400.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-4800.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));

	//�E�ɍs��5�̖�
	CEnemy::Create(D3DXVECTOR3(-4300.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-4300.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-4400.0f, 200.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-4500.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-4500.0f, 300.0f, 0.0f), CEnemy::ENEMY_TARGET_03, 1, D3DXVECTOR3(60.0f, 50.0f, 0.0f));

	//���ɍs��
	CEnemy::Create(D3DXVECTOR3(100.0f, -1600.0f, 0.0f), CEnemy::ENEMY_TARGET_01, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(650.0f, -1600.0f, 0.0f), CEnemy::ENEMY_TARGET_01, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(1200.0f, -1600.0f, 0.0f), CEnemy::ENEMY_TARGET_01, 1, D3DXVECTOR3(30.0f, 30.0f, 0.0f));

	//3�A�P		�{�X
	CEnemy::Create(D3DXVECTOR3(-6000.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_05, 10, D3DXVECTOR3(100.0f, 80.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-6400.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_05, 10, D3DXVECTOR3(100.0f, 80.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(-6800.0f, 100.0f, 0.0f), CEnemy::ENEMY_TARGET_05, 10, D3DXVECTOR3(100.0f, 80.0f, 0.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CGame::Uninit(void)
{
	CRanking::SaveRanking();
	//�S�Ă̏I������
	CScene::ReleaseAll();
	//
	CBullet::Unlood();
	//
	CPlayer::Unlood();
	/*m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;*/
	//
	CExplosion::Unlood();
	//
	CBg::Unlood();
	//
	//CPause::Unlood();
	//
	CEnemy::Unlood();
	//
	CItem::Unlood();
	//
	CNumber::Unlood();
	//
	CEffect::Unlood();
	CPauselogo::Unlood();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CGame::Update(void)
{
	CFade *pFade = CManager::GetFade();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CInputJoystick *pJoystick = CManager::GetInputJoystick();
}

void CGame::Draw(void)
{

}

CGame *CGame::Create(void)
{
	CGame *pGame;
	pGame = new  CGame;
	pGame->Init();
		
	return pGame;
}
//CPlayer *CGame::GetPlayer(int nIdx)
//{
//	return m_pPlayer[nIdx];
//}