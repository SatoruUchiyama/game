//=============================================================================
//
// ���ʏ��� [field.cpp]
// Author : Ishida Takuto
//
//=============================================================================
#include "field.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MESHFIELD_01		"data/TEXTURE/river000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_MESHFIELD_00		"data/TEXTURE/river001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define FIELD_WIDTH		(1000.0f)		// ��
#define FIELD_DEPTH		(4500.0f)		// ���s
#define MAX_TEXTURE		(2)				// �e�N�X�`����
#define MAX_FIELD		(2)				// �t�B�[���h���i�n�ʂ𑝂₵�����Ƃ��ɒl��ς��Ă��������j

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureField[MAX_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Field g_Field[MAX_FIELD];

//=============================================================================
// ����������
//=============================================================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_00, &g_pTextureField[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_01, &g_pTextureField[1]);

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_Field[nCntField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu�̏�����
		g_Field[nCntField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �����̏�����
		g_Field[nCntField].nType = nCntField;										// �t�B�[���h�̃e�N�X�`���w��
	}

	// ���_���̍쐬
	MakeVertexField(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureField[nCntTex] != NULL)
		{
			g_pTextureField[nCntTex]->Release();
			g_pTextureField[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateField(void)
{
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex += D3DXVECTOR2(0.000f, -0.0004f);
	pVtx[1].tex += D3DXVECTOR2(0.000f, -0.0004f);
	pVtx[2].tex += D3DXVECTOR2(0.000f, -0.0004f);
	pVtx[3].tex += D3DXVECTOR2(0.000f, -0.0004f);

	pVtx[4].tex += D3DXVECTOR2(0.0003f, 0.0003f);
	pVtx[5].tex += D3DXVECTOR2(0.0003f, 0.0003f);
	pVtx[6].tex += D3DXVECTOR2(0.0003f, 0.0003f);
	pVtx[7].tex += D3DXVECTOR2(0.0003f, 0.0003f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffField->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX	mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Field[nCntField].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Field[nCntField].rot.y, g_Field[nCntField].rot.x, g_Field[nCntField].rot.z);
		D3DXMatrixMultiply(&g_Field[nCntField].mtxWorld, &g_Field[nCntField].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Field[nCntField].pos.x, g_Field[nCntField].pos.y, g_Field[nCntField].pos.z);
		D3DXMatrixMultiply(&g_Field[nCntField].mtxWorld, &g_Field[nCntField].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Field[nCntField].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureField[g_Field[nCntField].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntField, 2);
	}

	// ���e�X�g�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	// ���_�o�b�t�@�̏���ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-FIELD_WIDTH, 0.0f + (nCntField * 0.001f), FIELD_DEPTH);
		pVtx[1].pos = D3DXVECTOR3(FIELD_WIDTH, 0.0f + (nCntField * 0.001f), FIELD_DEPTH);
		pVtx[2].pos = D3DXVECTOR3(-FIELD_WIDTH, 0.0f + (nCntField * 0.001f), -FIELD_DEPTH);
		pVtx[3].pos = D3DXVECTOR3(FIELD_WIDTH, 0.0f + (nCntField * 0.001f), -FIELD_DEPTH);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�

	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffField->Unlock();
}

//=============================================================================
// �����蔻��̏���
//=============================================================================
//bool CollisionField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
//{
//	bool bLand = false;		// �n�ʂɐڒ����Ă��邩�ǂ���	[true : �ڒ����Ă���	false : �����Ă���]
//
//	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
//	{
//		if (pPos->y < g_Field[nCntField].pos.y && pPosOld->y >= g_Field[nCntField].pos.y)
//		{// �ォ�瓖��������
//			bLand = true;							// �n�ʂɐڒ���Ԃɂ���
//			pPos->y = g_Field[nCntField].pos.y;	// ���܂��Ă���̂�n�ʂ̏�ɖ߂�
//			pMove->y = 0.0f;						// �������x��0�ɂ���
//		}
//	}
//
//	return bLand;	// �ڒ���Ԃ�Ԃ�
//}