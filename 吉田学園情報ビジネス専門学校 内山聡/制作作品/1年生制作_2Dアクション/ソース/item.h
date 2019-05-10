//=============================================================================
//
// �e���� [bullet.h]
// Author :
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"



typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	float fwidth;				//��
	float Height;				//����
	int nCntAnimation;			//Animation�J�E���^�[
	int nCntAnimationPattern;	//Animation�p�^�[��
	//ITENTYPE type;			//
	bool bUse;					//�g�p���Ă��邩

} Item;
//*****************************************************************************
// �v���g�^�C�v�錾
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
