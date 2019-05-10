//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : 
//=============================================================================
#include "time.h"
#include "game.h"
#include "billboard.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"date/TEXTURE/number999.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Time						g_nTime[4];					// �X�R�A
//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	int nCountTimePotato;
	int nCntTime;
	int nCount2;
	float fPotato;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (nCountTimePotato = 0; nCountTimePotato < 4; nCountTimePotato++)
	{
		g_nTime[nCountTimePotato].bUse = false;
		g_nTime[nCountTimePotato].fwidth = 0;
		g_nTime[nCountTimePotato].Height = 0;
		g_nTime[nCountTimePotato].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
	}
	// �X�R�A�̏�����
	//g_nTime = 6000;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SCORE,		// �t�@�C���̖��O
		&g_pTextureTime);	// �e�N�X�`���ւ̃|�C���^

							// ���_���̍쐬
							//MakeVertexTime(pDevice);

	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_SCORE,
		&g_pTextureTime
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * (4 * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffTime->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCount2 = 0; nCount2 < 4; nCount2++)
	{
		for (nCntTime = 0, fPotato = 0; nCntTime < 4; nCntTime++, fPotato -= 40)
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
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{
	int nKioku;
	int nCntTime;
	int nPotatoCoin= PotatoCoinGet();
	int nCountTime;

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffTime->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCountTime = 0; nCountTime < 4; nCountTime++)
	{
		if (g_nTime[nCountTime].bUse == true)
		{
			if (g_nTime[nCountTime].nTime > 0 && nPotatoCoin > 0)
			{
				g_nTime[nCountTime].nTime--;
			}
			else if (g_nTime[nCountTime].nTime == 0)
			{
				SetGameState(GAMESTATE_END);
			}
			nKioku = g_nTime[nCountTime].nTime;

			for (nCntTime = 0; nCntTime < 4; nCntTime++)
			{
				//�e�N�X�`���ݒ�
				pVtx[nCntTime * 4].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 0.0f);
				pVtx[nCntTime * 4 + 1].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 0.0f);
				pVtx[nCntTime * 4 + 2].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 1.0f);
				pVtx[nCntTime * 4 + 3].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 1.0f);
				nKioku /= 10;
			}
		}
		pVtx += (4 * 4);
	}
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	int nCntTime;
	int nCountTimePotato;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	// �|���S���̕`��
	for (nCountTimePotato = 0; nCountTimePotato < 4; nCountTimePotato++)
	{
		if (g_nTime[nCountTimePotato].bUse == true)
		{
			for (nCntTime = 0; nCntTime < 4; nCntTime++)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
			}
		}
	}
	
}

void Settime(D3DXVECTOR3 Pos, float fwidth, float Height)
{
	int nCount;
	int nCountTime;
	D3DXVECTOR3 nPos;

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^
	g_pVtxBuffTime->Lock		//���_�o�b�t�@�����b�N
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCount = 0; nCount < 4; nCount++)
	{
		if (g_nTime[nCount].bUse == false)		//�g�p���ĂȂ��Ȃ�
		{
			g_nTime[nCount].pos = Pos;
			g_nTime[nCount].fwidth = fwidth;
			g_nTime[nCount].Height = Height;
			g_nTime[nCount].bUse = true;
			g_nTime[0].nTime = 6000;
			g_nTime[1].nTime = 0;
			g_nTime[2].nTime = 0;
			g_nTime[3].nTime = 0;
			nPos = Pos;

			for (nCountTime = 0; nCountTime < 4; nCountTime++)
			{
				//���_�ݒ�
				pVtx[nCountTime * 4].pos = D3DXVECTOR3(nPos.x, nPos.y, 0.0f);
				pVtx[nCountTime * 4 + 1].pos = D3DXVECTOR3(nPos.x + g_nTime[nCount].fwidth, nPos.y, 0.0f);
				pVtx[nCountTime * 4 + 2].pos = D3DXVECTOR3(nPos.x, nPos.y + g_nTime[nCount].Height, 0.0f);
				pVtx[nCountTime * 4 + 3].pos = D3DXVECTOR3(nPos.x + g_nTime[nCount].fwidth, nPos.y + g_nTime[nCount].Height, 0.0f);

				nPos.x -= 45;
			}
			break;
		}
		pVtx += (4 * 4);
	}
	g_pVtxBuffTime->Unlock();
}


////=============================================================================
//// ���_���̍쐬
////=============================================================================
//void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
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
void AddTime(int nValue)
{
	int nCountPotato;

	for (nCountPotato = 0; nCountPotato < 4; nCountPotato++)
	{
		if (g_nTime[nCountPotato].bUse == true)
		{
			g_nTime[nCountPotato].nTime += nValue;
		}
	}
}

Time *GetTime(void)
{
	return &g_nTime[0];
}