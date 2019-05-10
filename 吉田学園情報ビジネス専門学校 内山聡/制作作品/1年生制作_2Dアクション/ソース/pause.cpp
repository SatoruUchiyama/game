#include "main.h"
#include "bg.h"
#include "input.h"
#include "game.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePAUSE = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPAUSE = NULL;

//マクロ定義
#define PAUSE_TEXTURE_NAME ""				//テクスチャーの名前
#define PAUSE_POS_X (0)					//
#define PAUSE_POS_Y (0)					//
#define PAUSE_WIDTH (SCREEN_WIDTH)			//
#define PAUSE_HEIGHT (SCREEN_HEIGHT)		//

//
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
//	int nCntPAUSE;

	//textureの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\resize-img100.jpg", &g_pTexturePAUSE);

	//
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPAUSE, NULL);

	VERTEX_2D *pVtx;

	g_pVtxBuffPAUSE->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);

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

	g_pVtxBuffPAUSE->Unlock();
}

//
void UninitPause(void)
{
//	int nCntPAUSE;

		if (g_pTexturePAUSE != NULL)
		{
			g_pTexturePAUSE->Release();
			g_pTexturePAUSE = NULL;
		}

	if (g_pVtxBuffPAUSE != NULL)
	{
		g_pVtxBuffPAUSE->Release();
		g_pVtxBuffPAUSE = NULL;
	}
}

//
void UpdatePause(void)
{
	if (GetKeyboardPress(DIK_Z) == true)
	{
		SetMode(MODE_TITLE);
	}
}

//
void DrawPause(void)
{
	LPDIRECT3DDEVICE9  pDevice;
//	int nCntPAUSE;

	//
	pDevice = GetDevice();

	//
	pDevice->SetStreamSource(0, g_pVtxBuffPAUSE, 0, sizeof(VERTEX_2D));

	//
	pDevice->SetFVF(FVF_VERTEX_2D);

		//
		pDevice->SetTexture(0, g_pTexturePAUSE);

		//
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
