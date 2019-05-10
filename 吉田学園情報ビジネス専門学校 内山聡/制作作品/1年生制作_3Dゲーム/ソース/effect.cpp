//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : 
//
//=============================================================================
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EFFECT_ICE		"date/TEXTURE/pipo-hiteffect009.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT_BLOOD	"date/TEXTURE/pipo-hiteffect013.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT_FIRE		"date/TEXTURE/honoo_hi_fire.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MAX_EFFECT2			(8000)							// �G�t�F�N�g�̍ő吔
#define	MAX_EFFECT					(1000)									// �G�t�F�N�g�̍ő吔
#define	MAX_EFFECTSMOKE				(50)									// �G�t�F�N�g�̍ő吔
#define MAX_TEXTURE					(3)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect[MAX_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Effect					g_aEffect[MAX_EFFECT2];		// �G�t�F�N�g�̏��
int g_nNumEffect;
//=============================================================================
// ����������
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEffect;

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT2; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_EFFECT_ICE,
		&g_pTextureEffect[0]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_EFFECT_BLOOD,
		&g_pTextureEffect[1]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_EFFECT_FIRE,
		&g_pTextureEffect[2]
	);
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT2,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffEffect,NULL);

	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT2; nCntEffect++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureEffect[nCount] != NULL)
		{
			g_pTextureEffect[nCount]->Release();
			g_pTextureEffect[nCount] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		if (g_aEffect[nCntEffect].bUse == true)
		{// �G�t�F�N�g���g�p����Ă���ꍇ
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{// �e�G�t�F�N�g�̏ꍇ
			 // g_aEffect[nCntEffect].nLife--;
				g_aEffect[nCntEffect].fRadius -= 0.2f;

				if (/*g_aEffect[nCntEffect].nLife <= 0 || */g_aEffect[nCntEffect].fRadius <= 0)
				{// ���C�t��0�ȉ��̏ꍇ
					g_aEffect[nCntEffect].fRadius = 0;
					g_aEffect[nCntEffect].bUse = false;
				}
			}
			if (g_aEffect[nCntEffect].bUse == true)
			{
				g_aEffect[nCntEffect].fRadius -= 0.5f;

				if (g_aEffect[nCntEffect].fRadius <= 0)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
			}
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION || g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION || g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONSMOKE)
			{// �����G�t�F�N�g�̏ꍇ
				g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;	// �ړ��l���

				g_aEffect[nCntEffect].nLife--;				// ��������

															// ���a����
				if (g_aEffect[nCntEffect].nLife > 0)
				{
					g_aEffect[nCntEffect].fRadius += 0.0005f;
				}
				else
				{
					g_aEffect[nCntEffect].fRadius -= 0.5f;
				}

				if (g_aEffect[nCntEffect].fRadius <= 0)
				{// ���C�t��0�ȉ��̏ꍇ
					g_aEffect[nCntEffect].bUse = false;
				}
			}
		}
		// ���_�ݒ�
		pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
	}
	SetSmokeEffect(D3DXVECTOR3(30.0f, 30.0f, 0.0f), EFFECTTYPE_RESURRECTIONSMOKE, 10, 10, 10, 2);
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	int nCntEffect;
	
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT2; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_aEffect[nCntEffect].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntEffect].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntEffect].mtxWorld._13 = mtxView._31;
			g_aEffect[nCntEffect].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntEffect].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntEffect].mtxWorld._23 = mtxView._32;
			g_aEffect[nCntEffect].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].nTypeTx]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}
	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
}

/*//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	

	// ���_�o�b�t�@�̏���ݒ�


}*/

//=============================================================================
// �G�t�F�N�g�ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife, int nTypeTx)
{
	int nCntEffect;
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;			// ��ސݒ�

 			g_aEffect[nCntEffect].bUse = true;

			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

			//pVtx += nCntEffect * 4;
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(- g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3( g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(- g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius,  -g_aEffect[nCntEffect].fRadius, 0.0f);

			g_pVtxBuffEffect->Unlock();
			break;
		}
		
	}
}

//=========================================================================================================================
// �p�[�e�B�N���G�t�F�N�g�ݒ菈��
//=========================================================================================================================
void SetParticleEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx)
{
	int nCntEffect;			// �G�t�F�N�g�J�E���^
	int nCount = 0;			// �G�t�F�N�g���J�E���^

	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

							// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		if (g_aEffect[nCntEffect].bUse == false)
		{// �G�t�F�N�g���g�p����Ă��Ȃ�

			g_aEffect[nCntEffect].pos = pos;			// pos�l���
			g_aEffect[nCntEffect].Type = Type;			// ��ސݒ�
			g_aEffect[nCntEffect].nLife = nLife;		// �����ݒ�
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;			// ��ސݒ�

			g_aEffect[nCntEffect].bUse = true;			// �g�p���Ă�����

														// �ړ������_����
			g_aEffect[nCntEffect].move.x = sinf((rand() % 628) / 50.0f) * ((rand() % 3) + 1);
			g_aEffect[nCntEffect].move.y = cosf((rand() % 628) / 50.0f) * ((rand() % 3) + 1);
			g_aEffect[nCntEffect].move.z = tanf((rand() % 628) / 50.0f) * ((rand() % 3) + 1);

			int nNumber = rand() % 3 + 1;

			// col�l���
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.5f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.8f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 0.5f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); }
			}

			g_aEffect[nCntEffect].fRadius = (rand() % nRadius + 1) * 1.0f;	// ���a�ݒ�

																			// ���_�ݒ�
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;

			nCount++;		// �����J�E���g
			if (nCount == nSetMax)
			{// �����ő吔�ɂȂ����ꍇ
				break;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
//�p�[�e�B�N���̏���
//=============================================================================
void SetSmokeEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx)
{
	int nCntEffect;			// �G�t�F�N�g�J�E���^
	int nCount = 0;			// �G�t�F�N�g���J�E���^

	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

							// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECTSMOKE; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		if (g_aEffect[nCntEffect].bUse == false)
		{// �G�t�F�N�g���g�p����Ă��Ȃ�

			g_aEffect[nCntEffect].pos = pos;			// pos�l���
			g_aEffect[nCntEffect].Type = Type;			// ��ސݒ�
			g_aEffect[nCntEffect].nLife = nLife;		// �����ݒ�
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;	// ��ސݒ�

			g_aEffect[nCntEffect].bUse = true;			// �g�p���Ă�����


														// �ړ������_����
			g_aEffect[nCntEffect].move.x = sinf((rand() % 25) / 700.0f) * ((rand() % 3) + 1);
			//	g_aEffect[nCntEffect].move.z = tanf((rand() % 628) / 100.0f) * ((rand() % 3) + 1);
			g_aEffect[nCntEffect].move.y = cosf((rand() % 100) / 100.0f)  * ((rand() % 3) + 1);
		

			int nNumber = rand() % 3 + 1;

			// col�l���
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.5f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONSMOKE)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.8f, 1.0f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			}

			g_aEffect[nCntEffect].fRadius = (rand() % nRadius + 1) * 1.0f;	// ���a�ݒ�

																			// ���_�ݒ�
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;

			nCount++;		// �����J�E���g
			if (nCount == nSetMax)
			{// �����ő吔�ɂȂ����ꍇ
			 //g_aEffect[nCntEffect].bUse = false;
				nSetMax = 0;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}