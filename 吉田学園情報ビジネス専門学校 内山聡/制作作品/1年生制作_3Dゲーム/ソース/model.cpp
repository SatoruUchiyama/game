//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 
//
//=============================================================================
#include "model.h"
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
//LPD3DXMESH g_pMeshModel[POLYGON_MODEL] = {};
Model g_aModel[POLYGON_MODEL];
//int g_nIdxShadow;
//=============================================================================
// 初期化処理
//=============================================================================
void InitModel(void)
{
	int nCount2;
	for (nCount2 = 0; nCount2 < POLYGON_MODEL; nCount2++)
	{
		g_aModel[nCount2].g_VtxMinModel = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_aModel[nCount2].g_VtxMaxModel = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
	}
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCount3 = 0; nCount3 < POLYGON_MODEL; nCount3++)
	{
		g_aModel[nCount3].ModelType = MODEL_NOMAL;
		g_aModel[nCount3].pos = D3DXVECTOR3(0, 0, 0);
		g_aModel[nCount3].rot = D3DXVECTOR3(0, 0, 0);
		g_aModel[nCount3].bUse = false;
	}

	//g_nIdxShadow = SetShadow(g_posModel, g_rotModel);
	// Xファイルの読み込み		tanknsu.x		car000.x なすび2.x石粒2.x
	D3DXLoadMeshFromX("date\\model\\置き松明2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[0].g_pBuffMatModel, NULL, &g_aModel[0].g_nNumMatModel, &g_aModel[0].g_pMeshModel[0]);
	D3DXLoadMeshFromX("date\\model\\線路.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[1].g_pBuffMatModel, NULL, &g_aModel[1].g_nNumMatModel, &g_aModel[1].g_pMeshModel[1]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[2].g_pBuffMatModel, NULL, &g_aModel[2].g_nNumMatModel, &g_aModel[2].g_pMeshModel[2]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[3].g_pBuffMatModel, NULL, &g_aModel[3].g_nNumMatModel, &g_aModel[3].g_pMeshModel[3]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[4].g_pBuffMatModel, NULL, &g_aModel[4].g_nNumMatModel, &g_aModel[4].g_pMeshModel[4]);
//	D3DXLoadMeshFromX("date\\model\\枯れ木.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[5].g_pBuffMatModel, NULL, &g_aModel[5].g_nNumMatModel, &g_aModel[5].g_pMeshModel[5]);
	//D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[3].g_pBuffMatModel, NULL, &g_aModel[3].g_nNumMatModel, &g_aModel[3].g_pMeshModel[3]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[5].g_pBuffMatModel, NULL, &g_aModel[5].g_nNumMatModel, &g_aModel[5].g_pMeshModel[5]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[6].g_pBuffMatModel, NULL, &g_aModel[6].g_nNumMatModel, &g_aModel[6].g_pMeshModel[6]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[7].g_pBuffMatModel, NULL, &g_aModel[7].g_nNumMatModel, &g_aModel[7].g_pMeshModel[7]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[8].g_pBuffMatModel, NULL, &g_aModel[8].g_nNumMatModel, &g_aModel[8].g_pMeshModel[8]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[9].g_pBuffMatModel, NULL, &g_aModel[9].g_nNumMatModel, &g_aModel[9].g_pMeshModel[9]);

	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[10].g_pBuffMatModel, NULL, &g_aModel[10].g_nNumMatModel, &g_aModel[10].g_pMeshModel[10]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[11].g_pBuffMatModel, NULL, &g_aModel[11].g_nNumMatModel, &g_aModel[11].g_pMeshModel[11]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[12].g_pBuffMatModel, NULL, &g_aModel[12].g_nNumMatModel, &g_aModel[12].g_pMeshModel[12]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[13].g_pBuffMatModel, NULL, &g_aModel[13].g_nNumMatModel, &g_aModel[13].g_pMeshModel[13]);
	D3DXLoadMeshFromX("date\\model\\宝石.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[14].g_pBuffMatModel, NULL, &g_aModel[14].g_nNumMatModel, &g_aModel[14].g_pMeshModel[14]);

	D3DXLoadMeshFromX("date\\model\\つる.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[15].g_pBuffMatModel, NULL, &g_aModel[15].g_nNumMatModel, &g_aModel[15].g_pMeshModel[15]);
	D3DXLoadMeshFromX("date\\model\\つる.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[16].g_pBuffMatModel, NULL, &g_aModel[16].g_nNumMatModel, &g_aModel[16].g_pMeshModel[16]);
	D3DXLoadMeshFromX("date\\model\\つる.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[17].g_pBuffMatModel, NULL, &g_aModel[17].g_nNumMatModel, &g_aModel[17].g_pMeshModel[17]);
	D3DXLoadMeshFromX("date\\model\\つる.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[18].g_pBuffMatModel, NULL, &g_aModel[18].g_nNumMatModel, &g_aModel[18].g_pMeshModel[18]);
	D3DXLoadMeshFromX("date\\model\\つる.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[19].g_pBuffMatModel, NULL, &g_aModel[19].g_nNumMatModel, &g_aModel[19].g_pMeshModel[19]);

	D3DXLoadMeshFromX("date\\model\\つる.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[20].g_pBuffMatModel, NULL, &g_aModel[20].g_nNumMatModel, &g_aModel[20].g_pMeshModel[20]);
	D3DXLoadMeshFromX("date\\model\\つる.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[21].g_pBuffMatModel, NULL, &g_aModel[21].g_nNumMatModel, &g_aModel[21].g_pMeshModel[21]);
	D3DXLoadMeshFromX("date\\model\\つる.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[22].g_pBuffMatModel, NULL, &g_aModel[22].g_nNumMatModel, &g_aModel[22].g_pMeshModel[22]);
	D3DXLoadMeshFromX("date\\model\\つる.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[23].g_pBuffMatModel, NULL, &g_aModel[23].g_nNumMatModel, &g_aModel[23].g_pMeshModel[23]);
	D3DXLoadMeshFromX("date\\model\\つる.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[24].g_pBuffMatModel, NULL, &g_aModel[24].g_nNumMatModel, &g_aModel[24].g_pMeshModel[24]);



	int nNumVtx;			//頂点数
	DWORD sizeFVF;			//頂点フォーマット7のサイズ
	BYTE *pVtxBuff;			//頂点バッファへのポインタ

	for (int nCount = 0; nCount < POLYGON_MODEL; nCount++)
	{
		//頂点数を取得
		nNumVtx = g_aModel[nCount].g_pMeshModel[nCount]->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[nCount].g_pMeshModel[nCount]->GetFVF());
		//頂点バッファをロック
		g_aModel[nCount].g_pMeshModel[nCount]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
			//
			if (vtx.x < g_aModel[nCount].g_VtxMinModel.x)
			{
				g_aModel[nCount].g_VtxMinModel.x = vtx.x;
			}
			if (vtx.z < g_aModel[nCount].g_VtxMinModel.z)
			{
				g_aModel[nCount].g_VtxMinModel.z = vtx.z;
			}
			if (vtx.y < g_aModel[nCount].g_VtxMinModel.y)
			{
				g_aModel[nCount].g_VtxMinModel.y = vtx.y;
			}

			//
			if (vtx.x > g_aModel[nCount].g_VtxMaxModel.x)
			{
				g_aModel[nCount].g_VtxMaxModel.x = vtx.x;
			}
			if (vtx.z > g_aModel[nCount].g_VtxMaxModel.z)
			{
				g_aModel[nCount].g_VtxMaxModel.z = vtx.z;
			}
			if (vtx.y > g_aModel[nCount].g_VtxMaxModel.y)
			{
				g_aModel[nCount].g_VtxMaxModel.y = vtx.y;
			}
			pVtxBuff += sizeFVF;		//サイズ分ポインタを進める

		}
		//頂点バッファをアンロック
		g_aModel[nCount].g_pMeshModel[nCount]->UnlockVertexBuffer();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	for (int nCount = 0; nCount < POLYGON_MODEL; nCount++)
	{
		// メッシュの開放
		if (g_aModel[nCount].g_pMeshModel[nCount] != NULL)
		{
			g_aModel[nCount].g_pMeshModel[nCount]->Release();
			g_aModel[nCount].g_pMeshModel[nCount] = NULL;
		}
		// マテリアルの開放
		if (g_aModel[nCount].g_pBuffMatModel != NULL)
		{
			g_aModel[nCount].g_pBuffMatModel->Release();
			g_aModel[nCount].g_pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{
	/*Player *pPlayer;

	pPlayer = GetPlayer();*/
	
	//Trigger
	//SetPositionShadow(g_nIdxShadow, g_posModel);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCount = 0; nCount < POLYGON_MODEL; nCount++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aModel[nCount].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCount].rot.y, g_aModel[nCount].rot.x, g_aModel[nCount].rot.z);
		D3DXMatrixMultiply(&g_aModel[nCount].mtxWorld, &g_aModel[nCount].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_aModel[nCount].pos.x, g_aModel[nCount].pos.y, g_aModel[nCount].pos.z);
		D3DXMatrixMultiply(&g_aModel[nCount].mtxWorld, &g_aModel[nCount].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCount].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_aModel[nCount].g_pBuffMatModel->GetBufferPointer();

		for(int nCntMat = 0;nCntMat<(int)g_aModel[nCount].g_nNumMatModel;nCntMat++)
		{
			if (g_aModel[nCount].bUse == true)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, NULL);
				// モデル(パーツ)の描画
				g_aModel[nCount].g_pMeshModel[nCount]->DrawSubset(nCntMat);
			}
		}
		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// セットモデル
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int Type)
{
	int nCntModel;

	for (nCntModel = 0; nCntModel < POLYGON_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{
			g_aModel[nCntModel].pos = pos;
			g_aModel[nCntModel].rot = rot;
			g_aModel[nCntModel].bUse = true;
			g_aModel[nCntModel].Type = Type;

			break;
		}
	}
}
//=============================================================================
// モデルの当たり判定
//=============================================================================
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	int nCount;
	bool bLand = false;
	for (nCount = 0; nCount < POLYGON_MODEL; nCount++)
	{
		if (pPos->x > g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMinModel.x && pPos->x < g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMaxModel.x)
		{
			if (pPosold->z >= g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMaxModel.z && pPos->z < g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMaxModel.z)
			{
				pPos->z = g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMaxModel.z;
			}
			else if (pPosold->z <= g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMinModel.z && pPos->z > g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMinModel.z)
			{
				pPos->z = g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMinModel.z;
			}
		}
		if (pPos->z > g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMinModel.z && pPos->z < g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMaxModel.z)
		{
			if (pPosold->x >= g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMaxModel.x && pPos->x < g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMaxModel.x)
			{
				pPos->x = g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMaxModel.x;
			}
			else if (pPosold->x <= g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMinModel.x && pPos->x > g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMinModel.x)
			{
				pPos->x = g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMinModel.x;
			}
		}
	}
	return bLand;
}