//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �G�t�F�N�g�̎��
typedef enum
{
	EFFECTTYPE_WEAK_ATTACK = 0,		// ��U��
	EFFECTTYPE_STRONG_ATTACK,		// ���U��
	EFFECTTYPE_AKR,					// �d���wA�EK�ER�x
	EFFECTTYPE_3DBULLET,			// ���Ă�����
	EFFECTTYPE_MAX
}EFFECTTYPE;

// �e�N�X�`���̏��
typedef struct
{
	char *pFilename;		// �e�N�X�`����
}EffectTexture;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rot;		// ����
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXCOLOR col;			// �F
	float fRadius;			// ���a(�傫��)
	int nLife;				// �\������(����)
	int nType;				// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
} EFFECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, int nType);
#endif
