#pragma once
//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : 
//
//=============================================================================
#ifndef _BALLET_H_
#define _BALLET_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	D3DXVECTOR3 life;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	int g_nIdxShadow;
	bool bUse;
}Ballet;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBallet(void);
void UninitBallet(void);
void UpdateBallet(void);
void DrawBallet(void);
void SetBallet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move);
void DeleteBallet(int nBallet);

#endif
#pragma once
