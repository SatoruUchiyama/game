//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// ���b�V��(�C���f�b�N�X�o�b�t�@�g�p)�̏��� [meshField.cpp]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "meshField.h"
#include "particle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexmeshField(LPDIRECT3DDEVICE9 pDevice);		// ���_���̐���
void MakeIndexmeshField(LPDIRECT3DDEVICE9 pDevice);			// �C���f�b�N�X�̐���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_apTexturemeshField[MESHFIELDTYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
meshField g_ameshField[MAX_MESHFIELD];								// ���b�V���̏��

// -----�@�e�N�X�`�����@----- //
meshFieldTexture g_ameshFieldTexture[MESHFIELDTYPE_MAX] =
{
	{"data/TEXTURE/field000.jpg"}		// 000
};

// -----�@�t�B�[���h�z�u���@----- //
meshFieldInfo g_ameshFieldInfo[] =
{// �ʒu(pos),							����(rot),					������	X,	Z
	{ D3DXVECTOR3(0.0f,-100.0f,0.0f),		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	5,	10			,3000.0f, 6000.0f },
};

int g_NumMAXmeshFieldInfo;		// �z�u���̍ő吔

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitmeshField(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �z�u���̍ő吔
	g_NumMAXmeshFieldInfo = sizeof g_ameshFieldInfo / sizeof(meshFieldInfo);

	// �e�N�X�`���̓ǂݍ���
	for (int nTex = 0; nTex < MESHFIELDTYPE_MAX; nTex++)
	{
		D3DXCreateTextureFromFile(pDevice, g_ameshFieldTexture[nTex].pFilename, &g_apTexturemeshField[nTex]);
	}

	// ������
	for (int nCntmeshField = 0; nCntmeshField < MAX_MESHFIELD; nCntmeshField++)
	{
		g_ameshField[nCntmeshField].pVtxBuff = NULL;
		g_ameshField[nCntmeshField].pIdxBuff = NULL;
		g_ameshField[nCntmeshField].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_ameshField[nCntmeshField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ameshField[nCntmeshField].nNumSplitX = 0;
		g_ameshField[nCntmeshField].nNumSplitZ = 0;
		g_ameshField[nCntmeshField].fWidth = 0.0f;
		g_ameshField[nCntmeshField].fDepth = 0.0f;
		g_ameshField[nCntmeshField].nNumVertex = 0;
		g_ameshField[nCntmeshField].nNumIndex = 0;
		g_ameshField[nCntmeshField].nNumPolygon = 0;
	}

	// �z�u���̑��
	for (int nCntmeshField = 0; nCntmeshField < g_NumMAXmeshFieldInfo; nCntmeshField++)
	{
		g_ameshField[nCntmeshField].pos = g_ameshFieldInfo[nCntmeshField].pos;
		g_ameshField[nCntmeshField].rot = g_ameshFieldInfo[nCntmeshField].rot;
		g_ameshField[nCntmeshField].nNumSplitX = g_ameshFieldInfo[nCntmeshField].nNumSplitX;
		g_ameshField[nCntmeshField].nNumSplitZ = g_ameshFieldInfo[nCntmeshField].nNumSplitZ;
		g_ameshField[nCntmeshField].fWidth = g_ameshFieldInfo[nCntmeshField].fWidth;
		g_ameshField[nCntmeshField].fDepth = g_ameshFieldInfo[nCntmeshField].fDepth;
		// ���_�� = (X������ + 1) * (Z������ + 1)
		g_ameshField[nCntmeshField].nNumVertex = (g_ameshField[nCntmeshField].nNumSplitX + 1) * (g_ameshField[nCntmeshField].nNumSplitZ + 1);
		// �C���f�b�N�X�� = X������ * Z������ * 2 + (Z������ - 1) * 4 + 2
		g_ameshField[nCntmeshField].nNumIndex = g_ameshField[nCntmeshField].nNumSplitX * g_ameshField[nCntmeshField].nNumSplitZ * 2 + (g_ameshField[nCntmeshField].nNumSplitZ - 1) * 4 + 2;
		// �|���S���� = �C���f�b�N�X�� - 2
		g_ameshField[nCntmeshField].nNumPolygon = g_ameshField[nCntmeshField].nNumIndex - 2;
	}

	// ���_���̍쐬
	MakeVertexmeshField(pDevice);

	// �C���f�b�N�X�̐���
	MakeIndexmeshField(pDevice);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitmeshField(void)
{
	for (int nCntmeshField = 0; nCntmeshField < MAX_MESHFIELD; nCntmeshField++)
	{
		// ���_�o�b�t�@�̊J��
		if (g_ameshField[nCntmeshField].pVtxBuff != NULL)
		{
			g_ameshField[nCntmeshField].pVtxBuff->Release();
			g_ameshField[nCntmeshField].pVtxBuff = NULL;
		}
		// �C���f�b�N�X�̔j��
		if (g_ameshField[nCntmeshField].pIdxBuff != NULL)
		{
			g_ameshField[nCntmeshField].pIdxBuff->Release();
			g_ameshField[nCntmeshField].pIdxBuff = NULL;
		}
	}
	// �e�N�X�`���̔j��
	for (int nTex = 0; nTex < MESHFIELDTYPE_MAX; nTex++)
	{
		if (g_apTexturemeshField[nTex] != NULL)
		{
			g_apTexturemeshField[nTex]->Release();
			g_apTexturemeshField[nTex] = NULL;
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdatemeshField(void)
{
	//SetParticleEmitter(D3DXVECTOR3(-100.0f, 50.0f, -620.0f), 3);
	//SetParticleEmitter(D3DXVECTOR3(0.0f, 50.0f, -620.0f), 3);
	//SetParticleEmitter(D3DXVECTOR3(100.0f, 50.0f, -620.0f), 3);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawmeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	for (int nCntmeshField = 0; nCntmeshField < g_NumMAXmeshFieldInfo; nCntmeshField++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_ameshField[nCntmeshField].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_ameshField[nCntmeshField].rot.y, g_ameshField[nCntmeshField].rot.x, g_ameshField[nCntmeshField].rot.z);
		D3DXMatrixMultiply(&g_ameshField[nCntmeshField].mtxWorld,
			&g_ameshField[nCntmeshField].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_ameshField[nCntmeshField].pos.x, g_ameshField[nCntmeshField].pos.y, g_ameshField[nCntmeshField].pos.z);
		D3DXMatrixMultiply(&g_ameshField[nCntmeshField].mtxWorld,
			&g_ameshField[nCntmeshField].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_ameshField[nCntmeshField].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_ameshField[nCntmeshField].pVtxBuff, 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_ameshField[nCntmeshField].pIdxBuff);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturemeshField[ MESHFIELDTYPE_000]);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_ameshField[nCntmeshField].nNumVertex, 0, g_ameshField[nCntmeshField].nNumPolygon);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���_���̍쐬
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeVertexmeshField(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

	for (int nCntmeshField = 0; nCntmeshField < g_NumMAXmeshFieldInfo; nCntmeshField++)
	{
		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_ameshField[nCntmeshField].nNumVertex,		// �m�ۂ���o�b�t�@�̃T�C�Y
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,				// ���_�t�H�[�}�b�g
			D3DPOOL_MANAGED,
			&g_ameshField[nCntmeshField].pVtxBuff,
			NULL);

		//--- ���_���̐ݒ� ---//
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_ameshField[nCntmeshField].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W
		for (int nCnt1 = 0; nCnt1 < g_ameshField[nCntmeshField].nNumSplitZ + 1; nCnt1++)
		{// ���s�̎�
			for (int nCnt2 = 0; nCnt2 < g_ameshField[nCntmeshField].nNumSplitX + 1; nCnt2++)
			{// ���̎�
				pVtx[nCnt1 * (g_ameshField[nCntmeshField].nNumSplitX + 1) + nCnt2].pos =
					D3DXVECTOR3(-g_ameshField[nCntmeshField].fWidth / 2 + g_ameshField[nCntmeshField].fWidth / g_ameshField[nCntmeshField].nNumSplitX * nCnt2,
						0.0f,
						g_ameshField[nCntmeshField].fDepth / 2 - g_ameshField[nCntmeshField].fDepth / g_ameshField[nCntmeshField].nNumSplitZ * nCnt1);
			}
		}
		// �@��
		for (int nNor = 0; nNor < g_ameshField[nCntmeshField].nNumVertex; nNor++)
		{
			pVtx[nNor].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}
		// ���_�J���[
		for (int nCol = 0; nCol < g_ameshField[nCntmeshField].nNumVertex; nCol++)
		{
			pVtx[nCol].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		// �e�N�X�`�����W
		for (int nCnt1 = 0; nCnt1 < g_ameshField[nCntmeshField].nNumSplitZ + 1; nCnt1++)
		{// ���s�̎�
			for (int nCnt2 = 0; nCnt2 < g_ameshField[nCntmeshField].nNumSplitX + 1; nCnt2++)
			{// ���̎�
				//// �ꖇ
				//pVtx[nCnt1 * (g_ameshField[nCntmeshField].nNumSplitX + 1) + nCnt2].tex = D3DXVECTOR2(1.0f / (g_ameshField[nCntmeshField].nNumSplitX) * nCnt2, 1.0f / (g_ameshField[nCntmeshField].nNumSplitZ) * nCnt1);
				// �������ɍ��킹��
				pVtx[nCnt1 * (g_ameshField[nCntmeshField].nNumSplitX + 1) + nCnt2].tex = D3DXVECTOR2(0.5f * nCnt2, 0.5f * nCnt1);
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		g_ameshField[nCntmeshField].pVtxBuff->Unlock();
	}
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C���f�b�N�X�̍쐬
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeIndexmeshField(LPDIRECT3DDEVICE9 pDevice)
{
	WORD *pIdx;		// �C���f�b�N�X�f�[�^�ւ̃|�C���^

	for (int nCntmeshField = 0; nCntmeshField < g_NumMAXmeshFieldInfo; nCntmeshField++)
	{
		// �C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_ameshField[nCntmeshField].nNumIndex,		// �m�ۂ���o�b�t�@�̃T�C�Y
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,				// �C���f�b�N�X�t�H�[�}�b�g [16bit (2byte)]
			D3DPOOL_MANAGED,
			&g_ameshField[nCntmeshField].pIdxBuff,
			NULL);

		// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
		g_ameshField[nCntmeshField].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		// �C���f�b�N�X�̐ݒ�
		for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < g_ameshField[nCntmeshField].nNumIndex; nCnt1++, nCnt2 += 2)
		{
			if ((nCnt2 + 2) % (g_ameshField[nCntmeshField].nNumSplitX * 2 + 4) == 0 && nCnt2 != 0)
			{// �k�ރ|���S��
				pIdx[nCnt2] = pIdx[nCnt2 - 1];											// �E��C���f�b�N�X
				pIdx[nCnt2 + 1] = nCnt1 + g_ameshField[nCntmeshField].nNumSplitX + 1;	// �����C���f�b�N�X
				nCnt1--;
			}
			else
			{// �ʏ�̃|���S��
				pIdx[nCnt2] = nCnt1 + g_ameshField[nCntmeshField].nNumSplitX + 1;
				pIdx[nCnt2 + 1] = nCnt1;
			}
		}
		// �C���f�b�N�X���A�����b�N����
		g_ameshField[nCntmeshField].pIdxBuff->Unlock();
	}
}
