//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number999.png"	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
Score					g_Score[4];					// スコア

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{
	int nCountScorePotato;
	int nCntScore;
	float fPotato;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	for (nCountScorePotato = 0; nCountScorePotato < 4; nCountScorePotato++)
	{
		g_Score[nCountScorePotato].bUse = false;
		g_Score[nCountScorePotato].fwidth = 0;
		g_Score[nCountScorePotato].Height = 0;
		g_Score[nCountScorePotato].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Score[nCountScorePotato].g_Score = 0;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
								&g_pTextureScore);	// テクスチャへのポインタ

	// 頂点情報の作成
	//MakeVertexScore(pDevice);

	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_SCORE,
		&g_pTextureScore
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * (8 * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロック
	g_pVtxBuffScore->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCountScorePotato = 0; nCountScorePotato < 4; nCountScorePotato++)
	{
		for (nCntScore = 0, fPotato = 1200; nCntScore < 8; nCntScore++, fPotato -= 30)
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
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	// テクスチャの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	int nKioku;
	int nCountScorePotato;
	int nCntScore;

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロック
	g_pVtxBuffScore->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCountScorePotato = 0; nCountScorePotato < 4; nCountScorePotato++)
	{
		if (g_Score[nCountScorePotato].bUse == true)
		{
			nKioku = g_Score[nCountScorePotato].g_Score;
			for (nCntScore = 0; nCntScore < 8; nCntScore++)
			{
				//テクスチャ設定
				pVtx[nCntScore * 4].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 0.0f);
				pVtx[nCntScore * 4 + 1].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 0.0f);
				pVtx[nCntScore * 4 + 2].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 1.0f);
				pVtx[nCntScore * 4 + 3].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 1.0f);
				nKioku /= 10;
			}
		}
		pVtx += (8 * 4);
	}
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	int nCountScorePotato;
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	// ポリゴンの描画
	for (nCountScorePotato = 0; nCountScorePotato < 4; nCountScorePotato++)
	{
		if (g_Score[nCountScorePotato].bUse == true)
		{
			for (nCntScore = 0; nCntScore < 8; nCntScore++)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
			}
		}
	}
}


void SetScore(D3DXVECTOR3 Pos, float fwidth, float Height)
{
	int nCount;
	int nCountScore;
	D3DXVECTOR3 nPos;

	VERTEX_2D *pVtx;			//頂点情報へのポインタ
	g_pVtxBuffScore->Lock		//頂点バッファをロック
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCount = 0; nCount < 4; nCount++)
	{
		if (g_Score[nCount].bUse == false)		//使用してないなら
		{
			g_Score[nCount].pos = Pos;
			g_Score[nCount].fwidth = fwidth;
			g_Score[nCount].Height = Height;
			g_Score[nCount].bUse = true;
			nPos = Pos;

			for (nCountScore = 0; nCountScore < 8; nCountScore++)
			{				
				//頂点設定
				pVtx[nCountScore * 4].pos = D3DXVECTOR3(nPos.x, nPos.y, 0.0f);
				pVtx[nCountScore * 4 + 1].pos = D3DXVECTOR3(nPos.x + g_Score[nCount].fwidth, nPos.y, 0.0f);
				pVtx[nCountScore * 4 + 2].pos = D3DXVECTOR3(nPos.x, nPos.y + g_Score[nCount].Height, 0.0f);
				pVtx[nCountScore * 4 + 3].pos = D3DXVECTOR3(nPos.x + g_Score[nCount].fwidth, nPos.y + g_Score[nCount].Height, 0.0f);

				nPos.x -= g_Score[nCount].fwidth;
			}
			break;
		}
		pVtx += (8 * 4);
	}
	g_pVtxBuffScore->Unlock();
}

////=============================================================================
//// 頂点情報の作成
////=============================================================================
//void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
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
void AddScore(int nValue)
{
	int nCountScorePotato;

	for (nCountScorePotato = 0; nCountScorePotato < 4; nCountScorePotato++)
	{
		if (g_Score[nCountScorePotato].bUse == true)
		{
			g_Score[nCountScorePotato].g_Score += nValue;
		}
	}
}
