//=============================================================================
//
// メッシュ処理 [meshfield.cpp]
// Author : 
//
//=============================================================================
#include "MeshField.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_Z			(10)
#define MAX_X			(10)
#define MAX_Y			(2)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureMeshField = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;	//頂点バッファのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//インデックスバッファのポインタ
D3DXVECTOR3 g_posMeshField;							//位置
D3DXVECTOR3 g_rotMeshField;							//向き
D3DXMATRIX g_mtxWorldMeshField;						//ワールドマトリックス
int g_nNumVertexMeshField;							//頂点数
int g_nNumIndexMeshField;							//インデックス数
int g_nNumPolygonMeshField;							//ポリゴン数

//=============================================================================
// 初期化処
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	int nCount_z;
	int nCount_X;
	int nCountPotato = 0;
	D3DXCreateTextureFromFile						// テクスチャの読み込み
	(
		pDevice,
		"date\\TEXTURE\\sand_.jpg",
		&g_pTextureMeshField
	);
	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MAX_Z+1)*(MAX_X+1), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshField, NULL);
	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * (MAX_X*MAX_Z*2+(4*(MAX_Z-1))+2), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshField, NULL);

	VERTEX_3D*pVtx;									//頂点情報へのポインタ

	WORD*pIdx;										//インデックスデータへのポインタ

	//バッファをロック
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);


	for (nCount_z = 0; nCount_z < MAX_Z + 1; nCount_z++)
	{
		for (nCount_X = 0; nCount_X < MAX_X + 1; nCount_X++)
		{
			pVtx[0].pos = D3DXVECTOR3(-100.0f + (nCount_X * 100.0f), 0, 100.0f - (nCount_z * 100.0f));
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].tex = D3DXVECTOR2(nCount_X*1.0f, nCount_z*1.0f);
			pVtx += 1;
		}
	}
	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(-100, 0, 100);
	//pVtx[1].pos = D3DXVECTOR3(0, 0, 100);
	//pVtx[2].pos = D3DXVECTOR3(100, 0, 100);
	//pVtx[3].pos = D3DXVECTOR3(-100, 0, 0);
	//pVtx[4].pos = D3DXVECTOR3(0, 0, 0);
	//pVtx[5].pos = D3DXVECTOR3(100, 0, 0);
	//pVtx[6].pos = D3DXVECTOR3(-100, 0, -100);
	//pVtx[7].pos = D3DXVECTOR3(0, 0, -100);
	//pVtx[8].pos = D3DXVECTOR3(100, 0, -100);
	////法線の設定
	//pVtx[0].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[1].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[2].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[3].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[4].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[5].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[6].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[7].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);
	//pVtx[8].nor = D3DXVECTOR3(	0.0,	1.0,	0.0);

	////頂点カラーの設定
	//pVtx[0].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[1].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[2].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[3].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[4].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[5].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[6].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[7].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//pVtx[8].col = D3DXCOLOR(	1.0,	1.0,	1.0,	1.0);
	//
	//////テクスチャ設定
	//pVtx[0].tex = D3DXVECTOR2(	0.0,	0.0);
	//pVtx[1].tex = D3DXVECTOR2(	1.0,	0.0);
	//pVtx[2].tex = D3DXVECTOR2(	2.0,	0.0);
	//pVtx[3].tex = D3DXVECTOR2(	0.0,	1.0);
	//pVtx[4].tex = D3DXVECTOR2(	1.0,	1.0);
	//pVtx[5].tex = D3DXVECTOR2(	2.0,	1.0);
	//pVtx[6].tex = D3DXVECTOR2(	0.0,	2.0);
	//pVtx[7].tex = D3DXVECTOR2(	1.0,	2.0);
	//pVtx[8].tex = D3DXVECTOR2(	2.0,	2.0);
	

	//頂点バッファをアンロックする
	g_pVtxBuffMeshField->Unlock();

	//インデックスバッファをロックする
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
	for (nCount_z = 0; nCount_z < MAX_Z; nCount_z++)
	{
		for (nCount_X = 0; nCount_X < MAX_X + 1; nCount_X++, nCountPotato++)
		{
			pIdx[0] = nCountPotato + MAX_X +1;
			pIdx[1] = nCountPotato;
			pIdx += 2;
			if (nCount_z < MAX_Z && nCount_X == MAX_X)
			{
				pIdx[0] = nCountPotato;
				pIdx[1] = nCountPotato + (MAX_X + 1) +1;

				pIdx += 2;
			}
		}
	}
	/*pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;*/

	//インデックスバッファをアンロックする
	g_pIdxBuffMeshField->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	//// テクスチャの開放
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//インデックスバッファの開放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MAX_X*MAX_Z * 2 + (4 * (MAX_Z - 1))+2), 0, (MAX_X*MAX_Z * 2 + (4 * (MAX_Z - 1))));
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}

