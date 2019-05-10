//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 
//=============================================================================
#include "time.h"
#include "game.h"
#include "billboard.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"date/TEXTURE/number999.png"	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// 頂点バッファへのポインタ
Time						g_nTime[4];					// スコア
//=============================================================================
// 初期化処理
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
	// スコアの初期化
	//g_nTime = 6000;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_SCORE,		// ファイルの名前
		&g_pTextureTime);	// テクスチャへのポインタ

							// 頂点情報の作成
							//MakeVertexTime(pDevice);

	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_SCORE,
		&g_pTextureTime
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * (4 * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロック
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

			//頂点設定
			pVtx[0].pos = D3DXVECTOR3(fPotato, 30.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(fPotato + 30.0f, 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(fPotato, 80.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(fPotato + 30.0f, 80.0f, 0.0f);
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
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTime(void)
{
	// テクスチャの開放
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTime(void)
{
	int nKioku;
	int nCntTime;
	int nPotatoCoin= PotatoCoinGet();
	int nCountTime;

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロック
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
				//テクスチャ設定
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
// 描画処理
//=============================================================================
void DrawTime(void)
{
	int nCntTime;
	int nCountTimePotato;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTime);

	// ポリゴンの描画
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

	VERTEX_2D *pVtx;			//頂点情報へのポインタ
	g_pVtxBuffTime->Lock		//頂点バッファをロック
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCount = 0; nCount < 4; nCount++)
	{
		if (g_nTime[nCount].bUse == false)		//使用してないなら
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
				//頂点設定
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
//// 頂点情報の作成
////=============================================================================
//void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
//{
//	// テクスチャの開放
//	
//
//	// 頂点バッファの開放
//	
//
//}

//=============================================================================
// スコアの加算
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