//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"


typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fwidth;
	float Height;
	int nRanking;
	bool bUse;

} Ranking;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
//void SetRanking(D3DXVECTOR3 Pos, float fwidth, float Height);
void AddRanking(int nValue);
Ranking *GetRanking(void);
#endif
#pragma once
#pragma once
