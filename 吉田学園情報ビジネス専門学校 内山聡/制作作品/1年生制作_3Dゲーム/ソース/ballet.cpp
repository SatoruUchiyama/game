//=============================================================================
//
// 弾処理 [ballet.cpp]
// Author : 
//
//=============================================================================
#include "ballet.h"
#include "shadow.h"
#include "input.h"
#include "explosion.h"
#include "effect.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BALLET			(256)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBallet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Ballet g_aBallet[MAX_BALLET];					//構造体のグローバル変数

//			テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pTextureBallet = NULL;

//			頂点バッファのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallet = NULL;	


//=============================================================================
// 初期化処理
//=============================================================================
void InitBallet(void)
{
	int nCntBill;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	for (nCntBill = 0; nCntBill < MAX_BALLET; nCntBill++)
	{

		g_aBallet[nCntBill].g_nIdxShadow = 0;
		g_aBallet[nCntBill].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,"date\\TEXTURE\\bullet000.png",&g_pTextureBallet);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BALLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBallet, NULL);

	//頂点情報へのポインタ
	VERTEX_3D*pVtx;	

	//バッファをロック											
	g_pVtxBuffBallet->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntBill = 0; nCntBill < MAX_BALLET; nCntBill++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-2, 2, 0.0);
		pVtx[1].pos = D3DXVECTOR3(2, 2, 0.0);
		pVtx[2].pos = D3DXVECTOR3(-2, -2.0, 0.0);
		pVtx[3].pos = D3DXVECTOR3(2, -2.0, 0.0);

		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[1].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[2].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[3].nor = D3DXVECTOR3(0.0, 0.0, -1.0);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);

		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBallet->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBallet(void)
{
	// テクスチャの開放
	if (g_pTextureBallet != NULL)
	{
		g_pTextureBallet->Release();
		g_pTextureBallet = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBallet != NULL)
	{
		g_pVtxBuffBallet->Release();
		g_pVtxBuffBallet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBallet(void)
{
	//弾の移動処理
	for (int nCntBill2 = 0; nCntBill2 < MAX_BALLET; nCntBill2++)
	{
		if (g_aBallet[nCntBill2].bUse == true)
		{
			//エフェクトのセット
			SetEffect(g_aBallet[nCntBill2].pos, D3DXCOLOR(1.0f, 0.5f, 0.7f, 1.0f), 20, 20,0);
			g_aBallet[nCntBill2].pos += g_aBallet[nCntBill2].move;
			SetPositionShadow(g_aBallet[nCntBill2].g_nIdxShadow, g_aBallet[nCntBill2].pos);

			//前方の弾の処理
			if (g_aBallet[nCntBill2].pos.z >= 100)
			{
				g_aBallet[nCntBill2].bUse = false;
				DeleteShadow(g_aBallet[nCntBill2].g_nIdxShadow);
				DeleteBallet(nCntBill2);
			}
			//左方向の弾の処理
			else if (g_aBallet[nCntBill2].pos.x >= 200)
			{
				g_aBallet[nCntBill2].bUse = false;
				DeleteShadow(g_aBallet[nCntBill2].g_nIdxShadow);
				DeleteBallet(nCntBill2);
			}
			//後ろ方向の弾の処理
			else if (g_aBallet[nCntBill2].pos.z <= -200)
			{
				g_aBallet[nCntBill2].bUse = false;
				DeleteShadow(g_aBallet[nCntBill2].g_nIdxShadow);
				DeleteBallet(nCntBill2);
			}
			//右方向の弾の処理
			else if (g_aBallet[nCntBill2].pos.x <= -100)
			{
				g_aBallet[nCntBill2].bUse = false;
				DeleteShadow(g_aBallet[nCntBill2].g_nIdxShadow);
				DeleteBallet(nCntBill2);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBallet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	int nCntBallet;

	//アルファテスト処理
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//D3DCMP_GREATER

	for (nCntBallet = 0; nCntBallet < MAX_BALLET; nCntBallet++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBallet[nCntBallet].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		g_aBallet[nCntBallet].mtxWorld._11 = mtxView._11;
		g_aBallet[nCntBallet].mtxWorld._12 = mtxView._21;
		g_aBallet[nCntBallet].mtxWorld._13 = mtxView._31;
		g_aBallet[nCntBallet].mtxWorld._21 = mtxView._12;
		g_aBallet[nCntBallet].mtxWorld._22 = mtxView._22;
		g_aBallet[nCntBallet].mtxWorld._23 = mtxView._32;
		g_aBallet[nCntBallet].mtxWorld._31 = mtxView._13;
		g_aBallet[nCntBallet].mtxWorld._32 = mtxView._23;
		g_aBallet[nCntBallet].mtxWorld._33 = mtxView._33;

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aBallet[nCntBallet].pos.x, g_aBallet[nCntBallet].pos.y, g_aBallet[nCntBallet].pos.z);
		D3DXMatrixMultiply(&g_aBallet[nCntBallet].mtxWorld, &g_aBallet[nCntBallet].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBallet[nCntBallet].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBallet, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBallet);

		// ポリゴンの描画
		if (g_aBallet[nCntBallet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBallet, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
//	弾の設定
//=============================================================================
void SetBallet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	int nCntBallet;

	for (nCntBallet = 0; nCntBallet < MAX_BALLET; nCntBallet++)
	{
		if (g_aBallet[nCntBallet].bUse == false)
		{
			g_aBallet[nCntBallet].pos = pos;
			g_aBallet[nCntBallet].rot = rot;
			g_aBallet[nCntBallet].move = move;
			g_aBallet[nCntBallet].g_nIdxShadow = SetShadow(g_aBallet[nCntBallet].pos, g_aBallet[nCntBallet].rot);
			g_aBallet[nCntBallet].bUse = true;
			break;
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBallet(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}

void DeleteBallet(int nBallet)
{
	SetParticleEffect(g_aBallet[nBallet].pos, EFFECTTYPE_RESURRECTIONSMOKE, 80, 20, 50, 1);

	g_aBallet[nBallet].bUse = false;
}

