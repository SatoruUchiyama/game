//=============================================================================
//
// 爆発処理 [bullet.cpp]
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
// マクロ定義
//*****************************************************************************
#define	MAX_EXPLOSION			(50)									// 爆発の最大数
#define POLYGON_TEXTURE_NAME	"data\\TEXTURE\\coin000001.png"			//読み込むテクスチャファイル
#define POLYGON_POS_X			(SCREEN_WIDTH / 2 - 100)				//ポリゴンの左上X座標
#define POLYGON_POS_Y			(SCREEN_HEIGHT / 2 - 100)				//ポリゴンの左上Y座標
#define POLYGON_WIDTH			(SCREEN_WIDTH / 2 + 100)				//ポリゴンの幅
#define POLYGON_HEIGHT			(SCREEN_HEIGHT / 2 + 100)				//ポリゴンの高さ
#define POLYGON_TEXTURE_SPEED	(10)										//テクスチャアニメーションスピード
#define POLYGON_TEXTURE_PATTERN	(10)									//テクスチャアニメーションパターン数
#define POLYGON_TEXTURE_UV_U	(0.2f)									//テクスチャアニメーションU範囲
#define POLYGON_TEXTURE_UV_V	(0.5f)									//テクスチャアニメーションV範囲




//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItem = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// 頂点バッファへのポインタ
Item g_aItem[MAX_EXPLOSION];
D3DXVECTOR3 posItem;										//アニメーションカウンター
D3DXVECTOR3 moveItem;										//アニメーションパターンNo.
int nCoinCount;


//=============================================================================
// 初期化処理
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;
	nCoinCount = 0;
	// デバイスの取得
	pDevice = GetDevice();

	// Itemの情報の初期化
	for(nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
		g_aItem[nCntItem].nCntAnimation = 0;						//アニメーションカウンター
		g_aItem[nCntItem].nCntAnimationPattern = 0;				//アニメーションパターン
		g_aItem[nCntItem].fwidth = 10;							//幅
		g_aItem[nCntItem].Height = 15;							//高さ
		g_aItem[nCntItem].bUse = false;							//使用しているか
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		POLYGON_TEXTURE_NAME,
		&g_pTextureItem
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロック
	g_pVtxBuffItem->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{
		//頂点設定
			
		
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 50, g_aItem[nCntItem].pos.y - 50,0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 50, g_aItem[nCntItem].pos.y - 50,0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 50, g_aItem[nCntItem].pos.y,0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 50, g_aItem[nCntItem].pos.y,0.0f);
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

		//頂点バッファをアンロック
		pVtx += 4;
	}
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	// テクスチャの開放
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;
	VERTEX_2D *pVtx;	//頂点情報へのポインタ
	g_pVtxBuffItem->Lock	//頂点バッファをロック
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
				//頂点設定

				
				g_aItem[nCntItem].nCntAnimation++;

				if ((g_aItem[nCntItem].nCntAnimation % POLYGON_TEXTURE_SPEED) == 0)
				{
					g_aItem[nCntItem].nCntAnimationPattern = (g_aItem[nCntItem].nCntAnimationPattern + 1)%4;

					//頂点設定
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
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureItem);

	// ポリゴンの描画
	for(nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//=============================================================================
// 爆発の設定処理
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
			//Itemを消す　スコアを加算
			//Itemをすべて取ったらTIMERを消す
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