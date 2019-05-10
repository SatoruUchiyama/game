//=============================================================================
//
// モデル処理 [model.h]
// Author : 
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

#define POLYGON_ITEM			(1)
typedef enum
{
	ITEM_NOMAL = 0,			//
	ITEM_EXPLOSION,
	ITEM_RESURRECTION,		//乗ると動く床
							//ITEM_RESURRECTIONSMOKE,
							//ITEM_BULLET,
	ITEM_MAX
}ITEMTYPE;
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posDest;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;
	D3DXVECTOR3 life;
	DWORD g_nNumMatItem = 0;
	int Type;
	ITEMTYPE ItemType;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 g_VtxMinItem;
	D3DXVECTOR3 g_VtxMaxItem;
	LPD3DXBUFFER g_pBuffMatItem = NULL;
	LPD3DXMESH g_pMeshItem[POLYGON_ITEM] = {};
	//	D3DXMATRIX mtxView;
	int g_nIdxShadow;
	bool bUse;
}Item;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
//bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int Type);
#endif
#pragma once
