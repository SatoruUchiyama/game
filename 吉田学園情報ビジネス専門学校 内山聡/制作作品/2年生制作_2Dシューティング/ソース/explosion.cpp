//==========================================================================-==
//
// Player���� [player.cpp]
// Author : satoru uchiyama
//
//==========================================================================-==
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�:
//-----------------------------------------------------------------------------


LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;


HRESULT CExplosion::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\explosion000.png", &m_pTexture);

	return S_OK;
}
void CExplosion::Unlood(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//-----------------------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-----------------------------------------------------------------------------
CExplosion::CExplosion():CScene2d(6)
{

}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CExplosion::~CExplosion()
{

}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT CExplosion::Init(D3DXVECTOR3 posExplosion)
{
	//CScene2d::SetLength(30.0f, 30.0f);
	CScene2d::Init();
	CScene2d::SetPos(posExplosion);
	CScene2d::SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	SetObjType(CScene::OBJTYPE_EXPLOSION);//�^�C�v�̎d����
	SetExplosion(0);
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CExplosion::Update(void)
{
	m_nCounterAnimation++;
	if ((m_nCounterAnimation % 5) == 0)
	{
		m_nPatternAnimation = (m_nPatternAnimation + 1) % 8;
		SetExplosion(m_nPatternAnimation);
		if (m_nPatternAnimation >= 8 - 1)
		{
			Uninit();
		}
	}
}

void CExplosion::Draw(void)
{
	CScene2d::Draw();
}

CExplosion *CExplosion::Create(D3DXVECTOR3 posExplosion)
{
	CExplosion *pExplosion;
	pExplosion = new  CExplosion;
	pExplosion->Init(posExplosion);

	pExplosion->BindTexture(m_pTexture);

	return pExplosion;
}
