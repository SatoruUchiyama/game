//=============================================================================
//
// �Ԃт珈�� [petals.cpp]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#include "petals.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PETALS_TEXTURENAME00	"data/TEXTURE/petal000.png"
#define MAX_PETALS			(128)		// �Ԃт�̍ő吔
#define MAX_TEXTURE			(1)			// �e�N�X�`���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePetals[MAX_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPetals = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
PETALS g_aPetals[MAX_PETALS];

//=============================================================================
// �|���S������������
//=============================================================================
void InitPetals(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �W�F�l���[�^�̏���������
	for (int nCntPetals = 0; nCntPetals < MAX_PETALS; nCntPetals++)
	{
		g_aPetals[nCntPetals].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPetals[nCntPetals].fRadius = 0;
		g_aPetals[nCntPetals].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPetals[nCntPetals].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPetals[nCntPetals].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPetals[nCntPetals].angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPetals[nCntPetals].bMoveWidth = false;
		g_aPetals[nCntPetals].bMoveAngle = false;
		g_aPetals[nCntPetals].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PETALS_TEXTURENAME00, &g_pTexturePetals[0]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PETALS,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPetals,
		NULL);

	VERTEX_3D*pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPetals->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̍��W
	for (int nCntPetals = 0; nCntPetals < MAX_PETALS; nCntPetals++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aPetals[nCntPetals].fRadius, g_aPetals[nCntPetals].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPetals[nCntPetals].fRadius, g_aPetals[nCntPetals].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aPetals[nCntPetals].fRadius, -g_aPetals[nCntPetals].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPetals[nCntPetals].fRadius, -g_aPetals[nCntPetals].fRadius, 0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPetals->Unlock();
}

//=============================================================================
// �|���S���I������
//=============================================================================
void UninitPetals(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		// �e�N�X�`���̔j��
		if (g_pTexturePetals[nCntTex] != NULL)
		{
			g_pTexturePetals[nCntTex]->Release();
			g_pTexturePetals[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPetals != NULL)
	{
		g_pVtxBuffPetals->Release();
		g_pVtxBuffPetals = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePetals(void)
{
	int nCntPetals;

	VERTEX_3D*pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPetals->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPetals = 0; nCntPetals < MAX_PETALS; nCntPetals++)
	{
		if (g_aPetals[nCntPetals].bUse == true)
		{// �g���Ă���
			if (g_aPetals[nCntPetals].pos.y <= 0)
			{// �n�ʂɂ��������
				g_aPetals[nCntPetals].bUse = false;
			}

			// ��]������
			g_aPetals[nCntPetals].rot += g_aPetals[nCntPetals].angle;

			// ���~
			if (g_aPetals[nCntPetals].bMoveAngle)
			{// �ɂ₩
				g_aPetals[nCntPetals].move.y += 0.01f;

				if (g_aPetals[nCntPetals].move.y >= 0.3f)
				{// ���܂ŏ㏸����
					g_aPetals[nCntPetals].bMoveAngle = false;
				}
			}
			else if (!g_aPetals[nCntPetals].bMoveAngle)
			{// �}
				g_aPetals[nCntPetals].move.y -= 0.01f;

				if (g_aPetals[nCntPetals].move.y <= -0.8f)
				{// ���܂ŉ��~����
					g_aPetals[nCntPetals].bMoveAngle = true;
				}
			}

			// ���̈ړ�
			if (g_aPetals[nCntPetals].bMoveWidth)
			{// �{����
				g_aPetals[nCntPetals].move.x += 0.01f;

				if (g_aPetals[nCntPetals].move.x >= 0.8f)
				{// ���܂ő��x��������
					g_aPetals[nCntPetals].bMoveWidth = false;
				}
			}
			else if (!g_aPetals[nCntPetals].bMoveWidth)
			{// -����
				g_aPetals[nCntPetals].move.x -= 0.01f;

				if (g_aPetals[nCntPetals].move.x <= -0.8f)
				{// ���܂ő��x���オ����
					g_aPetals[nCntPetals].bMoveWidth = true;
				}
			}

			// �ړ��ʂ����Z
			g_aPetals[nCntPetals].pos += g_aPetals[nCntPetals].move;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aPetals[nCntPetals].fRadius, g_aPetals[nCntPetals].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPetals[nCntPetals].fRadius, g_aPetals[nCntPetals].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aPetals[nCntPetals].fRadius, -g_aPetals[nCntPetals].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPetals[nCntPetals].fRadius, -g_aPetals[nCntPetals].fRadius, 0.0f);
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPetals->Unlock();
}

//=============================================================================
// �|���S���`�揈��
//=============================================================================
void DrawPetals(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX	mtxRot, mtxTrans, mtxView;		// �v�Z�p�}�g���b�N�X
	int nCntPetals;

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);		// �J�����O�𖳌���

	// ���Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	for (nCntPetals = 0; nCntPetals < MAX_PETALS; nCntPetals++)
	{
		if (g_aPetals[nCntPetals].bUse == true)
		{// �Ԃт炪�g���Ă����
		 // ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aPetals[nCntPetals].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPetals[nCntPetals].rot.y, g_aPetals[nCntPetals].rot.x, g_aPetals[nCntPetals].rot.z);
			D3DXMatrixMultiply(&g_aPetals[nCntPetals].mtxWorld, &g_aPetals[nCntPetals].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aPetals[nCntPetals].pos.x, g_aPetals[nCntPetals].pos.y, g_aPetals[nCntPetals].pos.z);
			D3DXMatrixMultiply(&g_aPetals[nCntPetals].mtxWorld, &g_aPetals[nCntPetals].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aPetals[nCntPetals].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffPetals, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePetals[g_aPetals[nCntPetals].nType]);

			// �`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPetals, 2);
		}
	}

	// Z�o�b�t�@�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);		// ���ʂ��J�����O
}

//=============================================================================
// �Ԃт�̐ݒ�
//=============================================================================
void SetPetals(D3DXVECTOR3 pos, int nNumber)
{
	VERTEX_3D*pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPetals->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntNumber = 0; nCntNumber < nNumber; nCntNumber++)
	{
		for (int nCntPetals = 0; nCntPetals < MAX_PETALS; nCntPetals++)
		{
			if (g_aPetals[nCntPetals].bUse == false)
			{// �g�p����Ă��Ȃ�����
				g_aPetals[nCntPetals].pos = pos;
				g_aPetals[nCntPetals].move = D3DXVECTOR3(-15 + (rand() % 30) + ((rand() % 10) * 0.1f) * 0.008f,
					-(((rand() % 2) + 1) * 0.5f + ((rand() % 5) * 0.1f)),
					-15 + (rand() % 30) + ((rand() % 10) * 0.1f)) * 0.008f;
				g_aPetals[nCntPetals].fRadius = 10;
				g_aPetals[nCntPetals].col = D3DXCOLOR(1.0f, 0.5f, 0.8f, 1.0f);
				g_aPetals[nCntPetals].angle = D3DXVECTOR3((-5 + (rand() % 10)) * 0.01f, (-5 + (rand() % 10)) * 0.01f, (-5 + (rand() % 10)) * 0.01f);
				g_aPetals[nCntPetals].bUse = true;
				g_aPetals[nCntPetals].nType = 0;
				// ���ɗh�炷����
				if(rand() % 2 == 0){ g_aPetals[nCntPetals].bMoveWidth = false; }
				else{ g_aPetals[nCntPetals].bMoveWidth = true; }

				// �c�ɗh�炷����
				if (rand() % 2 == 0) { g_aPetals[nCntPetals].bMoveAngle = false; }
				else { g_aPetals[nCntPetals].bMoveAngle = true; }

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(-g_aPetals[nCntPetals].fRadius, g_aPetals[nCntPetals].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aPetals[nCntPetals].fRadius, g_aPetals[nCntPetals].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_aPetals[nCntPetals].fRadius, -g_aPetals[nCntPetals].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aPetals[nCntPetals].fRadius, -g_aPetals[nCntPetals].fRadius, 0.0f);
				break;
			}
		}
	}
}
