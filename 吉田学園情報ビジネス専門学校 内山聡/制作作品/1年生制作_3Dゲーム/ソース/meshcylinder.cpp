//=============================================================================
//
// メッシュ処理 [meshcylinder.cpp]
// Author : 
//
//=============================================================================
#include "MeshCylinder.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_Z			(1)
#define MAX_X			(10)
#define MAX_Y			(1)
#define MAX_VERTICAL	(1)					//垂直方向の分割数
#define MAX_LEVEL		(5)					//水平方向の分割数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureMeshCylinder = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;	//頂点バッファのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;	//インデックスバッファのポインタ
D3DXVECTOR3 g_posMeshCylinder;							//位置
D3DXVECTOR3 g_rotMeshCylinder;							//向き
D3DXMATRIX g_mtxWorldMeshCylinder;						//ワールドマトリックス
int g_nNumVertexMeshCylinder;							//頂点数
int g_nNumIndexMeshCylinder;							//インデックス数
int g_nNumPolygonMeshCylinder;							//ポリゴン数

//=============================================================================
// 初期化処
//=============================================================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	int nCount_z;
	int nCount_X;
	int nCountPotato = 0;
	int nCntV, nCntH;
	D3DXCreateTextureFromFile						// テクスチャの読み込み
	(
		pDevice,
		"date\\TEXTURE\\th3XE4616V.jpg",
		&g_pTextureMeshCylinder
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MAX_Y + 1)*(MAX_X + 1), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshCylinder, NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * (((MAX_X + 1) * 2) * MAX_Y + (2 * (MAX_Y - 1))), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshCylinder, NULL);

	//ポインタ
	VERTEX_3D*pVtx;									//頂点情報へのポインタ
	WORD*pIdx;										//インデックスデータへのポインタ


													//バッファをロック
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntV = 0; nCntV < MAX_Y +1; nCntV++)
	{
		for (nCntH = 0; nCntH < MAX_X +1; nCntH++)
		{
			pVtx[0].pos.x = sinf((-D3DX_PI*(1.0f / (MAX_X / 2))) * nCntH) * 20;
			pVtx[0].pos.y = 50.0f-(nCntV*50);
			pVtx[0].pos.z = cosf((-D3DX_PI*(1.0f / (MAX_X / 2))) * nCntH) * 20;

			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].tex = D3DXVECTOR2(nCntV*1.0f, nCntH*1.0f);
			pVtx += 1;
		}
	}

	//

	//頂点バッファをアンロックする
	g_pVtxBuffMeshCylinder->Unlock();

	//インデックスバッファをロックする
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
	for (nCount_z = 0; nCount_z < MAX_Y; nCount_z++)
	{
		for (nCount_X = 0; nCount_X < MAX_X + 1; nCount_X++, nCountPotato++)
		{
			pIdx[0] = nCountPotato + MAX_X + 1;
			pIdx[1] = nCountPotato;
			pIdx += 2;
			if (nCount_z < MAX_Y && nCount_X == MAX_X)
			{
				pIdx[0] = nCountPotato + 0;
				pIdx[1] = nCountPotato + (MAX_X + 1) + 1;

				pIdx += 2;
			}
		}
	}

	//インデックスバッファをアンロックする
	g_pIdxBuffMeshCylinder->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshCylinder(void)
{
	//// テクスチャの開放
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//インデックスバッファの開放
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshCylinder(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshCylinder);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCylinder);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MAX_Y + 1)*(MAX_X + 1), 0, (MAX_X*MAX_Y * 2 + (4 * (MAX_Y - 1))));
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}

