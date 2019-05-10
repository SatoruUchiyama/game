//=============================================================================
//
// 弾処理 [bullet.h]
// Author :
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

typedef enum
{
	BLOCKTYPE_NOMAL = 0,			//
	BLOCKTYPE_JUMP,
	BLOCKTYPE_VELUTOKONNBERA,		//乗ると動く床
	BLOCKTYPE_MARUTA,
	BLOCKTYPE_BOU,
	BULLETTYPE_MAX
}BLOCKTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fwidth;
	float Height;
	int nType;
	BLOCKTYPE BrockType;
	bool bUse;
	
} Block;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 Pos, float fwidth, float Height, int nType);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);

/*//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BLOCK (128)		//弾の最大数*/

#endif
