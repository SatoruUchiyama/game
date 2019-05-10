//=============================================================================
//
// ���b�V���̕Ǐ��� [polygon.cpp]
// Author : 
//
//=============================================================================
#include "MeshWall.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_Z			(1)
#define MAX_X			(10)
#define MAX_Y			(5)
#define MAX_VERTICAL	(8)					//���������̕�����
#define MAX_LEVEL		(4)					//���������̕�����
#define MAX_WALL		(4)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureMeshWall = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;	//���_�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;	//�C���f�b�N�X�o�b�t�@�̃|�C���^
int g_nNumVertexMeshWall;							//���_��
int g_nNumIndexMeshWall;							//�C���f�b�N�X��
int g_nNumPolygonMeshWall;							//�|���S����
MeshWall g_Wall[MAX_WALL];
//=============================================================================
// ��������
//=============================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	int nCount_z;
	int nCount_X;
	int nCountPotato = 0; 
	//g_Wall[nCount].pos.z = 100;

	for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{
		if (nCount == 0)
		{
			g_Wall[nCount].pos = D3DXVECTOR3(0.0f,400.0f,100.0f);
			g_Wall[nCount].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f) * D3DX_PI;
		}
		if (nCount == 1)
		{
			g_Wall[nCount].pos = D3DXVECTOR3(900.0f, 400.0f, 0.0f);
			g_Wall[nCount].rot = D3DXVECTOR3(0.0f, 0.5f, 0.0f) * D3DX_PI;
		}
		if (nCount == 2)
		{
			g_Wall[nCount].pos = D3DXVECTOR3(800.0f, 400.0f, -900.0f);
			g_Wall[nCount].rot = D3DXVECTOR3(0.0f, 1.0f, 0.0f) * D3DX_PI;
		}
		if (nCount == 3)
		{
			g_Wall[nCount].pos = D3DXVECTOR3(-100.0f, 400.0f, -800.0f);
			g_Wall[nCount].rot = D3DXVECTOR3(0.0f, -0.5f, 0.0f) * D3DX_PI;
		}
	}

	//int nCntV, nCntH;
	D3DXCreateTextureFromFile						// �e�N�X�`���̓ǂݍ���
	(
		pDevice,
		"date\\TEXTURE\\th.jpg",
		&g_pTextureMeshWall
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MAX_Y + 1)*(MAX_X + 1), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshWall, NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (((MAX_X + 1) * 2) * MAX_Y + (2 * (MAX_Y - 1))), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshWall, NULL);

	//�|�C���^
	VERTEX_3D*pVtx;									//���_���ւ̃|�C���^
	WORD*pIdx;										//�C���f�b�N�X�f�[�^�ւ̃|�C���^


	//�o�b�t�@�����b�N
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	//
	for (nCount_z = 0; nCount_z < MAX_Y + 1; nCount_z++)
	{
		for (nCount_X = 0; nCount_X < MAX_X + 1; nCount_X++)
		{
			pVtx[0].pos = D3DXVECTOR3(-100.0f + (nCount_X *100.0f), 100.0f - (nCount_z * 100.0f), 0);
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].tex = D3DXVECTOR2(nCount_X*1.0f, nCount_z*1.0f);
			pVtx += 1;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshWall->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N����
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̐ݒ�
	for (nCount_z = 0; nCount_z < MAX_Y ; nCount_z++)
	{
		for (nCount_X = 0; nCount_X < MAX_X + 1; nCount_X++, nCountPotato++)
		{
			pIdx[0] = nCountPotato + MAX_X + 1;
			pIdx[1] = nCountPotato;
			pIdx += 2;
			if (nCount_z < MAX_Y && nCount_X == MAX_X)
			{
				pIdx[0] = nCountPotato + 0;
				pIdx[1] = nCountPotato + (MAX_X + 1) + 1;

				pIdx += 2;
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshWall->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshWall(void)
{
	//// �e�N�X�`���̊J��
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshWall(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Wall[nCount].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCount].rot.y, g_Wall[nCount].rot.x, g_Wall[nCount].rot.z);
		D3DXMatrixMultiply(&g_Wall[nCount].mtxWorld, &g_Wall[nCount].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Wall[nCount].pos.x, g_Wall[nCount].pos.y, g_Wall[nCount].pos.z);
		D3DXMatrixMultiply(&g_Wall[nCount].mtxWorld, &g_Wall[nCount].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCount].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshWall);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshWall);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MAX_Y + 1)*(MAX_X + 1), 0, (MAX_X*MAX_Y * 2 + (4 * (MAX_Y - 1))));

	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

