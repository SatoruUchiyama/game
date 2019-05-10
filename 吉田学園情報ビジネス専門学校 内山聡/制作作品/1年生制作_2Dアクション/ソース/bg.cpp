#include "main.h"
#include "bg.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBG[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;
float nPotatoidou;
//マクロ定義
#define BG_TEXTURE_NAME ""				//テクスチャーの名前
#define BG_POS_X (0)					//
#define BG_POS_Y (0)					//
#define BG_WIDTH (SCREEN_WIDTH)			//
#define BG_HEIGHT (SCREEN_HEIGHT)		//
#define BG_TEX_SPEED	(0.0005f)
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//textureの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sky000.jpg",&g_pTextureBG[0]);

	//textureの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mountain0000.png", &g_pTextureBG[1]);


	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*2, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBG, NULL);

	nPotatoidou = 0;
	int nCount;
	VERTEX_2D *pVtx;

	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < 2; nCount++)
	{
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
		pVtx += 4;
	}
	
	g_pVtxBuffBG->Unlock();
}
void UninitBG(void)
{
	int nCount;
	for (nCount = 0; nCount < 2; nCount++)
	{
		if (g_pTextureBG[nCount] != NULL)
		{
			g_pTextureBG[nCount]->Release();
			g_pTextureBG[nCount] = NULL;
		}
	}
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}
void UpdateBG(void)
{
	VERTEX_2D *pVtx;
//	int nCount;
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	nPotatoidou += BG_TEX_SPEED;

	
		pVtx[0].tex = D3DXVECTOR2(0.0f + nPotatoidou, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f + nPotatoidou, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nPotatoidou, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f + nPotatoidou, 1.0f);

		pVtx += 4;

		pVtx[0].tex = D3DXVECTOR2(0.0f , 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		
	g_pVtxBuffBG->Unlock();
}
void DrawBG(void)
{
	int nCount;
	LPDIRECT3DDEVICE9  pDevice;
	pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (nCount = 0; nCount < 2; nCount++)
	{
		pDevice->SetTexture(0, g_pTextureBG[nCount]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCount*4,2);
	}
	
}