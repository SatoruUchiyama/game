//=============================================================================
//
// ���b�V������ [meshcylinder.cpp]
// Author : 
//
//=============================================================================
#include "MeshCylinder.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_Z			(1)
#define MAX_X			(10)
#define MAX_Y			(1)
#define MAX_VERTICAL	(1)					//���������̕�����
#define MAX_LEVEL		(5)					//���������̕�����
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureMeshCylinder = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;	//���_�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;	//�C���f�b�N�X�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posMeshCylinder;							//�ʒu
D3DXVECTOR3 g_rotMeshCylinder;							//����
D3DXMATRIX g_mtxWorldMeshCylinder;						//���[���h�}�g���b�N�X
int g_nNumVertexMeshCylinder;							//���_��
int g_nNumIndexMeshCylinder;							//�C���f�b�N�X��
int g_nNumPolygonMeshCylinder;							//�|���S����

//=============================================================================
// ��������
//=============================================================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	int nCount_z;
	int nCount_X;
	int nCountPotato = 0;
	int nCntV, nCntH;
	D3DXCreateTextureFromFile						// �e�N�X�`���̓ǂݍ���
	(
		pDevice,
		"date\\TEXTURE\\th3XE4616V.jpg",
		&g_pTextureMeshCylinder
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MAX_Y + 1)*(MAX_X + 1), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshCylinder, NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (((MAX_X + 1) * 2) * MAX_Y + (2 * (MAX_Y - 1))), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshCylinder, NULL);

	//�|�C���^
	VERTEX_3D*pVtx;									//���_���ւ̃|�C���^
	WORD*pIdx;										//�C���f�b�N�X�f�[�^�ւ̃|�C���^


													//�o�b�t�@�����b�N
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntV = 0; nCntV < MAX_Y +1; nCntV++)
	{
		for (nCntH = 0; nCntH < MAX_X +1; nCntH++)
		{
			pVtx[0].pos.x = sinf((-D3DX_PI*(1.0f / (MAX_X / 2))) * nCntH) * 20;
			pVtx[0].pos.y = 50.0f-(nCntV*50);
			pVtx[0].pos.z = cosf((-D3DX_PI*(1.0f / (MAX_X / 2))) * nCntH) * 20;

			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].tex = D3DXVECTOR2(nCntV*1.0f, nCntH*1.0f);
			pVtx += 1;
		}
	}

	//

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshCylinder->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N����
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̐ݒ�
	for (nCount_z = 0; nCount_z < MAX_Y; nCount_z++)
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
	g_pIdxBuffMeshCylinder->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshCylinder(void)
{
	//// �e�N�X�`���̊J��
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshCylinder(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshCylinder);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCylinder);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MAX_Y + 1)*(MAX_X + 1), 0, (MAX_X*MAX_Y * 2 + (4 * (MAX_Y - 1))));
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

