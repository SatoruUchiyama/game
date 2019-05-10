//==========================================================================-==
//
// �V�[������ [scene.cpp]
// Author : satoru uchiyama
//
//==========================================================================-==
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�:
//-----------------------------------------------------------------------------

//*============================================================================
//	�f�t�H���g�R���X�g���N�^
//*============================================================================
CScene2d::CScene2d(int nPriority) :CScene(nPriority)
{
	m_pTexture = NULL;		   // �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;		  // ���_�o�b�t�@�ւ̃|�C���^
}
//*============================================================================
//	�f�X�g���N�^
//*============================================================================
CScene2d::~CScene2d()
{

}

//*============================================================================
// �|���S���̏���������
//*============================================================================
HRESULT CScene2d::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager manager;
	pDevice = manager.GetRenderer()->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	m_fLength = sqrtf((m_fwidth / 2 + m_fwidth / 2)*(m_fheight / 2 + m_fheight / 2));
	m_fAngle = atan2f(m_fwidth / 2, m_fheight / 2);

	// �|���S���̈ʒu��ݒ�
	//m_posPolygon = posd;
	//m_posPolygon = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	VERTEX_2D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

#if 1	//Texture����]
	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x, m_posPolygon.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x, m_posPolygon.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x, m_posPolygon.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x, m_posPolygon.y, 0.0f);

#endif

#if 0	//Texture��]
	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x + sinf(-D3DX_PI + m_fAngle + m_rotPolygon.x)*m_fLength,
		m_posPolygon.y + cosf(-D3DX_PI + m_fAngle + m_rotPolygon.y)*m_fLength, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x + sinf(D3DX_PI - m_fAngle + m_rotPolygon.x)*m_fLength,
		m_posPolygon.y + cosf(D3DX_PI - m_fAngle + m_rotPolygon.y)*m_fLength, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x + sinf(-m_fAngle + m_rotPolygon.x)*m_fLength,
		m_posPolygon.y + cosf(-m_fAngle + m_rotPolygon.y)*m_fLength, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + sinf(m_fAngle + m_rotPolygon.x)*m_fLength,
		m_posPolygon.y + cosf(m_fAngle + m_rotPolygon.y)*m_fLength, 0.0f);

#endif
	// �e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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

//*============================================================================
// �|���S���̏I������
//*============================================================================
void CScene2d::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//*============================================================================
// �|���S���̍X�V����
//*============================================================================
void CScene2d::Update(void)
{
	
}

//*============================================================================
// �|���S���̕`�揈��
//*============================================================================
void CScene2d::Draw(void)
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

//CScene2d *CScene2d::Create(D3DXVECTOR3 posd)
//{
//	CScene2d *pScene2d;
//
//	pScene2d = new  CScene2d;
//
//
//	pScene2d->Init();
//
//
//	pScene2d->m_posPolygon = posd;
//
//	return pScene2d;
//}


//********************************************
//
//********************************************
void CScene2d::SetPos(D3DXVECTOR3 pos)
{
	/*m_rotPolygon.x -= 0.08f;
	m_rotPolygon.y -= 0.08f;*/
	m_posPolygon = pos;

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	/*pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x + sinf(-D3DX_PI + m_fAngle + m_rotPolygon.x)*m_fLength,
		m_posPolygon.y + cosf(-D3DX_PI + m_fAngle + m_rotPolygon.y)*m_fLength, 0.0f);

	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x + sinf(D3DX_PI - m_fAngle + m_rotPolygon.x)*m_fLength,
		m_posPolygon.y + cosf(D3DX_PI - m_fAngle + m_rotPolygon.y)*m_fLength, 0.0f);

	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x + sinf(-m_fAngle + m_rotPolygon.x)*m_fLength,
		m_posPolygon.y + cosf(-m_fAngle + m_rotPolygon.y)*m_fLength, 0.0f);

	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + sinf(m_fAngle + m_rotPolygon.x)*m_fLength,
		m_posPolygon.y + cosf(m_fAngle + m_rotPolygon.y)*m_fLength, 0.0f);*/

#if 1	//Texture����]
	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x - m_sizePolygon.x, m_posPolygon.y - m_sizePolygon.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x + m_sizePolygon.x, m_posPolygon.y - m_sizePolygon.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x - m_sizePolygon.x, m_posPolygon.y + m_sizePolygon.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + m_sizePolygon.x, m_posPolygon.y + m_sizePolygon.y, 0.0f);

#endif

	m_pVtxBuff->Unlock();
}

void CScene2d::SetSize(D3DXVECTOR3 sizeBg)
{
	/*m_rotPolygon.x -= 0.08f;
	m_rotPolygon.y -= 0.08f;*/
	m_sizePolygon = sizeBg;
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

#if 1	//Texture����]
	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x - sizeBg.x, m_posPolygon.y - sizeBg.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x + sizeBg.x, m_posPolygon.y - sizeBg.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x - sizeBg.x, m_posPolygon.y + sizeBg.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + sizeBg.x, m_posPolygon.y + sizeBg.y, 0.0f);

#endif

	m_pVtxBuff->Unlock();
}
void CScene2d::SetColor(D3DXCOLOR color)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(color.r, color.g, color.b, color.a);
	pVtx[1].col = D3DXCOLOR(color.r, color.g, color.b, color.a);
	pVtx[2].col = D3DXCOLOR(color.r, color.g, color.b, color.a);
	pVtx[3].col = D3DXCOLOR(color.r, color.g, color.b, color.a);

	m_pVtxBuff->Unlock();
}
//********************************************
//	�����̏���
//********************************************
void CScene2d::SetExplosion(int PatternAnimation)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0.125f*PatternAnimation, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f*PatternAnimation+ 0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.125f*PatternAnimation, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f*PatternAnimation+ 0.125f, 1.0f);

	m_pVtxBuff->Unlock();
}

//********************************************
//	�|���S���̒�������
//********************************************
void CScene2d::SetLength(float fwidth, float fheight)
{
	m_fwidth = fwidth;
	m_fheight = fheight;

	m_fLength = sqrtf((m_fwidth / 2 + m_fwidth / 2)*(m_fheight / 2 + m_fheight / 2));
	m_fAngle = atan2f(m_fwidth / 2, m_fheight / 2);
}

//********************************************
//	
//********************************************
void CScene2d::SetBgTexPos(D3DXVECTOR2 *pBgTexPos)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`���̐���
	pVtx[0].tex = pBgTexPos[0];
	pVtx[1].tex = pBgTexPos[1];
	pVtx[2].tex = pBgTexPos[2];
	pVtx[3].tex = pBgTexPos[3];

	m_pVtxBuff->Unlock();
}

D3DXVECTOR3 CScene2d::GetPos(void)
{
	return m_posPolygon;
}

//--------------------------------------------
//	�e�N�X�`���̎󂯓n��
//--------------------------------------------
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}