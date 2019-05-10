//=============================================================================
//
// �������� [bullet.cpp]
// Author : storu utiyama
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "score.h"
#include "game.h"
#include "sound.h"
#include "explosion.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EXPLOSION			(50)									// �����̍ő吔
#define POLYGON_TEXTURE_NAME	"data\\TEXTURE\\coin000001.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define POLYGON_POS_X			(SCREEN_WIDTH / 2 - 100)				//�|���S���̍���X���W
#define POLYGON_POS_Y			(SCREEN_HEIGHT / 2 - 100)				//�|���S���̍���Y���W
#define POLYGON_WIDTH			(SCREEN_WIDTH / 2 + 100)				//�|���S���̕�
#define POLYGON_HEIGHT			(SCREEN_HEIGHT / 2 + 100)				//�|���S���̍���
#define POLYGON_TEXTURE_SPEED	(10)										//�e�N�X�`���A�j���[�V�����X�s�[�h
#define POLYGON_TEXTURE_PATTERN	(10)									//�e�N�X�`���A�j���[�V�����p�^�[����
#define POLYGON_TEXTURE_UV_U	(0.2f)									//�e�N�X�`���A�j���[�V����U�͈�
#define POLYGON_TEXTURE_UV_V	(0.5f)									//�e�N�X�`���A�j���[�V����V�͈�




//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItem = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Item g_aItem[MAX_EXPLOSION];
D3DXVECTOR3 posItem;										//�A�j���[�V�����J�E���^�[
D3DXVECTOR3 moveItem;										//�A�j���[�V�����p�^�[��No.
int nCoinCount;


//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;
	nCoinCount = 0;
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// Item�̏��̏�����
	for(nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_aItem[nCntItem].nCntAnimation = 0;						//�A�j���[�V�����J�E���^�[
		g_aItem[nCntItem].nCntAnimationPattern = 0;				//�A�j���[�V�����p�^�[��
		g_aItem[nCntItem].fwidth = 10;							//��
		g_aItem[nCntItem].Height = 15;							//����
		g_aItem[nCntItem].bUse = false;							//�g�p���Ă��邩
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		POLYGON_TEXTURE_NAME,
		&g_pTextureItem
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffItem->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{
		//���_�ݒ�
			
		
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 50, g_aItem[nCntItem].pos.y - 50,0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 50, g_aItem[nCntItem].pos.y - 50,0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 50, g_aItem[nCntItem].pos.y,0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 50, g_aItem[nCntItem].pos.y,0.0f);
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		pVtx += 4;
	}
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	g_pVtxBuffItem->Lock	//���_�o�b�t�@�����b�N
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for(nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{
		if (g_aItem[nCntItem] .bUse == true)
		{
			
				
				//g_aItem[nCntItem].bUse = false;
				//���_�ݒ�

				
				g_aItem[nCntItem].nCntAnimation++;

				if ((g_aItem[nCntItem].nCntAnimation % POLYGON_TEXTURE_SPEED) == 0)
				{
					g_aItem[nCntItem].nCntAnimationPattern = (g_aItem[nCntItem].nCntAnimationPattern + 1)%4;

					//���_�ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 30, g_aItem[nCntItem].pos.y - 30, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 30, g_aItem[nCntItem].pos.y - 30, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 30, g_aItem[nCntItem].pos.y, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 30, g_aItem[nCntItem].pos.y, 0.0f);

					pVtx[0].tex = D3DXVECTOR2(0.25f*(g_aItem[nCntItem].nCntAnimationPattern % 4), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(0.25f*(g_aItem[nCntItem].nCntAnimationPattern % 4) + 0.25f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.25f*(g_aItem[nCntItem].nCntAnimationPattern % 4), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.25f*(g_aItem[nCntItem].nCntAnimationPattern % 4) + 0.25f, 1.0f);

					
				}
				//break;
				
		}
		pVtx += 4;

	}
	g_pVtxBuffItem->Unlock();


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureItem);

	// �|���S���̕`��
	for(nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetItem(D3DXVECTOR3 pos)
{
	int nCntItem;
	VERTEX_2D *pVtx;

	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{

		if (g_aItem[nCntItem].bUse == false)
		{
			nCoinCount++;
			g_aItem[nCntItem].pos = pos;

			pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 30, g_aItem[nCntItem].pos.y - 30, 0.0f);
			pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 30, g_aItem[nCntItem].pos.y - 30, 0.0f);
			pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 30, g_aItem[nCntItem].pos.y, 0.0f);
			pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 30, g_aItem[nCntItem].pos.y, 0.0f);

			g_aItem[nCntItem].bUse = true;
			break;
		}
		//pVtx += 4;

	}
	g_pVtxBuffItem->Unlock();
}

void CollisionItem()
{
	int nCount;
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCount = 0; nCount < MAX_EXPLOSION; nCount++)
	{
		if (g_aItem[nCount].bUse == true)
		{
			//Item�������@�X�R�A�����Z
			//Item�����ׂĎ������TIMER������
			if (g_aItem[nCount].pos.x - 10 < pPlayer->pos.x + 40 &&
				g_aItem[nCount].pos.x + 10 > pPlayer->pos.x - 40 &&
				g_aItem[nCount].pos.y - 10 < pPlayer->pos.y  + 20&&
				g_aItem[nCount].pos.y + 10 > pPlayer->pos.y - 70)
			{
				PlaySound(SOUND_LABEL_SE_HIT001);
				AddScore(100000);
				g_aItem[nCount].bUse = false;

				SetExplosion(g_aItem[nCount].pos,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
				nCoinCount--;
				if (nCoinCount == 0)
				{
					SetGameState(GAMESTATE_END);
				}

			}
		}
	}

}


Item *GetItem(void)
{
	return &g_aItem[0];
}

int PotatoCoinGet(void)
{
	return nCoinCount; 
}