//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : 
//
//=============================================================================
#include "wall.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_WALL			(4)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureWall = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;							//���_�o�b�t�@�̃|�C���^


Wall g_aWall[MAX_WALL];
																			//=============================================================================
																			// ����������
																			//=============================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	
	D3DXCreateTextureFromFile			// �e�N�X�`���̓ǂݍ���
	(
		pDevice,
		"date\\TEXTURE\\th.jpg",
		&g_pTextureWall
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4* MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffWall, NULL);


	VERTEX_3D*pVtx;								//���_���ւ̃|�C���^
												//�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�

	pVtx[0].pos = D3DXVECTOR3(-100.0, 100.0, 0.0);
	pVtx[1].pos = D3DXVECTOR3(100.0, 100.0, 0.0);
	pVtx[2].pos = D3DXVECTOR3(-100.0, 0.0, 0.0);
	pVtx[3].pos = D3DXVECTOR3(100.0, 0.0, 0.0);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
	pVtx[1].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
	pVtx[2].nor = D3DXVECTOR3(0.0, 0.0,	-1.0);
	pVtx[3].nor = D3DXVECTOR3(0.0, 0.0, -1.0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	////�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	//g_posWall = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
//	g_rotWall = D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f);
}

//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	//// �e�N�X�`���̊J��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;
	int nCntWall;
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureWall);

		if (g_aWall[nCntWall].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].bUse = true;
			break;
		}
	}
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

