//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// ���b�V���h�[������ [meshDome.cpp]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "meshDome.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexmeshDome(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexmeshDome(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_apTexturemeshDome[MESHDOMETYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
meshDome g_ameshDome[MAX_MESHDOME];								// ���b�V���h�[���̏��

// -----�@�e�N�X�`�����@----- //
meshDomeTexture g_apTexturemeshDomeInfo[MESHDOMETYPE_MAX] =
{
	{ "data/TEXTURE/sky001.jpg" },
	{ "data/TEXTURE/wall004.jpg" }
};

// -----�@�z�u���@----- //
meshDomeInfo g_ameshDomeInfo[] =
{// �ʒu(pos),							����(rot),						���a,		V,		H,		�e�N�X�`���̎��,	�e�N�X�`���ړ����x,				�`�悷���
	{ D3DXVECTOR3(0.0f,0.0f,0.0f),		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	5000.0f,	100,	100,	MESHDOMETYPE_000,	D3DXVECTOR2(0.00005f,0.0f),	DRAWSIDE_IN }
};

int g_NumMAXmeshDomeInfo;		// �z�u���̍ő吔

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitmeshDome(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �z�u���̍ő吔
	g_NumMAXmeshDomeInfo = sizeof g_ameshDomeInfo / sizeof(meshDomeInfo);

	// �e�N�X�`���̓ǂݍ���
	for (int nCntmeshDomeTex = 0; nCntmeshDomeTex < MESHDOMETYPE_MAX; nCntmeshDomeTex++)
	{
		D3DXCreateTextureFromFile(pDevice, g_apTexturemeshDomeInfo[nCntmeshDomeTex].pFilename, &g_apTexturemeshDome[nCntmeshDomeTex]);
	}

	// ������
	for (int nCntmeshDome = 0; nCntmeshDome < MAX_MESHDOME; nCntmeshDome++)
	{
		g_ameshDome[nCntmeshDome].pVtxBuff = NULL;								// ���_�o�b�t�@�ւ̃|�C���^
		g_ameshDome[nCntmeshDome].pIdxBuff = NULL;								// �C���f�b�N�X�o�b�t�@�̃|�C���^
		g_ameshDome[nCntmeshDome].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
		g_ameshDome[nCntmeshDome].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
		g_ameshDome[nCntmeshDome].fRadius = 0.0f;								// ���a
		g_ameshDome[nCntmeshDome].nNumSplitV = 0;								// �c�����̃u���b�N��
		g_ameshDome[nCntmeshDome].nNumSplitH = 0;								// �������̃u���b�N��
		g_ameshDome[nCntmeshDome].nNumVertex = 0;								// ���_��
		g_ameshDome[nCntmeshDome].nNumIndex = 0;								// �C���f�b�N�X��
		g_ameshDome[nCntmeshDome].nNumPolygon = 0;								// �|���S����
		g_ameshDome[nCntmeshDome].TexType = MESHDOMETYPE_000;					// �e�N�X�`���̎��
		g_ameshDome[nCntmeshDome].TexMoveSpeed = D3DXVECTOR2(0.0f, 0.0f);		// �e�N�X�`���ړ����x
		g_ameshDome[nCntmeshDome].DrawSide = DRAWSIDE_BOTH;						// �`�悷���
	}

	// �z�u���
	for (int nCntmeshDome = 0; nCntmeshDome < g_NumMAXmeshDomeInfo; nCntmeshDome++)
	{
		g_ameshDome[nCntmeshDome].pos = g_ameshDomeInfo[nCntmeshDome].pos;
		g_ameshDome[nCntmeshDome].rot = g_ameshDomeInfo[nCntmeshDome].rot;
		g_ameshDome[nCntmeshDome].fRadius = g_ameshDomeInfo[nCntmeshDome].fRadius;
		g_ameshDome[nCntmeshDome].nNumSplitV = g_ameshDomeInfo[nCntmeshDome].nNumSplitV;
		g_ameshDome[nCntmeshDome].nNumSplitH = g_ameshDomeInfo[nCntmeshDome].nNumSplitH;
		g_ameshDome[nCntmeshDome].TexType = g_ameshDomeInfo[nCntmeshDome].TexType;
		g_ameshDome[nCntmeshDome].TexMoveSpeed = g_ameshDomeInfo[nCntmeshDome].TexMoveSpeed;
		g_ameshDome[nCntmeshDome].DrawSide = g_ameshDomeInfo[nCntmeshDome].DrawSide;

		// ���_�� = (�������� + 1) * (�c������ + 1)
		g_ameshDome[nCntmeshDome].nNumVertex = (g_ameshDome[nCntmeshDome].nNumSplitH + 1) * (g_ameshDome[nCntmeshDome].nNumSplitV + 1);
		// �C���f�b�N�X�� = �������� * �c������ * 2 + (�c������ - 1) * 4 + 2
		g_ameshDome[nCntmeshDome].nNumIndex = g_ameshDome[nCntmeshDome].nNumSplitH * g_ameshDome[nCntmeshDome].nNumSplitV * 2 + (g_ameshDome[nCntmeshDome].nNumSplitV - 1) * 4 + 2;
		// �|���S���� = �C���f�b�N�X�� - 2
		g_ameshDome[nCntmeshDome].nNumPolygon = g_ameshDome[nCntmeshDome].nNumIndex - 2;
	}

	// ���_���̍쐬
	MakeVertexmeshDome(pDevice);

	// �C���f�b�N�X���̍쐬
	MakeIndexmeshDome(pDevice);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitmeshDome(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < MESHDOMETYPE_MAX; nCntTex++)
	{
		if (g_apTexturemeshDome[nCntTex] != NULL)
		{
			g_apTexturemeshDome[nCntTex]->Release();
			g_apTexturemeshDome[nCntTex] = NULL;
		}
	}

	for (int nCntmeshDome = 0; nCntmeshDome < MAX_MESHDOME; nCntmeshDome++)
	{
		// ���_�o�b�t�@�̊J��
		if (g_ameshDome[nCntmeshDome].pVtxBuff != NULL)
		{
			g_ameshDome[nCntmeshDome].pVtxBuff->Release();
			g_ameshDome[nCntmeshDome].pVtxBuff = NULL;
		}

		// �C���f�b�N�X�o�b�t�@�̊J��
		if (g_ameshDome[nCntmeshDome].pIdxBuff != NULL)
		{
			g_ameshDome[nCntmeshDome].pIdxBuff->Release();
			g_ameshDome[nCntmeshDome].pIdxBuff = NULL;
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdatemeshDome(void)
{
	for (int nCntmeshDome = 0; nCntmeshDome < g_NumMAXmeshDomeInfo; nCntmeshDome++)
	{
		VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_ameshDome[nCntmeshDome].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���̐ݒ�
		for (int nCntPos = 0; nCntPos < g_ameshDome[nCntmeshDome].nNumVertex; nCntPos++,pVtx++)
		{
			// �e�N�X�`�����W
			pVtx[0].tex += g_ameshDome[nCntmeshDome].TexMoveSpeed;
		}
		// ���_�o�b�t�@���A�����b�N����
		g_ameshDome[nCntmeshDome].pVtxBuff->Unlock();
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawmeshDome(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot,mtxTrans;					// �v�Z�p�}�g���b�N�X����

	// ���C�g�I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntmeshDome = 0; nCntmeshDome < g_NumMAXmeshDomeInfo; nCntmeshDome++)
	{
		// �`�悷��ʂ�ݒ�
		switch (g_ameshDome[nCntmeshDome].DrawSide)
		{
		case DRAWSIDE_BOTH:
			// �J�����O�I�t
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			break;
		case DRAWSIDE_IN:
			// �\�ʃJ�����O
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
			break;
		case DRAWSIDE_OUT:
			// ���ʃJ�����O
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			break;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_ameshDome[nCntmeshDome].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ameshDome[nCntmeshDome].rot.y, g_ameshDome[nCntmeshDome].rot.x, g_ameshDome[nCntmeshDome].rot.z);
		D3DXMatrixMultiply(&g_ameshDome[nCntmeshDome].mtxWorld, &g_ameshDome[nCntmeshDome].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_ameshDome[nCntmeshDome].pos.x, g_ameshDome[nCntmeshDome].pos.y, g_ameshDome[nCntmeshDome].pos.z);
		D3DXMatrixMultiply(&g_ameshDome[nCntmeshDome].mtxWorld, &g_ameshDome[nCntmeshDome].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_ameshDome[nCntmeshDome].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_ameshDome[nCntmeshDome].pVtxBuff, 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_ameshDome[nCntmeshDome].pIdxBuff);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturemeshDome[g_ameshDome[nCntmeshDome].TexType]);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_ameshDome[nCntmeshDome].nNumVertex, 0, g_ameshDome[nCntmeshDome].nNumPolygon);
	}

	// ���C�g�I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �J�����O�ݒ��߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���_���̍쐬
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeVertexmeshDome(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntmeshDome = 0; nCntmeshDome < g_NumMAXmeshDomeInfo; nCntmeshDome++)
	{
		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_ameshDome[nCntmeshDome].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_ameshDome[nCntmeshDome].pVtxBuff,
			NULL);

		VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_ameshDome[nCntmeshDome].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_[H]�̊p�x���v�Z
		float fAngleH = D3DX_PI * 2 / g_ameshDome[nCntmeshDome].nNumSplitH;
		float fDestAngleH = 0.0f;		// �ړI�̊p�x���i�[����֐�
		// ���_[V]�̊p�x���v�Z
		float fAngleV = D3DX_PI / g_ameshDome[nCntmeshDome].nNumSplitV;
		float fDestAngleV = D3DX_PI;		// �ړI�̊p�x���i�[����֐�

		// ���_���W�̐ݒ�
		for (int nCnt1 = 0; nCnt1 < g_ameshDome[nCntmeshDome].nNumSplitV + 1; nCnt1++)
		{// �c�̎�
			 // �p�x[H]�̃��Z�b�g
			fDestAngleH = 0.0f;

			for (int nCnt2 = 0; nCnt2 < g_ameshDome[nCntmeshDome].nNumSplitH + 1; nCnt2++)
			{// ���̎�
				// �p�x[H]�`�F�b�N
				if (fDestAngleH > D3DX_PI)
				{
					fDestAngleH -= D3DX_PI * 2;
				}

				pVtx[nCnt1 * (g_ameshDome[nCntmeshDome].nNumSplitH + 1) + nCnt2].pos =
					D3DXVECTOR3(sinf(fDestAngleH) * g_ameshDome[nCntmeshDome].fRadius * sinf(fDestAngleV),
						cosf(fDestAngleV) * g_ameshDome[nCntmeshDome].fRadius,
						cosf(fDestAngleH) * g_ameshDome[nCntmeshDome].fRadius * sinf(fDestAngleV)) + g_ameshDome[nCntmeshDome].pos;

				// �p�x[H]��i�߂�
				fDestAngleH += fAngleH;
			}
			// �p�x[V]��i�߂�
			fDestAngleV -= fAngleV;
		}
		// �@���̐ݒ�@
		for (int nCntNor = 0; nCntNor < g_ameshDome[nCntmeshDome].nNumVertex; nCntNor++)
		{
			D3DXVec3Normalize(&pVtx[nCntNor].nor, &pVtx[nCntNor].pos);		// ���K������
		}

		// ���_�J���[�̐ݒ�
		for (int nCntCol = 0; nCntCol < g_ameshDome[nCntmeshDome].nNumVertex; nCntCol++)
		{
			pVtx[nCntCol].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// �e�N�X�`���̐ݒ�
		for (int nCntTex = 0; nCntTex < g_ameshDome[nCntmeshDome].nNumVertex; nCntTex++)
		{
			pVtx[nCntTex].tex = D3DXVECTOR2(1.0f / 2.0f / g_ameshDome[nCntmeshDome].nNumSplitH * (nCntTex % (g_ameshDome[nCntmeshDome].nNumSplitH + 1)),
				1.0f / 2.0f / g_ameshDome[nCntmeshDome].nNumSplitV * (nCntTex / (g_ameshDome[nCntmeshDome].nNumSplitH + 1)));
		}

		// ���_�o�b�t�@���A�����b�N����
		g_ameshDome[nCntmeshDome].pVtxBuff->Unlock();
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C���f�b�N�X���̍쐬
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeIndexmeshDome(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntmeshDome = 0; nCntmeshDome < g_NumMAXmeshDomeInfo; nCntmeshDome++)
	{
		// �C���f�b�N�X�o�b�t�@�𐶐�
		// �C���f�b�N�X���̍쐬
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_ameshDome[nCntmeshDome].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,			// �C���f�b�N�X�t�H�[�}�b�g [16bit (2byte)]
			D3DPOOL_MANAGED,
			&g_ameshDome[nCntmeshDome].pIdxBuff,
			NULL);

		WORD *pIdx;				// �C���f�b�N�X�f�[�^�ւ̃|�C���^

		// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
		g_ameshDome[nCntmeshDome].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		// �C���f�b�N�X�̐ݒ�
		for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < g_ameshDome[nCntmeshDome].nNumIndex; nCnt1++, nCnt2 += 2)
		{
			if ((nCnt2 + 2) % (g_ameshDome[nCntmeshDome].nNumSplitH * 2 + 4) == 0 && nCnt2 != 0)
			{// �k�ރ|���S��
				pIdx[nCnt2] = pIdx[nCnt2 - 1];
				pIdx[nCnt2 + 1] = nCnt1 + g_ameshDome[nCntmeshDome].nNumSplitH + 1;
				nCnt1--;
			}
			else
			{// �ʏ�̃|���S��
				pIdx[nCnt2] = nCnt1 + g_ameshDome[nCntmeshDome].nNumSplitH + 1;
				pIdx[nCnt2 + 1] = nCnt1;
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		g_ameshDome[nCntmeshDome].pIdxBuff->Unlock();
	}
}
