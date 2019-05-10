//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "model.h"
#include "player.h"
#include "title.h"
#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_FRAME				(10)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_Camera;
int g_nCount = MAX_FRAME;

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	g_Camera.posV = D3DXVECTOR3(0.0f, 85.0f, -200.0f);
	g_Camera.posR = D3DXVECTOR3(0.0f, 45.0f, 0.0f);
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	
	g_Camera.typ = CAMERASTATE_NONE;
	g_Camera.fLength = g_Camera.posR.z - g_Camera.posV.z;
	g_Camera.fAngle = atan2f(g_Camera.posV.x - g_Camera.posR.x, g_Camera.posV.z - g_Camera.posR.z);
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	Player *pPlayer;

	pPlayer = GetPlayer();

	float fSabun;

	if (g_Camera.typ == CAMERARASTATE_GAME) 
	{
		//----------------------------------------------
		//	左旋回 (Q)
		//----------------------------------------------
		/*if (GetKeyboardPress(DIK_Q) == true)
		{
			g_Camera.fAngle -= 0.05f;
			g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.fAngle)*g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.fAngle)*g_Camera.fLength;
		}*/
		//----------------------------------------------
		//	右旋回 (E)
		//----------------------------------------------
		/*if (GetKeyboardPress(DIK_E) == true)
		{
			g_Camera.fAngle += 0.05f;
			g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.fAngle)*g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.fAngle)*g_Camera.fLength;
		}*/
		//----------------------------------------------
		//	注視点を中心に右旋回 (Z)
		//----------------------------------------------
		if (GetKeyboardPress(DIK_Z) == true)
		{
			g_Camera.fAngle += 0.05f;

			g_Camera.posVDest.x = g_Camera.posRDest.x - sinf(g_Camera.fAngle)*g_Camera.fLength;
			g_Camera.posVDest.z = g_Camera.posRDest.z - cosf(g_Camera.fAngle)*g_Camera.fLength;
		}
		//----------------------------------------------
		//	注視点を中心に左旋回 (C)
		//----------------------------------------------
		if (GetKeyboardPress(DIK_C) == true)
		{
			g_Camera.fAngle -= 0.05f;
			g_Camera.posVDest.x = g_Camera.posRDest.x - sinf(g_Camera.fAngle)*g_Camera.fLength;
			g_Camera.posVDest.z = g_Camera.posRDest.z - cosf(g_Camera.fAngle)*g_Camera.fLength;
		}
		//----------------------------------------------
		//	下に行く
		//----------------------------------------------
		//if (GetKeyboardPress(DIK_B) == true)
		//{

		//	//g_Camera.posV.y -= 0.5f;
		//	g_Camera.posR.y -= 0.5f;
		//}
		//----------------------------------------------
		//	上に行く
		//----------------------------------------------
		//if (GetKeyboardPress(DIK_V) == true)
		//{
		//	//g_Camera.posV.y += 0.5f;
		//	g_Camera.posR.y += 0.5f;
		//}

		//----------------------------------------------
		//	
		//----------------------------------------------
		/*if (GetKeyboardPress(DIK_N) == true)
		{
			g_Camera.posV.y -= 0.5f;
			g_Camera.posR.y -= 0.5f;
		}*/
		//----------------------------------------------
		//	
		//----------------------------------------------
		/*if (GetKeyboardPress(DIK_M) == true)
		{
			g_Camera.posV.y += 0.5f;
			g_Camera.posR.y += 0.5f;
		}*/

		if (pPlayer->move.z < 0.0001f && pPlayer->move.x < 0.0001f && pPlayer->move.y < 0.0001f &&pPlayer->move.z > -0.0001f && pPlayer->move.x > -0.0001f && pPlayer->move.y > -0.0001f)
		{

			if (g_nCount > 0)
			{
				g_nCount--;
			}
			else if (g_nCount == 0)
			{
				//--------------------------------------------------------------------------------------------
				// カメラの移動処理
				//--------------------------------------------------------------------------------------------
				if (g_Camera.fAngle > D3DX_PI)
				{
					g_Camera.fAngle -= D3DX_PI*2.0f;
				}
				if (g_Camera.fAngle < -D3DX_PI)
				{
					g_Camera.fAngle += D3DX_PI*2.0f;
				}

				fSabun = (pPlayer->rot.y - g_Camera.fAngle + D3DX_PI);

				if (fSabun > D3DX_PI)
				{
					fSabun -= D3DX_PI*2.0f;
				}
				if (fSabun < -D3DX_PI)
				{
					fSabun += D3DX_PI*2.0f;
				}

				g_Camera.fAngle += fSabun * 0.1f;

				if (g_Camera.fAngle > D3DX_PI)
				{
					g_Camera.fAngle -= D3DX_PI*2.0f;
				}
				if (g_Camera.fAngle < -D3DX_PI)
				{
					g_Camera.fAngle += D3DX_PI*2.0f;
				}


			}

		}
		else
		{
			g_nCount = MAX_FRAME;
		}
		g_Camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y)* 10.0f;
		g_Camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y)* 10.0f;
		g_Camera.posVDest.x = pPlayer->pos.x - sinf(g_Camera.fAngle)* g_Camera.fLength;
		g_Camera.posVDest.z = pPlayer->pos.z - cosf(g_Camera.fAngle)* g_Camera.fLength;

		g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x)* 0.1f;												//注視点
		g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z)* 0.1f;
		g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x)* 0.1f;												//視点
		g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z)* 0.1f;
	}
	if (g_Camera.typ == CAMERASTATE_TAITLE)
	{
			/*g_Camera.fAngle -= 0.05f;
			g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.fAngle)*g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.fAngle)*g_Camera.fLength;*/
		
		//g_Camera.posV = D3DXVECTOR3(0.0f, 50.0f, -70.0f);

		g_Camera.fAngle += 0.01f;
		if (g_Camera.fAngle > D3DX_PI)
		{
			g_Camera.fAngle = -D3DX_PI;
		}
		/*g_Camera.fAngle += 0.05f;
		g_Camera.posVDest.x = g_Camera.posRDest.x - sinf(g_Camera.fAngle)*g_Camera.fLength;
		g_Camera.posVDest.z = g_Camera.posRDest.z - cosf(g_Camera.fAngle)*g_Camera.fLength;*/

		g_Camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y)* 10.0f;
		g_Camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y)* 10.0f;
		g_Camera.posVDest.x = pPlayer->pos.x - sinf(g_Camera.fAngle)* g_Camera.fLength;
		g_Camera.posVDest.z = pPlayer->pos.z - cosf(g_Camera.fAngle)* g_Camera.fLength;

		g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x)* 0.1f;												//注視点
		g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z)* 0.1f;
		g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x)* 0.1f;												//視点
		g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z)* 0.1f;

		g_Camera.posR = D3DXVECTOR3(0.0f, 45.0f, 0.0f);
		
	}
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(CameraEx CameraEx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	g_Camera.typ = CameraEx;
	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1500.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}

Camera *GetCamera(void)
{
	return &g_Camera;
}