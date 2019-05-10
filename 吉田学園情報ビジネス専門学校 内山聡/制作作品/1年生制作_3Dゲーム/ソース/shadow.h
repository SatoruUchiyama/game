//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : 
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
//*****************************************************************************
// 影の構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Shadow;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
void DeleteShadow(int nIdxShadow2);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif
#pragma once
