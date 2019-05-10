//=============================================================================
//
// ���f������ [model.cpp]
// Author : 
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "ballet.h"
#include "model.h"
#include "fade.h"
#include "billboard.h"
#include "enemy.h"
#include "effect.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ATARI				(890)
#define MAX_ATARI2				(90)

#define MAX_PARTS				(7)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Player g_Player;

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	
	// X�t�@�C���̓ǂݍ���		tanknsu.x		car000.x �Ȃ���2.x	tanknsu.x
	D3DXLoadMeshFromX("date\\model\\����1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBuffMatPlayer, NULL, &g_Player.aModel[0].nNumMatPlayer, &g_Player.aModel[0].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\��1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBuffMatPlayer, NULL, &g_Player.aModel[1].nNumMatPlayer, &g_Player.aModel[1].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\����1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[2].pBuffMatPlayer, NULL, &g_Player.aModel[2].nNumMatPlayer, &g_Player.aModel[2].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\�E��1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[3].pBuffMatPlayer, NULL, &g_Player.aModel[3].nNumMatPlayer, &g_Player.aModel[3].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\���r1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[4].pBuffMatPlayer, NULL, &g_Player.aModel[4].nNumMatPlayer, &g_Player.aModel[4].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\�E�r1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[5].pBuffMatPlayer, NULL, &g_Player.aModel[5].nNumMatPlayer, &g_Player.aModel[5].pMeshPlayer);
	D3DXLoadMeshFromX("date\\model\\�Ȃ���2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[6].pBuffMatPlayer, NULL, &g_Player.aModel[6].nNumMatPlayer, &g_Player.aModel[6].pMeshPlayer);
	// �ʒu�E�����̏����ݒ�				yoroi.x
	g_Player.pos = D3DXVECTOR3(0, 0, 0);
	g_Player.rot = D3DXVECTOR3(0, 0, 0);
	g_Player.move = D3DXVECTOR3(0, 0, 0.0f);
	g_Player.posold = D3DXVECTOR3(0, 0, 0);
	g_Player.rotDest = D3DXVECTOR3(0, 0, 0);

	g_Player.aModel[0].pos = D3DXVECTOR3(0,15,0);
	g_Player.aModel[1].pos = D3DXVECTOR3(0, 20, 0);
	g_Player.aModel[2].pos = D3DXVECTOR3(5, 0, 0);
	g_Player.aModel[3].pos = D3DXVECTOR3(-5, 0, 0);
	g_Player.aModel[4].pos = D3DXVECTOR3(5, 15, 0);
	g_Player.aModel[5].pos = D3DXVECTOR3(-5, 15, 0);
	g_Player.aModel[6].pos = D3DXVECTOR3(-15, 0, 0);

	g_Player.aModel[0].nIdxModelParent = -1;
	g_Player.aModel[1].nIdxModelParent = 0;
	g_Player.aModel[2].nIdxModelParent = 0;
	g_Player.aModel[3].nIdxModelParent = 0;
	g_Player.aModel[4].nIdxModelParent = 0;
	g_Player.aModel[5].nIdxModelParent = 0;
	g_Player.aModel[6].nIdxModelParent = 5;

	g_Player.g_nIdxShadow = SetShadow(g_Player.pos, g_Player.rot);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// ���b�V���̊J��
		if (g_Player.aModel[nCount].pMeshPlayer != NULL)
		{
			g_Player.aModel[nCount].pMeshPlayer->Release();
			g_Player.aModel[nCount].pMeshPlayer = NULL;
		}
	}
	for (int nCount2 = 0; nCount2 < MAX_PARTS; nCount2++)
	{
		// �}�e���A���̊J��
		if (g_Player.aModel[nCount2].pBuffMatPlayer != NULL)
		{
			g_Player.aModel[nCount2].pBuffMatPlayer->Release();
			g_Player.aModel[nCount2].pBuffMatPlayer = NULL;
		}

	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	float fSabun;

	g_Player.posold = g_Player.pos;
	//�E�ړ��̏���
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		SetEffect(g_Player.pos, D3DXCOLOR(1.0f, 0.5f, 0.7f, 1.0f), 20, 20, 0);// �v���C���[�ɒǔ�����p�[�e�B�N��
		//�E��
		if (GetKeyboardPress(DIK_UP) == true)
		{
			g_Player.move.x -= sinf(pCamera->fAngle - D3DX_PI*0.75f) * 1.0f;
			g_Player.move.z -= cosf(pCamera->fAngle - D3DX_PI*0.75f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle - D3DX_PI *0.75f;
		}
		//�E��
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			g_Player.move.x -= sinf(pCamera->fAngle - D3DX_PI*0.25f) * 1.0f;
			g_Player.move.z -= cosf(pCamera->fAngle - D3DX_PI*0.25f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle - D3DX_PI *0.25f;
		}
		//�E
		else
		{
			g_Player.move.x += sinf(pCamera->fAngle + D3DX_PI*0.5f) * 1.0f;
			g_Player.move.z += cosf(pCamera->fAngle + D3DX_PI*0.5f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle + D3DX_PI* -0.5f;
		}
	}
	//���ړ��̏���
	else if (GetKeyboardPress(DIK_LEFT) == true)
	{
		SetEffect(g_Player.pos, D3DXCOLOR(1.0f, 0.5f, 0.7f, 1.0f), 20, 20, 0);//	�v���C���[�ɒǔ�����p�[�e�B�N��
		//����
		if (GetKeyboardPress(DIK_UP) == true)
		{
			g_Player.move.x -= sinf(pCamera->fAngle + D3DX_PI*0.75f) * 1.0f;
			g_Player.move.z -= cosf(pCamera->fAngle + D3DX_PI*0.75f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle + D3DX_PI *0.75f;
		}
		//����
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			g_Player.move.x -= sinf(pCamera->fAngle + D3DX_PI*0.25f) * 1.0f;
			g_Player.move.z -= cosf(pCamera->fAngle + D3DX_PI*0.25f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle + D3DX_PI *0.25f;
		}
		//��
		else
		{
			g_Player.move.x -= sinf(pCamera->fAngle + D3DX_PI*0.5f) * 1.0f;
			g_Player.move.z -= cosf(pCamera->fAngle + D3DX_PI*0.5f) * 1.0f;

			g_Player.rotDest.y = pCamera->fAngle + D3DX_PI* 0.5f;
		}
	}
	//��
	else if (GetKeyboardPress(DIK_UP) == true)
	{
		SetEffect(g_Player.pos, D3DXCOLOR(1.0f, 0.5f, 0.7f, 1.0f), 20, 20, 0);//	�v���C���[�ɒǔ�����p�[�e�B�N��

		g_Player.move.x -= sinf(D3DX_PI + pCamera->fAngle) * 1.0f;
		g_Player.move.z -= cosf(D3DX_PI + pCamera->fAngle) * 1.0f;

		g_Player.rotDest.y = pCamera->fAngle - D3DX_PI *1.0f;
	}
	//��
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{
		SetEffect(g_Player.pos, D3DXCOLOR(1.0f, 0.5f, 0.7f, 1.0f), 20, 20, 0);//	�v���C���[�ɒǔ�����p�[�e�B�N��
		g_Player.move.x += sinf(D3DX_PI + pCamera->fAngle) * 1.0f;
		g_Player.move.z += cosf(D3DX_PI + pCamera->fAngle) * 1.0f;

		g_Player.rotDest.y = pCamera->fAngle - D3DX_PI *0.0f;
	}

	//�v���C���[�㉺�̈ړ�����
	//��
	if (GetKeyboardPress(DIK_R) == true)
	{
		g_Player.move.y += 1;
	}
	if (GetKeyboardPress(DIK_Y) == true)
	{//��
		g_Player.move.y -= 1;
	}

	//�e���˂̏���
	/*if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBallet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 8, g_Player.pos.z), g_Player.rot, D3DXVECTOR3(sinf(g_Player.rot.y - D3DX_PI) * 5, 0.0f, cosf(g_Player.rot.y - D3DX_PI) * 5));
	}*/

//	CollisionItem();		//�r���{�[�h�̓����蔻��
	//�ǂƂ̓����蔻��		���ߑł�
	if (MAX_ATARI <= g_Player.pos.x)
	{
		g_Player.pos.x = MAX_ATARI;
	}
	if (-MAX_ATARI2 >= g_Player.pos.x)
	{
		g_Player.pos.x = -MAX_ATARI2;
	}
	if (-MAX_ATARI >= g_Player.pos.z)
	{
		g_Player.pos.z = -MAX_ATARI;
	}
	if (MAX_ATARI2 <= g_Player.pos.z)
	{
		g_Player.pos.z = MAX_ATARI2;
	}

	if (g_Player.rotDest.y > D3DX_PI)
	{
		g_Player.rotDest.y -= D3DX_PI*2.0f;
	}
	if (g_Player.rotDest.y < -D3DX_PI)
	{
		g_Player.rotDest.y += D3DX_PI*2.0f;
	}

	fSabun = (g_Player.rotDest.y - g_Player.rot.y);

	if (fSabun > D3DX_PI)
	{
		fSabun -= D3DX_PI*2.0f;
	}
	if (fSabun < -D3DX_PI)
	{
		fSabun += D3DX_PI*2.0f;
	}

	g_Player.rot.y += fSabun * 0.1f;

	//���΍s�����
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI*2.0f;
	}
	if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI*2.0f;
	}

	g_Player.move.x += (0.0f - g_Player.move.x) * 0.2f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.2f;
	g_Player.move.y += (0.0f - g_Player.move.y) * 0.2f;

	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.z += g_Player.move.z;
	g_Player.pos.y += g_Player.move.y;

//	CollisionModel(&g_Player.pos, &g_Player.posold, &g_Player.move);
	CollisionEnemy(&g_Player.pos, &g_Player.posold, &g_Player.move);
	//�e�̔z�u
	SetPositionShadow(g_Player.g_nIdxShadow, g_Player.pos);

	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;
	D3DXMATRIX mtxParent;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (g_Player.aModel[nCount].nIdxModelParent < 0)
		{
			//�e
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			//�q
			mtxParent = g_Player.aModel[g_Player.aModel[nCount].nIdxModelParent].mtxWorldPlayer;
		}
		//-----------------------------------------------
		//					�e
		//-----------------------------------------------
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aModel[nCount].mtxWorldPlayer);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCount].rot.y, g_Player.aModel[nCount].rot.x, g_Player.aModel[nCount].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCount].mtxWorldPlayer, &g_Player.aModel[nCount].mtxWorldPlayer, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCount].pos.x, g_Player.aModel[nCount].pos.y, g_Player.aModel[nCount].pos.z);
	
		//
		D3DXMatrixMultiply(&g_Player.aModel[nCount].mtxWorldPlayer, &g_Player.aModel[nCount].mtxWorldPlayer, &mtxTrans);

		//
		D3DXMatrixMultiply(&g_Player.aModel[nCount].mtxWorldPlayer, &g_Player.aModel[nCount].mtxWorldPlayer, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCount].mtxWorldPlayer);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCount].pBuffMatPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCount].nNumMatPlayer; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
			// ���f��(�p�[�c)�̕`��
			g_Player.aModel[nCount].pMeshPlayer->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}
//�v���C���[�|�C���^
Player *GetPlayer(void)
{
	return &g_Player;
}