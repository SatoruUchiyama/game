//=============================================================================
//
// ���b�V������ [meshfield.cpp]
// Author : 
//
//=============================================================================
#include "MeshField.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_Z			(10)
#define MAX_X			(10)
#define MAX_Y			(2)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureMeshField = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;	//���_�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//�C���f�b�N�X�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posMeshField;							//�ʒu
D3DXVECTOR3 g_rotMeshField;							//����
D3DXMATRIX g_mtxWorldMeshField;						//���[���h�}�g���b�N�X
int g_nNumVertexMeshField;							//���_��
int g_nNumIndexMeshField;							//�C���f�b�N�X��
int g_nNumPolygonMeshField;							//�|���S����

//=============================================================================
// ��������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	int nCount_z;
	int nCount_X;
	int nCountPotato = 0;
	D3DXCreateTextureFromFile						// �e�N�X�`���̓ǂݍ���
	(
		pDevice,
		"date\\TEXTURE\\sand_.jpg",
		&g_pTextureMeshField
	);
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MAX_Z+1)*(MAX_X+1), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshField, NULL);
	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (MAX_X*MAX_Z*2+(4*(MAX_Z-1))+2), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshField, NULL);

	VERTEX_3D*pVtx;									//���_���ւ̃|�C���^

	WORD*pIdx;										//�C���f�b�N�X�f�[�^�ւ̃|�C���^

	//�o�b�t�@�����b�N
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);


	for (nCount_z = 0; nCount_z < MAX_Z + 1; nCount_z++)
	{
		for (nCount_X = 0; nCount_X < MAX_X + 1; nCount_X++)
		{
			pVtx[0].pos = D3DXVECTOR3(-100.0f + (nCount_X * 100.0f), 0, 100.0f - (nCount_z * 100.0f));
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].tex = D3DXVECTOR2(nCount_X*1.0f, nCount_z*1.0f);
			pVtx += 1;
		}
	}
	////���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(-100, 0, 100);
	//pVtx[1].pos = D3DXVECTOR3(0, 0, 100);
	//pVtx[2].pos = D3DXVECTOR3(100, 0, 100);
	//pVtx[3].pos = D3DXVECTOR3(-100, 0, 0);
	//pVtx[4].pos = D3DXVECTOR3(0, 0, 0);
	//pVtx[5].pos = D3DXVECTOR3(100, 0, 0);
	//pVtx[6].pos = D3DXVECTOR3(-100, 0, -100);
	//pVtx[7].pos = D3DXVECTOR3(0, 0, -100);
	//pVtx[8].pos = D3DXVECTOR3(100, 0, -100);
	////�@���̐ݒ�
	//pVtx[0].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[1].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[2].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[3].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[4].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[5].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[6].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[7].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[8].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);

	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[1].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[2].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[3].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[4].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[5].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[6].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[7].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[8].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//
	//////�e�N�X�`���ݒ�
	//pVtx[0].tex = D3DXVECTOR2(	0.0,	0.0);
	//pVtx[1].tex = D3DXVECTOR2(	1.0,	0.0);
	//pVtx[2].tex = D3DXVECTOR2(	2.0,	0.0);
	//pVtx[3].tex = D3DXVECTOR2(	0.0,	1.0);
	//pVtx[4].tex = D3DXVECTOR2(	1.0,	1.0);
	//pVtx[5].tex = D3DXVECTOR2(	2.0,	1.0);
	//pVtx[6].tex = D3DXVECTOR2(	0.0,	2.0);
	//pVtx[7].tex = D3DXVECTOR2(	1.0,	2.0);
	//pVtx[8].tex = D3DXVECTOR2(	2.0,	2.0);
	

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshField->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N����
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̐ݒ�
	for (nCount_z = 0; nCount_z < MAX_Z; nCount_z++)
	{
		for (nCount_X = 0; nCount_X < MAX_X + 1; nCount_X++, nCountPotato++)
		{
			pIdx[0] = nCountPotato + MAX_X +1;
			pIdx[1] = nCountPotato;
			pIdx += 2;
			if (nCount_z < MAX_Z && nCount_X == MAX_X)
			{
				pIdx[0] = nCountPotato;
				pIdx[1] = nCountPotato + (MAX_X + 1) +1;

				pIdx += 2;
			}
		}
	}
	/*pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;*/

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshField->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	//// �e�N�X�`���̊J��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MAX_X*MAX_Z * 2 + (4 * (MAX_Z - 1))+2), 0, (MAX_X*MAX_Z * 2 + (4 * (MAX_Z - 1))));
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

