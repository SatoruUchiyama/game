//=============================================================================
//
// 変身ゲージ処理 [gauge.h]
// Author : Ishida Takuto
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_GAUGE		(MAX_STAMINA)	// ゲージの上限

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 左上の位置
	D3DXCOLOR col;			// 色
	float fLength;			// バーの長さ
	int nType;				// テクスチャの種類
}Gauge;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGauge(void);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);


void AddSubtractGauge(int nValue);		// ゲージを増減させる
int GetGauge(void);						// ゲージの取得

#endif
