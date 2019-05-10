//=============================================================================
//
// ゲーム画面 [game.cpp]
// Author : storu utiyama
//
//
//	1ボブの首を動かす
//	2透明のアイテムをランダム移動
//	3ボブの目線をアイテムに向ける
//	
//	
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "ballet.h"
#include "meshField.h"
#include "meshWall.h"
#include "meshcylinder.h"
#include "explosion.h"
#include "effect.h"
#include "player.h"
#include "fade.h"
#include "pause.h"
#include "score.h"
#include "time.h"
#include "enemy.h"
#include "item.h"
//=============================================================================
// グローバル変数
//=============================================================================
GAMESTATE g_gamestate = GAMESTATE_NONE;
int nCounterGameState;
bool g_bPause;
//=============================================================================
// 初期化処理
//=============================================================================
void InitGame(void)
{
	InitScore();				//スコアの初期化処理
	InitTime();					//
	InitCamera();				// カメラの初期化処理
	InitLight();				//ライトの初期化処理	
	InitShadow();				//影の初期化処理
	InitMeshField();			//床の初期化処理
	InitMeshWall();				//壁の初期化処理
	//InitMeshCylinder();		//円柱の初期化処理
	//InitPolygon();			//ポリゴンの初期化処理
	//InitWall();				//壁の初期化処理
	InitExplosion();			//爆発の初期化処理
	InitBillboard();			//ビルボード(木)の初期化処理
	InitEffect();				//エフェクトの
	InitBallet();				//弾の初期化処理
	InitPause();				//ポーズ画面の初期化処理処理
	InitModel();
	InitItem();
	InitEnemy();
	InitModel();
	InitPlayer();

	//						壁をセット
	//SetWall(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	//SetWall(D3DXVECTOR3(0.0, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.0f, 0.0f));
	//SetWall(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//						ビルボードのセット
	/*SetBillboard(D3DXVECTOR3(800.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetBillboard(D3DXVECTOR3(750.0f, 0.0f, -160.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, -170.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));*/
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, -850.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	//						モデルのセット
	SetModel(D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetModel(D3DXVECTOR3(-60.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	SetModel(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
	//SetModel(D3DXVECTOR3(-100.0f, 0.0f, 80.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(50.0f, 0.0f, -160.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	
	//宝石
	SetModel(D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(800.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(650.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(450.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(250.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);

	SetModel(D3DXVECTOR3(300.0f, 0.0f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(800.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(650.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(450.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(250.0f, 0.0f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);

	//つる
	SetModel(D3DXVECTOR3(0.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(200.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(400.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(600.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(800.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);

	SetModel(D3DXVECTOR3(0.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, 16.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(200.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, 16.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(400.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, 16.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(600.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, 16.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(800.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, 16.0f, 0.0f), 3);



	SetItem(D3DXVECTOR3(50.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	//						敵のセット
	/*SetEnemy(D3DXVECTOR3(600.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(550.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(450.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(100.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 4);
	*/
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 4);

	SetEnemy(D3DXVECTOR3(830.0f, 0.0f, -850.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(-50.0f, 0.0f, -850.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(830.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(-50.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 4);

	//
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 550, SCREEN_HEIGHT / 2 - 350, 0.0f), 30.0f, 40.0f);
	//
	Settime(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 350, 0.0f), 30.0f, 40.0f);
	
	
	GAMESTATE g_gamestate = GAMESTATE_NORMAL;
	nCounterGameState = 0;
	g_bPause = false;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	//
	//スコアの終了処理
	UninitScore();
	//
	UninitTime();
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// 床の生成の終了処理
	UninitMeshField();

	// 壁の生成の終了処理
	UninitMeshWall();

	// 円柱の終了処理
	//UninitMeshCylinder();

	
	// ポリゴンの終了処理
	//UninitPolygon();

	// 影の終了処理
	UninitShadow();

	//爆発の処理
	UninitExplosion();

	// ビルボード(木)の終了処理
	UninitBillboard();

	//エフェクトの処理
	UninitEffect();

	// 弾の終了処理
	UninitBallet();

	// プレイヤーの終了処理
	UninitModel();

	UninitItem();
	//
	UninitEnemy();
	UninitPlayer();

	UninitPause();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}
	
	//
	if (g_bPause == false)
	{  
		UpdateScore();			//スコアの更新処理
		UpdateTime();			//タイムの更新処理
		UpdateCamera();			//カメラの更新処理
		UpdateLight();			//ライトの更新処理
		UpdateMeshField();		//床の生成の更新処理
		UpdateMeshWall();		//壁の生成の更新処理
		UpdateMeshCylinder();	//円柱の生成の更新処理
		//UpdatePolygon();		//ポリゴンの更新処理
		//UpdateWall();			//壁の更新処理
		UpdateShadow();			//影の生成の更新処理
		UpdateExplosion();		//爆発の更新処理
		UpdateBillboard();		//ビルボード(木)の更新処理
		UpdateEffect();			//エフェクトの更新処理
		UpdateBallet();			//弾の更新処理
		UpdateModel();			//プレイヤーの更新処理
		UpdateItem();			//アイテムの更新処理
		UpdateEnemy();			//敵の更新処理
		UpdatePlayer();			//プレイヤーの更新処理

		//========================
		//ゲームステート
		//========================
		switch (g_gamestate)
		{
		case GAMESTATE_NORMAL:
			break;
		case GAMESTATE_END:
			nCounterGameState++;//フェードカウント
			if (nCounterGameState >= 60)//フェードする時間
			{
				g_gamestate = GAMESTATE_NORMAL;
				SetFade(MODE_RESULT);
			}
		}
	}
	else
	{
		UpdatePause();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	//
	SetCamera(CAMERARASTATE_GAME);

	DrawScore();
	DrawTime();
	DrawMeshField();
	DrawMeshWall();
	//DrawPolygon();// ポリゴンの描画処理
	//DrawWall();
	DrawShadow();
	DrawModel();
	DrawItem();
	DrawEnemy();
	DrawExplosion();
	DrawEffect();
	DrawPlayer();
	DrawBallet();
	DrawBillboard();
	//DrawMeshCylinder();
	//DrawPause();

	if (g_bPause == true)
	{
		DrawPause();
	}
}

void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	//nCounterGameState = 0;
}
GAMESTATE GetGameState(void)
{
	return g_gamestate;
}