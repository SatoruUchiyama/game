
//=============================================================================
//
// モデル処理 [model.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

#define POLYGON_ENEMY			(9)
typedef enum
{
	ENEMY_NOMAL = 0,			//
	ENEMY_EXPLOSION,
	ENEMY_RESURRECTION,		//乗ると動く床
							//ENEMY_RESURRECTIONSMOKE,
							//ENEMY_BULLET,
							ENEMY_MAX
}ENEMYTYPE;
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posDest;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;
	D3DXVECTOR3 life;
	DWORD g_nNumMatEnemy = 0;
	int Type;
	ENEMYTYPE EnemyType;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 g_VtxMinEnemy;
	D3DXVECTOR3 g_VtxMaxEnemy;
	LPD3DXBUFFER g_pBuffMatEnemy = NULL;
	LPD3DXMESH g_pMeshEnemy[POLYGON_ENEMY] = {};
	//	D3DXMATRIX mtxView;
	int g_nIdxShadow;
	bool bUse;
}Enemy;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int Type);
#endif
