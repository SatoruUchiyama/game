//-------------------------------------------------------
//
//ポリゴンの処理 [polygon.cpp]
//Author:satoru utiyama
//
//-------------------------------------------------------
#include "main.h"
#include "player.h"
#include "block.h"
#include "input.h"
#include "item.h"
#include <time.h>
#include <stdlib.h>
#include "sound.h"

//-------------------------------------------------------
//マクロ定義
//-------------------------------------------------------
#define POLYGON_POS_X				(SCREEN_WIDTH - 250)
#define POLYGON_POS_Y				(SCREEN_HEIGHT / 2 - 150)
#define POLYGON_WIDTH				(SCREEN_WIDTH - 150)
#define POLYGON_HEIGHT				(SCREEN_HEIGHT / 2 - 50)

#define POLYGON_HANKEI				(40)		//プレイヤーの大きさ
#define POLYGON_TEXTURE_UV_U		(0.25f)		//U
#define POLYGON_TEXTURE_UV_V		(0.5f)		//V

//グローバル変数

int g_nPotatotate;
//VERTEX_2D g_aVertex[4];
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;

Player g_Player;
int g_nCounterAnim;	//アニメーションカウンター
int g_nPattenAnim;	//アニメーションパターン
void InitPlayer(void)
{
	g_nCounterAnim = 0;	//カウンターを初期化
	g_nPattenAnim = 0;	//パターンを初期化
	g_nPotatotate = 0; //

	g_Player.pos = D3DXVECTOR3(450, 400, 0.0f);
	g_Player.move = D3DXVECTOR3(0, 0, 0.0f);
	g_Player.bJunp = false;
	g_Player.bUse = true;

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//textureの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player0001.png",&g_pTexturePlayer);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL);

	VERTEX_2D *pVtx;

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);


	g_pVtxBuffPlayer->Unlock();
}
void UninitPlayer(void)
{
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//--------------------------------------------------------
//ポリゴン更新処理
//--------------------------------------------------------
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;	//

	static float nPosY = 0;
	int nPoint = 0;

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_nCounterAnim++;

	if (g_Player.pos.x < 0)
	{
		g_Player.pos.x  = SCREEN_WIDTH;
	}
	else if (g_Player.pos.x > SCREEN_WIDTH)
	{
		g_Player.pos.x = 0;
	}

	//-------------------------左移動-------------------------
	if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Player.move.x -= 1;

		if ((g_nCounterAnim % 5) == 0)
		{
			g_nPattenAnim = (g_nPattenAnim + 1) % 4;

			//左移動の判断
			g_nPotatotate = 1;
		}
	}

	//-------------------------右移動-------------------------
	else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Player.move.x += 1;
		if ((g_nCounterAnim % 5) == 0)
		{
			g_nPattenAnim = (g_nPattenAnim + 1) % 4;

			//右移動の判断
			g_nPotatotate = 0;
		}
	}
	else
	{
		if ((g_nCounterAnim % 5) == 0 && g_nPattenAnim == 1 || g_nPattenAnim == 3 && g_Player.bJunp == false)
		{
			g_nPattenAnim = (g_nPattenAnim + 1) % 4;
		}
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.bJunp == false || GetKeyboardTrigger(DIK_UP) == true && g_Player.bJunp == false)
	{
		g_Player.bJunp = true;
		g_Player.move.y -= 30;
		PlaySound(SOUND_LABEL_SE_HIT000);
		if (g_nPattenAnim == 0 || g_nPattenAnim == 2)
		{
			g_nPattenAnim = (g_nPattenAnim + 1) % 4;
		}
	}
	g_Player.posold = g_Player.pos;

	g_Player.move.y += 2;

	g_Player.move.x += (0.0f - g_Player.move.x) * 0.1f;

	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;

	if (CollisionBlock(&g_Player.pos, &g_Player.posold, &g_Player.move) == true)
	{
		g_Player.bJunp = false;
	}
	else 
	{
//		g_Player.bJunp = true;
	}

	
	CollisionItem();
	/*else
	{
		if (g_Player.bJunp == false)
		{
			g_Player.bJunp = true;
		}
	}*/
	if (g_Player.pos.y >= SCREEN_HEIGHT)
	{ 
		g_Player.bJunp = false;
		g_Player.pos.y = SCREEN_HEIGHT;
		g_Player.move.y = 0.0f;
	}

    //頂点設定
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - POLYGON_HANKEI, g_Player.pos.y - 80, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + POLYGON_HANKEI, g_Player.pos.y - 80, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - POLYGON_HANKEI, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + POLYGON_HANKEI, g_Player.pos.y, 0.0f);

	// アニメーション　右移動　左移動
	pVtx[0].tex = D3DXVECTOR2(POLYGON_TEXTURE_UV_U*(g_nPattenAnim), g_nPotatotate * POLYGON_TEXTURE_UV_V);
	pVtx[1].tex = D3DXVECTOR2(POLYGON_TEXTURE_UV_U*(g_nPattenAnim)+POLYGON_TEXTURE_UV_U, g_nPotatotate * POLYGON_TEXTURE_UV_V);
	pVtx[2].tex = D3DXVECTOR2(POLYGON_TEXTURE_UV_U*(g_nPattenAnim), g_nPotatotate * POLYGON_TEXTURE_UV_V + POLYGON_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(POLYGON_TEXTURE_UV_U*(g_nPattenAnim)+POLYGON_TEXTURE_UV_U, g_nPotatotate * POLYGON_TEXTURE_UV_V + POLYGON_TEXTURE_UV_V);
		//
	g_pVtxBuffPlayer->Unlock();
}

void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9  pDevice;
	pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, g_pTexturePlayer);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}

//void CollisionItem()
//{
//	int nCount;
//	Player *pPlayer;
//	pPlayer = GetPlayer();
//
//	for (nCount = 0; nCount < MAX_EXPLOSION; nCount++, pPlayer++)
//	{
//		if (pPlayer->bUse == true)
//		{
//			/*Itemを消す　スコアを加算
//			Itemをすべて取ったらTIMERを消す*/
//			if (g_aItem[nCount].pos.x-50 > pPlayer->pos.x +40&&
//				g_aItem[nCount].pos.x+50 < pPlayer->pos.x -40 &&
//				g_aItem[nCount].pos.y-50 > pPlayer->pos.y + 40 && 
//				g_aItem[nCount].pos.y + 50 < pPlayer->pos.y - 40)
//			{
//				g_aItem[nCount].bUse = false;
//			}
//
//
//		}
//	}
//}