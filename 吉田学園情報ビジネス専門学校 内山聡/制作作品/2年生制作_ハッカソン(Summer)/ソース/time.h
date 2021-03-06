//=============================================================================
//
// タイム処理 [time.h]
// Author : 佐藤亮太
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"       // メイン情報のヘッダー

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TIME_SET			(2)								// 2つでワンセット
#define MAX_TIME_SET_TYPE	(3)								// ワンセットの種類の数

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef enum
{// タイムの種類
	TimeType_MilliSecond = 0,			// ミリ秒
	TimeType_Second,					// 秒
	TimeType_Minute,					// 分
	TimeType_MAX
}TimeType;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);

int GetTime(void);				// 現在のタイムを返す
void ResetTime(void);			// タイムを初期化する
#endif
