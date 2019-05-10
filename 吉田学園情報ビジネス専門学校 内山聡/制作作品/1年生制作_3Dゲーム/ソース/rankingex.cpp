//=========================================================================================================================
//
// ポリゴンの処理 [polygon.cpp]
// Author : satoru utiyama
//
//=========================================================================================================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "ranking.h"
#include "rankingex.h"

//#include "sound.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRankingEx = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingEx = NULL;
int g_nCountTimer;

//マクロ定義
#define RESULT_TEXTURE_NAME ""				//テクスチャーの名前
#define RESULT_POS_X (0)					//
#define RESULT_POS_Y (0)					//
#define RESULT_WIDTH (SCREEN_WIDTH)			//
#define RESULT_HEIGHT (SCREEN_HEIGHT)		//

void InitRankingEx(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//textureの読み込み
	D3DXCreateTextureFromFile(pDevice, "date\\TEXTURE\\resize-img2.jpg", &g_pTextureRankingEx);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRankingEx, NULL);

	VERTEX_2D *pVtx;

	g_nCountTimer = 0;

	g_pVtxBuffRankingEx->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);

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


	g_pVtxBuffRankingEx->Unlock();
	InitRanking();
}
void UninitRankingEx(void)
{
	if (g_pTextureRankingEx != NULL)
	{
		g_pTextureRankingEx->Release();
		g_pTextureRankingEx = NULL;
	}
	if (g_pVtxBuffRankingEx != NULL)
	{
		g_pVtxBuffRankingEx->Release();
		g_pVtxBuffRankingEx = NULL;
	}
	UninitRanking();
}
void UpdateRankingEx(void)
{
	g_nCountTimer++;
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(MODE_TITLE);
	}
	else if (g_nCountTimer % 300 == 0)
	{
		SetFade(MODE_TITLE);
	}
	UpdateRanking();
}
void DrawRankingEx(void)
{
	LPDIRECT3DDEVICE9  pDevice;
	pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffRankingEx, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, g_pTextureRankingEx);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	DrawRanking();

}