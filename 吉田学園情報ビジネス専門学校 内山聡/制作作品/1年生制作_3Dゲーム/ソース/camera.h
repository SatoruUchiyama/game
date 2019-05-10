//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// カメラの構造体
//*****************************************************************************
typedef enum
{
	CAMERASTATE_NONE = 0,
	CAMERARASTATE_GAME,
	CAMERASTATE_TAITLE,
	CAMERASTATE_MAX
}CameraEx;
typedef struct
{
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posVDest;
	D3DXVECTOR3 posR;
	D3DXVECTOR3 posRDest;
	D3DXVECTOR3 vecU;
	float fAngle;
	float fLength;
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
	int typ;
}Camera;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(CameraEx CameraEx);
Camera *GetCamera(void);

#endif
