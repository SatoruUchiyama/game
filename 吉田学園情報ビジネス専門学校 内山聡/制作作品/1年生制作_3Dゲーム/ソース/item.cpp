//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 
//
//=============================================================================
#include "item.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "ballet.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ATARI				(200)
#define MAX_ATARI2				(80)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
//LPD3DXMESH g_pMeshItem[POLYGON_ITEM] = {};
Item g_aItem[POLYGON_ITEM];
//int g_nIdxShadow;
//=============================================================================
// 初期化処理
//=============================================================================
void InitItem(void)
{
	int nCount2;
	for (nCount2 = 0; nCount2 < POLYGON_ITEM; nCount2++)
	{
		g_aItem[nCount2].g_VtxMinItem = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
		g_aItem[nCount2].g_VtxMaxItem = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	}
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCount3 = 0; nCount3 < POLYGON_ITEM; nCount3++)
	{
		g_aItem[nCount3].ItemType = ITEM_NOMAL;
		g_aItem[nCount3].pos = D3DXVECTOR3(0, 0, 0);
		g_aItem[nCount3].rot = D3DXVECTOR3(0, 0, 0);
		g_aItem[nCount3].bUse = false;
	}

	//g_nIdxShadow = SetShadow(g_posItem, g_rotItem);
	// Xファイルの読み込み		tanknsu.x		car000.x なすび2.x
	D3DXLoadMeshFromX("date\\model\\石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aItem[0].g_pBuffMatItem, NULL, &g_aItem[0].g_nNumMatItem, &g_aItem[0].g_pMeshItem[0]);



	int nNumVtx;			//頂点数
	DWORD sizeFVF;			//頂点フォーマット7のサイズ
	BYTE *pVtxBuff;			//頂点バッファへのポインタ

	for (int nCount = 0; nCount < POLYGON_ITEM; nCount++)
	{
		//頂点数を取得
		nNumVtx = g_aItem[nCount].g_pMeshItem[nCount]->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aItem[nCount].g_pMeshItem[nCount]->GetFVF());
		//頂点バッファをロック
		g_aItem[nCount].g_pMeshItem[nCount]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
			//
			if (vtx.x < g_aItem[nCount].g_VtxMinItem.x)
			{
				g_aItem[nCount].g_VtxMinItem.x = vtx.x;
			}
			if (vtx.z < g_aItem[nCount].g_VtxMinItem.z)
			{
				g_aItem[nCount].g_VtxMinItem.z = vtx.z;
			}
			if (vtx.y < g_aItem[nCount].g_VtxMinItem.y)
			{
				g_aItem[nCount].g_VtxMinItem.y = vtx.y;
			}

			//
			if (vtx.x > g_aItem[nCount].g_VtxMaxItem.x)
			{
				g_aItem[nCount].g_VtxMaxItem.x = vtx.x;
			}
			if (vtx.z > g_aItem[nCount].g_VtxMaxItem.z)
			{
				g_aItem[nCount].g_VtxMaxItem.z = vtx.z;
			}
			if (vtx.y > g_aItem[nCount].g_VtxMaxItem.y)
			{
				g_aItem[nCount].g_VtxMaxItem.y = vtx.y;
			}
			pVtxBuff += sizeFVF;		//サイズ分ポインタを進める

		}
		//頂点バッファをアンロック
		g_aItem[nCount].g_pMeshItem[nCount]->UnlockVertexBuffer();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	for (int nCount = 0; nCount < POLYGON_ITEM; nCount++)
	{
		// メッシュの開放
		if (g_aItem[nCount].g_pMeshItem[nCount] != NULL)
		{
			g_aItem[nCount].g_pMeshItem[nCount]->Release();
			g_aItem[nCount].g_pMeshItem[nCount] = NULL;
		}
		// マテリアルの開放
		if (g_aItem[nCount].g_pBuffMatItem != NULL)
		{
			g_aItem[nCount].g_pBuffMatItem->Release();
			g_aItem[nCount].g_pBuffMatItem = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	/*Player *pPlayer;

	pPlayer = GetPlayer();*/

	//Trigger
	//SetPositionShadow(g_nIdxShadow, g_posItem);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCount = 0; nCount < POLYGON_ITEM; nCount++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aItem[nCount].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aItem[nCount].rot.y, g_aItem[nCount].rot.x, g_aItem[nCount].rot.z);
		D3DXMatrixMultiply(&g_aItem[nCount].mtxWorld, &g_aItem[nCount].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_aItem[nCount].pos.x, g_aItem[nCount].pos.y, g_aItem[nCount].pos.z);
		D3DXMatrixMultiply(&g_aItem[nCount].mtxWorld, &g_aItem[nCount].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aItem[nCount].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_aItem[nCount].g_pBuffMatItem->GetBufferPointer();

		for (int nCntMat = 0; nCntMat<(int)g_aItem[nCount].g_nNumMatItem; nCntMat++)
		{
			if (g_aItem[nCount].bUse == true)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, NULL);
				// モデル(パーツ)の描画
				g_aItem[nCount].g_pMeshItem[nCount]->DrawSubset(nCntMat);
			}
		}
		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}


}
//=============================================================================
// セットモデル
//=============================================================================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int Type)
{
	int nCntItem;

	for (nCntItem = 0; nCntItem < POLYGON_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].rot = rot;
			g_aItem[nCntItem].bUse = true;
			g_aItem[nCntItem].Type = Type;


			break;
		}
	}
}