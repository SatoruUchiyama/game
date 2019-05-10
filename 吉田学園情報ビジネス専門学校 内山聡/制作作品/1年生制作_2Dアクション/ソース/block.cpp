//=============================================================================
//
// �e���� [bullet.cpp]
// Author :
//
//=============================================================================
#include "block.h"
#include "player.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_TEXTURE_NAME	"data\\TEXTURE\\animal_blox02_d_03.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define POLYGON_TEXTURE_SPEED	(5)										//�e�N�X�`���A�j���[�V�����X�s�[�h
#define POLYGON_TEXTURE_PATTERN	(10)									//�e�N�X�`���A�j���[�V�����p�^�[����
#define POLYGON_TEXTURE_UV_U	(1.0f)									//�e�N�X�`���A�j���[�V����U�͈�
#define POLYGON_TEXTURE_UV_V	(1.0f)									//�e�N�X�`���A�j���[�V����V�͈�
#define POLYGON_BLOCK			(50)									//�u���b�N�̐�
#define POLYGON_TYPE			(5)
//#define 

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[POLYGON_TYPE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Block g_Block[POLYGON_BLOCK];

//=============================================================================
// ����������
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;
	for (nCount = 0; nCount < POLYGON_BLOCK; nCount++)
	{
		g_Block[nCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCount].fwidth = 0;
		g_Block[nCount].Height = 0;
		g_Block[nCount].bUse = false;
		g_Block[nCount].BrockType = BLOCKTYPE_NOMAL;
	}
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �ǂ̏��̏�����

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		POLYGON_TEXTURE_NAME,
		&g_pTextureBlock[0]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data\\TEXTURE\\block400.jpg",
		&g_pTextureBlock[1]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data\\TEXTURE\\block005.jpg",
		&g_pTextureBlock[2]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data\\TEXTURE\\block0011.jpg",
		&g_pTextureBlock[3]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data\\TEXTURE\\pipe0110.png",
		&g_pTextureBlock[4]
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D)*4 * POLYGON_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL
	);
	
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffBlock->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCount = 0; nCount < POLYGON_BLOCK; nCount++)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(450, 450, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(600, 450, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(450, 470, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(600, 470, 0.0f);
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(POLYGON_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, POLYGON_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(POLYGON_TEXTURE_UV_U, POLYGON_TEXTURE_UV_V);

		//���_�o�b�t�@���A�����b�N
		pVtx += 4;
	}
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBlock(void)
{
	int nCount;
	for (nCount = 0; nCount < POLYGON_TYPE; nCount++)
	{
		if (g_pTextureBlock[nCount] != NULL)
		{
			g_pTextureBlock[nCount]->Release();
			g_pTextureBlock[nCount] = NULL;
		}
	}
	// �e�N�X�`���̊J��

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlock(void)
{
	int nCount;

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffBlock->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCount = 0; nCount < POLYGON_BLOCK; nCount++)
	{

		if (g_Block[nCount].bUse == true)
		{
			//���_�ݒ� BLOCKTYPE_MARUTA
			pVtx[nCount * 4].pos = D3DXVECTOR3(g_Block[nCount].pos.x, g_Block[nCount].pos.y, 0.0f);
			pVtx[nCount * 4 + 1].pos = D3DXVECTOR3(g_Block[nCount].pos.x + g_Block[nCount].fwidth, g_Block[nCount].pos.y, 0.0f);
			pVtx[nCount * 4 + 2].pos = D3DXVECTOR3(g_Block[nCount].pos.x, g_Block[nCount].pos.y + g_Block[nCount].Height, 0.0f);
			pVtx[nCount * 4 + 3].pos = D3DXVECTOR3(g_Block[nCount].pos.x + g_Block[nCount].fwidth, g_Block[nCount].pos.y + g_Block[nCount].Height, 0.0f);

			
		}
	

	}
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pTextureBlock);

	// �|���S���̕`��
	for (nCount = 0; nCount < POLYGON_BLOCK; nCount++)
	{
		if (g_Block[nCount].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureBlock[g_Block[nCount].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount*4, 2);
		}
	}

}

void SetBlock(D3DXVECTOR3 Pos, float fwidth, float Height ,int nType)
{
	int nCount=0;
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^
	g_pVtxBuffBlock->Lock		//���_�o�b�t�@�����b�N
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCount = 0; nCount < POLYGON_BLOCK; nCount++)
	{
		if (g_Block[nCount].bUse == false)		//�g�p���ĂȂ��Ȃ�
		{
			g_Block[nCount].pos = Pos;
			g_Block[nCount].fwidth = fwidth;
			g_Block[nCount].Height = Height;
			g_Block[nCount].nType = nType;
			g_Block[nCount].bUse = true;

			switch (g_Block[nCount].nType)
			{
			case 0:
				g_Block[nCount].BrockType = BLOCKTYPE_NOMAL;
			break;

			case 1:
				g_Block[nCount].BrockType = BLOCKTYPE_JUMP;
				break;
			case 2:
				g_Block[nCount].BrockType = BLOCKTYPE_VELUTOKONNBERA;
				break;
			case 3:
				g_Block[nCount].BrockType = BLOCKTYPE_MARUTA;
				break;


			}
		//���_�ݒ� BLOCKTYPE_MARUTA
			pVtx[nCount * 4].pos = D3DXVECTOR3(g_Block[nCount].pos.x, g_Block[nCount].pos.y, 0.0f);
			pVtx[nCount * 4 + 1].pos = D3DXVECTOR3(g_Block[nCount].pos.x + g_Block[nCount].fwidth, g_Block[nCount].pos.y, 0.0f);
			pVtx[nCount * 4 + 2].pos = D3DXVECTOR3(g_Block[nCount].pos.x, g_Block[nCount].pos.y + g_Block[nCount].Height, 0.0f);
			pVtx[nCount * 4 + 3].pos = D3DXVECTOR3(g_Block[nCount].pos.x + g_Block[nCount].fwidth, g_Block[nCount].pos.y + g_Block[nCount].Height, 0.0f);

			break;
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}
	
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	int nCount;
	bool bLand = false;

	Player *pPlayer = GetPlayer();

	for (nCount = 0; nCount < POLYGON_BLOCK; nCount++)
	{
		if (g_Block[nCount].bUse == true)
		{
			//�㉺�̏���
			if (pPos->x + 20 > g_Block[nCount].pos.x && pPos->x - 20 < g_Block[nCount].pos.x + g_Block[nCount].fwidth)
			{
				//��̓����蔻��
				if (pPos->y >= g_Block[nCount].pos.y && g_Block[nCount].pos.y >= pPosold->y)
				{
					bLand = true;
					if (g_Block[nCount].BrockType == BLOCKTYPE_JUMP)
					{
						pPos->y = g_Block[nCount].pos.y;
						pMove->y = 0.0f;
 						pMove->y = -15.0f;
						
						PlaySound(SOUND_LABEL_SE_SHOT);
						//SOUND_LABEL_SE_SHOT
					}
					else if (g_Block[nCount].BrockType == BLOCKTYPE_NOMAL)
					{	
						pPos->y = g_Block[nCount].pos.y;
						pMove->y = 0.0f;
					

					}
					else if (g_Block[nCount].BrockType == BLOCKTYPE_VELUTOKONNBERA)
					{
						pPos->y = g_Block[nCount].pos.y;
						pMove->y = 0.0f;

						pMove->x -= 0.9f;
						//PlaySound(SOUND_LABEL_SE_HIT000);
						/*if (pPlayer->bJunp == true)
						{
 							pMove->x -= 10.0f;
						}*/
					}
					else if (g_Block[nCount].BrockType == BLOCKTYPE_MARUTA)
					{
						
						pPos->y = g_Block[nCount].pos.y += 1;
						pMove->y = 0.0f;
					}
					else
					{
						pPos->y = g_Block[nCount].pos.y;
						pMove->y = 0.0f;
					}

				}
				//���̓����蔻��
				else if (pPos->y - 80 <= g_Block[nCount].pos.y + g_Block[nCount].Height && g_Block[nCount].pos.y + g_Block[nCount].Height <= pPosold->y - 80)
				{
		//			bLand = true;
					pPos->y = g_Block[nCount].pos.y + g_Block[nCount].Height + 80;
					pMove->y = 0.0f;

					//�����炠����Ə�ɏオ��
					if (g_Block[nCount].BrockType == BLOCKTYPE_MARUTA)
					{
						g_Block[nCount].pos.y -= 10;
					}
				}
			}
			//���̓����蔻��
			if (pPos->y > g_Block[nCount].pos.y && pPos->y - 80 < g_Block[nCount].pos.y + g_Block[nCount].Height)
			{
				//�@��
				if (pPos->x + 20  >= g_Block[nCount].pos.x && g_Block[nCount].pos.x >= pPosold->x + 20)
				{
					//bLand = true;
					
					pPos->x = g_Block[nCount].pos.x - 20;
					pMove->x = 0.0f;

					//�����炠����Ƃ����
					if (g_Block[nCount].BrockType == BLOCKTYPE_MARUTA)
					{
						g_Block[nCount].pos.x += 4;
					}
					
				}
				//	�E
				else if (pPos->x - 20 <= g_Block[nCount].pos.x + g_Block[nCount].fwidth && g_Block[nCount].pos.x + g_Block[nCount].fwidth <= pPosold->x - 20)
				{
					//bLand = true;

					pPos->x = g_Block[nCount].pos.x + g_Block[nCount].fwidth + 20;
					pMove->x = 0.0f;

					//�����炠����Ƃ����
					if (g_Block[nCount].BrockType == BLOCKTYPE_MARUTA)
					{
						g_Block[nCount].pos.x -= 4;
					}
				}
			}
		}
	}

	return bLand;
}