//=============================================================================
//
// ビルボード処理 [billboard.cpp]
// Author : 
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"
#include "player.h"
#include "fade.h"
#include "score.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_WALL			(1)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Billboard g_aBillboard[MAX_WALL];

// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pTextureBillboard = NULL;
//頂点バッファのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;
//アイテムのカウンター
int nCoinCount;
int nCountPotatoCount = 0;
int nCountPotato= 0;

//=============================================================================
// 初期化処理
//=============================================================================
void InitBillboard(void)
{
	int nCntBill;
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntBill = 0; nCntBill < MAX_WALL; nCntBill++)
	{
		g_aBillboard[nCntBill].pos = D3DXVECTOR3(0, 0, 0);
		g_aBillboard[nCntBill].rot = D3DXVECTOR3(0, 0, 0);
		g_aBillboard[nCntBill].move = D3DXVECTOR3(0, 0, 0);
		g_aBillboard[nCntBill].col =  D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aBillboard[nCntBill].g_nIdxShadow = 0;
		nCoinCount = 0;
		g_aBillboard[nCntBill].bUse = false;
	}

	D3DXCreateTextureFromFile			// テクスチャの読み込み
	(
		pDevice,
		"date\\TEXTURE\\thOVLTTVLV.png",
		&g_pTextureBillboard
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBillboard, NULL);


	VERTEX_3D*pVtx;								//頂点情報へのポインタ
												//バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBill = 0; nCntBill < MAX_WALL; nCntBill++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-20, 40, 0.0);
		pVtx[1].pos = D3DXVECTOR3(20, 40, 0.0);
		pVtx[2].pos = D3DXVECTOR3(-20, 0.0, 0.0);
		pVtx[3].pos = D3DXVECTOR3(20, 0.0, 0.0);

		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[1].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[2].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[3].nor = D3DXVECTOR3(0.0, 0.0, -1.0);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);

		////テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
		
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBillboard(void)
{
	//// テクスチャの開放
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
	
	// 頂点バッファの開放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBillboard(void)
{
	int nCount = 0;
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCount; nCount < MAX_WALL; nCount++)
	{
		if (g_aBillboard[nCount].bUse == true)
		{
			//g_aBillboard[nCount].bUse = false;
			//Itemを消す　スコアを加算
			//Itemをすべて取ったらTIMERを消す
			if (g_aBillboard[nCount].pos.x - 20 < pPlayer->pos.x &&
				g_aBillboard[nCount].pos.x + 20 > pPlayer->pos.x &&
				g_aBillboard[nCount].pos.z - 20 < pPlayer->pos.z &&
				g_aBillboard[nCount].pos.z + 20 > pPlayer->pos.z )
			{
				AddScore(1000);
				g_aBillboard[nCount].bUse = false;
				nCoinCount--;
				if (nCoinCount == 0)
				{
					SetFade(MODE_RESULT);
				}
			}
		}
	}
	

	//nCountPotatoCount++;
	//if (nCountPotatoCount == 180) 
	//{
	//	//g_aBillboard[0].rot.z = (rand() % 50) * ((rand() % 80) - 1.0f);
	//	g_aBillboard[0].pos.z = (rand() % 10)* ((rand() % 80) + 1.0f);
	//	//g_aBillboard[0].pos.z =(rand() % 50) / -100.0f;
	//	nCountPotatoCount = 0;
	//}
	nCountPotato++;
	if (nCountPotato == 240)
	{
		//g_aBillboard[0].rot.z = (rand() % 50) * ((rand() % 80) - 1.0f);
		g_aBillboard[0].move.x = (rand() % 600 + 1) * 0.01f;
		g_aBillboard[0].move.z = (rand() % 600 + 1) * 0.01f;
		//g_aBillboard[0].pos.z =(rand() % 50) / -100.0f;
		nCountPotato = 0;
	}

	if (g_aBillboard[0].pos.x + g_aBillboard[0].move.x > 900 || g_aBillboard[0].pos.x + g_aBillboard[0].move.x < -100)
	{
		g_aBillboard[0].move.x *= -1;
	}
	if (g_aBillboard[0].pos.z + g_aBillboard[0].move.z > 100 || g_aBillboard[0].pos.z + g_aBillboard[0].move.z < -900)
	{
		g_aBillboard[0].move.z *= -1;
	}

	g_aBillboard[0].pos += g_aBillboard[0].move;

	if (GetKeyboardPress(DIK_W) == true)
	{
		g_aBillboard[0].pos.x += 5;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_aBillboard[0].pos.z -= 5;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	int nCntBillboard;
	int nCntBill;

	//アルファテスト処理
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntBillboard = 0; nCntBillboard < MAX_WALL; nCntBillboard++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		
		g_aBillboard[nCntBillboard].mtxWorld._11 = mtxView._11;
		g_aBillboard[nCntBillboard].mtxWorld._12 = mtxView._21;
		g_aBillboard[nCntBillboard].mtxWorld._13 = mtxView._31;
		g_aBillboard[nCntBillboard].mtxWorld._21 = mtxView._12;
		g_aBillboard[nCntBillboard].mtxWorld._22 = mtxView._22;
		g_aBillboard[nCntBillboard].mtxWorld._23 = mtxView._32;
		g_aBillboard[nCntBillboard].mtxWorld._31 = mtxView._13;
		g_aBillboard[nCntBillboard].mtxWorld._32 = mtxView._23;
		g_aBillboard[nCntBillboard].mtxWorld._33 = mtxView._33;

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
		D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		for (nCntBill = 0; nCntBill < MAX_WALL; nCntBill++)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBillboard);

			if (g_aBillboard[nCntBillboard].bUse == true)
			{
				// ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCntBillboard, 2);
			}
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// セット処理
//=============================================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	int nCntItem;
//	VERTEX_3D *pVtx;

	//g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_WALL; nCntItem++)
	{

		if (g_aBillboard[nCntItem].bUse == false)
		{
			nCoinCount++;
			g_aBillboard[nCntItem].pos = pos;
			g_aBillboard[nCntItem].rot = rot;
			g_aBillboard[nCntItem].col = col;
			/*pVtx[nCntItem].pos = D3DXVECTOR3(g_aBillboard[nCntItem].pos.x - 30, g_aBillboard[nCntItem].pos.y - 30, 0.0f);
			pVtx[nCntItem].pos = D3DXVECTOR3(g_aBillboard[nCntItem].pos.x + 30, g_aBillboard[nCntItem].pos.y - 30, 0.0f);
			pVtx[nCntItem].pos = D3DXVECTOR3(g_aBillboard[nCntItem].pos.x - 30, g_aBillboard[nCntItem].pos.y, 0.0f);
			pVtx[nCntItem].pos = D3DXVECTOR3(g_aBillboard[nCntItem].pos.x + 30, g_aBillboard[nCntItem].pos.y, 0.0f);*/
			//g_aBillboard[nCntItem].g_nIdxShadow = SetShadow(g_aBillboard[nCntItem].pos, g_aBillboard[nCntItem].rot);
			g_aBillboard[nCntItem].bUse = true;
			break;
		}
		/*pVtx += 4;*/

	}
	//g_pVtxBuffBillboard->Unlock();
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}
//double Uniform(void) {
//	return (g_aBillboard[0].pos.z +=(double)rand() + 1.0f) / ((double)RAND_MAX + 2.0f);
//}

//double rand_Lnormal(double mu, double sigma) {
//	double z = mu + sigma*sqrt(-2.0*log(Uniform()))*sin(2.0*D3DX_PI*Uniform());//gauss random number
//	return exp(z);
//}

//double rand_gamma(double theta, double kappa) {
//
//	int int_kappa;
//	double frac_kappa;
//
//	int_kappa = (int)kappa;
//	frac_kappa = kappa - (double)int_kappa;
//
//	double u, uu;
//	double b, p, x_frac, x_int;
//	int i;
//
//	/*integer part*/
//	x_int = 0;
//	for (i = 0; i<int_kappa; i++) {
//		x_int += -log(Uniform()); // add expnential random number with mean 1
//	}
//
//	/*fractional part*/
//	if (fabs(frac_kappa) < 0.01) x_frac = 0;
//
//	else {
//		b = (exp(1.0) + frac_kappa) / exp(1.0);
//		while (1) {
//
//			u = Uniform();
//			p = b*u;
//
//			uu = Uniform();
//
//			if (p <= 1.0) {
//				x_frac = pow(p, 1.0 / frac_kappa);
//				if (uu <= exp(-x_frac)) break;
//			}
//
//			else {
//				x_frac = -log((b - p) / frac_kappa);
//				if (uu <= pow(x_frac, frac_kappa - 1.0)) break;
//			}
//
//		}
//	}
//
//	return (x_int + x_frac)*theta;
//}
int PotatoCoinGet(void)
{
	return nCoinCount;
}

//ビルボードのポインタ
Billboard *GetBillboard(void)
{
	return &g_aBillboard[0];
}