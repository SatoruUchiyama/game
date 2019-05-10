//=============================================================================
//
// 弾処理 [bullet.h]
// Author :
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"



typedef struct
{
	D3DXVECTOR3 pos;			//位置
	float fwidth;				//幅
	float Height;				//高さ
	int nCntAnimation;			//Animationカウンター
	int nCntAnimationPattern;	//Animationパターン
	//ITENTYPE type;			//
	bool bUse;					//使用しているか

} Item;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos);
void CollisionItem(void);
Item *GetItem(void);
int PotatoCoinGet(void);
#endif
