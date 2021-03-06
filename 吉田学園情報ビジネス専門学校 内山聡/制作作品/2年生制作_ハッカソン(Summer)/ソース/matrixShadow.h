//=========================================================================================================================
//
// 投影処理 [matrixmatrixShadow.h]
// Author :
//
//=========================================================================================================================
#ifndef _MATRIXSHADOW_H_
#define _MATRIXSHADOW_H_

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitmatrixShadow(void);																		// 影初期化処理
void UninitmatrixShadow(void);																		// 影終了処理
void UpdatematrixShadow(void);																		// 影更新処理
void DrawmatrixShadow(void);																		// 影描画処理
void SetmatrixShadow(D3DXMATRIX &mtxWorld, LPD3DXMESH &pMesh, DWORD &nNumMat, D3DXVECTOR3 pos);		// 影の設定
D3DXVECTOR3 CheckShadowPosition(D3DXVECTOR3 pos);													// 影を投影する位置を調べる

#endif
