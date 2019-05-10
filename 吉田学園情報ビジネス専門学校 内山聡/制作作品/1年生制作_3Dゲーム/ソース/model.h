//=============================================================================
//
// モデル処理 [model.h]
// Author : 
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

#define POLYGON_MODEL			(25)
typedef enum
{
	MODEL_NOMAL = 0,		//
	MODEL_EXPLOSION,
	MODEL_RESURRECTION,		//乗ると動く床
	//MODEL_RESURRECTIONSMOKE,
	//MODEL_BULLET,
	MODEL_MAX
}MODELTYPE;
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posDest;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;
	D3DXVECTOR3 life;
	DWORD g_nNumMatModel = 0;
	int Type;
	MODELTYPE ModelType;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 g_VtxMinModel;
	D3DXVECTOR3 g_VtxMaxModel;
	LPD3DXBUFFER g_pBuffMatModel = NULL;
	LPD3DXMESH g_pMeshModel[POLYGON_MODEL] = {};
	//	D3DXMATRIX mtxView;
	int g_nIdxShadow;
	bool bUse;
}Model;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int Type);
#endif
