//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : 
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT			(3)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_light[MAX_LIGHT];

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir[MAX_LIGHT];
	int nCount;
	//int nCount2;

	for (nCount = 0; nCount < MAX_LIGHT; nCount++)
	{
		// ���C�g���N���A����
		ZeroMemory(&g_light[nCount], sizeof(D3DLIGHT9));
	
		// ���C�g�̎�ނ�ݒ�
		g_light[nCount].Type = D3DLIGHT_DIRECTIONAL;

	}
		// ���C�g�̊g�U����ݒ�	 ���C�g�̕����̐ݒ�
		//���C�g�P
		g_light[0].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

		//���C�g�P
		g_light[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		vecDir[1] = D3DXVECTOR3(0.0f, -0.8f, 0.4f);

		//���C�g�P
		g_light[2].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);
		vecDir[2] = D3DXVECTOR3(-0.2f, -0.8f, 0.4f);
		
		
		
		

	for (nCount = 0; nCount < MAX_LIGHT; nCount++)
	{

		D3DXVec3Normalize(&vecDir[nCount], &vecDir[nCount]);		//
		g_light[nCount].Direction = vecDir[nCount];					//
		// ���C�g��ݒ肷��
		pDevice->SetLight(nCount, &g_light[nCount]);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCount, TRUE);
	}
	

}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
}

