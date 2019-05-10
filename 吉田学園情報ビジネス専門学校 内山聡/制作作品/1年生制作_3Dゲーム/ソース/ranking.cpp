//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : 
//
//=============================================================================
#include "ranking.h"
#include "game.h"
//#include "item.h"
#include "time.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RANKING		"date/TEXTURE/number999.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define RANKING_MAX			(2)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Ranking						g_nRanking[RANKING_MAX];					// �X�R�A

//=============================================================================
// ����������
//=============================================================================
void InitRanking(void)
{
	int nCountRankingPotato;
	int nCntRanking;
	int nCount2;

//	int nPotato1;
	//	int nCount;
	float fPotato;
	float fPotatoY;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (nCountRankingPotato = 0; nCountRankingPotato < RANKING_MAX; nCountRankingPotato++)
	{
		g_nRanking[nCountRankingPotato].bUse = true;
		g_nRanking[nCountRankingPotato].fwidth = 0;
		g_nRanking[nCountRankingPotato].Height = 0;
		g_nRanking[nCountRankingPotato].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}

	Time pTime;
	pTime = *GetTime();

	// �X�R�A�̏�����
	g_nRanking[0].nRanking = pTime.nTime;	//ima
	if (g_nRanking[0].nRanking > g_nRanking[1].nRanking)
	{
		g_nRanking[1].nRanking = g_nRanking[0].nRanking;
	}
	 


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING,		// �t�@�C���̖��O
		&g_pTextureRanking);	// �e�N�X�`���ւ̃|�C���^

	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_RANKING,
		&g_pTextureRanking
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * (RANKING_MAX * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffRanking->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCount2 = 0, fPotatoY = 200.0f; nCount2 < RANKING_MAX; nCount2++, fPotatoY += 200 )
	{
		for (nCntRanking = 0, fPotato = 700 ; nCntRanking < 4; nCntRanking++, fPotato -= 80)
		{

			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(fPotato, fPotatoY, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(fPotato + 80.0f, fPotatoY, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(fPotato, fPotatoY + 80.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(fPotato + 80.0f, fPotatoY + 80.0f, 0.0f);
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
	g_pVtxBuffRanking->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRanking(void)
{
	int nKioku;
	int nCntRanking;
	//int nPotatoCoin = PotatoCoinGet();
	int nCountRanking;

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffRanking->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCountRanking = 0; nCountRanking < RANKING_MAX; nCountRanking++)
	{
		if (g_nRanking[nCountRanking].bUse == true)
		{

			nKioku = g_nRanking[nCountRanking].nRanking;

			for (nCntRanking = 0; nCntRanking < 4; nCntRanking++)
			{
				//�e�N�X�`���ݒ�
				pVtx[nCntRanking * 4].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 0.0f);
				pVtx[nCntRanking * 4 + 1].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 0.0f);
				pVtx[nCntRanking * 4 + 2].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 1.0f);
				pVtx[nCntRanking * 4 + 3].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 1.0f);
				nKioku /= 10;
			}
		}
		pVtx += (4 * 4);


	}
	g_pVtxBuffRanking->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	int nCntRanking;
	int nCountRankingPotato;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking);

	// �|���S���̕`��
	for (nCountRankingPotato = 0; nCountRankingPotato < RANKING_MAX; nCountRankingPotato++)
	{
		if (g_nRanking[nCountRankingPotato].bUse == true)
		{
			for (nCntRanking = 0; nCntRanking < 4; nCntRanking++)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCountRankingPotato * 4 * 4) + (nCntRanking * 4), 2);
			}
		}
	}

}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddRanking(int nValue)
{
	int nCountPotato;

	for (nCountPotato = 0; nCountPotato < 4; nCountPotato++)
	{
		if (g_nRanking[nCountPotato].bUse == true)
		{
			g_nRanking[nCountPotato].nRanking += nValue;
		}
	}
}

Ranking *GetRanking(void)
{
	return &g_nRanking[0];
}