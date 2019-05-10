//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �t�F�[�h���� [fade.cpp]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_FADE		""					// �t�F�[�h�̃e�N�X�`����
#define FADE_POS_X			(0)					// �t�F�[�h�̍���X���W
#define FADE_POS_Y			(0)					// �t�F�[�h�̍���Y���W			
#define FADE_WIDTH			(SCREEN_WIDTH)		// �t�F�[�h�̕�
#define FADE_HEIGHT			(SCREEN_HEIGHT)		// �t�F�[�h�̍���
#define FADE_SPEED			(0.01f)				// �t�F�[�h�X�s�[�h	
#define TITLE_FADE_SLOW		(3)					// �t�F�[�h�X�s�[�h��x������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);		// ���_���̐ݒ�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureFade = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
FADE					g_fade;					// �t�F�[�h���
MODE					g_modeNext;				// ���̃��[�h
D3DXCOLOR				g_colorFade;			// �t�F�[�h�F

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitFade(MODE modeNext)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_fade = FADE_IN;			// �t�F�[�h�C�����
	g_modeNext = modeNext;		
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		// �Ó]

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FADE, &g_pTextureFade);

	// ���_���̐ݒ�
	MakeVertexFade(pDevice);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitFade(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateFade(void)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�@�t�F�[�h�C��
			g_colorFade.a -= FADE_SPEED;		// ��ʂ𓧖��ɂ��Ă���

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;		// �������Ă��Ȃ���Ԃɂ���
			}
		}
		else if (g_fade == FADE_OUT)
		{// �t�F�[�h�A�E�g
			// ���݂̃��[�h���擾
			MODE Mode = GetMode();

			g_colorFade.a += FADE_SPEED;		// ��ʂ��Ó]���Ă���

			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;		// �t�F�[�h�C����Ԃɂ���

				// ���[�h�ݒ�
				SetMode(g_modeNext);
			}
		}

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[
		for (int nCol = 0; nCol < 4; nCol++)
		{
			pVtx[nCol].col = g_colorFade;
		}

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffFade->Unlock();
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawFade(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���_���̍쐬
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		// �m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&g_pVtxBuffFade,
								NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	// ���_���
	pVtx[0].pos = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(FADE_POS_X + FADE_WIDTH, FADE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y + FADE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(FADE_POS_X + FADE_WIDTH, FADE_POS_Y + FADE_HEIGHT, 0.0f);
	// rhw
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].rhw = 1.0f;
	}
	// ���_�J���[
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;
	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �t�F�[�h�̐ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;										// �t�F�[�h�A�E�g���
	g_modeNext = modeNext;									// ���̃��[�h
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// �������(����)
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �t�F�[�h�̎擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FADE GetFade(void)
{
	return g_fade;
}

