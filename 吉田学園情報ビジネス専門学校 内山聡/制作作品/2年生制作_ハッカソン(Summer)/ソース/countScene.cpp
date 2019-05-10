//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �J�E���g�V�[������ [countScene.cpp]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "game.h"
#include "countScene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COUNTSCENE_WIDTH		(600.0f)				// ��
#define COUNTSCENE_HEIGHT		(200.0f)				// ����
#define START_COUNTSCENE_X		(SCREEN_WIDTH / 2)		// �J�n�ʒu[X]
#define START_COUNTSCENE_Y		(SCREEN_HEIGHT / 2)		// �J�n�ʒu[Y]
#define COUNTSCENE_FADESPEED	(0.1f)					// �t�F�[�h���x
#define COUNTSCENE_WAITTIME		(120)					// �ҋ@����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexcountScene(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffcountScene = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
COUNTSCENE				g_CountScene;						// �J�E���g�V�[�����

LPDIRECT3DTEXTURE9		g_pTexturecountScene[COUNTSCENETYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^

//--- �e�N�X�`�� ---//
CountSceneTexInfo g_aCountScenetexInfo[COUNTSCENETYPE_MAX] =
{
	{ "data/TEXTURE/�X�^�[�g.png" },		// �X�^�[�g
	{ "data/TEXTURE/goal.png" },		// �S�[��
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitcountScene(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ������
	g_CountScene.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);	// ��\��
	g_CountScene.type = COUNTSCENETYPE_START;
	g_CountScene.countSceneState = COUNTSCENESTATE_NONE;
	g_CountScene.countSceneStateCounter = 0;

	// �e�N�X�`���̓ǂݍ���
	for (int nCntTex = 0; nCntTex < COUNTSCENETYPE_MAX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice, g_aCountScenetexInfo[nCntTex].pFilename, &g_pTexturecountScene[nCntTex]);
	}

	// ���_���̍쐬
	MakeVertexcountScene(pDevice);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitcountScene(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < COUNTSCENETYPE_MAX; nCntTex++)
	{
		if (g_pTexturecountScene[nCntTex] != NULL)
		{
			g_pTexturecountScene[nCntTex]->Release();
			g_pTexturecountScene[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffcountScene != NULL)
	{
		g_pVtxBuffcountScene->Release();
		g_pVtxBuffcountScene = NULL;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdatecountScene(void)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	if (g_CountScene.countSceneState != COUNTSCENESTATE_NONE)
	{// �������Ă��Ȃ�
		if (g_CountScene.countSceneState == COUNTSCENESTATE_IN)
		{// �J�E���g�V�[���C�����
			if (g_CountScene.color.a < 1.0f)
			{
				g_CountScene.color.a += COUNTSCENE_FADESPEED;
			}

			if(g_CountScene.color.a >= 1.0f)
			{
				g_CountScene.color.a = 1.0f;
				g_CountScene.countSceneState = COUNTSCENESTATE_WAIT;	// �ҋ@���
			}
		}
		else if (g_CountScene.countSceneState == COUNTSCENESTATE_WAIT)
		{// �J�E���g�V�[���ҋ@���
			if (g_CountScene.countSceneStateCounter < COUNTSCENE_WAITTIME)
			{
				g_CountScene.countSceneStateCounter++;
			}

			if (g_CountScene.countSceneStateCounter == COUNTSCENE_WAITTIME)
			{
				g_CountScene.countSceneState = COUNTSCENESTATE_OUT;		// �A�E�g���
			}
		}
		else if (g_CountScene.countSceneState == COUNTSCENESTATE_OUT)
		{// �J�E���g�V�[���A�E�g���
			if (g_CountScene.color.a > 0.0f)
			{
				g_CountScene.color.a -= COUNTSCENE_FADESPEED;
			}

			if (g_CountScene.color.a >= 0.0f)
			{
				g_CountScene.color.a = 0.0f;
				g_CountScene.countSceneState = COUNTSCENESTATE_NONE;	// �������Ă��Ȃ�
			}
		}
	}

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffcountScene->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntcountScene = 0; nCntcountScene < MAX_COUNTSCENE; nCntcountScene++, pVtx += 4)
	{
		// ���_���W�̍X�V
		pVtx[0].col = g_CountScene.color;
		pVtx[1].col = g_CountScene.color;
		pVtx[2].col = g_CountScene.color;
		pVtx[3].col = g_CountScene.color;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffcountScene->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawcountScene(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffcountScene, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturecountScene[g_CountScene.type]);

	// �|���S���̕`��
	for (int nCntcountScene = 0; nCntcountScene < MAX_COUNTSCENE; nCntcountScene++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
								nCntcountScene * 4,		// �`����J�n���钸�_�C���f�b�N�X
								2);						// �`�悷��v���~�e�B�u��
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���_���̍쐬
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeVertexcountScene(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_COUNTSCENE,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffcountScene,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffcountScene->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	for (int nCntcountScene = 0; nCntcountScene < MAX_COUNTSCENE; nCntcountScene++, pVtx += 4)
	{
		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(START_COUNTSCENE_X + (-COUNTSCENE_WIDTH / 2), START_COUNTSCENE_Y + (-COUNTSCENE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(START_COUNTSCENE_X + COUNTSCENE_WIDTH / 2, START_COUNTSCENE_Y + (-COUNTSCENE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(START_COUNTSCENE_X + (-COUNTSCENE_WIDTH / 2), START_COUNTSCENE_Y + COUNTSCENE_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(START_COUNTSCENE_X + COUNTSCENE_WIDTH / 2, START_COUNTSCENE_Y + COUNTSCENE_HEIGHT / 2, 0.0f);
		// rhw
		for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
		{
			pVtx[nCntVtx].rhw = 1.0f;
		}
		// ���_�J���[
		for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
		{
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffcountScene->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �J�E���g�V�[���̐ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetcountScene(COUNTSCENETYPE type)
{
	// ���̑��
	g_CountScene.type = type;								// ���
	g_CountScene.countSceneState = COUNTSCENESTATE_IN;		// �J�E���g�V�[���C��
	g_CountScene.countSceneStateCounter = 0;				// ��ԃJ�E���^�[
}