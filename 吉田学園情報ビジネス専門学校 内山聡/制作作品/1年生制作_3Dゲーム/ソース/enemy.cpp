//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "enemy.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "ballet.h"
#include "player.h"
#include "fade.h"
#include "billboard.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
//*****************************************************************************
// グローバル変数
//*****************************************************************************
//LPD3DXMESH g_pMeshEnemy[POLYGON_ENEMY] = {};
Enemy g_aEnemy[POLYGON_ENEMY];
//int g_nIdxShadow;
int nCountPotato2;
//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	nCountPotato2 = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCount3 = 0; nCount3 < POLYGON_ENEMY; nCount3++)
	{
		g_aEnemy[nCount3].g_VtxMinEnemy = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
		g_aEnemy[nCount3].g_VtxMaxEnemy = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
		g_aEnemy[nCount3].EnemyType = ENEMY_NOMAL;
		g_aEnemy[nCount3].pos = D3DXVECTOR3(0, 0, 0);
		g_aEnemy[nCount3].rot = D3DXVECTOR3(0, 0, 0);
		g_aEnemy[nCount3].bUse = false;
	}

	//g_nIdxShadow = SetShadow(g_posEnemy, g_rotEnemy);
	// Xファイルの読み込み		tanknsu.x		car000.x なすび2.x
	for (int nCount4 = 0; nCount4 < POLYGON_ENEMY; nCount4++)
	{
		D3DXLoadMeshFromX("date\\model\\顔.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aEnemy[nCount4].g_pBuffMatEnemy, NULL, &g_aEnemy[nCount4].g_nNumMatEnemy, &g_aEnemy[nCount4].g_pMeshEnemy[nCount4]);
	}
	
	/*D3DXLoadMeshFromX("date\\model\\顔.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aEnemy[1].g_pBuffMatEnemy, NULL, &g_aEnemy[1].g_nNumMatEnemy, &g_aEnemy[1].g_pMeshEnemy[1]);
	D3DXLoadMeshFromX("date\\model\\顔.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aEnemy[2].g_pBuffMatEnemy, NULL, &g_aEnemy[2].g_nNumMatEnemy, &g_aEnemy[2].g_pMeshEnemy[2]);
	D3DXLoadMeshFromX("date\\model\\顔.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aEnemy[3].g_pBuffMatEnemy, NULL, &g_aEnemy[3].g_nNumMatEnemy, &g_aEnemy[3].g_pMeshEnemy[3]);
	D3DXLoadMeshFromX("date\\model\\顔.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aEnemy[4].g_pBuffMatEnemy, NULL, &g_aEnemy[4].g_nNumMatEnemy, &g_aEnemy[4].g_pMeshEnemy[4]);
	D3DXLoadMeshFromX("date\\model\\顔.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aEnemy[5].g_pBuffMatEnemy, NULL, &g_aEnemy[4].g_nNumMatEnemy, &g_aEnemy[4].g_pMeshEnemy[4]);
	D3DXLoadMeshFromX("date\\model\\顔.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aEnemy[6].g_pBuffMatEnemy, NULL, &g_aEnemy[4].g_nNumMatEnemy, &g_aEnemy[4].g_pMeshEnemy[4]);
	D3DXLoadMeshFromX("date\\model\\顔.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aEnemy[7].g_pBuffMatEnemy, NULL, &g_aEnemy[4].g_nNumMatEnemy, &g_aEnemy[4].g_pMeshEnemy[4]);
	D3DXLoadMeshFromX("date\\model\\顔.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aEnemy[8].g_pBuffMatEnemy, NULL, &g_aEnemy[4].g_nNumMatEnemy, &g_aEnemy[4].g_pMeshEnemy[4]);
*/



	int nNumVtx;			//頂点数
	DWORD sizeFVF;			//頂点フォーマット7のサイズ
	BYTE *pVtxBuff;			//頂点バッファへのポインタ

	for (int nCount = 0; nCount < POLYGON_ENEMY; nCount++)
	{
		//頂点数を取得
		nNumVtx = g_aEnemy[nCount].g_pMeshEnemy[nCount]->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aEnemy[nCount].g_pMeshEnemy[nCount]->GetFVF());
		//頂点バッファをロック
		g_aEnemy[nCount].g_pMeshEnemy[nCount]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
			//
			if (vtx.x < g_aEnemy[nCount].g_VtxMinEnemy.x)
			{
				g_aEnemy[nCount].g_VtxMinEnemy.x = vtx.x;
			}
			if (vtx.z < g_aEnemy[nCount].g_VtxMinEnemy.z)
			{
				g_aEnemy[nCount].g_VtxMinEnemy.z = vtx.z;
			}
			if (vtx.y < g_aEnemy[nCount].g_VtxMinEnemy.y)
			{
				g_aEnemy[nCount].g_VtxMinEnemy.y = vtx.y;
			}

			//
			if (vtx.x > g_aEnemy[nCount].g_VtxMaxEnemy.x)
			{
				g_aEnemy[nCount].g_VtxMaxEnemy.x = vtx.x;
			}
			if (vtx.z > g_aEnemy[nCount].g_VtxMaxEnemy.z)
			{
				g_aEnemy[nCount].g_VtxMaxEnemy.z = vtx.z;
			}
			if (vtx.y > g_aEnemy[nCount].g_VtxMaxEnemy.y)
			{
				g_aEnemy[nCount].g_VtxMaxEnemy.y = vtx.y;
			}
			pVtxBuff += sizeFVF;		//サイズ分ポインタを進める

		}
		//頂点バッファをアンロック
		g_aEnemy[nCount].g_pMeshEnemy[nCount]->UnlockVertexBuffer();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int nCount = 0; nCount < POLYGON_ENEMY; nCount++)
	{
		// メッシュの開放
		if (g_aEnemy[nCount].g_pMeshEnemy[nCount] != NULL)
		{
			g_aEnemy[nCount].g_pMeshEnemy[nCount]->Release();
			g_aEnemy[nCount].g_pMeshEnemy[nCount] = NULL;
		}
		// マテリアルの開放
		if (g_aEnemy[nCount].g_pBuffMatEnemy != NULL)
		{
			g_aEnemy[nCount].g_pBuffMatEnemy->Release();
			g_aEnemy[nCount].g_pBuffMatEnemy = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	Billboard *pBillboard;
	pBillboard = GetBillboard();

	for (int nCount = 0; nCount < POLYGON_ENEMY; nCount++)
	{

		if (g_aEnemy[nCount].bUse == true)
		{
			g_aEnemy[nCount].rot.y = atan2f(pBillboard->pos.x - g_aEnemy[nCount].pos.x, pBillboard->pos.z - g_aEnemy[nCount].pos.z)+D3DX_PI;
		}
		g_aEnemy[nCount].pos.y = sinf((rand() % 50) / 300.0f) * ((rand() % 80) + 1);
	}
	
	nCountPotato2++;
	if (nCountPotato2 == 240)
	{
		for (int nCount2 = 0; nCount2 < 5; nCount2++)
		{
			//g_aEnemy[0].rot.z = (rand() % 50) * ((rand() % 80) - 1.0f);
			g_aEnemy[nCount2].move.x = (rand() % 500 + 1) * 0.01f;
			g_aEnemy[nCount2].move.z = (rand() % 500 + 1) * 0.01f;
			//g_aEnemy[0].pos.z =(rand() % 50) / -100.0f;
			nCountPotato2 = 0;
		}
	}
	for (int nCount3 = 0; nCount3 < 5; nCount3++)
	{
		if (g_aEnemy[nCount3].pos.x + g_aEnemy[nCount3].move.x > 900 || g_aEnemy[nCount3].pos.x + g_aEnemy[nCount3].move.x < -100)
		{
			g_aEnemy[nCount3].move.x *= -1;
		}
		if (g_aEnemy[nCount3].pos.z + g_aEnemy[nCount3].move.z > 100 || g_aEnemy[nCount3].pos.z + g_aEnemy[nCount3].move.z < -900)
		{
			g_aEnemy[nCount3].move.z *= -1;
		}
		g_aEnemy[nCount3].pos += g_aEnemy[nCount3].move;
	}


	//Trigger
	//SetPositionShadow(g_nIdxShadow, g_posEnemy);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCount = 0; nCount < POLYGON_ENEMY; nCount++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aEnemy[nCount].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCount].rot.y, g_aEnemy[nCount].rot.x, g_aEnemy[nCount].rot.z);
		D3DXMatrixMultiply(&g_aEnemy[nCount].mtxWorld, &g_aEnemy[nCount].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCount].pos.x, g_aEnemy[nCount].pos.y, g_aEnemy[nCount].pos.z);
		D3DXMatrixMultiply(&g_aEnemy[nCount].mtxWorld, &g_aEnemy[nCount].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCount].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_aEnemy[nCount].g_pBuffMatEnemy->GetBufferPointer();

		for (int nCntMat = 0; nCntMat<(int)g_aEnemy[nCount].g_nNumMatEnemy; nCntMat++)
		{
			if (g_aEnemy[nCount].bUse == true)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, NULL);
				// モデル(パーツ)の描画
				g_aEnemy[nCount].g_pMeshEnemy[nCount]->DrawSubset(nCntMat);
			}
		}
		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}


}
//=============================================================================
// セットモデル
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int Type)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < POLYGON_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].rot = rot;
			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].Type = Type;
			break;
		}
	}
}
//=============================================================================
// モデルの当たり判定
//=============================================================================
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	Player *pPlayer;

	pPlayer = GetPlayer();
	int nCount;
	bool bLand = false;
	for (nCount = 0; nCount < POLYGON_ENEMY; nCount++)
	{
		if (pPos->x > g_aEnemy[nCount].pos.x + g_aEnemy[nCount].g_VtxMinEnemy.x && pPos->x < g_aEnemy[nCount].pos.x + g_aEnemy[nCount].g_VtxMaxEnemy.x)
		{
			if (pPosold->z >= g_aEnemy[nCount].pos.z + g_aEnemy[nCount].g_VtxMaxEnemy.z && pPos->z < g_aEnemy[nCount].pos.z + g_aEnemy[nCount].g_VtxMaxEnemy.z)
			{
				pPos->z = g_aEnemy[nCount].pos.z + g_aEnemy[nCount].g_VtxMaxEnemy.z;
				
			}
			else if (pPosold->z <= g_aEnemy[nCount].pos.z + g_aEnemy[nCount].g_VtxMinEnemy.z && pPos->z > g_aEnemy[nCount].pos.z + g_aEnemy[nCount].g_VtxMinEnemy.z)
			{
				pPos->z = g_aEnemy[nCount].pos.z + g_aEnemy[nCount].g_VtxMinEnemy.z;
			}
		}
		if (pPos->z > g_aEnemy[nCount].pos.z + g_aEnemy[nCount].g_VtxMinEnemy.z && pPos->z < g_aEnemy[nCount].pos.z + g_aEnemy[nCount].g_VtxMaxEnemy.z)
		{
			if (pPosold->x >= g_aEnemy[nCount].pos.x + g_aEnemy[nCount].g_VtxMaxEnemy.x && pPos->x < g_aEnemy[nCount].pos.x + g_aEnemy[nCount].g_VtxMaxEnemy.x)
			{
				pPos->x = g_aEnemy[nCount].pos.x + g_aEnemy[nCount].g_VtxMaxEnemy.x;
			}
			else if (pPosold->x <= g_aEnemy[nCount].pos.x + g_aEnemy[nCount].g_VtxMinEnemy.x && pPos->x > g_aEnemy[nCount].pos.x + g_aEnemy[nCount].g_VtxMinEnemy.x)
			{
				pPos->x = g_aEnemy[nCount].pos.x + g_aEnemy[nCount].g_VtxMinEnemy.x;
			}
		}
	}
	return bLand;
}