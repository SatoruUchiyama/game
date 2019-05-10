//=========================================================================================================================
//
// ポリゴンの処理 [polygon.cpp]
// Author : satoru utiyama
//
//=========================================================================================================================
#include "main.h"
#include "titlemain.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitleMain[3] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleMain = NULL;
D3DXVECTOR2 g_titlemain;
int PotatoColor;
int ChangePotatoColor;

//マクロ定義
#define TITLE_TEXTURE_NAME ""				//テクスチャーの名前
#define TITLE_POS_X (0)					//
#define TITLE_POS_Y (0)					//
#define TITLE_WIDTH (SCREEN_WIDTH)			//
#define TITLE_HEIGHT (SCREEN_HEIGHT)		//


void InitTitleMain(void)
{
	PotatoColor = 255;
	ChangePotatoColor = 5;
	g_titlemain = D3DXVECTOR2(640, -300);
//	int nCount;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//textureの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\resize-img7.jpg", &g_pTextureTitleMain[0]);
	//textureの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\press_enter1.png", &g_pTextureTitleMain[1]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\resize-img10.png", &g_pTextureTitleMain[2]);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*3, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleMain, NULL);

	VERTEX_2D *pVtx;

	g_pVtxBuffTitleMain->Lock(0, 0, (void**)&pVtx, 0);

	
		pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		pVtx[0].pos = D3DXVECTOR3(640 - 100, 640 - 30, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(640 + 100, 640 - 30, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(640 - 100, 640 + 30, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(640 + 100, 640 + 30, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		pVtx[0].pos = D3DXVECTOR3(g_titlemain.x - 400, g_titlemain.y - 250, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_titlemain.x + 400, g_titlemain.y - 250, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_titlemain.x - 400, g_titlemain.y + 250, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_titlemain.x + 400, g_titlemain.y + 250, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	g_pVtxBuffTitleMain->Unlock();
}
void UninitTitleMain(void)
{
	int nCount;
	for (nCount = 0; nCount < 3; nCount++)
	{
		if (g_pTextureTitleMain[nCount] != NULL)
		{
			g_pTextureTitleMain[nCount]->Release();
			g_pTextureTitleMain[nCount] = NULL;
		}

	}
	if (g_pVtxBuffTitleMain != NULL)
	{
		g_pVtxBuffTitleMain->Release();
		g_pVtxBuffTitleMain = NULL;
	}

}
void UpdateTitleMain(void)
{

	VERTEX_2D *pVtx;
	//	int nCount;
	g_pVtxBuffTitleMain->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	PotatoColor -= ChangePotatoColor;
	
	if (PotatoColor < 50 || PotatoColor >= 255)
	{
		ChangePotatoColor *= -1;
	}


	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, PotatoColor);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, PotatoColor);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, PotatoColor);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, PotatoColor);

	pVtx += 4;

	
	if (300 >= g_titlemain.y)
	{
		g_titlemain.y += 10;
	}

	pVtx[0].pos = D3DXVECTOR3(g_titlemain.x - 400, g_titlemain.y - 250, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_titlemain.x + 400, g_titlemain.y - 250, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_titlemain.x - 400, g_titlemain.y + 250, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_titlemain.x + 400, g_titlemain.y + 250, 0.0f);

	g_pVtxBuffTitleMain->Unlock();
	
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		TITLEMAIN_PIKARI;

		PlaySound(SOUND_LABEL_SE_POTATO4);
		SetFade(MODE_TITLE);
	}
}
void DrawTitleMain(void)
{
	int nCount;
	LPDIRECT3DDEVICE9  pDevice;
	pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffTitleMain, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < 3; nCount++)
	{
		pDevice->SetTexture(0, g_pTextureTitleMain[nCount]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCount* 4, 2);

	}
}