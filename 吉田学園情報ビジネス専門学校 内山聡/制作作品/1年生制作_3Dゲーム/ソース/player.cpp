//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "ballet.h"
#include "model.h"
#include "fade.h"
#include "billboard.h"
#include "enemy.h"
#include "effect.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ATARI				(890)
#define MAX_ATARI2				(90)

#define MAX_PARTS				(7)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player g_Player;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	
	// Xファイルの読み込み		tanknsu.x		car000.x なすび2.x	tanknsu.x
	D3DXLoadMeshFromX("date\\model\\胴体1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBuffMatPlayer, NULL, &g_Player.aModel[0].nNumMatPlayer, &g_Player.aModel[0].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\顔1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBuffMatPlayer, NULL, &g_Player.aModel[1].nNumMatPlayer, &g_Player.aModel[1].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\左足1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[2].pBuffMatPlayer, NULL, &g_Player.aModel[2].nNumMatPlayer, &g_Player.aModel[2].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\右足1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[3].pBuffMatPlayer, NULL, &g_Player.aModel[3].nNumMatPlayer, &g_Player.aModel[3].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\左腕1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[4].pBuffMatPlayer, NULL, &g_Player.aModel[4].nNumMatPlayer, &g_Player.aModel[4].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\右腕1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[5].pBuffMatPlayer, NULL, &g_Player.aModel[5].nNumMatPlayer, &g_Player.aModel[5].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\なすび2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[6].pBuffMatPlayer, NULL, &g_Player.aModel[6].nNumMatPlayer, &g_Player.aModel[6].pMeshPlayer);
	// 位置・向きの初期設定				yoroi.x
	g_Player.pos = D3DXVECTOR3(0, 0, 0);
	g_Player.rot = D3DXVECTOR3(0, 0, 0);
	g_Player.move = D3DXVECTOR3(0, 0, 0.0f);
	g_Player.posold = D3DXVECTOR3(0, 0, 0);
	g_Player.rotDest = D3DXVECTOR3(0, 0, 0);

	g_Player.aModel[0].pos = D3DXVECTOR3(0,15,0);
	g_Player.aModel[1].pos = D3DXVECTOR3(0, 20, 0);
	g_Player.aModel[2].pos = D3DXVECTOR3(5, 0, 0);
	g_Player.aModel[3].pos = D3DXVECTOR3(-5, 0, 0);
	g_Player.aModel[4].pos = D3DXVECTOR3(5, 15, 0);
	g_Player.aModel[5].pos = D3DXVECTOR3(-5, 15, 0);
	g_Player.aModel[6].pos = D3DXVECTOR3(-15, 0, 0);

	g_Player.aModel[0].nIdxModelParent = -1;
	g_Player.aModel[1].nIdxModelParent = 0;
	g_Player.aModel[2].nIdxModelParent = 0;
	g_Player.aModel[3].nIdxModelParent = 0;
	g_Player.aModel[4].nIdxModelParent = 0;
	g_Player.aModel[5].nIdxModelParent = 0;
	g_Player.aModel[6].nIdxModelParent = 5;

	g_Player.g_nIdxShadow = SetShadow(g_Player.pos, g_Player.rot);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// メッシュの開放
		if (g_Player.aModel[nCount].pMeshPlayer != NULL)
		{
			g_Player.aModel[nCount].pMeshPlayer->Release();
			g_Player.aModel[nCount].pMeshPlayer = NULL;
		}
	}
	for (int nCount2 = 0; nCount2 < MAX_PARTS; nCount2++)
	{
		// マテリアルの開放
		if (g_Player.aModel[nCount2].pBuffMatPlayer != NULL)
		{
			g_Player.aModel[nCount2].pBuffMatPlayer->Release();
			g_Player.aModel[nCount2].pBuffMatPlayer = NULL;
		}

	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	float fSabun;

	g_Player.posold = g_Player.pos;
	//右移動の処理
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		SetEffect(g_Player.pos, D3DXCOLOR(1.0f, 0.5f, 0.7f, 1.0f), 20, 20, 0);// プレイヤーに追尾するパーティクル
		//右上
		if (GetKeyboardPress(DIK_UP) == true)
		{
			g_Player.move.x -= sinf(pCamera->fAngle - D3DX_PI*0.75f) * 1.0f;
			g_Player.move.z -= cosf(pCamera->fAngle - D3DX_PI*0.75f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle - D3DX_PI *0.75f;
		}
		//右下
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			g_Player.move.x -= sinf(pCamera->fAngle - D3DX_PI*0.25f) * 1.0f;
			g_Player.move.z -= cosf(pCamera->fAngle - D3DX_PI*0.25f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle - D3DX_PI *0.25f;
		}
		//右
		else
		{
			g_Player.move.x += sinf(pCamera->fAngle + D3DX_PI*0.5f) * 1.0f;
			g_Player.move.z += cosf(pCamera->fAngle + D3DX_PI*0.5f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle + D3DX_PI* -0.5f;
		}
	}
	//左移動の処理
	else if (GetKeyboardPress(DIK_LEFT) == true)
	{
		SetEffect(g_Player.pos, D3DXCOLOR(1.0f, 0.5f, 0.7f, 1.0f), 20, 20, 0);//	プレイヤーに追尾するパーティクル
		//左上
		if (GetKeyboardPress(DIK_UP) == true)
		{
			g_Player.move.x -= sinf(pCamera->fAngle + D3DX_PI*0.75f) * 1.0f;
			g_Player.move.z -= cosf(pCamera->fAngle + D3DX_PI*0.75f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle + D3DX_PI *0.75f;
		}
		//左下
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			g_Player.move.x -= sinf(pCamera->fAngle + D3DX_PI*0.25f) * 1.0f;
			g_Player.move.z -= cosf(pCamera->fAngle + D3DX_PI*0.25f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle + D3DX_PI *0.25f;
		}
		//左
		else
		{
			g_Player.move.x -= sinf(pCamera->fAngle + D3DX_PI*0.5f) * 1.0f;
			g_Player.move.z -= cosf(pCamera->fAngle + D3DX_PI*0.5f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle + D3DX_PI* 0.5f;
		}
	}
	//上
	else if (GetKeyboardPress(DIK_UP) == true)
	{
		SetEffect(g_Player.pos, D3DXCOLOR(1.0f, 0.5f, 0.7f, 1.0f), 20, 20, 0);//	プレイヤーに追尾するパーティクル

		g_Player.move.x -= sinf(D3DX_PI + pCamera->fAngle) * 1.0f;
		g_Player.move.z -= cosf(D3DX_PI + pCamera->fAngle) * 1.0f;

		g_Player.rotDest.y = pCamera->fAngle - D3DX_PI *1.0f;
	}
	//下
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{
		SetEffect(g_Player.pos, D3DXCOLOR(1.0f, 0.5f, 0.7f, 1.0f), 20, 20, 0);//	プレイヤーに追尾するパーティクル
		g_Player.move.x += sinf(D3DX_PI + pCamera->fAngle) * 1.0f;
		g_Player.move.z += cosf(D3DX_PI + pCamera->fAngle) * 1.0f;

		g_Player.rotDest.y = pCamera->fAngle - D3DX_PI *0.0f;
	}

	//プレイヤー上下の移動処理
	//上
	if (GetKeyboardPress(DIK_R) == true)
	{
		g_Player.move.y += 1;
	}
	if (GetKeyboardPress(DIK_Y) == true)
	{//下
		g_Player.move.y -= 1;
	}

	//弾発射の処理
	/*if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBallet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 8, g_Player.pos.z), g_Player.rot, D3DXVECTOR3(sinf(g_Player.rot.y - D3DX_PI) * 5, 0.0f, cosf(g_Player.rot.y - D3DX_PI) * 5));
	}*/

//	CollisionItem();		//ビルボードの当たり判定
	//壁との当たり判定		決め打ち
	if (MAX_ATARI <= g_Player.pos.x)
	{
		g_Player.pos.x = MAX_ATARI;
	}
	if (-MAX_ATARI2 >= g_Player.pos.x)
	{
		g_Player.pos.x = -MAX_ATARI2;
	}
	if (-MAX_ATARI >= g_Player.pos.z)
	{
		g_Player.pos.z = -MAX_ATARI;
	}
	if (MAX_ATARI2 <= g_Player.pos.z)
	{
		g_Player.pos.z = MAX_ATARI2;
	}

	if (g_Player.rotDest.y > D3DX_PI)
	{
		g_Player.rotDest.y -= D3DX_PI*2.0f;
	}
	if (g_Player.rotDest.y < -D3DX_PI)
	{
		g_Player.rotDest.y += D3DX_PI*2.0f;
	}

	fSabun = (g_Player.rotDest.y - g_Player.rot.y);

	if (fSabun > D3DX_PI)
	{
		fSabun -= D3DX_PI*2.0f;
	}
	if (fSabun < -D3DX_PI)
	{
		fSabun += D3DX_PI*2.0f;
	}

	g_Player.rot.y += fSabun * 0.1f;

	//反対行くやつ
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI*2.0f;
	}
	if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI*2.0f;
	}

	g_Player.move.x += (0.0f - g_Player.move.x) * 0.2f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.2f;
	g_Player.move.y += (0.0f - g_Player.move.y) * 0.2f;

	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.z += g_Player.move.z;
	g_Player.pos.y += g_Player.move.y;

//	CollisionModel(&g_Player.pos, &g_Player.posold, &g_Player.move);
	CollisionEnemy(&g_Player.pos, &g_Player.posold, &g_Player.move);
	//影の配置
	SetPositionShadow(g_Player.g_nIdxShadow, g_Player.pos);

	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;
	D3DXMATRIX mtxParent;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (g_Player.aModel[nCount].nIdxModelParent < 0)
		{
			//親
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			//子
			mtxParent = g_Player.aModel[g_Player.aModel[nCount].nIdxModelParent].mtxWorldPlayer;
		}
		//-----------------------------------------------
		//					親
		//-----------------------------------------------
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aModel[nCount].mtxWorldPlayer);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCount].rot.y, g_Player.aModel[nCount].rot.x, g_Player.aModel[nCount].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCount].mtxWorldPlayer, &g_Player.aModel[nCount].mtxWorldPlayer, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCount].pos.x, g_Player.aModel[nCount].pos.y, g_Player.aModel[nCount].pos.z);
	
		//
		D3DXMatrixMultiply(&g_Player.aModel[nCount].mtxWorldPlayer, &g_Player.aModel[nCount].mtxWorldPlayer, &mtxTrans);

		//
		D3DXMatrixMultiply(&g_Player.aModel[nCount].mtxWorldPlayer, &g_Player.aModel[nCount].mtxWorldPlayer, &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCount].mtxWorldPlayer);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCount].pBuffMatPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCount].nNumMatPlayer; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// テクスチャの設定
			pDevice->SetTexture(0, NULL);
			// モデル(パーツ)の描画
			g_Player.aModel[nCount].pMeshPlayer->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}
//プレイヤーポインタ
Player *GetPlayer(void)
{
	return &g_Player;
}