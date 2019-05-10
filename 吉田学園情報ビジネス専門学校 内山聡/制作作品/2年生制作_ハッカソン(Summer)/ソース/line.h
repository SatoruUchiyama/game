//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// ���C������ [line.h]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"

//*****************************************************************************
// �\����
//*****************************************************************************
// ���C���̏��
typedef struct
{
	int nIdxLine;				// ���̎g�p�ԍ�
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 posStart;		// �J�n�ʒu
	D3DXVECTOR3 posEnd;			// �I���ʒu
	D3DXCOLOR col;				// �J���[
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	bool bUse;					// �g�p���Ă��邩�ǂ���
}Line;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitLine(void);
void UninitLine(void);
void UpdateLine(void);
void DrawLine(void);

void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 posStart, D3DXVECTOR3 posEnd, D3DXCOLOR col,int nIdxLine);
int SetColisionLine(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);
int SetColisionLine2(D3DXVECTOR3 pos, float fRadius, float fHeight);
void SetPositionLine(int nIdxLine,D3DXVECTOR3 pos);
void DeleteLine(int nIdxLine);
#endif
