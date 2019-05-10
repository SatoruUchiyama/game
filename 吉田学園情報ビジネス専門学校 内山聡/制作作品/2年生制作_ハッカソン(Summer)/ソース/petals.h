//=============================================================================
//
// �Ԃт珈�� [petals.h]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#ifndef _PETALS_H_
#define _PETALS_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 angle;
	D3DXCOLOR col;
	float fRadius;
	bool bUse;
	int nType;
	bool bMoveAngle;		// �c�̊ɋ}
	bool bMoveWidth;		// ���̂����
	D3DXMATRIX mtxWorld;
}PETALS;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPetals(void);
void UninitPetals(void);
void UpdatePetals(void);
void DrawPetals(void);

void SetPetals(D3DXVECTOR3 pos, int nNumber);
#endif