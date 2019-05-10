#pragma once

#ifndef _GAME_H_
#define _GAME_H_



typedef enum
{
	GAMESTATE_NONE=0,
	GAMESTATE_NORMAL,
	GAMESTATE_END,
	GAMESTATE_CHAN,
	GAMESTATE_MAX
}GAMESTATE;

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
#endif // !_POLYGON_H_