//=============================================================================
//
// �p�[�e�B�N������ [particle.cpp]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "particle.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PARTICLE_FILENAME	"data/TEXTFILE/particle.txt"				// �p�[�e�B�N���f�[�^
#define TEXTURE_FILENAME	"data/TEXTFILE/particle_texture.txt"		// �e�N�X�`����

#define MAX_EMITTER_TYPE	(32)							// �p�[�e�B�N���̎�ނ̍ő吔
#define MAX_PARTICLE		(1024)							// �p�[�e�B�N���̍ő吔

#define MAX_TEXTURE			(32)								// �e�N�X�`���̍ő吔
#define MAX_TYPE			(32)								// ���ڂ̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice);

void FileInputParticle(void);
void TextureInputParticle(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureParticle[MAX_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Particle g_aParticle[MAX_PARTICLE];				// �p�[�e�B�N��
ParEmitter g_aEmitter[MAX_EMITTER];				// �\���p�̃G�~�b�^
ParEmitter g_aEditEmitter[MAX_EMITTER_TYPE];		// �G�f�B�b�g�p�̃G�~�b�^

int g_nCntParticle;		// �o��������Ԋu�̃J�E���^

int g_nSelectParticleEmitter;				// �I�𒆂̃G�~�b�^
int g_nSelectParticleType;					// �I�𒆂̍���

int g_nNumParticleData;						// �p�[�e�B�N���̎�ނ̐�
int g_nNumParticleTexture;					// �e�N�X�`���̐�

int g_nCntAngle;						// �p�[�e�B�N���̊p�x�v�Z�p�J�E���^

//=============================================================================
// ����������
//=============================================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �p�[�e�B�N���̏���������
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].fRadius = 0;
		g_aParticle[nCntParticle].nType = 0;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].fAngle = 0.0f;
		g_aParticle[nCntParticle].fBouncing = 0.0f;
		g_aParticle[nCntParticle].nIdx = 0;
		g_aParticle[nCntParticle].bUse = false;
	}

	// �G�~�b�^�̏���������
	for (int nCntEmitter = 0; nCntEmitter < MAX_EMITTER; nCntEmitter++)
	{
		g_aEmitter[nCntEmitter].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEmitter[nCntEmitter].nWidth[0] = 0;
		g_aEmitter[nCntEmitter].nWidth[1] = 0;
		g_aEmitter[nCntEmitter].nHeight[0] = 0;
		g_aEmitter[nCntEmitter].nHeight[1] = 0;
		g_aEmitter[nCntEmitter].nDepth[0] = 0;
		g_aEmitter[nCntEmitter].nDepth[1] = 0;
		g_aEmitter[nCntEmitter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEmitter[nCntEmitter].flameCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEmitter[nCntEmitter].nRadius[0] = 0;
		g_aEmitter[nCntEmitter].nRadius[1] = 0;
		g_aEmitter[nCntEmitter].fFlameRadius = 0;
		g_aEmitter[nCntEmitter].fSpread = 0.0f;
		g_aEmitter[nCntEmitter].nAppear = 1;
		g_aEditEmitter[nCntEmitter].fRotSpeed = 0.0f;
		g_aEmitter[nCntEmitter].nParLife[0] = 0;
		g_aEmitter[nCntEmitter].nParLife[1] = 0;
		g_aEmitter[nCntEmitter].nLife = 0;
		g_aEmitter[nCntEmitter].nType = 0;
		g_aEmitter[nCntEmitter].nLap = 0;
		g_aEmitter[nCntEmitter].bLoop = false;
		g_aEmitter[nCntEmitter].bBouncing = false;
		g_aEmitter[nCntEmitter].bUse = false;
	}
	for (int nCntEmitter = 0; nCntEmitter < MAX_EMITTER_TYPE; nCntEmitter++)
	{
		g_aEditEmitter[nCntEmitter].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEditEmitter[nCntEmitter].nWidth[0] = 0;
		g_aEditEmitter[nCntEmitter].nWidth[1] = 0;
		g_aEditEmitter[nCntEmitter].nHeight[0] = 0;
		g_aEditEmitter[nCntEmitter].nHeight[1] = 0;
		g_aEditEmitter[nCntEmitter].nDepth[0] = 0;
		g_aEditEmitter[nCntEmitter].nDepth[1] = 0;
		g_aEditEmitter[nCntEmitter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEditEmitter[nCntEmitter].flameCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEditEmitter[nCntEmitter].nRadius[0] = 0;
		g_aEditEmitter[nCntEmitter].nRadius[1] = 0;
		g_aEditEmitter[nCntEmitter].fFlameRadius = 0;
		g_aEditEmitter[nCntEmitter].fSpread = 0.0f;
		g_aEditEmitter[nCntEmitter].nAppear = 1;
		g_aEditEmitter[nCntEmitter].nParLife[0] = 0;
		g_aEditEmitter[nCntEmitter].nParLife[1] = 0;
		g_aEditEmitter[nCntEmitter].nLife = 0;
		g_aEditEmitter[nCntEmitter].nLap = 1;
		g_aEditEmitter[nCntEmitter].fRotSpeed = 0.0f;
		g_aEditEmitter[nCntEmitter].nType = 0;
		g_aEditEmitter[nCntEmitter].bLoop = false;
		g_aEditEmitter[nCntEmitter].bBouncing = false;
		g_aEditEmitter[nCntEmitter].bUse = false;
	}

	g_nCntParticle = 0;
	g_nNumParticleTexture = 1;
	g_nCntAngle = 0;

	FileInputParticle();
	TextureInputParticle();

	// �p�[�e�B�N���̒��_���̍쐬
	MakeVertexParticle(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitParticle(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		if (g_pTextureParticle[nCntTexture] != NULL)
		{
			g_pTextureParticle[nCntTexture]->Release();
			g_pTextureParticle[nCntTexture] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateParticle(void)
{
	int nCntParticle;	// for���p�̃J�E���^

	for (int nCntEmitter = 0; nCntEmitter < MAX_EMITTER; nCntEmitter++)
	{
		if (g_aEmitter[nCntEmitter].bUse == true)
		{// �g�p����Ă���G�~�b�^

			g_aEmitter[nCntEmitter].nLife--;	// �G�~�b�^�̕\�����Ԃ��J�E���g

			if (g_aEmitter[nCntEmitter].nLife <= 0 && g_aEmitter[nCntEmitter].bLoop == false)
			{// ��莞�Ԍo�߂ŃG�~�b�^������
				g_aEmitter[nCntEmitter].bUse = false;
			}

			// �o��������Ԋu�̃J�E���g
			g_nCntParticle = (g_nCntParticle + 1) % g_aEmitter[nCntEmitter].nAppear;

			if (g_nCntParticle == 0)
			{// �o��������
				for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
				{// �p�[�e�B�N��������
					if (g_aParticle[nCntParticle].bUse == false)
					{// �g���Ă��Ȃ�
						g_aParticle[nCntParticle].fAngle = 1.0f / (g_aEmitter[nCntEmitter].nLap / 2);
						g_aParticle[nCntParticle].pos = g_aEmitter[nCntEmitter].pos;
						g_aParticle[nCntParticle].move = D3DXVECTOR3(sinf(D3DX_PI * (0.0f + (g_aParticle[nCntParticle].fAngle * g_nCntAngle))) * ((g_aEmitter[nCntEmitter].nWidth[0] + (rand() % (1 + (g_aEmitter[nCntEmitter].nWidth[1] * 2)) - 1)) + ((rand() % 10) * 0.1f)) * g_aEmitter[nCntEmitter].fSpread,
							((rand() % (1 + g_aEmitter[nCntEmitter].nHeight[1])) + g_aEmitter[nCntEmitter].nHeight[0]) + ((rand() % 10) * 0.1f),
							cosf(D3DX_PI * (0.0f + (g_aParticle[nCntParticle].fAngle * g_nCntAngle))) * ((g_aEmitter[nCntEmitter].nDepth[0] + (rand() % (1 + (g_aEmitter[nCntEmitter].nDepth[1] * 2)) - 1)) + ((rand() % 10) * 0.1f)) * g_aEmitter[nCntEmitter].fSpread);
						g_aParticle[nCntParticle].col = g_aEmitter[nCntEmitter].col;
						g_aParticle[nCntParticle].fRadius = g_aEmitter[nCntEmitter].nRadius[0] + (rand() % (1 + (g_aEmitter[nCntEmitter].nRadius[1] - g_aEmitter[nCntEmitter].nRadius[0])) - 1) + ((rand() % 10) * 0.1f);
						g_aParticle[nCntParticle].nLife = g_aEmitter[nCntEmitter].nParLife[0] + (rand() % (1 + (g_aEmitter[nCntEmitter].nParLife[1] - g_aEmitter[nCntEmitter].nParLife[0])) - 1);
						g_aParticle[nCntParticle].nType = g_aEmitter[nCntEmitter].nType;
						g_aParticle[nCntParticle].nIdx = nCntEmitter;
						g_aParticle[nCntParticle].fGravity = g_aEmitter[nCntEmitter].fGravity;
						g_aParticle[nCntParticle].bDraw = g_aEmitter[nCntEmitter].bDraw;
						g_aParticle[nCntParticle].bUse = true;

						g_nCntAngle = (g_nCntAngle + 1) % g_aEmitter[nCntEmitter].nLap;
						break;
					}
				}
			}
		}
	}

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// �p�[�e�B�N���̍X�V
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	VERTEX_3D*pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{// �g���Ă���
			g_aParticle[nCntParticle].nLife--;		// �\�����Ԃ��J�E���g

			// �\�����Ԃ�0�ȉ��ɂȂ���
			if (g_aParticle[nCntParticle].nLife <= 0)
			{// �g�p���Ă��Ȃ���Ԃɂ���
				g_aParticle[nCntParticle].bUse = false;
			}
#if 0
			if (6 == g_aParticle[nCntParticle].nType)
			{// �h���S���̉�
				D3DXVECTOR3 rot = GetNeckRot();

				g_aParticle[nCntParticle].move -= D3DXVECTOR3(sinf(rot.y) * 0.3f, 0.0f, cosf(rot.y) * 0.3f);
			}
#endif
			g_aParticle[nCntParticle].move.y -= g_aParticle[nCntParticle].fGravity;		// �d�͂�������

			g_aParticle[nCntParticle].fBouncing = g_aParticle[nCntParticle].pos.y;		// �l���L��

			g_aParticle[nCntParticle].pos += g_aParticle[nCntParticle].move;							// �ʒu�̍X�V
			g_aParticle[nCntParticle].col += g_aEmitter[g_aParticle[nCntParticle].nIdx].flameCol;				// �F�̍X�V
			g_aParticle[nCntParticle].fRadius += g_aEmitter[g_aParticle[nCntParticle].nIdx].fFlameRadius;		// �傫���̍X�V

			if (g_aParticle[nCntParticle].pos.y <= 0 && g_aEmitter[g_aParticle[nCntParticle].nIdx].bBouncing == true)
			{// �o�E���h
				g_aParticle[nCntParticle].move.y += (g_aParticle[nCntParticle].fBouncing - g_aParticle[nCntParticle].pos.y) * 2.0f;
			}

			// ���_�̊p�x
			g_aParticle[nCntParticle].fRotAngle = atan2f(g_aParticle[nCntParticle].pos.x - (g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius), g_aParticle[nCntParticle].pos.y - (g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius));

			// ���S���璸�_�܂ł̋���
			g_aParticle[nCntParticle].fLength = sqrtf((g_aParticle[nCntParticle].fRadius * g_aParticle[nCntParticle].fRadius) + (g_aParticle[nCntParticle].fRadius * g_aParticle[nCntParticle].fRadius));

			if (g_aEmitter[g_aParticle[nCntParticle].nIdx].nRot == 1)
			{// ���v���
				g_aParticle[nCntParticle].fCntRot -= g_aEmitter[g_aParticle[nCntParticle].nIdx].fRotSpeed;			// ��]�̃J�E���^
			}
			else if (g_aEmitter[g_aParticle[nCntParticle].nIdx].nRot == 2)
			{// �����v���
				g_aParticle[nCntParticle].fCntRot += g_aEmitter[g_aParticle[nCntParticle].nIdx].fRotSpeed;			// ��]�̃J�E���^
			}
			else if (g_aEmitter[g_aParticle[nCntParticle].nIdx].nRot == 3)
			{// �����_��
				if (nCntParticle % 2 == 0)
				{// ���v���
					g_aParticle[nCntParticle].fCntRot += g_aEmitter[g_aParticle[nCntParticle].nIdx].fRotSpeed;		// ��]�̃J�E���^
				}
				else
				{// �����v���
					g_aParticle[nCntParticle].fCntRot -= g_aEmitter[g_aParticle[nCntParticle].nIdx].fRotSpeed;		// ��]�̃J�E���^
				}
			}

			//���_���W�̐ݒ�
			pVtx[0].pos.x = sinf(g_aParticle[nCntParticle].fRotAngle + g_aParticle[nCntParticle].fCntRot) * -(g_aParticle[nCntParticle].fLength + g_aParticle[nCntParticle].fRadius);
			pVtx[0].pos.y = cosf(g_aParticle[nCntParticle].fRotAngle + g_aParticle[nCntParticle].fCntRot) * (g_aParticle[nCntParticle].fLength + g_aParticle[nCntParticle].fRadius);
			pVtx[1].pos.x = sinf(g_aParticle[nCntParticle].fRotAngle - g_aParticle[nCntParticle].fCntRot) * (g_aParticle[nCntParticle].fLength + g_aParticle[nCntParticle].fRadius);
			pVtx[1].pos.y = cosf(g_aParticle[nCntParticle].fRotAngle - g_aParticle[nCntParticle].fCntRot) * (g_aParticle[nCntParticle].fLength + g_aParticle[nCntParticle].fRadius);
			pVtx[2].pos.x = sinf(g_aParticle[nCntParticle].fRotAngle - g_aParticle[nCntParticle].fCntRot) * -(g_aParticle[nCntParticle].fLength + g_aParticle[nCntParticle].fRadius);
			pVtx[2].pos.y = cosf(g_aParticle[nCntParticle].fRotAngle - g_aParticle[nCntParticle].fCntRot) * -(g_aParticle[nCntParticle].fLength + g_aParticle[nCntParticle].fRadius);
			pVtx[3].pos.x = sinf(g_aParticle[nCntParticle].fRotAngle + g_aParticle[nCntParticle].fCntRot) * (g_aParticle[nCntParticle].fLength + g_aParticle[nCntParticle].fRadius);
			pVtx[3].pos.y = cosf(g_aParticle[nCntParticle].fRotAngle + g_aParticle[nCntParticle].fCntRot) * -(g_aParticle[nCntParticle].fLength + g_aParticle[nCntParticle].fRadius);

			//���_���W�̐ݒ�
			//pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);

			//���_�J���[
			pVtx[0].col = g_aParticle[nCntParticle].col;
			pVtx[1].col = g_aParticle[nCntParticle].col;
			pVtx[2].col = g_aParticle[nCntParticle].col;
			pVtx[3].col = g_aParticle[nCntParticle].col;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}


	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();
}

//=============================================================================
// �|���S���`�揈��
//=============================================================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX	mtxRot, mtxTrans, mtxView;		// �v�Z�p�}�g���b�N�X
	int nCntParticle;

	//�t�H�O���g�p���Ȃ�
	//pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{// �p�[�e�B�N�����g���Ă����
			if (g_aParticle[nCntParticle].bDraw == true)
			{ // ���u�����f�B���O�����Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}
			else
			{// ���u�����f�B���O�����ɖ߂�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aParticle[nCntParticle].mtxWorld);

			// ��]�𔽉f
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			g_aParticle[nCntParticle].mtxWorld._11 = mtxView._11;
			g_aParticle[nCntParticle].mtxWorld._12 = mtxView._21;
			g_aParticle[nCntParticle].mtxWorld._13 = mtxView._31;
			g_aParticle[nCntParticle].mtxWorld._21 = mtxView._12;
			g_aParticle[nCntParticle].mtxWorld._22 = mtxView._22;
			g_aParticle[nCntParticle].mtxWorld._23 = mtxView._32;
			g_aParticle[nCntParticle].mtxWorld._31 = mtxView._13;
			g_aParticle[nCntParticle].mtxWorld._32 = mtxView._23;
			g_aParticle[nCntParticle].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aParticle[nCntParticle].pos.x, g_aParticle[nCntParticle].pos.y, g_aParticle[nCntParticle].pos.z);
			D3DXMatrixMultiply(&g_aParticle[nCntParticle].mtxWorld, &g_aParticle[nCntParticle].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aParticle[nCntParticle].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureParticle[g_aParticle[nCntParticle].nType]);

			// �p�[�e�B�N���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntParticle, 2);
		}
	}

	// Z�o�b�t�@�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// ���e�X�g�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�t�H�O���g�p����
	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//=============================================================================
// �G�~�b�^�̐ݒ�
//=============================================================================
void SetParticleEmitter(D3DXVECTOR3 pos, int nType)
{
	for (int nCntEmitter = 0; nCntEmitter < MAX_EMITTER; nCntEmitter++)
	{
		if (g_aEmitter[nCntEmitter].bUse == false)
		{// �g�p����Ă����Ԃɂ���
			g_aEmitter[nCntEmitter].pos = pos;
			g_aEmitter[nCntEmitter].nWidth[0] = g_aEditEmitter[nType].nWidth[0];
			g_aEmitter[nCntEmitter].nWidth[1] = g_aEditEmitter[nType].nWidth[1];
			g_aEmitter[nCntEmitter].nHeight[0] = g_aEditEmitter[nType].nHeight[0];
			g_aEmitter[nCntEmitter].nHeight[1] = g_aEditEmitter[nType].nHeight[1];
			g_aEmitter[nCntEmitter].nDepth[0] = g_aEditEmitter[nType].nDepth[0];
			g_aEmitter[nCntEmitter].nDepth[1] = g_aEditEmitter[nType].nDepth[1];
			g_aEmitter[nCntEmitter].col = g_aEditEmitter[nType].col;
			g_aEmitter[nCntEmitter].flameCol = g_aEditEmitter[nType].flameCol;
			g_aEmitter[nCntEmitter].nRadius[0] = g_aEditEmitter[nType].nRadius[0];
			g_aEmitter[nCntEmitter].nRadius[1] = g_aEditEmitter[nType].nRadius[1];
			g_aEmitter[nCntEmitter].fFlameRadius = g_aEditEmitter[nType].fFlameRadius;
			g_aEmitter[nCntEmitter].fSpread = g_aEditEmitter[nType].fSpread;
			g_aEmitter[nCntEmitter].nAppear = g_aEditEmitter[nType].nAppear;
			g_aEmitter[nCntEmitter].nParLife[0] = g_aEditEmitter[nType].nParLife[0];
			g_aEmitter[nCntEmitter].nParLife[1] = g_aEditEmitter[nType].nParLife[1];
			g_aEmitter[nCntEmitter].nLap = g_aEditEmitter[nType].nLap;
			g_aEmitter[nCntEmitter].nLife = g_aEditEmitter[nType].nLife;
			g_aEmitter[nCntEmitter].nRot = g_aEditEmitter[nType].nRot;
			g_aEmitter[nCntEmitter].fRotSpeed = g_aEditEmitter[g_nSelectParticleEmitter].fRotSpeed;
			g_aEmitter[nCntEmitter].nType = g_aEditEmitter[nType].nType;
			g_aEmitter[nCntEmitter].bLoop = g_aEditEmitter[nType].bLoop;
			g_aEmitter[nCntEmitter].bBouncing = g_aEditEmitter[nType].bBouncing;
			g_aEmitter[nCntEmitter].fGravity = g_aEditEmitter[nType].fGravity;
			g_aEmitter[nCntEmitter].bDraw = g_aEditEmitter[nType].bDraw;

			g_aEmitter[nCntEmitter].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �G�~�b�^�̈ʒu�̐ݒ�
//=============================================================================
void SetPosParticleEmitter(int nIdx, D3DXVECTOR3 pos)
{
	if (g_aEmitter[nIdx].bUse == true)
	{// �ʒu���X�V
		g_aEmitter[nIdx].pos = pos;
	}
}

//=============================================================================
// �G�~�b�^�̍폜
//=============================================================================
void DestroyParticle(int nIdx)
{
	if (g_aEmitter[nIdx].bUse == true)
	{// �g���Ă��Ȃ���Ԃɂ���
		g_aEmitter[nIdx].bUse = false;
	}
}

//=============================================================================
// �t�@�C������f�[�^���擾
//=============================================================================
void FileInputParticle(void)
{
	FILE *pFile;
	int nCntEffect;
	int nBool;

	pFile = fopen(PARTICLE_FILENAME, "r");

	if (NULL != pFile)
	{
		for (nCntEffect = 0; nCntEffect < MAX_EMITTER_TYPE; nCntEffect++)
		{// �f�[�^���܂킷
			fscanf(pFile, "%d %d %d", &g_aEditEmitter[nCntEffect].nWidth[1], &g_aEditEmitter[nCntEffect].nHeight[1], &g_aEditEmitter[nCntEffect].nDepth[1]);	// �ړ��ʂ̍ő�
			fscanf(pFile, "%d %d %d", &g_aEditEmitter[nCntEffect].nWidth[0], &g_aEditEmitter[nCntEffect].nHeight[0], &g_aEditEmitter[nCntEffect].nDepth[0]);	// �ړ��ʂ̍ŏ�
			fscanf(pFile, "%f %f %f %f", &g_aEditEmitter[nCntEffect].col.r, &g_aEditEmitter[nCntEffect].col.g, &g_aEditEmitter[nCntEffect].col.b, &g_aEditEmitter[nCntEffect].col.a);	// �F
			fscanf(pFile, "%f %f %f %f", &g_aEditEmitter[nCntEffect].flameCol.r, &g_aEditEmitter[nCntEffect].flameCol.g, &g_aEditEmitter[nCntEffect].flameCol.b, &g_aEditEmitter[nCntEffect].flameCol.a);	// �F
			fscanf(pFile, "%d %d", &g_aEditEmitter[nCntEffect].nRadius[0], &g_aEditEmitter[nCntEffect].nRadius[1]);			// �T�C�Y
			fscanf(pFile, "%f", &g_aEditEmitter[nCntEffect].fFlameRadius);	// �T�C�Y�̉��Z
			fscanf(pFile, "%d", &g_aEditEmitter[nCntEffect].nLife);			// �\������(����)
			fscanf(pFile, "%d %d", &g_aEditEmitter[nCntEffect].nParLife[0], &g_aEditEmitter[nCntEffect].nParLife[1]);		// �p�[�e�B�N���̕\������
			fscanf(pFile, "%d", &g_aEditEmitter[nCntEffect].nAppear);		// �o��Ԋu
			fscanf(pFile, "%f", &g_aEditEmitter[nCntEffect].fSpread);		// �L����
			fscanf(pFile, "%d", &g_aEditEmitter[nCntEffect].nLap);			// 1���ɏo����
			fscanf(pFile, "%f", &g_aEditEmitter[nCntEffect].fGravity);		// �d��
			fscanf(pFile, "%d", &g_aEditEmitter[nCntEffect].nRot);			// ��]�̃p�^�[��
			fscanf(pFile, "%f", &g_aEditEmitter[nCntEffect].fRotSpeed);		// ��]�̑��x
			fscanf(pFile, "%d", &nBool);									// ���[�v���邩�ǂ���
			if (nBool > 0)
			{// ���[�v���^�̂Ƃ�
				g_aEditEmitter[nCntEffect].bLoop = true;
			}
			else
			{// ���[�v���U�̂Ƃ�
				g_aEditEmitter[nCntEffect].bLoop = false;
			}

			fscanf(pFile, "%d", &nBool);									// �o�E���h���邩�ǂ���
			if (nBool > 0)
			{// �o�E���h���^�̂Ƃ�
				g_aEditEmitter[nCntEffect].bBouncing = true;
			}
			else
			{// �o�E���h���U�̂Ƃ�
				g_aEditEmitter[nCntEffect].bBouncing = false;
			}

			fscanf(pFile, "%d", &g_aEditEmitter[nCntEffect].nType);			// �e�N�X�`���̎��

			fscanf(pFile, "%d", &nBool);									// ���Z�����̗L��
			if (nBool > 0)
			{// �o�E���h���^�̂Ƃ�
				g_aEditEmitter[nCntEffect].bDraw = true;
			}
			else
			{// �o�E���h���U�̂Ƃ�
				g_aEditEmitter[nCntEffect].bDraw = false;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// ���s
		MessageBox(0, "�t�@�C�����J���܂���ł���", "effect.txt", MB_OK);
	}
}

//=============================================================================
// �t�@�C������e�N�X�`�����擾
//=============================================================================
void TextureInputParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FILE *pFile;
	char aFileName[MAX_TEXTURE][64];		// �e�N�X�`���̖��O
	int nCntTexture;

	pFile = fopen(TEXTURE_FILENAME, "r");

	if (NULL != pFile)
	{// �J����
		fscanf(pFile, "%d", &g_nNumParticleTexture);		// �e�N�X�`����

		for (nCntTexture = 0; nCntTexture < g_nNumParticleTexture; nCntTexture++)
		{
			fscanf(pFile, "%s\n", &aFileName[nCntTexture][0]);		// �e�N�X�`����
		}
		fclose(pFile);
	}
	else
	{// ���s
		MessageBox(0, "�t�@�C�����J���܂���ł���", "texture.txt", MB_OK);
	}

	// �e�N�X�`���̓ǂݍ���
	for (nCntTexture = 0; nCntTexture < g_nNumParticleTexture; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, &aFileName[nCntTexture][0], &g_pTextureParticle[nCntTexture]);
	}
}

//=============================================================================
// �p�[�e�B�N���̒��_���̍쐬
//=============================================================================
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	VERTEX_3D*pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̍��W
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBuffParticle->Unlock();
}

//=============================================================================
// �p�[�e�B�N���̃��Z�b�g
//=============================================================================
void DeleteParticle(void)
{
	// �p�[�e�B�N���̏���������
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].fRadius = 0;
		g_aParticle[nCntParticle].nType = 0;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].fAngle = 0.0f;
		g_aParticle[nCntParticle].fBouncing = 0.0f;
		g_aParticle[nCntParticle].nIdx = 0;
		g_aParticle[nCntParticle].bUse = false;
	}

	// �G�~�b�^�̏���������
	for (int nCntEmitter = 0; nCntEmitter < MAX_EMITTER; nCntEmitter++)
	{
		g_aEmitter[nCntEmitter].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEmitter[nCntEmitter].nWidth[0] = 0;
		g_aEmitter[nCntEmitter].nWidth[1] = 0;
		g_aEmitter[nCntEmitter].nHeight[0] = 0;
		g_aEmitter[nCntEmitter].nHeight[1] = 0;
		g_aEmitter[nCntEmitter].nDepth[0] = 0;
		g_aEmitter[nCntEmitter].nDepth[1] = 0;
		g_aEmitter[nCntEmitter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEmitter[nCntEmitter].flameCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEmitter[nCntEmitter].nRadius[0] = 0;
		g_aEmitter[nCntEmitter].nRadius[1] = 0;
		g_aEmitter[nCntEmitter].fFlameRadius = 0;
		g_aEmitter[nCntEmitter].fSpread = 0.0f;
		g_aEmitter[nCntEmitter].nAppear = 1;
		g_aEmitter[nCntEmitter].nParLife[0] = 0;
		g_aEmitter[nCntEmitter].nParLife[1] = 0;
		g_aEmitter[nCntEmitter].nLife = 0;
		g_aEmitter[nCntEmitter].nType = 0;
		g_aEmitter[nCntEmitter].nLap = 0;
		g_aEmitter[nCntEmitter].bLoop = false;
		g_aEmitter[nCntEmitter].bBouncing = false;
		g_aEmitter[nCntEmitter].bUse = false;
	}
}
