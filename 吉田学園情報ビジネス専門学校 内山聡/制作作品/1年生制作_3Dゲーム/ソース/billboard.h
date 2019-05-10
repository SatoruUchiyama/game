//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : 
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	int g_nIdxShadow;
	bool bUse;
}Billboard;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col);
int PotatoCoinGet(void);
Billboard *GetBillboard(void);
#endif
#pragma once
