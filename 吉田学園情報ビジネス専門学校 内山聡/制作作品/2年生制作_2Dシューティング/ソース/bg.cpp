//==========================================================================-==
//
// �w�i���� [bg.cpp]
// Author : Satoru Uchiyama
//
//==========================================================================-==

//=============================================================================
//	�w�b�_�[�ǂݍ���
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bg.h"
#include "scene2d.h"


LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_BG_TEXTURE] = {};

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CBg::CBg() :CScene(0)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
//	�e�N�X�`���̃��[�h
//=============================================================================
HRESULT CBg::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_0.jpg", &m_pTexture[0]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_kumo_kage.png", &m_pTexture[1]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_kumo_kage_01.png", &m_pTexture[2]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\bg5.png", &m_pTexture[3]);

	return S_OK;
}
//=============================================================================
//	�e�N�X�`���̔p��
//=============================================================================
void CBg::Unlood(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBg::Init(void)
{
	SetObjType(CScene::OBJTYPE_BG);		//�^�C�v�̎d����

	//	���W�̐ݒ�
	m_pScene2d[0]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pScene2d[1]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pScene2d[2]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pScene2d[3]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	
	//	�T�C�Y�̐ݒ�
	m_pScene2d[0]->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pScene2d[1]->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pScene2d[2]->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pScene2d[3]->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	m_texBase[0] = 0.0f;
	m_texBase[1] = 0.0f;
	m_texBase[2] = 0.0f;
	m_texBase[3] = 0.0f;
	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		if (m_pScene2d[nCount] != NULL)
		{
			m_pScene2d[nCount]->Uninit();
			m_pScene2d[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBg::Update(void)
{
	D3DXVECTOR2 BgTexPos[4*MAX_BG_TEXTURE];		//	�e�N�X�`���̒��_���

	int nCount2 = 0;							//	�w�i�̖������̃J�E���g

	//	�w�i�̈ړ��X�s�[�h
	m_texBase[0] -= SPEED_BG_00;
	m_texBase[1] -= SPEED_BG_01;
	m_texBase[2] -= SPEED_BG_02;
	m_texBase[3] -= SPEED_BG_03;

	//	�w�i�̍��W�X�V
	for (nCount2 = 0; nCount2 < MAX_BG_TEXTURE; nCount2++)
	{
		BgTexPos[nCount2 + 0] = D3DXVECTOR2(0.0f, m_texBase[nCount2]);
		BgTexPos[nCount2 + 1] = D3DXVECTOR2(1.0f, m_texBase[nCount2]);
		BgTexPos[nCount2 + 2] = D3DXVECTOR2(0.0f, m_texBase[nCount2] + 1.0f);
		BgTexPos[nCount2 + 3] = D3DXVECTOR2(1.0f, m_texBase[nCount2] + 1.0f);

		m_pScene2d[nCount2]->SetBgTexPos(&BgTexPos[0]);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBg::Draw(void)
{

}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CBg *CBg::Create(void)
{
	CBg *pBg;
	pBg = new  CBg;
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		pBg->m_pScene2d[nCount] = new CScene2d(0);
		pBg->m_pScene2d[nCount]->Init();
		pBg->m_pScene2d[nCount]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		pBg->m_pScene2d[nCount]->SetSize(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		pBg->m_pScene2d[nCount]->BindTexture(m_pTexture[nCount]);
	}
	pBg->Init();

	return pBg;
}