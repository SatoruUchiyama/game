//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"


typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fwidth;
	float Height;
	int g_Score;
	bool bUse;

} Score;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(D3DXVECTOR3 Pos, float fwidth, float Height);
void AddScore(int nValue);

#endif
