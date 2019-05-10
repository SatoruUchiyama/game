//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : 
//
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"

CFade::FADE CFade::m_fade = FADE_NONE;
CManager::MODE CFade::m_modeNext;
D3DXCOLOR CFade::m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CFade::CFade()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CFade::~CFade()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	m_fade = FADE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	// ���_���̐ݒ�
	MakeVertexFade(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
{
	// �e�N�X�`���̊J��
	if (m_pTextureFade != NULL)
	{
		m_pTextureFade->Release();
		m_pTextureFade = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_colorFade.a -= 0.025f;
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_colorFade.a += 0.025f;
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;

				//���[�h�ݒ�
				CManager::SetMode(m_modeNext);
			}
		}
	}

	VERTEX_2D *pVtx;

	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	m_pVtxBuffFade->Unlock();
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureFade);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void CFade::MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL
	);

	// ���_�o�b�t�@�̏���ݒ�
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	m_pVtxBuffFade->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�ݒ�
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N

	m_pVtxBuffFade->Unlock();
}
//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
CFade::FADE CFade::Get(void)
{
	return m_fade;
}

CFade *CFade::Create(void)
{
	CFade *pFade = NULL;
	if (pFade == NULL)
	{
		pFade = new CFade;
		
		pFade->Init();
	}
	return pFade;
}
void CFade::Set(CManager::MODE ModeNext)
{
	if (m_fade == FADE_NONE)
	{
		m_fade = FADE_OUT;
		m_modeNext = ModeNext;
		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

}