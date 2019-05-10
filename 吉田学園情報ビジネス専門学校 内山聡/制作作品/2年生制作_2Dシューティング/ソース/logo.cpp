//==========================================================================-==
//
// Player���� [player.cpp]
// Author : satoru uchiyama
//
//==========================================================================-==
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "logo.h"
#include "explosion.h"
#include "score.h"
//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

LPDIRECT3DTEXTURE9 CLogo::m_pTexture[MAX_LOGO] = {};

//-----------------------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-----------------------------------------------------------------------------
CLogo::CLogo() :CScene2d(4)
{

}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CLogo::~CLogo()
{

}

HRESULT CLogo::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\titl.png", &m_pTexture[0]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\�����L���O���S.png", &m_pTexture[1]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\�`���[�g���A��2.png", &m_pTexture[2]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\�v���[���e�[�V����1.png", &m_pTexture[3]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\start.png", &m_pTexture[4]);

	return S_OK;
}
//
void CLogo::Unlood(void)
{
	for (int nCount = 0; nCount < MAX_LOGO; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------4
HRESULT CLogo::Init(D3DXVECTOR3 posPlay, D3DXVECTOR3 size)
{
	//CScene2d::SetLength(50.0f, 50.0f);
	m_nLife = 3;
	CScene2d::Init();
	CScene2d::SetPos(D3DXVECTOR3(posPlay));
	CScene2d::SetSize(size);
	//SetObjType(CScene::OBJTYPE_ENEMY);//�^�C�v�̎d����
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CLogo::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CLogo::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();
	m_pos = GetPos();

	switch (m_type)
	{
	case LOGO_TYPE_00:
		m_move[m_type].x -= sinf(D3DX_PI*0.5) * 13.0f;
		m_move[m_type].y -= cosf(D3DX_PI*0.5) * 13.0f;

		m_move[m_type].x += (0.0f - m_move[m_type].x)*MAX_INERTIAL_ENEMY;
		m_move[m_type].y += (0.0f - m_move[m_type].y)*MAX_INERTIAL_ENEMY;

		m_pos += m_move[m_type];
	default:
		break;
	}
	
	if (-600 > m_pos.x)
	{
		//m_pos.x = SCREEN_WIDTH + m_pos.x;
		m_pos.x = SCREEN_WIDTH+1500 + m_pos.x;
	}

	CScene2d::SetPos(m_pos);
}

void CLogo::Draw(void)
{
	CScene2d::Draw();
}

CLogo *CLogo::Create(D3DXVECTOR3 posC,LOGO_TYPE type, D3DXVECTOR3 size)
{
	CLogo *pLogo;
	pLogo = new  CLogo;
	pLogo->Init(posC, size);
	pLogo->m_type = type;

	pLogo->BindTexture(m_pTexture[type]);

	return pLogo;
}