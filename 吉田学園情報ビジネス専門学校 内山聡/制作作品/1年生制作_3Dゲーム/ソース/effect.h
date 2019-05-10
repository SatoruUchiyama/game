//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

typedef enum
{
	EFFECTTYPE_NOMAL = 0,			//
	EFFECTTYPE_EXPLOSION,
	EFFECTTYPE_RESURRECTION,		//���Ɠ�����
	EFFECTTYPE_RESURRECTIONSMOKE,
	EFFECTTYPE_BULLET,
	EFFECTTYPE_MAX
}EFFECTTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	EFFECTTYPE Type;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	D3DXCOLOR col;			// �F
	int nSetMax;
	int nRadius;
	int nTypeTx;
	float fRadius;			// ���a(�傫��)
	int nLife;				// �\������(����)
	bool bUse;				// �g�p���Ă��邩�ǂ���
}Effect;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius,int nLife, int nTypeTx);

void SetParticleEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx);

void SetSmokeEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx);

#endif
