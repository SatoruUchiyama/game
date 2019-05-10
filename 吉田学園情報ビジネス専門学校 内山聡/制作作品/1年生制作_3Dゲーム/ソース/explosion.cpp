//=============================================================================
//
// 爆発処理 [bullet.cpp]
// Author : storu utiyama
//
//=============================================================================
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_EXPLOSION			(256)									// 爆発の最大数
#define POLYGON_TEXTURE_NAME	"date\\TEXTURE\\explosion000.png"			//読み込むテクスチャファイル
#define POLYGON_POS_X			(SCREEN_WIDTH / 2 - 100)				//ポリゴンの左上X座標
#define POLYGON_POS_Y			(SCREEN_HEIGHT / 2 - 100)				//ポリゴンの左上Y座標
#define POLYGON_WIDTH			(SCREEN_WIDTH / 2 + 100)				//ポリゴンの幅
#define POLYGON_HEIGHT			(SCREEN_HEIGHT / 2 + 100)				//ポリゴンの高さ
#define POLYGON_TEXTURE_SPEED	(5)										//テクスチャアニメーションスピード
#define POLYGON_TEXTURE_PATTERN	(10)									//テクスチャアニメーションパターン数
#define POLYGON_TEXTURE_UV_U	(0.2f)									//テクスチャアニメーションU範囲
#define POLYGON_TEXTURE_UV_V	(0.5f)									//テクスチャアニメーションV範囲
#define MAX_BOOON				(30)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;		
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxWorld;
	int nCnterAnim;
	int nPatternAnim;
	bool bUse;				//使用しているか
} Explosion;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// 頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];
D3DXVECTOR3 posExplosion;										//アニメーションカウンター
D3DXVECTOR3 moveExplosion;										//アニメーションパターンNo.


//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// デバイスの取得
	pDevice = GetDevice();

	// 爆発の情報の初期化
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCnterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		POLYGON_TEXTURE_NAME,
		&g_pTextureExplosion
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffExplosion,NULL);
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBallet, NULL);

	VERTEX_3D *pVtx;//頂点情報へのポインタ

	g_pVtxBuffExplosion->Lock//頂点バッファをロック
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[1].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[2].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[3].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		//頂点カラー設定
		pVtx[0].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[1].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[2].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		pVtx[3].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	// テクスチャの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion] .bUse == true)
		{
			g_aExplosion[nCntExplosion].nCnterAnim++;

			if ((g_aExplosion[nCntExplosion].nCnterAnim % POLYGON_TEXTURE_SPEED) == 0)
			{
				VERTEX_3D *pVtx;	//頂点情報へのポインタ
				g_pVtxBuffExplosion->Lock	//頂点バッファをロック
				(
					0,
					0,
					(void**)&pVtx,
					0
				);
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;

				pVtx[nCntExplosion * 4].pos = D3DXVECTOR3( -MAX_BOOON, MAX_BOOON, 0.0f);
				pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(MAX_BOOON, MAX_BOOON, 0.0f);
				pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3( -MAX_BOOON,-MAX_BOOON, 0.0f);
				pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(MAX_BOOON, -MAX_BOOON, 0.0f);

				pVtx[nCntExplosion * 4].tex = D3DXVECTOR2(0.125f*(g_aExplosion[nCntExplosion].nPatternAnim), 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(0.125f*(g_aExplosion[nCntExplosion].nPatternAnim) + 0.125f, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(0.125f*(g_aExplosion[nCntExplosion].nPatternAnim), 1.0f);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(0.125f*(g_aExplosion[nCntExplosion].nPatternAnim)+0.125f, 1.0f);

				g_pVtxBuffExplosion->Unlock();
				if (g_aExplosion[nCntExplosion].nPatternAnim == 7)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}
			}
		}
	}
	

}

//=============================================================================
// 描画処理	
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	int nCntExplosion;

	// デバイスの取得
	pDevice = GetDevice();

	//アルファテスト処理          D3DRS_ZFUNC          D3DRS_ZENABLE              D3DRS_ZWRITEENABLE
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DCMP_ALWAYS);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		g_aExplosion[nCntExplosion].mtxWorld._11 = mtxView._11;
		g_aExplosion[nCntExplosion].mtxWorld._12 = mtxView._21;
		g_aExplosion[nCntExplosion].mtxWorld._13 = mtxView._31;
		g_aExplosion[nCntExplosion].mtxWorld._21 = mtxView._12;
		g_aExplosion[nCntExplosion].mtxWorld._22 = mtxView._22;
		g_aExplosion[nCntExplosion].mtxWorld._23 = mtxView._32;
		g_aExplosion[nCntExplosion].mtxWorld._31 = mtxView._13;
		g_aExplosion[nCntExplosion].mtxWorld._32 = mtxView._23;
		g_aExplosion[nCntExplosion].mtxWorld._33 = mtxView._33;

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
		D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorld, &g_aExplosion[nCntExplosion].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);


		// ポリゴンの描画
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureExplosion);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

}

//=============================================================================
// 爆発の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_3D *pVtx;
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;

			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntExplosion * 4;
			pVtx[0].pos = D3DXVECTOR3(-MAX_BOOON, MAX_BOOON, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(MAX_BOOON, MAX_BOOON, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-MAX_BOOON, -MAX_BOOON, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(MAX_BOOON, -MAX_BOOON, 0.0f);

			pVtx[0].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f, 1.0f);

			g_pVtxBuffExplosion->Unlock();

			
			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
	}
}

