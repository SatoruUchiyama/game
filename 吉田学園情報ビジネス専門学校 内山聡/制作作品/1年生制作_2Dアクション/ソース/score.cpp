//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number999.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Score					g_Score[4];					// �X�R�A

//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{
	int nCountScorePotato;
	int nCntScore;
	float fPotato;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	for (nCountScorePotato = 0; nCountScorePotato < 4; nCountScorePotato++)
	{
		g_Score[nCountScorePotato].bUse = false;
		g_Score[nCountScorePotato].fwidth = 0;
		g_Score[nCountScorePotato].Height = 0;
		g_Score[nCountScorePotato].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Score[nCountScorePotato].g_Score = 0;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&g_pTextureScore);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	//MakeVertexScore(pDevice);

	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_SCORE,
		&g_pTextureScore
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * (8 * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffScore->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCountScorePotato = 0; nCountScorePotato < 4; nCountScorePotato++)
	{
		for (nCntScore = 0, fPotato = 1200; nCntScore < 8; nCntScore++, fPotato -= 30)
		{

			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(fPotato, 30.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(fPotato + 30.0f, 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(fPotato, 80.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(fPotato + 30.0f, 80.0f, 0.0f);
			//1.0f�ŌŒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//���_�J���[�ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			//�e�N�X�`���ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			//���_�o�b�t�@���A�����b�N
			pVtx += 4;
		}
	}
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	int nKioku;
	int nCountScorePotato;
	int nCntScore;

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffScore->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCountScorePotato = 0; nCountScorePotato < 4; nCountScorePotato++)
	{
		if (g_Score[nCountScorePotato].bUse == true)
		{
			nKioku = g_Score[nCountScorePotato].g_Score;
			for (nCntScore = 0; nCntScore < 8; nCntScore++)
			{
				//�e�N�X�`���ݒ�
				pVtx[nCntScore * 4].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 0.0f);
				pVtx[nCntScore * 4 + 1].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 0.0f);
				pVtx[nCntScore * 4 + 2].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 1.0f);
				pVtx[nCntScore * 4 + 3].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 1.0f);
				nKioku /= 10;
			}
		}
		pVtx += (8 * 4);
	}
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	int nCountScorePotato;
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	// �|���S���̕`��
	for (nCountScorePotato = 0; nCountScorePotato < 4; nCountScorePotato++)
	{
		if (g_Score[nCountScorePotato].bUse == true)
		{
			for (nCntScore = 0; nCntScore < 8; nCntScore++)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
			}
		}
	}
}


void SetScore(D3DXVECTOR3 Pos, float fwidth, float Height)
{
	int nCount;
	int nCountScore;
	D3DXVECTOR3 nPos;

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^
	g_pVtxBuffScore->Lock		//���_�o�b�t�@�����b�N
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCount = 0; nCount < 4; nCount++)
	{
		if (g_Score[nCount].bUse == false)		//�g�p���ĂȂ��Ȃ�
		{
			g_Score[nCount].pos = Pos;
			g_Score[nCount].fwidth = fwidth;
			g_Score[nCount].Height = Height;
			g_Score[nCount].bUse = true;
			nPos = Pos;

			for (nCountScore = 0; nCountScore < 8; nCountScore++)
			{				
				//���_�ݒ�
				pVtx[nCountScore * 4].pos = D3DXVECTOR3(nPos.x, nPos.y, 0.0f);
				pVtx[nCountScore * 4 + 1].pos = D3DXVECTOR3(nPos.x + g_Score[nCount].fwidth, nPos.y, 0.0f);
				pVtx[nCountScore * 4 + 2].pos = D3DXVECTOR3(nPos.x, nPos.y + g_Score[nCount].Height, 0.0f);
				pVtx[nCountScore * 4 + 3].pos = D3DXVECTOR3(nPos.x + g_Score[nCount].fwidth, nPos.y + g_Score[nCount].Height, 0.0f);

				nPos.x -= g_Score[nCount].fwidth;
			}
			break;
		}
		pVtx += (8 * 4);
	}
	g_pVtxBuffScore->Unlock();
}

////=============================================================================
//// ���_���̍쐬
////=============================================================================
//void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
//{
//	// �e�N�X�`���̊J��
//	
//
//	// ���_�o�b�t�@�̊J��
//	
//
//}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddScore(int nValue)
{
	int nCountScorePotato;

	for (nCountScorePotato = 0; nCountScorePotato < 4; nCountScorePotato++)
	{
		if (g_Score[nCountScorePotato].bUse == true)
		{
			g_Score[nCountScorePotato].g_Score += nValue;
		}
	}
}
