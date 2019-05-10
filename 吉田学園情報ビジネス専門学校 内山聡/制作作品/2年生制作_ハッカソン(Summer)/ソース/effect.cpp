//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EFFECT			(4096 * 3)		// �G�t�F�N�g�̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureEffect[EFFECTTYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;			// ���_�o�b�t�@�ւ̃|�C���^

// ----- �e�N�X�`�����  ----- //
EffectTexture g_aEffectTexture[EFFECTTYPE_MAX] =
{
	{ "data/TEXTURE/effect/effect000.png" },	// ��U��
	{ "data/TEXTURE/effect/effect000.png" },	// ���U��
	{ "data/TEXTURE/effect/effect000.png" },	// �d���wA�EK�ER�x
	{ "data/TEXTURE/effect/effect000.png" },	// ���Ă�����
};

EFFECT g_aEffect[MAX_EFFECT];		// �G�t�F�N�g�̏��

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ������
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].nType = 0;
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	for (int nTex = 0 ;nTex < EFFECTTYPE_MAX; nTex++)
	{
		D3DXCreateTextureFromFile(pDevice, g_aEffectTexture[nTex].pFilename, &g_apTextureEffect[nTex]);
	}

	// ���_���̍쐬
	MakeVertexEffect(pDevice);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitEffect(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nTex = 0; nTex < EFFECTTYPE_MAX; nTex++)
	{
		if (g_apTextureEffect[nTex] != NULL)
		{
			g_apTextureEffect[nTex]->Release();
			g_apTextureEffect[nTex] = NULL;
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateEffect(void)
{
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (g_aEffect[nCntEffect].bUse == true && g_aEffect[nCntEffect].nLife >= 0)
		{
			// �ʒu�̍X�V
			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;

			// �����̌���
			g_aEffect[nCntEffect].nLife--;

			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
			// ���a�̏k��
			if (g_aEffect[nCntEffect].fRadius >= 0.0f)
			{
				g_aEffect[nCntEffect].fRadius -= 0.5f;
			}
			if (g_aEffect[nCntEffect].fRadius <= 0.0f)
			{
				g_aEffect[nCntEffect].bUse = false;
			}

			//====================
			// ��ޕʏ���
			//====================
			switch (g_aEffect[nCntEffect].nType)
			{
				//--- ��U�� ---//
			case EFFECTTYPE_WEAK_ATTACK:
				break;

				//--- ���U�� ---//
			case EFFECTTYPE_STRONG_ATTACK:
				break;

				//--- �d���wA�EK�ER�x ---//
			case EFFECTTYPE_AKR:
				// ���ɗ�����ړ�������
				g_aEffect[nCntEffect].move.y = -0.8f;

				break;

				//--- �e[3D] ---//
			case EFFECTTYPE_3DBULLET:
				break;
			}

			//====================
			// ���_���̍X�V
			//====================
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(-(g_aEffect[nCntEffect].fRadius / 2), +(g_aEffect[nCntEffect].fRadius / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+(g_aEffect[nCntEffect].fRadius / 2), +(g_aEffect[nCntEffect].fRadius / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-(g_aEffect[nCntEffect].fRadius / 2), -(g_aEffect[nCntEffect].fRadius / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+(g_aEffect[nCntEffect].fRadius / 2), -(g_aEffect[nCntEffect].fRadius / 2), 0.0f);
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;		// �v�Z�p�}�g���b�N�X

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);		// �A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);					// �`��̊ [���l = 0]
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// �`��̏��� [�`���傫��]

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);				// ���C�e�B���O���[�h����

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)		// �g�p����Ă�����̂����v�Z & �`��
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			// -----  �r���{�[�h�̐ݒ�  ----- //
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

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aEffect[nCntEffect].rot.y, g_aEffect[nCntEffect].rot.x, g_aEffect[nCntEffect].rot.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld,
				&g_aEffect[nCntEffect].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld,
				&g_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEffect[g_aEffect[nCntEffect].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);		// �A���t�@�e�X�g�𖳌���

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���C�e�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);				// ���C�e�B���O���[�h�L��
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���_�̍쐬
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&g_pVtxBuffEffect,
								NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		//���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �@���̐ݒ�
		for (int nNor = 0; nNor < 4; nNor++)
		{
			pVtx[nNor].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);		// ���Œ�@[�@��z�͎�O�������Ă���]
		}
		// ���_�J���[�̐ݒ�
		for (int nCol = 0; nCol < 4; nCol++)
		{
			pVtx[nCol].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �G�t�F�N�g�ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife,int nType)
{
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].nType = nType;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(-(g_aEffect[nCntEffect].fRadius / 2), +(g_aEffect[nCntEffect].fRadius / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+(g_aEffect[nCntEffect].fRadius / 2), +(g_aEffect[nCntEffect].fRadius / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-(g_aEffect[nCntEffect].fRadius / 2), -(g_aEffect[nCntEffect].fRadius / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+(g_aEffect[nCntEffect].fRadius / 2), -(g_aEffect[nCntEffect].fRadius / 2), 0.0f);

			// ���_�J���[�̐ݒ�
			for (int nCol = 0; nCol < 4; nCol++)
			{
				pVtx[nCol].col = g_aEffect[nCntEffect].col;
			}

			// �g�p���
			g_aEffect[nCntEffect].bUse = true;

			break;		//�@�d�v�I
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
