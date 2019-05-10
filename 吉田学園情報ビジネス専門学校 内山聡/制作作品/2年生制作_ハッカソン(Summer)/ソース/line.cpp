//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// ���C������ [line.cpp]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "line.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LINE	(12 * 512)		// ���C���̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexLine(LPDIRECT3DDEVICE9 pDevice);		// ���_���̐���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine;	// ���_�o�b�t�@�ւ̃|�C���^
Line g_aLine[MAX_LINE];					// ���C���̏��
int g_nIdxLine = 0;						// ���C���̎g�p�ԍ�
bool g_bLine = true;					// ���C����`�悷�邩�ǂ���

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitLine(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ������
	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		g_aLine[nCntLine].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aLine[nCntLine].posStart = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].posEnd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aLine[nCntLine].bUse = false;
		g_aLine[nCntLine].nIdxLine = 0;
	}

	// ���_���̍쐬
	MakeVertexLine(pDevice);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitLine(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateLine(void)
{
	// �`��؂�ւ�
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_bLine = g_bLine ? false : true;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawLine(void)
{
	if (g_bLine == true)
	{// �`�悷��ꍇ
		LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
		D3DXMATRIX mtxTrans, mtxView;				// �v�Z�p�}�g���b�N�X

		// ���C�g�I�t
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
		{
			if (g_aLine[nCntLine].bUse == true)
			{
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aLine[nCntLine].mtxWorld);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans,
					g_aLine[nCntLine].pos.x, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z);
				D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld,
					&g_aLine[nCntLine].mtxWorld, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aLine[nCntLine].mtxWorld);

				// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				// �|���S��[��]�̕`��
				pDevice->DrawPrimitive(D3DPT_LINELIST, 2 * nCntLine, 1);
			}
		}

		// ���C�g�I��
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���_���̍쐬
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeVertexLine(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_LINE,		// �m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_3D,				// ���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&g_pVtxBuffLine,
								NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLine->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���C���̐ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 posStart, D3DXVECTOR3 posEnd, D3DXCOLOR col,int nIdxLine)
{
	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++, pVtx += 2)
	{
		if (g_aLine[nCntLine].bUse == false)
		{ // �e���g�p����Ă��Ȃ��ꍇ
			g_aLine[nCntLine].pos = pos;
			g_aLine[nCntLine].posStart = posStart;
			g_aLine[nCntLine].posEnd = posEnd;
			g_aLine[nCntLine].col = col;
			g_aLine[nCntLine].nIdxLine = nIdxLine;

			// ���_���W�̐ݒ�
			pVtx[0].pos = g_aLine[nCntLine].posStart;
			pVtx[1].pos = g_aLine[nCntLine].posEnd;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aLine[nCntLine].col;
			pVtx[1].col = g_aLine[nCntLine].col;

			g_aLine[nCntLine].bUse = true; // �g�p���Ă����Ԃɂ���

			break;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLine->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �����蔻��p���C���Z�b�g�̐ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int SetColisionLine(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	// �C���f�b�N�X��i�߂�
	g_nIdxLine++;

	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMin.z), D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMin.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMin.z), D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMin.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMin.z), D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMin.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMin.z), D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMin.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);

	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMax.z), D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMax.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMax.z), D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMax.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMax.z), D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMax.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMax.z), D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMax.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);

	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMin.z), D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMax.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMin.z), D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMax.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMin.z), D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMax.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMin.z), D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMax.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_nIdxLine);

	return g_nIdxLine;		// �C���f�b�N�X��Ԃ�
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �����蔻��p���C���Z�b�g�̐ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int SetColisionLine2(D3DXVECTOR3 pos, float fRadius, float fHeight)
{
	// �C���f�b�N�X��i�߂�
	g_nIdxLine++;

	//--- XZ [��] ---//
	SetLine(pos, D3DXVECTOR3(-fRadius,	fHeight,	-fRadius),	D3DXVECTOR3(fRadius,	fHeight,	-fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(fRadius,	fHeight,	-fRadius),	D3DXVECTOR3(fRadius,	fHeight,	fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(fRadius,	fHeight,	fRadius),	D3DXVECTOR3(-fRadius,	fHeight,	fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(-fRadius,	fHeight,	fRadius),	D3DXVECTOR3(-fRadius,	fHeight,	-fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);
	//--- XZ [��] ---//
	SetLine(pos, D3DXVECTOR3(-fRadius,	0.0f,		-fRadius),	D3DXVECTOR3(fRadius,	0.0f,		-fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(fRadius,	0.0f,		-fRadius),	D3DXVECTOR3(fRadius,	0.0f,		fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(fRadius,	0.0f,		fRadius),	D3DXVECTOR3(-fRadius,	0.0f,		fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(-fRadius,	0.0f,		fRadius),	D3DXVECTOR3(-fRadius,	0.0f,		-fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);
	//--- Y [�と����]---//
	SetLine(pos, D3DXVECTOR3(-fRadius,	fHeight,	-fRadius),	D3DXVECTOR3(-fRadius,	0.0f,		-fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(fRadius,	fHeight,	-fRadius),	D3DXVECTOR3(fRadius,	0.0f,		-fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(fRadius,	fHeight,	fRadius),	D3DXVECTOR3(fRadius,	0.0f,		fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);
	SetLine(pos, D3DXVECTOR3(-fRadius,	fHeight,	fRadius),	D3DXVECTOR3(-fRadius,	0.0f,		fRadius),	D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_nIdxLine);

	return g_nIdxLine;		// �C���f�b�N�X��Ԃ�
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���C���̈ʒu�X�V
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetPositionLine(int nIdxLine, D3DXVECTOR3 pos)
{
	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{// �g�p��� & �����C���f�b�N�X�̏ꍇ
		if (g_aLine[nCntLine].bUse == true && g_aLine[nCntLine].nIdxLine == nIdxLine)
		{
			g_aLine[nCntLine].pos = pos;		// �ʒu�̍X�V
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���C���̍폜
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DeleteLine(int nIdxLine)
{
	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{// �g�p��� & �����C���f�b�N�X�̏ꍇ
		if (g_aLine[nCntLine].bUse == true && g_aLine[nCntLine].nIdxLine == nIdxLine)
		{
			g_aLine[nCntLine].bUse = false;		// ���g�p�ɖ߂�
		}
	}
}