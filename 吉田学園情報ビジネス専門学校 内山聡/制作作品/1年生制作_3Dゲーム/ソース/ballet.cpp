//=============================================================================
//
// �e���� [ballet.cpp]
// Author : 
//
//=============================================================================
#include "ballet.h"
#include "shadow.h"
#include "input.h"
#include "explosion.h"
#include "effect.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BALLET			(256)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBallet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Ballet g_aBallet[MAX_BALLET];					//�\���̂̃O���[�o���ϐ�

//			�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureBallet = NULL;

//			���_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallet = NULL;	


//=============================================================================
// ����������
//=============================================================================
void InitBallet(void)
{
	int nCntBill;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	for (nCntBill = 0; nCntBill < MAX_BALLET; nCntBill++)
	{

		g_aBallet[nCntBill].g_nIdxShadow = 0;
		g_aBallet[nCntBill].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,"date\\TEXTURE\\bullet000.png",&g_pTextureBallet);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BALLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBallet, NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;	

	//�o�b�t�@�����b�N											
	g_pVtxBuffBallet->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntBill = 0; nCntBill < MAX_BALLET; nCntBill++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-2, 2, 0.0);
		pVtx[1].pos = D3DXVECTOR3(2, 2, 0.0);
		pVtx[2].pos = D3DXVECTOR3(-2, -2.0, 0.0);
		pVtx[3].pos = D3DXVECTOR3(2, -2.0, 0.0);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[1].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[2].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[3].nor = D3DXVECTOR3(0.0, 0.0, -1.0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);

		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBallet->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBallet(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBallet != NULL)
	{
		g_pTextureBallet->Release();
		g_pTextureBallet = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBallet != NULL)
	{
		g_pVtxBuffBallet->Release();
		g_pVtxBuffBallet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBallet(void)
{
	//�e�̈ړ�����
	for (int nCntBill2 = 0; nCntBill2 < MAX_BALLET; nCntBill2++)
	{
		if (g_aBallet[nCntBill2].bUse == true)
		{
			//�G�t�F�N�g�̃Z�b�g
			SetEffect(g_aBallet[nCntBill2].pos, D3DXCOLOR(1.0f, 0.5f, 0.7f, 1.0f), 20, 20,0);
			g_aBallet[nCntBill2].pos += g_aBallet[nCntBill2].move;
			SetPositionShadow(g_aBallet[nCntBill2].g_nIdxShadow, g_aBallet[nCntBill2].pos);

			//�O���̒e�̏���
			if (g_aBallet[nCntBill2].pos.z >= 100)
			{
				g_aBallet[nCntBill2].bUse = false;
				DeleteShadow(g_aBallet[nCntBill2].g_nIdxShadow);
				DeleteBallet(nCntBill2);
			}
			//�������̒e�̏���
			else if (g_aBallet[nCntBill2].pos.x >= 200)
			{
				g_aBallet[nCntBill2].bUse = false;
				DeleteShadow(g_aBallet[nCntBill2].g_nIdxShadow);
				DeleteBallet(nCntBill2);
			}
			//�������̒e�̏���
			else if (g_aBallet[nCntBill2].pos.z <= -200)
			{
				g_aBallet[nCntBill2].bUse = false;
				DeleteShadow(g_aBallet[nCntBill2].g_nIdxShadow);
				DeleteBallet(nCntBill2);
			}
			//�E�����̒e�̏���
			else if (g_aBallet[nCntBill2].pos.x <= -100)
			{
				g_aBallet[nCntBill2].bUse = false;
				DeleteShadow(g_aBallet[nCntBill2].g_nIdxShadow);
				DeleteBallet(nCntBill2);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBallet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	int nCntBallet;

	//�A���t�@�e�X�g����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//D3DCMP_GREATER

	for (nCntBallet = 0; nCntBallet < MAX_BALLET; nCntBallet++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBallet[nCntBallet].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		g_aBallet[nCntBallet].mtxWorld._11 = mtxView._11;
		g_aBallet[nCntBallet].mtxWorld._12 = mtxView._21;
		g_aBallet[nCntBallet].mtxWorld._13 = mtxView._31;
		g_aBallet[nCntBallet].mtxWorld._21 = mtxView._12;
		g_aBallet[nCntBallet].mtxWorld._22 = mtxView._22;
		g_aBallet[nCntBallet].mtxWorld._23 = mtxView._32;
		g_aBallet[nCntBallet].mtxWorld._31 = mtxView._13;
		g_aBallet[nCntBallet].mtxWorld._32 = mtxView._23;
		g_aBallet[nCntBallet].mtxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBallet[nCntBallet].pos.x, g_aBallet[nCntBallet].pos.y, g_aBallet[nCntBallet].pos.z);
		D3DXMatrixMultiply(&g_aBallet[nCntBallet].mtxWorld, &g_aBallet[nCntBallet].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBallet[nCntBallet].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBallet, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBallet);

		// �|���S���̕`��
		if (g_aBallet[nCntBallet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBallet, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
//	�e�̐ݒ�
//=============================================================================
void SetBallet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	int nCntBallet;

	for (nCntBallet = 0; nCntBallet < MAX_BALLET; nCntBallet++)
	{
		if (g_aBallet[nCntBallet].bUse == false)
		{
			g_aBallet[nCntBallet].pos = pos;
			g_aBallet[nCntBallet].rot = rot;
			g_aBallet[nCntBallet].move = move;
			g_aBallet[nCntBallet].g_nIdxShadow = SetShadow(g_aBallet[nCntBallet].pos, g_aBallet[nCntBallet].rot);
			g_aBallet[nCntBallet].bUse = true;
			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBallet(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

void DeleteBallet(int nBallet)
{
	SetParticleEffect(g_aBallet[nBallet].pos, EFFECTTYPE_RESURRECTIONSMOKE, 80, 20, 50, 1);

	g_aBallet[nBallet].bUse = false;
}

