//==========================================================================-==
//
// Player���� [player.cpp]
// Author : satoru uchiyama
//
//==========================================================================-==
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "effect.h"
//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�:
//-----------------------------------------------------------------------------


LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;


HRESULT CEffect::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\pipo-hiteffect004.png", &m_pTexture);

	return S_OK;
}
void CEffect::Unlood(void)
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
CEffect::CEffect() : CScene2d(2)
{

}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CEffect::~CEffect()
{

}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT CEffect::Init(D3DXVECTOR3 pos ,D3DXVECTOR3 size, float fRadius, int Life, D3DXCOLOR color)
{
	m_Life = Life;
	m_fRadius = fRadius;
	//CScene2d::SetLength(30.0f, 30.0f);
	CScene2d::Init();
	CScene2d::SetPos(pos);
	CScene2d::SetColor(color);
	//CScene2d::SetSize(size);
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CEffect::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CEffect::Update(void)
{
	
	m_pVtxBuff = GetVtxBuff();
	m_Pos = GetPos();
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	
	m_fRadius -= m_fRadius / m_Life;
	m_Life--;

	//pVtx += nCntEffect * 4;
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fRadius, m_Pos.y - m_fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fRadius, m_Pos.y - m_fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fRadius, m_Pos.y + m_fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fRadius, m_Pos.y + m_fRadius, 0.0f);

	m_pVtxBuff->Unlock();


	if (m_Life == 0 || m_fRadius == 0)
	{
		Uninit();
	}
}

void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager manager;
	pDevice = manager.GetRenderer()->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2d::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRadius, int Life, D3DXCOLOR color)
{
	CEffect *pEffect;
	pEffect = new  CEffect;
	pEffect->Init(pos, size, fRadius, Life, color);

	pEffect->BindTexture(m_pTexture);

	return pEffect;
}
