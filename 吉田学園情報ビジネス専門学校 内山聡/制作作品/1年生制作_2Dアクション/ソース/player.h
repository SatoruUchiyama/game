#pragma once
#ifndef _POLYGON_H_
#define _POLYGON_H_


typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 posold;			//�O��̈ʒu
	D3DXVECTOR3 move;
	float fwidth;				//��
	float Height;				//����
	int nType;
	int nCounterAnim;
	int nPattenAnim;
	bool bJunp;
	int nDirectanMove;
	bool bUse;
}Player;


void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
//void SetPlayer(float fwidth, float Height, int nType);
void DrawPlayer(void);
Player *GetPlayer(void);
#endif // !_POLYGON_H_

