//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : 
//
//=============================================================================
#include "wall.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_WALL			(4)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureWall = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;							//頂点バッファのポインタ


Wall g_aWall[MAX_WALL];
																			//=============================================================================
																			// 初期化処理
																			//=============================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	
	D3DXCreateTextureFromFile			// テクスチャの読み込み
	(
		pDevice,
		"date\\TEXTURE\\th.jpg",
		&g_pTextureWall
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4* MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffWall, NULL);


	VERTEX_3D*pVtx;								//頂点情報へのポインタ
												//バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定

	pVtx[0].pos = D3DXVECTOR3(-100.0, 100.0, 0.0);
	pVtx[1].pos = D3DXVECTOR3(100.0, 100.0, 0.0);
	pVtx[2].pos = D3DXVECTOR3(-100.0, 0.0, 0.0);
	pVtx[3].pos = D3DXVECTOR3(100.0, 0.0, 0.0);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
	pVtx[1].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
	pVtx[2].nor = D3DXVECTOR3(0.0, 0.0,	-1.0);
	pVtx[3].nor = D3DXVECTOR3(0.0, 0.0, -1.0);

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
	g_pVtxBuffWall->Unlock();

	//g_posWall = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
//	g_rotWall = D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWall(void)
{
	//// テクスチャの開放
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWall(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;
	int nCntWall;
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureWall);

		if (g_aWall[nCntWall].bUse == true)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].bUse = true;
			break;
		}
	}
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}

