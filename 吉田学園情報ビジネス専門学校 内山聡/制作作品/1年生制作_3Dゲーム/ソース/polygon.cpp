//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : 
//
//=============================================================================
#include "polygon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePolygon = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;							//頂点バッファのポインタ

D3DXVECTOR3 g_posPolygon;													//位置
D3DXVECTOR3 g_rotPolygon;													//向き
D3DXMATRIX g_mtxWorldPolygon;												//ワールドマトリックス

//=============================================================================
// 初期化処理
//=============================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

												
	D3DXCreateTextureFromFile			// テクスチャの読み込み
	(
		pDevice,
		"date\\TEXTURE\\lgf01a201405021100.jpg",
		&g_pTexturePolygon
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffPolygon, NULL);

	
	VERTEX_3D*pVtx;								//頂点情報へのポインタ
	//バッファをロック
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-100.0, 0.0, 100.0);
	pVtx[1].pos = D3DXVECTOR3(100.0, 0.0, 100.0);
	pVtx[2].pos = D3DXVECTOR3(-100.0, 0.0, -100.0);
	pVtx[3].pos = D3DXVECTOR3(100.0, 0.0, -100.0);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	////テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	//頂点バッファをアンロックする
	g_pVtxBuffPolygon->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{
	//// テクスチャの開放
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygon);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}

