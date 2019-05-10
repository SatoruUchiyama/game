//==========================================================================-==
//
// Player���� [bg.cpp]
// Author : Satoru Uchiyama
//
//==========================================================================-==
#include "main.h"
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------


LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;
//-----------------------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-----------------------------------------------------------------------------
CNumber::CNumber()
{

}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CNumber::~CNumber()
{

}
//Texture�̓ǂݍ���
HRESULT CNumber::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\number999.png", &m_pTexture);

	return S_OK;
}
//Texture�̓ǂݍ���
void CNumber::Unlood(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

HRESULT CNumber::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager manager;
	pDevice = manager.GetRenderer()->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 /**(MAX_TRUSS *4)*/, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_2D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

#if 1//Texture����]
	// ���_����ݒ�
	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - 25.0f, pos.y- 35.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 25.0f, pos.y- 35.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 25.0f, pos.y+ 35.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 25.0f, pos.y+ 35.0f, 0.0f);
	
#endif
	/*pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2, 0.0f);
*/
	// �e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_�o�b�t�@�̐���
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	m_pVtxBuff->Unlock();

	return S_OK;
}

void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void CNumber::Update(void)
{
	/*VERTEX_2D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2, 0.0f);

	m_pVtxBuff->Unlock();*/
}

void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager manager;
	pDevice = manager.GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void CNumber::DrawScore(int nKioku)
{
	VERTEX_2D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 1.0f);
	m_pVtxBuff->Unlock(); 
}