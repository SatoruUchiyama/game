//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 
//
//=============================================================================
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EFFECT_ICE		"date/TEXTURE/pipo-hiteffect009.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT_BLOOD	"date/TEXTURE/pipo-hiteffect013.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT_FIRE		"date/TEXTURE/honoo_hi_fire.png"	// 読み込むテクスチャファイル名
#define	MAX_EFFECT2			(8000)							// エフェクトの最大数
#define	MAX_EFFECT					(1000)									// エフェクトの最大数
#define	MAX_EFFECTSMOKE				(50)									// エフェクトの最大数
#define MAX_TEXTURE					(3)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect[MAX_TEXTURE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファへのポインタ
Effect					g_aEffect[MAX_EFFECT2];		// エフェクトの情報
int g_nNumEffect;
//=============================================================================
// 初期化処理
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEffect;

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT2; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_EFFECT_ICE,
		&g_pTextureEffect[0]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_EFFECT_BLOOD,
		&g_pTextureEffect[1]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_EFFECT_FIRE,
		&g_pTextureEffect[2]
	);
	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT2,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffEffect,NULL);

	VERTEX_3D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロック
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT2; nCntEffect++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		// テクスチャの開放
		if (g_pTextureEffect[nCount] != NULL)
		{
			g_pTextureEffect[nCount]->Release();
			g_pTextureEffect[nCount] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	// 頂点バッファをロック
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// エフェクトをカウント
		if (g_aEffect[nCntEffect].bUse == true)
		{// エフェクトが使用されている場合
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{// 弾エフェクトの場合
			 // g_aEffect[nCntEffect].nLife--;
				g_aEffect[nCntEffect].fRadius -= 0.2f;

				if (/*g_aEffect[nCntEffect].nLife <= 0 || */g_aEffect[nCntEffect].fRadius <= 0)
				{// ライフが0以下の場合
					g_aEffect[nCntEffect].fRadius = 0;
					g_aEffect[nCntEffect].bUse = false;
				}
			}
			if (g_aEffect[nCntEffect].bUse == true)
			{
				g_aEffect[nCntEffect].fRadius -= 0.5f;

				if (g_aEffect[nCntEffect].fRadius <= 0)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
			}
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION || g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION || g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONSMOKE)
			{// 爆発エフェクトの場合
				g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;	// 移動値代入

				g_aEffect[nCntEffect].nLife--;				// 寿命減少

															// 半径減少
				if (g_aEffect[nCntEffect].nLife > 0)
				{
					g_aEffect[nCntEffect].fRadius += 0.0005f;
				}
				else
				{
					g_aEffect[nCntEffect].fRadius -= 0.5f;
				}

				if (g_aEffect[nCntEffect].fRadius <= 0)
				{// ライフが0以下の場合
					g_aEffect[nCntEffect].bUse = false;
				}
			}
		}
		// 頂点設定
		pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
	}
	SetSmokeEffect(D3DXVECTOR3(30.0f, 30.0f, 0.0f), EFFECTTYPE_RESURRECTIONSMOKE, 10, 10, 10, 2);
	// 頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	int nCntEffect;
	
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT2; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_aEffect[nCntEffect].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntEffect].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntEffect].mtxWorld._13 = mtxView._31;
			g_aEffect[nCntEffect].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntEffect].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntEffect].mtxWorld._23 = mtxView._32;
			g_aEffect[nCntEffect].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].nTypeTx]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}
	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
}

/*//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	

	// 頂点バッファの情報を設定


}*/

//=============================================================================
// エフェクト設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife, int nTypeTx)
{
	int nCntEffect;
	VERTEX_3D *pVtx;	//頂点情報へのポインタ
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;			// 種類設定

 			g_aEffect[nCntEffect].bUse = true;

			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

			//pVtx += nCntEffect * 4;
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(- g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3( g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(- g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius,  -g_aEffect[nCntEffect].fRadius, 0.0f);

			g_pVtxBuffEffect->Unlock();
			break;
		}
		
	}
}

//=========================================================================================================================
// パーティクルエフェクト設定処理
//=========================================================================================================================
void SetParticleEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx)
{
	int nCntEffect;			// エフェクトカウンタ
	int nCount = 0;			// エフェクト個数カウンタ

	VERTEX_3D *pVtx;		// 頂点情報へのポインタ

							// 頂点バッファをロック
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// エフェクトをカウント
		if (g_aEffect[nCntEffect].bUse == false)
		{// エフェクトが使用されていない

			g_aEffect[nCntEffect].pos = pos;			// pos値代入
			g_aEffect[nCntEffect].Type = Type;			// 種類設定
			g_aEffect[nCntEffect].nLife = nLife;		// 寿命設定
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;			// 種類設定

			g_aEffect[nCntEffect].bUse = true;			// 使用している状態

														// 移動ランダム化
			g_aEffect[nCntEffect].move.x = sinf((rand() % 628) / 50.0f) * ((rand() % 3) + 1);
			g_aEffect[nCntEffect].move.y = cosf((rand() % 628) / 50.0f) * ((rand() % 3) + 1);
			g_aEffect[nCntEffect].move.z = tanf((rand() % 628) / 50.0f) * ((rand() % 3) + 1);

			int nNumber = rand() % 3 + 1;

			// col値代入
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.5f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.8f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 0.5f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); }
			}

			g_aEffect[nCntEffect].fRadius = (rand() % nRadius + 1) * 1.0f;	// 半径設定

																			// 頂点設定
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);

			// 頂点カラー設定
			pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;

			nCount++;		// 個数をカウント
			if (nCount == nSetMax)
			{// 個数が最大数になった場合
				break;
			}
		}
	}
	// 頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
//パーティクルの処理
//=============================================================================
void SetSmokeEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx)
{
	int nCntEffect;			// エフェクトカウンタ
	int nCount = 0;			// エフェクト個数カウンタ

	VERTEX_3D *pVtx;		// 頂点情報へのポインタ

							// 頂点バッファをロック
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECTSMOKE; nCntEffect++)
	{// エフェクトをカウント
		if (g_aEffect[nCntEffect].bUse == false)
		{// エフェクトが使用されていない

			g_aEffect[nCntEffect].pos = pos;			// pos値代入
			g_aEffect[nCntEffect].Type = Type;			// 種類設定
			g_aEffect[nCntEffect].nLife = nLife;		// 寿命設定
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;	// 種類設定

			g_aEffect[nCntEffect].bUse = true;			// 使用している状態


														// 移動ランダム化
			g_aEffect[nCntEffect].move.x = sinf((rand() % 25) / 700.0f) * ((rand() % 3) + 1);
			//	g_aEffect[nCntEffect].move.z = tanf((rand() % 628) / 100.0f) * ((rand() % 3) + 1);
			g_aEffect[nCntEffect].move.y = cosf((rand() % 100) / 100.0f)  * ((rand() % 3) + 1);
		

			int nNumber = rand() % 3 + 1;

			// col値代入
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.5f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONSMOKE)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.8f, 1.0f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			}

			g_aEffect[nCntEffect].fRadius = (rand() % nRadius + 1) * 1.0f;	// 半径設定

																			// 頂点設定
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);

			// 頂点カラー設定
			pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;

			nCount++;		// 個数をカウント
			if (nCount == nSetMax)
			{// 個数が最大数になった場合
			 //g_aEffect[nCntEffect].bUse = false;
				nSetMax = 0;
			}
		}
	}
	// 頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}