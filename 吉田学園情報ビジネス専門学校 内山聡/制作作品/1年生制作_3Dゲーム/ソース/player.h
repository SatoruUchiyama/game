#pragma once
//=============================================================================
//
// モデル処理 [model.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "model.h"

#define MAX_MODEL			(1)					//パーツ数

typedef struct
{
	LPD3DXMESH pMeshPlayer = NULL;
	LPD3DXBUFFER pBuffMatPlayer = NULL;
	DWORD nNumMatPlayer = 0;
	D3DXMATRIX mtxWorldPlayer;

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nIdxModelParent;
}Model2;
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posDest;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;
	D3DXVECTOR3 posold;			//前回の位置
	D3DXVECTOR3 life;
	D3DXVECTOR3 g_VtxMaxPlayer;
	D3DXVECTOR3 g_VtxMinPlayer;
	D3DXMATRIX mtxWorld;
	Model2 aModel[7];
//	D3DXMATRIX mtxView;
	int g_nIdxShadow;
	bool bUse;
}Player;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
#endif
