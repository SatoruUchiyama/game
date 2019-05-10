//=========================================================================================================================
//
// ポリゴンの処理 [polygon.cpp]
// Author : satoru utiyama
//
//=========================================================================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "meshWall.h"
#include "model.h"
#include "enemy.h"
//#include "sound.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
D3DXVECTOR2 g_titlemain;
int PotatoColor;
int ChangePotatoColor;
int g_nCountTimer2 = 0;
//マクロ定義
#define TITLE_TEXTURE_NAME ""				//テクスチャーの名前
#define TITLE_POS_X (0)					//
#define TITLE_POS_Y (0)					//
#define TITLE_WIDTH (SCREEN_WIDTH)			//
#define TITLE_HEIGHT (SCREEN_HEIGHT)		//




void InitTitle(void)
{

	PotatoColor = 255;
	ChangePotatoColor = 5;
	g_titlemain = D3DXVECTOR2(640, -300);
	//	int nCount;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//textureの読み込み
	//D3DXCreateTextureFromFile(pDevice, "date\\TEXTURE\\resize-img7.jpg", &g_pTextureTitle[0]);
	//textureの読み込み
	D3DXCreateTextureFromFile(pDevice, "date\\TEXTURE\\press_enter1.png", &g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice, "date\\TEXTURE\\ボブタイトル.png", &g_pTextureTitle[1]);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL);

	VERTEX_2D *pVtx;

	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);


	/*pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;*/

	pVtx[0].pos = D3DXVECTOR3(640 - 100, 640 - 30, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(640 + 100, 640 - 30, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(640 - 100, 640 + 30, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(640 + 100, 640 + 30, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	pVtx[0].pos = D3DXVECTOR3(g_titlemain.x - 400, g_titlemain.y - 250, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_titlemain.x + 400, g_titlemain.y - 250, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_titlemain.x - 400, g_titlemain.y + 250, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_titlemain.x + 400, g_titlemain.y + 250, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffTitle->Unlock();

	// カメラの初期化処理
	InitCamera();
	// ライトの初期化処理
	InitLight();
	//床の初期化処理
	InitMeshField();
	InitMeshWall();
	InitModel();
	InitEnemy();

	SetModel(D3DXVECTOR3(-60.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
	SetModel(D3DXVECTOR3(-60.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
	SetModel(D3DXVECTOR3(30.0f, -30.0f, -100.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), 2);
	SetModel(D3DXVECTOR3(-60.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);

	//SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);

}
void UninitTitle(void)
{
	int nCount;
	for (nCount = 0; nCount < 2; nCount++)
	{
		if (g_pTextureTitle[nCount] != NULL)
		{
			g_pTextureTitle[nCount]->Release();
			g_pTextureTitle[nCount] = NULL;
		}

	}
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
	// カメラの初期化処理
	UninitCamera();
	// ライトの初期化処理
	UninitLight();
	//床の初期化処理
	UninitMeshField();
	UninitMeshWall();
	UninitModel();
	UninitEnemy();
}
void UpdateTitle(void)
{

	VERTEX_2D *pVtx;
	//	int nCount;
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	

	PotatoColor -= ChangePotatoColor;

	if (PotatoColor < 50 || PotatoColor >= 255)
	{
		ChangePotatoColor *= -1;
	}


	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, PotatoColor);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, PotatoColor);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, PotatoColor);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, PotatoColor);

	pVtx += 4;


	if (300 >= g_titlemain.y)
	{
		g_titlemain.y += 10;
	}

	pVtx[0].pos = D3DXVECTOR3(g_titlemain.x - 400, g_titlemain.y - 250, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_titlemain.x + 400, g_titlemain.y - 250, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_titlemain.x - 400, g_titlemain.y + 250, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_titlemain.x + 400, g_titlemain.y + 250, 0.0f);

	g_pVtxBuffTitle->Unlock();
	g_nCountTimer2++;
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		TITLE_PIKARI;

		//PlaySound(SOUND_LABEL_SE_POTATO4);
		SetFade(MODE_TUTORIAL);
	}
	else if (g_nCountTimer2 % 300 == 0)
	{
		SetFade(MODE_RANKING);
	}
	// カメラの初期化処理
	UpdateCamera();
	// ライトの初期化処理
	UpdateLight();
	//床の初期化処理
	UpdateMeshField();

	UpdateMeshWall();

	UpdateModel();
	UpdateEnemy();
}
void DrawTitle(void)
{
	//床の初期化処理
	DrawMeshField();
	DrawMeshWall();
	DrawModel();
	SetCamera(CAMERASTATE_TAITLE);

	int nCount;
	LPDIRECT3DDEVICE9  pDevice;
	pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < 2; nCount++)
	{
		pDevice->SetTexture(0, g_pTextureTitle[nCount]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);

	}
}