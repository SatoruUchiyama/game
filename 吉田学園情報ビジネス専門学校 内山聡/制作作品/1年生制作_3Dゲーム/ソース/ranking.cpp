//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 
//
//=============================================================================
#include "ranking.h"
#include "game.h"
//#include "item.h"
#include "time.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RANKING		"date/TEXTURE/number999.png"	// 読み込むテクスチャファイル名
#define RANKING_MAX			(2)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// 頂点バッファへのポインタ
Ranking						g_nRanking[RANKING_MAX];					// スコア

//=============================================================================
// 初期化処理
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

	// スコアの初期化
	g_nRanking[0].nRanking = pTime.nTime;	//ima
	if (g_nRanking[0].nRanking > g_nRanking[1].nRanking)
	{
		g_nRanking[1].nRanking = g_nRanking[0].nRanking;
	}
	 


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RANKING,		// ファイルの名前
		&g_pTextureRanking);	// テクスチャへのポインタ

	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_RANKING,
		&g_pTextureRanking
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * (RANKING_MAX * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロック
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

			//頂点設定
			pVtx[0].pos = D3DXVECTOR3(fPotato, fPotatoY, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(fPotato + 80.0f, fPotatoY, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(fPotato, fPotatoY + 80.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(fPotato + 80.0f, fPotatoY + 80.0f, 0.0f);
			//1.0fで固定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//頂点カラー設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			//テクスチャ設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			//頂点バッファをアンロック
			pVtx += 4;
		}

	}
	g_pVtxBuffRanking->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRanking(void)
{
	// テクスチャの開放
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRanking(void)
{
	int nKioku;
	int nCntRanking;
	//int nPotatoCoin = PotatoCoinGet();
	int nCountRanking;

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
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
				//テクスチャ設定
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
// 描画処理
//=============================================================================
void DrawRanking(void)
{
	int nCntRanking;
	int nCountRankingPotato;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking);

	// ポリゴンの描画
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
// スコアの加算
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