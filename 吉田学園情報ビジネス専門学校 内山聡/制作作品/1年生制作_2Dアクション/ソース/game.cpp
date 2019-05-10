//=============================================================================
//
// ゲーム画面 [game.cpp]
// Author : storu utiyama
//
//=============================================================================

#include "main.h"
#include "bg.h"
#include "input.h"
#include "block.h"
#include "player.h"
#include "item.h"
#include "game.h"
#include "score.h"
#include "fade.h"
#include "time.h"
#include "pause.h"
#include "sound.h"
#include "explosion.h"

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
	g_bPause = false;
	
	InitBG();
	InitExplosion();
	InitScore();
	InitTime();
	InitBlock();
	InitItem();
	InitPause();
	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 0.0f), 200.0f, 30.0f, 0);

	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 100, 0.0f), 200.0f, 30.0f, 3);		// ブロック　４

	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 - 100, 0.0f), 90.0f, 500.0f, 4);		// ブロック　５
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450, SCREEN_HEIGHT / 2 - 300, 0.0f), 90.0f, 405.0f, 4);		// ブロック　５

	

	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 280, SCREEN_HEIGHT / 2 + 100, 0.0f), 50.0f, 50.0f, 0);		// ブロック　２
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 330, SCREEN_HEIGHT / 2 + 100, 0.0f), 50.0f, 50.0f, 0);		// ブロック　３
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 380, SCREEN_HEIGHT / 2 + 100, 0.0f), 50.0f, 50.0f, 0);		// ブロック　４
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 430, SCREEN_HEIGHT / 2 + 100, 0.0f), 50.0f, 50.0f, 0);		// ブロック　５
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 480, SCREEN_HEIGHT / 2 + 100, 0.0f), 50.0f, 50.0f, 0);		// ブロック　６
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 530, SCREEN_HEIGHT / 2 + 100, 0.0f), 50.0f, 50.0f, 0);		// ブロック　７
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 580, SCREEN_HEIGHT / 2 + 100, 0.0f), 50.0f, 50.0f, 0);		// ブロック　８
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 630, SCREEN_HEIGHT / 2 + 100, 0.0f), 50.0f, 50.0f, 0);		// ブロック　９

	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2 - 175, 0.0f), 50.0f, 50.0f, 0);		// ブロック　３
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - 175, 0.0f), 50.0f, 50.0f, 0);		// ブロック　３
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 175, 0.0f), 50.0f, 50.0f, 0);		// ブロック　３
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 175, 0.0f), 50.0f, 50.0f, 0);		// ブロック　３
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 175, 0.0f), 50.0f, 50.0f, 0);		// ブロック　３

	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 450, SCREEN_HEIGHT / 2 - 225, 0.0f), 50.0f, 50.0f, 0);		// ブロック　３
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 - 275, 0.0f), 50.0f, 50.0f, 0);		// ブロック　３

	

	//SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50, 0.0f), 200.0f, 30.0f, 3);		// ブロック　４


	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 450, SCREEN_HEIGHT / 2 + 150, 0.0f), 50.0f, 50.0f, 0);		// ブロック　４
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2 + 150, 0.0f), 50.0f, 50.0f, 0);		// ブロック　４
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 + 150, 0.0f), 50.0f, 50.0f, 0);		// ブロック　４
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 + 150, 0.0f), 50.0f, 50.0f, 0);		// ブロック　４
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 + 150, 0.0f), 50.0f, 50.0f, 0);		// ブロック　４
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 150, 0.0f), 50.0f, 50.0f, 0);		// ブロック　４

	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 230, SCREEN_HEIGHT / 2 + 100, 0.0f), 50.0f, 50.0f, 0);		// ブロック　５
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 230, SCREEN_HEIGHT / 2 + 150, 0.0f), 50.0f, 50.0f, 0);		// ブロック　５
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 230, SCREEN_HEIGHT / 2 + 200, 0.0f), 50.0f, 50.0f, 0);		// ブロック　５
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 230, SCREEN_HEIGHT / 2 + 250, 0.0f), 50.0f, 50.0f, 0);		// ブロック　５
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 230, SCREEN_HEIGHT / 2 + 300, 0.0f), 50.0f, 50.0f, 0);		// ブロック　５

	

	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 650, SCREEN_HEIGHT / 2 - 300, 0.0f), 30.0f, 30.0f, 0);		// ブロック　６
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 620, SCREEN_HEIGHT / 2 - 300, 0.0f), 30.0f, 30.0f, 0);		// ブロック　６
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 590, SCREEN_HEIGHT / 2 - 300, 0.0f), 30.0f, 30.0f, 0);		// ブロック　６
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 560, SCREEN_HEIGHT / 2 - 300, 0.0f), 30.0f, 30.0f, 0);		// ブロック　６
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 530, SCREEN_HEIGHT / 2 - 300, 0.0f), 30.0f, 30.0f, 0);		// ブロック　６

	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250, SCREEN_HEIGHT / 2 - 300, 0.0f), 400.0f, 30.0f, 2);		// ブロック　７

	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250, SCREEN_HEIGHT / 2 - 550, 0.0f), 50.0f, 180.0f, 0);		// ブロック　８
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250, SCREEN_HEIGHT / 2 - 500, 0.0f), 50.0f, 50.0f, 0);		// ブロック　８
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250, SCREEN_HEIGHT / 2 - 450, 0.0f), 50.0f, 50.0f, 0);		// ブロック　８
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250, SCREEN_HEIGHT / 2 - 400, 0.0f), 50.0f, 50.0f, 0);		// ブロック　８
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250, SCREEN_HEIGHT / 2 - 350, 0.0f), 50.0f, 50.0f, 0);		// ブロック　８

	SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 1280, SCREEN_HEIGHT - 30, 0.0f), 1280.0f, 30.0f, 2);			// ブロック　９
	SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 + 200, 0.0f), 70.0f, 30.0f, 1);		// ブロック　１
	


	//			コイン　設定
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, 0.0f));		//横　　縦			0
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 + 120, 0.0f));					//	1
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 120, 0.0f));					//	2
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 + 140, 0.0f));				//	3
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 140, 0.0f));				//	4

	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300 , SCREEN_HEIGHT / 2 - 250, 0.0f));		//横　　縦			0
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 350 , SCREEN_HEIGHT / 2 - 220, 0.0f));					//	1
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 250 , SCREEN_HEIGHT / 2 - 280, 0.0f));					//	2
	//SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 400 , SCREEN_HEIGHT / 2 - 220, 0.0f));				//	3
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200 , SCREEN_HEIGHT / 2 - 280, 0.0f));				//	4

	//SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 -300 + 270, SCREEN_HEIGHT / 2 - 250, 0.0f));		
	//SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 -350 + 270, SCREEN_HEIGHT / 2 - 220, 0.0f));			
	//SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 -250 + 270, SCREEN_HEIGHT / 2 - 280, 0.0f));			
	//SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 -400 + 270, SCREEN_HEIGHT / 2 - 190, 0.0f));			
	//SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 -200 + 270, SCREEN_HEIGHT / 2 - 310, 0.0f));		

	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 - 200, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 250, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 , 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 0.0f));



	//SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 + 50, 0.0f));					//	5

	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 350, SCREEN_HEIGHT / 2 + 200, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 + 200, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450, SCREEN_HEIGHT / 2 + 200, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 200, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 550, SCREEN_HEIGHT / 2 + 200, 0.0f));

	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 350, SCREEN_HEIGHT / 2 + 250, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 + 250, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450, SCREEN_HEIGHT / 2 + 250, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 250, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 550, SCREEN_HEIGHT / 2 + 250, 0.0f));

	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 350, SCREEN_HEIGHT / 2 + 300, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 + 300, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450, SCREEN_HEIGHT / 2 + 300, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 300, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 550, SCREEN_HEIGHT / 2 + 300, 0.0f));


	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 350, SCREEN_HEIGHT / 2 - 150, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 - 150, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 150, 0.0f));
	
	
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 350, SCREEN_HEIGHT / 2 - 100, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 - 100, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f));
	
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 350, SCREEN_HEIGHT / 2 - 50, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 - 50, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 50, 0.0f));

	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 590, SCREEN_HEIGHT / 2 - 220, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 540, SCREEN_HEIGHT / 2 - 220, 0.0f));

	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 350, SCREEN_HEIGHT / 2 - 300, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 - 300, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450, SCREEN_HEIGHT / 2 - 300, 0.0f));		//右上のコイン
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 - 300, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 550, SCREEN_HEIGHT / 2 - 300, 0.0f));

	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 580, SCREEN_HEIGHT / 2 - 150, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 580, SCREEN_HEIGHT / 2 - 200, 0.0f));
	SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 + 580, SCREEN_HEIGHT / 2 - 100, 0.0f));


	SetScore(D3DXVECTOR3 (SCREEN_WIDTH / 2 + 550, SCREEN_HEIGHT / 2 - 350, 0.0f), 30.0f, 40.0f);

	Settime(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 350, 0.0f), 30.0f, 40.0f);

	InitPlayer();
	GAMESTATE g_gamestate = GAMESTATE_NORMAL;
	nCounterGameState = 0;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	
	UninitBG();
	UninitExplosion();
	UninitPlayer();
	UninitBlock();
	UninitItem();
	UninitScore();
	UninitTime();
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
		PlaySound(SOUND_LABEL_SE_POTATO2);
	}

	//
	if (g_bPause == false)
	{
		
		UpdateBG();
		UpdateExplosion();
		//
		UpdatePlayer();
		UpdateBlock();
		UpdateItem();
		UpdateScore();
		UpdateTime();
		switch (g_gamestate)
		{
		case GAMESTATE_NORMAL:
			break;
		case GAMESTATE_END:
			nCounterGameState++;
			if (nCounterGameState >= 60)
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
	
	DrawBG();
	DrawExplosion();
	DrawBlock();
	DrawItem();
	DrawScore();
	DrawTime();
	DrawPlayer();
	//DrawPause();
	if (g_bPause == true)
	{
		DrawPause();
	}
}

void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
//	nCounterGameState = 0;
}
GAMESTATE GetGameState(void)
{
	return g_gamestate;
}