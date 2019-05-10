//=============================================================================
//
// UI���� [UI.cpp]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#include "UI.h"
#include "Gamepad.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_TEXTURENAME0	"data/TEXTURE/LB.jpg"	// �^�C�g���̃e�N�X�`����
#define UI_TEXTURENAME1	"data/TEXTURE/RB.jpg"	// �^�C�g���̃e�N�X�`����
#define UI_TEXTURENAME2	"data/TEXTURE/LT.jpg"	// �^�C�g���̃e�N�X�`����
#define UI_TEXTURENAME3	"data/TEXTURE/RT.jpg"	// �^�C�g���̃e�N�X�`����
#define UI_SIZE_X	(50.0f)	// �^�C�g���̑傫��(X)
#define UI_SIZE_Y	(50.0f)	// �^�C�g���̑傫��(Y)
#define MAX_UI		(4)			// �^�C�g���̃e�N�X�`����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureUI[MAX_UI] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
UI g_aUI[MAX_UI];
int g_nCntUI;

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	g_aUI[0].pos = D3DXVECTOR3(UI_SIZE_X + 10.0f, UI_SIZE_Y + 10.0f, 0.0f);
	g_aUI[0].nType = 0;
	g_aUI[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_aUI[1].pos = D3DXVECTOR3(UI_SIZE_X + 120.0f, UI_SIZE_Y + 10.0f, 0.0f);
	g_aUI[1].nType = 1;
	g_aUI[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_aUI[2].pos = D3DXVECTOR3(UI_SIZE_X + 10.0f, UI_SIZE_Y + 120.0f, 0.0f);
	g_aUI[2].nType = 2;
	g_aUI[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_aUI[3].pos = D3DXVECTOR3(UI_SIZE_X + 120.0f, UI_SIZE_Y + 120.0f, 0.0f);
	g_aUI[3].nType = 3;
	g_aUI[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_nCntUI = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, UI_TEXTURENAME0, &g_pTextureUI[0]);
	D3DXCreateTextureFromFile(pDevice, UI_TEXTURENAME1, &g_pTextureUI[1]);
	D3DXCreateTextureFromFile(pDevice, UI_TEXTURENAME2, &g_pTextureUI[2]);
	D3DXCreateTextureFromFile(pDevice, UI_TEXTURENAME3, &g_pTextureUI[3]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUI,
		NULL);

	VERTEX_2D*pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{
		// ���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - UI_SIZE_X, g_aUI[nCntUI].pos.y - UI_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + UI_SIZE_X, g_aUI[nCntUI].pos.y - UI_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - UI_SIZE_X, g_aUI[nCntUI].pos.y + UI_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + UI_SIZE_X, g_aUI[nCntUI].pos.y + UI_SIZE_Y, 0.0f);

		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffUI->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitUI(void)
{
	for (int nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureUI[nCntUI] != NULL)
		{
			g_pTextureUI[nCntUI]->Release();
			g_pTextureUI[nCntUI] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffUI != NULL)
	{
		g_pVtxBuffUI->Release();
		g_pVtxBuffUI = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateUI(void)
{
	for (int nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{
		g_aUI[nCntUI].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	}

	if (GetGamapadKeyPress(ELECOM_LB))
	{
		g_aUI[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (GetGamapadKeyPress(ELECOM_RB))
	{
		g_aUI[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (GetGamapadKeyPress(ELECOM_LT))
	{
		g_aUI[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (GetGamapadKeyPress(ELECOM_RT))
	{
		g_aUI[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	VERTEX_2D*pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{
		// ���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - UI_SIZE_X, g_aUI[nCntUI].pos.y - UI_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + UI_SIZE_X, g_aUI[nCntUI].pos.y - UI_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x - UI_SIZE_X, g_aUI[nCntUI].pos.y + UI_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aUI[nCntUI].pos.x + UI_SIZE_X, g_aUI[nCntUI].pos.y + UI_SIZE_Y, 0.0f);

		// ���_�J���[
		pVtx[0].col = g_aUI[nCntUI].col;
		pVtx[1].col = g_aUI[nCntUI].col;
		pVtx[2].col = g_aUI[nCntUI].col;
		pVtx[3].col = g_aUI[nCntUI].col;

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffUI->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffUI, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntUI = 0; nCntUI < MAX_UI; nCntUI++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureUI[g_aUI[nCntUI].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntUI, 2);
	}
}
