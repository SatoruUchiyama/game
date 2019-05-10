//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#include "title.h"
#include "fade.h"
#include "sound.h"
#include "camera.h"
#include "input.h"
#include "light.h"
#include "field.h"
#include "meshField.h"
#include "object.h"
#include "meshDome.h"
#include "Gamepad.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_TEXTURENAME0	"data/TEXTURE/title.png"	// �^�C�g���̃e�N�X�`����
#define TITLE_TEXTURENAME1	"data/TEXTURE/Pressstart.png"	// �^�C�g���̃e�N�X�`����
#define TITLE_SIZE_X	(380.0f)	// �^�C�g���̑傫��(X)
#define TITLE_SIZE_Y	(125.0f)	// �^�C�g���̑傫��(Y)
#define ENTER_WIDTH		(150.0f)	// �uPRESS ENTER�v�̕�
#define ENTER_HEIGHT	(50.0f)		// �uPRESS ENTER�v�̍���
#define MAX_TITLE		(2)			// �^�C�g���̃e�N�X�`����
#define TITLE_TIME		(600)		// �����L���O��ʂ܂ł̎���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
TITLE g_aTitle[MAX_TITLE];
int g_nTransparent;
int g_nCntTitle;

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitTitle(void)
{
	// �J�����̏���������
	InitCamera();

	// ���C�g
	InitLight();

	// �t�B�[���h
	InitField();

	// ���b�V���t�B�[���h
	InitmeshField();

	// ���b�V���h�[��
	InitmeshDome();

	// �I�u�W�F�N�g
	InitObject();

	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();


	g_aTitle[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 0.0f);
	g_aTitle[0].nType = 0;
	g_aTitle[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	g_aTitle[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 0.0f);
	g_aTitle[1].nType = 1;
	g_aTitle[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	g_nTransparent = 0;
	g_nCntTitle = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME0, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME1, &g_pTextureTitle[1]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aTitle[0].pos.x - TITLE_SIZE_X, g_aTitle[0].pos.y - TITLE_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitle[0].pos.x + TITLE_SIZE_X, g_aTitle[0].pos.y - TITLE_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitle[0].pos.x - TITLE_SIZE_X, g_aTitle[0].pos.y + TITLE_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitle[0].pos.x + TITLE_SIZE_X, g_aTitle[0].pos.y + TITLE_SIZE_Y, 0.0f);

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

	// ���_�̍��W
	pVtx[4].pos = D3DXVECTOR3(g_aTitle[1].pos.x - ENTER_WIDTH, g_aTitle[1].pos.y - ENTER_HEIGHT, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_aTitle[1].pos.x + ENTER_WIDTH, g_aTitle[1].pos.y - ENTER_HEIGHT, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_aTitle[1].pos.x - ENTER_WIDTH, g_aTitle[1].pos.y + ENTER_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_aTitle[1].pos.x + ENTER_WIDTH, g_aTitle[1].pos.y + ENTER_HEIGHT, 0.0f);

	// 1.0f�ŌŒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	// ���_�J���[
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	// �e�N�X�`�����W
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitTitle(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g
	UninitLight();

	// �t�B�[���h
	UninitField();

	// ���b�V���t�B�[���h
	UninitmeshField();

	// ���b�V���h�[��
	UninitmeshDome();

	// �I�u�W�F�N�g
	UninitObject();

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateTitle(void)
{
	// �J�����̍X�V����
	UpdateCamera();

	// ���C�g
	UpdateLight();

	// ���b�V���h�[��
	UpdatemeshDome();

	// ���b�V���t�B�[���h
	UpdatemeshField();

	// �I�u�W�F�N�g
	UpdateObject();

	// �t�B�[���h
	UpdateField();

	if (g_aTitle[0].col.a < 1.0f)
	{
		g_aTitle[0].col.a += 0.005f;

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamapadKeyTrigger(ELECOM_START))
		{// �X�L�b�v
			g_aTitle[0].col.a = 1.0f;
		}
	}
	else
	{
		g_nCntTitle++;	// �����L���O��ʂ܂ł̃J�E���^

		FADE pFade;

		// �t�F�[�h�̎擾
		pFade = GetFade();
		if (pFade == FADE_NONE)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamapadKeyTrigger(ELECOM_START))
			{// ���j���[��ʂ�
				// ���[�h�I��
				SetFade(MODE_TUTORIAL);
			}
			else if (g_nCntTitle >= TITLE_TIME)
			{// ���Ԍo�߂Ń����L���O��ʂ�
				//���[�h�I��
				SetFade(MODE_RESULT);
			}
		}

		if (g_aTitle[1].col.a <= 1.0f && g_nTransparent == 0)
		{//	�����x��1.0f�̎�
			g_aTitle[1].col.a -= 0.02f;
			if (g_aTitle[1].col.a <= 0.0f)
			{// 0.0f�ȉ��ɂȂ����Ƃ�
				g_aTitle[1].col.a = 0.0f;
				g_nTransparent = 1;
			}
		}
		else if (g_aTitle[1].col.a >= 0.0f && g_nTransparent == 1)
		{//	�����x��0.0f�̎�
			g_aTitle[1].col.a += 0.02f;
			if (g_aTitle[1].col.a >= 1.0f)
			{// 1.0f�ȏ�ɂȂ����Ƃ�
				g_aTitle[1].col.a = 1.0f;
				g_nTransparent = 0;
			}
		}
	}

	VERTEX_2D*pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aTitle[0].pos.x - TITLE_SIZE_X, g_aTitle[0].pos.y - TITLE_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitle[0].pos.x + TITLE_SIZE_X, g_aTitle[0].pos.y - TITLE_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitle[0].pos.x - TITLE_SIZE_X, g_aTitle[0].pos.y + TITLE_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitle[0].pos.x + TITLE_SIZE_X, g_aTitle[0].pos.y + TITLE_SIZE_Y, 0.0f);

	// ���_�̍��W
	pVtx[4].pos = D3DXVECTOR3(g_aTitle[1].pos.x - ENTER_WIDTH, g_aTitle[1].pos.y - ENTER_HEIGHT, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_aTitle[1].pos.x + ENTER_WIDTH, g_aTitle[1].pos.y - ENTER_HEIGHT, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_aTitle[1].pos.x - ENTER_WIDTH, g_aTitle[1].pos.y + ENTER_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_aTitle[1].pos.x + ENTER_WIDTH, g_aTitle[1].pos.y + ENTER_HEIGHT, 0.0f);

	// ���_�J���[
	pVtx[0].col = g_aTitle[0].col;
	pVtx[1].col = g_aTitle[0].col;
	pVtx[2].col = g_aTitle[0].col;
	pVtx[3].col = g_aTitle[0].col;

	pVtx[4].col = g_aTitle[1].col;
	pVtx[5].col = g_aTitle[1].col;
	pVtx[6].col = g_aTitle[1].col;
	pVtx[7].col = g_aTitle[1].col;

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawTitle(void)
{
	// �J����
	SetCamera();		// ���C���J����

	// ���b�V���t�B�[���h
	DrawmeshField();

	// ���b�V���h�[��
	DrawmeshDome();

	// �I�u�W�F�N�g
	DrawObject();

	// �t�B�[���h
	DrawField();

	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[g_aTitle[nCntTitle].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTitle, 2);
	}
}
