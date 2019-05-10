//=============================================================================
//
// �J�������� [camera.cpp]
// Author : 
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "model.h"
#include "player.h"
#include "title.h"
#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_FRAME				(10)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_Camera;
int g_nCount = MAX_FRAME;

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	g_Camera.posV = D3DXVECTOR3(0.0f, 85.0f, -200.0f);
	g_Camera.posR = D3DXVECTOR3(0.0f, 45.0f, 0.0f);
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	
	g_Camera.typ = CAMERASTATE_NONE;
	g_Camera.fLength = g_Camera.posR.z - g_Camera.posV.z;
	g_Camera.fAngle = atan2f(g_Camera.posV.x - g_Camera.posR.x, g_Camera.posV.z - g_Camera.posR.z);
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	Player *pPlayer;

	pPlayer = GetPlayer();

	float fSabun;

	if (g_Camera.typ == CAMERARASTATE_GAME) 
	{
		//----------------------------------------------
		//	������ (Q)
		//----------------------------------------------
		/*if (GetKeyboardPress(DIK_Q) == true)
		{
			g_Camera.fAngle -= 0.05f;
			g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.fAngle)*g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.fAngle)*g_Camera.fLength;
		}*/
		//----------------------------------------------
		//	�E���� (E)
		//----------------------------------------------
		/*if (GetKeyboardPress(DIK_E) == true)
		{
			g_Camera.fAngle += 0.05f;
			g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.fAngle)*g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.fAngle)*g_Camera.fLength;
		}*/
		//----------------------------------------------
		//	�����_�𒆐S�ɉE���� (Z)
		//----------------------------------------------
		if (GetKeyboardPress(DIK_Z) == true)
		{
			g_Camera.fAngle += 0.05f;

			g_Camera.posVDest.x = g_Camera.posRDest.x - sinf(g_Camera.fAngle)*g_Camera.fLength;
			g_Camera.posVDest.z = g_Camera.posRDest.z - cosf(g_Camera.fAngle)*g_Camera.fLength;
		}
		//----------------------------------------------
		//	�����_�𒆐S�ɍ����� (C)
		//----------------------------------------------
		if (GetKeyboardPress(DIK_C) == true)
		{
			g_Camera.fAngle -= 0.05f;
			g_Camera.posVDest.x = g_Camera.posRDest.x - sinf(g_Camera.fAngle)*g_Camera.fLength;
			g_Camera.posVDest.z = g_Camera.posRDest.z - cosf(g_Camera.fAngle)*g_Camera.fLength;
		}
		//----------------------------------------------
		//	���ɍs��
		//----------------------------------------------
		//if (GetKeyboardPress(DIK_B) == true)
		//{

		//	//g_Camera.posV.y -= 0.5f;
		//	g_Camera.posR.y -= 0.5f;
		//}
		//----------------------------------------------
		//	��ɍs��
		//----------------------------------------------
		//if (GetKeyboardPress(DIK_V) == true)
		//{
		//	//g_Camera.posV.y += 0.5f;
		//	g_Camera.posR.y += 0.5f;
		//}

		//----------------------------------------------
		//	
		//----------------------------------------------
		/*if (GetKeyboardPress(DIK_N) == true)
		{
			g_Camera.posV.y -= 0.5f;
			g_Camera.posR.y -= 0.5f;
		}*/
		//----------------------------------------------
		//	
		//----------------------------------------------
		/*if (GetKeyboardPress(DIK_M) == true)
		{
			g_Camera.posV.y += 0.5f;
			g_Camera.posR.y += 0.5f;
		}*/

		if (pPlayer->move.z < 0.0001f && pPlayer->move.x < 0.0001f && pPlayer->move.y < 0.0001f &&pPlayer->move.z > -0.0001f && pPlayer->move.x > -0.0001f && pPlayer->move.y > -0.0001f)
		{

			if (g_nCount > 0)
			{
				g_nCount--;
			}
			else if (g_nCount == 0)
			{
				//--------------------------------------------------------------------------------------------
				// �J�����̈ړ�����
				//--------------------------------------------------------------------------------------------
				if (g_Camera.fAngle > D3DX_PI)
				{
					g_Camera.fAngle -= D3DX_PI*2.0f;
				}
				if (g_Camera.fAngle < -D3DX_PI)
				{
					g_Camera.fAngle += D3DX_PI*2.0f;
				}

				fSabun = (pPlayer->rot.y - g_Camera.fAngle + D3DX_PI);

				if (fSabun > D3DX_PI)
				{
					fSabun -= D3DX_PI*2.0f;
				}
				if (fSabun < -D3DX_PI)
				{
					fSabun += D3DX_PI*2.0f;
				}

				g_Camera.fAngle += fSabun * 0.1f;

				if (g_Camera.fAngle > D3DX_PI)
				{
					g_Camera.fAngle -= D3DX_PI*2.0f;
				}
				if (g_Camera.fAngle < -D3DX_PI)
				{
					g_Camera.fAngle += D3DX_PI*2.0f;
				}


			}

		}
		else
		{
			g_nCount = MAX_FRAME;
		}
		g_Camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y)* 10.0f;
		g_Camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y)* 10.0f;
		g_Camera.posVDest.x = pPlayer->pos.x - sinf(g_Camera.fAngle)* g_Camera.fLength;
		g_Camera.posVDest.z = pPlayer->pos.z - cosf(g_Camera.fAngle)* g_Camera.fLength;

		g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x)* 0.1f;												//�����_
		g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z)* 0.1f;
		g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x)* 0.1f;												//���_
		g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z)* 0.1f;
	}
	if (g_Camera.typ == CAMERASTATE_TAITLE)
	{
			/*g_Camera.fAngle -= 0.05f;
			g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.fAngle)*g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.fAngle)*g_Camera.fLength;*/
		
		//g_Camera.posV = D3DXVECTOR3(0.0f, 50.0f, -70.0f);

		g_Camera.fAngle += 0.01f;
		if (g_Camera.fAngle > D3DX_PI)
		{
			g_Camera.fAngle = -D3DX_PI;
		}
		/*g_Camera.fAngle += 0.05f;
		g_Camera.posVDest.x = g_Camera.posRDest.x - sinf(g_Camera.fAngle)*g_Camera.fLength;
		g_Camera.posVDest.z = g_Camera.posRDest.z - cosf(g_Camera.fAngle)*g_Camera.fLength;*/

		g_Camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y)* 10.0f;
		g_Camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y)* 10.0f;
		g_Camera.posVDest.x = pPlayer->pos.x - sinf(g_Camera.fAngle)* g_Camera.fLength;
		g_Camera.posVDest.z = pPlayer->pos.z - cosf(g_Camera.fAngle)* g_Camera.fLength;

		g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x)* 0.1f;												//�����_
		g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z)* 0.1f;
		g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x)* 0.1f;												//���_
		g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z)* 0.1f;

		g_Camera.posR = D3DXVECTOR3(0.0f, 45.0f, 0.0f);
		
	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(CameraEx CameraEx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	g_Camera.typ = CameraEx;
	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1500.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}

Camera *GetCamera(void)
{
	return &g_Camera;
}