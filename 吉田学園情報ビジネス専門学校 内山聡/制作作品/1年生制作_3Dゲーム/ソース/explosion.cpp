//=============================================================================
//
// �������� [bullet.cpp]
// Author : storu utiyama
//
//=============================================================================
#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EXPLOSION			(256)									// �����̍ő吔
#define POLYGON_TEXTURE_NAME	"date\\TEXTURE\\explosion000.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define POLYGON_POS_X			(SCREEN_WIDTH / 2 - 100)				//�|���S���̍���X���W
#define POLYGON_POS_Y			(SCREEN_HEIGHT / 2 - 100)				//�|���S���̍���Y���W
#define POLYGON_WIDTH			(SCREEN_WIDTH / 2 + 100)				//�|���S���̕�
#define POLYGON_HEIGHT			(SCREEN_HEIGHT / 2 + 100)				//�|���S���̍���
#define POLYGON_TEXTURE_SPEED	(5)										//�e�N�X�`���A�j���[�V�����X�s�[�h
#define POLYGON_TEXTURE_PATTERN	(10)									//�e�N�X�`���A�j���[�V�����p�^�[����
#define POLYGON_TEXTURE_UV_U	(0.2f)									//�e�N�X�`���A�j���[�V����U�͈�
#define POLYGON_TEXTURE_UV_V	(0.5f)									//�e�N�X�`���A�j���[�V����V�͈�
#define MAX_BOOON				(30)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;		
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxWorld;
	int nCnterAnim;
	int nPatternAnim;
	bool bUse;				//�g�p���Ă��邩
} Explosion;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];
D3DXVECTOR3 posExplosion;										//�A�j���[�V�����J�E���^�[
D3DXVECTOR3 moveExplosion;										//�A�j���[�V�����p�^�[��No.


//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �����̏��̏�����
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCnterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		POLYGON_TEXTURE_NAME,
		&g_pTextureExplosion
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffExplosion,NULL);
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBallet, NULL);

	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

	g_pVtxBuffExplosion->Lock//���_�o�b�t�@�����b�N
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[1].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[2].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[3].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		//���_�J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[1].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[2].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[3].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion] .bUse == true)
		{
			g_aExplosion[nCntExplosion].nCnterAnim++;

			if ((g_aExplosion[nCntExplosion].nCnterAnim % POLYGON_TEXTURE_SPEED) == 0)
			{
				VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
				g_pVtxBuffExplosion->Lock	//���_�o�b�t�@�����b�N
				(
					0,
					0,
					(void**)&pVtx,
					0
				);
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;

				pVtx[nCntExplosion * 4].pos = D3DXVECTOR3( -MAX_BOOON, MAX_BOOON, 0.0f);
				pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(MAX_BOOON, MAX_BOOON, 0.0f);
				pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3( -MAX_BOOON,-MAX_BOOON, 0.0f);
				pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(MAX_BOOON, -MAX_BOOON, 0.0f);

				pVtx[nCntExplosion * 4].tex = D3DXVECTOR2(0.125f*(g_aExplosion[nCntExplosion].nPatternAnim), 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(0.125f*(g_aExplosion[nCntExplosion].nPatternAnim) + 0.125f, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(0.125f*(g_aExplosion[nCntExplosion].nPatternAnim), 1.0f);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(0.125f*(g_aExplosion[nCntExplosion].nPatternAnim)+0.125f, 1.0f);

				g_pVtxBuffExplosion->Unlock();
				if (g_aExplosion[nCntExplosion].nPatternAnim == 7)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}
			}
		}
	}
	

}

//=============================================================================
// �`�揈��	
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	int nCntExplosion;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//�A���t�@�e�X�g����          D3DRS_ZFUNC          D3DRS_ZENABLE              D3DRS_ZWRITEENABLE
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DCMP_ALWAYS);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		g_aExplosion[nCntExplosion].mtxWorld._11 = mtxView._11;
		g_aExplosion[nCntExplosion].mtxWorld._12 = mtxView._21;
		g_aExplosion[nCntExplosion].mtxWorld._13 = mtxView._31;
		g_aExplosion[nCntExplosion].mtxWorld._21 = mtxView._12;
		g_aExplosion[nCntExplosion].mtxWorld._22 = mtxView._22;
		g_aExplosion[nCntExplosion].mtxWorld._23 = mtxView._32;
		g_aExplosion[nCntExplosion].mtxWorld._31 = mtxView._13;
		g_aExplosion[nCntExplosion].mtxWorld._32 = mtxView._23;
		g_aExplosion[nCntExplosion].mtxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
		D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorld, &g_aExplosion[nCntExplosion].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);


		// �|���S���̕`��
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureExplosion);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_3D *pVtx;
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;

			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntExplosion * 4;
			pVtx[0].pos = D3DXVECTOR3(-MAX_BOOON, MAX_BOOON, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(MAX_BOOON, MAX_BOOON, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-MAX_BOOON, -MAX_BOOON, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(MAX_BOOON, -MAX_BOOON, 0.0f);

			pVtx[0].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f, 1.0f);

			g_pVtxBuffExplosion->Unlock();

			
			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
	}
}

