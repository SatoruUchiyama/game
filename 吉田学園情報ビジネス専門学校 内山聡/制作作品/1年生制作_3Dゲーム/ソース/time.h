//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"


typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fwidth;
	float Height;
	int nTime;
	bool bUse;

} Time;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void Settime(D3DXVECTOR3 Pos, float fwidth, float Height);
void AddTime(int nValue);
Time *GetTime(void);
#endif
#pragma once
