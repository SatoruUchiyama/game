//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : 
//
//=============================================================================
#include "shadow.h"
//#include "model.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SHADOW			(255)				//	�e�̌�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureShadow = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;							//���_�o�b�t�@�̃|�C���^

											//����
											//���[���h�}�g���b�N�X
Shadow g_aShadow[MAX_SHADOW];												//
													
//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	int nCount;
	for (nCount = 0; nCount < MAX_SHADOW; nCount++)
	{
		g_aShadow[nCount].bUse = false;
		g_aShadow[nCount].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aShadow[nCount].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	D3DXCreateTextureFromFile			// �e�N�X�`���̓ǂݍ���
	(
		pDevice,
		"date\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4* MAX_SHADOW, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffShadow, NULL);


	VERTEX_3D*pVtx;								//���_���ւ̃|�C���^
												//�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (nCount = 0; nCount < MAX_SHADOW; nCount++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0, 0.0, 10.0);
		pVtx[1].pos = D3DXVECTOR3(10.0, 0.0, 10.0);
		pVtx[2].pos = D3DXVECTOR3(-10.0, 0.0, -10.0);
		pVtx[3].pos = D3DXVECTOR3(10.0, 0.0, -10.0);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
		pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
		pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
		pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);

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

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	//// �e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;
	int nCntShadow;
	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);



	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureShadow);

		if (g_aShadow[nCntShadow].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntShadow, 2);
		}
	}
	//���̐ݒ�ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;
			g_aShadow[nCntShadow].pos.y = 0.2f;

			break;
		}
	}
	return nCntShadow;
}

//=============================================================================
// �e�̈ʒu�̐ݒ�
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	if (g_aShadow[nIdxShadow].bUse == true)
	{
		g_aShadow[nIdxShadow].pos = D3DXVECTOR3(pos.x,0.0f,pos.z);
	}
}

void DeleteShadow(int nIdxShadow2)
{
	g_aShadow[nIdxShadow2].bUse = false;
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

