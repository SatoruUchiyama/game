//=============================================================================
//
// �J�������� [camera.cpp]
// Author :�@�L�n�@���u�@���@����
//
//=============================================================================
#include "camera.h"		//�J����
#include "input.h"		//�L�[�{�[�h
#include "player.h"		//�v���C���[
#include "player2.h"	//�v���C���[
#include "bullet.h"		//�e
#include "object.h"		//�I�u�W�F�N�g
#include "sound.h"		//�T�E���h
#include "effect.h"		//�G�t�F�N�g
#include "enemy.h"		//�S

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_ANGLE			(0.01f)				//�J�����p�x�̈ړ���
#define MOVE_ANGLE1			(0.001f)			//�J�����p�x�̈ړ���
//#define MOVE_CAMERA			(1200.0f)			//�J�����̋���
#define MOVE_OBJECT			(1000.0f)
#define MOVE_CAMERA			(160.0f)			//�J�����̋���
#define CAMERA_KM			(1200.0f)			//�J�����̕`�拗��
#define MOVE_SPEED			(0.001f)
#define MOVE_ANGLE2			(15.0f)
#define MOVE_ANGLE3			(0.03f)
#define MAX_CAMERA			(3)					//�J�����̍ő吔

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_Camera[MAX_CAMERA];					//�J�����̏��
int g_nCount;									//�b���J�E���g
float g_fCameraAngle = 45.0f;					//�p�x
float g_fRot;

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	//�v���C���[�̏��
	Object pObject = *GetObject();

	//================
	//1�v���C���[�ڂ̃J�����̈ʒu
	//================
	g_Camera[0].posV = D3DXVECTOR3(0.0f, 70.0f, 40.0f);			//���_�̏����l
	g_Camera[0].posR = D3DXVECTOR3(0.0f, 70.0f, 340.0f);				//�����_�̏����l
	g_Camera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//�@���̌���
	g_Camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	g_Camera[0].fLength = g_Camera[0].posV.z - g_Camera[0].posR.z;	//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	g_Camera[0].nCntTimer = 0;										//����
	g_Camera[0].nType = CAMERA_TYPE_NONE;							//���
	g_fCameraAngle = 45.0f;											//�p�x
	g_fRot = 0;

	//�r���[�|�[�g�̏���������
	g_Camera[0].ViewPort.X = 0;
	g_Camera[0].ViewPort.Y = 0;
	g_Camera[0].ViewPort.Width = SCREEN_WIDTH;
	g_Camera[0].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[0].ViewPort.MinZ = 0.0f;
	g_Camera[0].ViewPort.MaxZ = 1.0f;

	//================
	// 2�v���C���[�ڂ̃J�����̈ʒu
	//================
	g_Camera[1].posV = D3DXVECTOR3(2000.0f, 70.0f, -4100.0f);			//���_�̏����l
	g_Camera[1].posR = D3DXVECTOR3(2000.0f, 70.0f, -3800.0f);				//�����_�̏����l
	g_Camera[1].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	g_Camera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	g_Camera[1].fLength = g_Camera[1].posV.z - g_Camera[1].posR.z;	//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	g_Camera[1].nCntTimer = 0;										//����
	g_Camera[1].nType = CAMERA_TYPE_NONE;							//���
	g_fCameraAngle = 45.0f;											//�p�x
	g_fRot = 0;

	//�r���[�|�[�g�̏���������
	g_Camera[1].ViewPort.X = 0;
	g_Camera[1].ViewPort.Y = SCREEN_HEIGHT / 2;
	g_Camera[1].ViewPort.Width = SCREEN_WIDTH;
	g_Camera[1].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[1].ViewPort.MinZ = 0.0f;
	g_Camera[1].ViewPort.MaxZ = 1.0f;

	//================
	// �^�C�g���̃J�����̈ʒu
	//================
	g_Camera[2].posV = D3DXVECTOR3(1500.0f, 60.0f, -3600.0f);			//���_�̏����l
	g_Camera[2].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	g_Camera[2].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	g_Camera[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	g_Camera[2].fLength = g_Camera[2].posV.z - g_Camera[2].posR.z;	//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	g_Camera[2].nCntTimer = 0;										//����
	g_Camera[2].nType = CAMERA_TYPE_NONE;							//���
	g_fCameraAngle = 45.0f;											//�p�x
	g_fRot = 0;

	//�r���[�|�[�g�̏���������
	g_Camera[2].ViewPort.X = 0;
	g_Camera[2].ViewPort.Y = 0;
	g_Camera[2].ViewPort.Width = SCREEN_WIDTH;
	g_Camera[2].ViewPort.Height = SCREEN_HEIGHT;
	g_Camera[2].ViewPort.MinZ = 0.0f;
	g_Camera[2].ViewPort.MaxZ = 1.0f;
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
void UpdateCamera()
{
	//�v���C���[�̏��
	Object *pObject = GetObject();
	Player *pPlayer = GetPlayer();
	Player2 *pPlayer2 = GetPlayer2();
	Enemy *pEnemy = GetEnemy();
	Bullet *pBullet = GetBullet();

	int nCount = 0;
	float fcof = 0;

	////============================
	////��s�@�̌��ɃJ�������s���悤�ɂ��鏈��
	////============================
	for (int nCount = 0; nCount < MAX_CAMERA; nCount++)
	{
		if (g_Camera[nCount].nType == CAMERA_TYPE_GAME)
		{//�Q�[�����J����
			if (nCount == 0)
			{//�v���C���[�̃J����

				if (GetKeyboardPress(DIK_Q) == true)
				{
					g_Camera[nCount].fAngle -= 0.04f;
					g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
					g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;

				}
				if (GetKeyboardPress(DIK_E) == true)
				{
					g_Camera[nCount].fAngle += 0.04f;
					g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
					g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
				}

				g_Camera[nCount].posVDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y);
				//g_Camera[nCount].posVDest.y = pPlayer->pos.y;
				g_Camera[nCount].posVDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y);
				g_Camera[nCount].posRDest.x = pPlayer->pos.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
				//g_Camera[nCount].posRDest.y = pPlayer->pos.y;
				g_Camera[nCount].posRDest.z = pPlayer->pos.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;

				if (pPlayer->move.x > 0.7f || pPlayer->move.x < -0.7f || pPlayer->move.z > 0.7f || pPlayer->move.z < -0.7f)
				{// �ړ���

					if (g_Camera[nCount].nCntTimer < 10)
					{
						if (g_Camera[nCount].posR.y < 52.0f || g_Camera[nCount].posV.y < 54.0f)
						{
							g_Camera[nCount].posR.y += 2.0f / 10.0f;
							g_Camera[nCount].posV.y += 4.0f / 10.0f;
						}
					}
					else
					{
						if (g_Camera[nCount].posR.y > 50.0f || g_Camera[nCount].posV.y > 50.0f)
						{
							g_Camera[nCount].posR.y -= 1.5f / 10.0f;
							g_Camera[nCount].posV.y -= 3.0f / 10.0f;
						}
					}

					if (g_Camera[nCount].nCntTimer < 20)
					{
						g_Camera[nCount].nCntTimer++;
					}
					else
					{
						g_Camera[nCount].nCntTimer = 0;
					}

					fcof = 0.1f + (float)(g_Camera[nCount].nCntTimer * 0.001f);
				}
				else
				{// ��~��
					g_Camera[nCount].nCntTimer = 0;

					fcof = 0.09f;

					if (g_Camera[nCount].posR.y != 50.0f || g_Camera[nCount].posV.y != 50.0f)
					{
						g_Camera[nCount].posR.y += (50.0f - g_Camera[nCount].posR.y) / 10.0f;
						g_Camera[nCount].posV.y += (50.0f - g_Camera[nCount].posV.y) / 10.0f;
					}
				}

				// �l���
				g_Camera[nCount].posR.x += (g_Camera[nCount].posRDest.x - g_Camera[nCount].posR.x) * fcof;
				g_Camera[nCount].posR.z += (g_Camera[nCount].posRDest.z - g_Camera[nCount].posR.z) * fcof;
				g_Camera[nCount].posV.x += (g_Camera[nCount].posVDest.x - g_Camera[nCount].posV.x) * fcof;
				g_Camera[nCount].posV.z += (g_Camera[nCount].posVDest.z - g_Camera[nCount].posV.z) * fcof;

				/*//===================================
				//�����_���v���C���[�ɒǏ]�悤�ɂ���
				//===================================
				g_Camera[nCount].posV.x = pPlayer->pos.x;
				g_Camera[nCount].posV.z = pPlayer->pos.z;
				//���_���v���C���[�ɒǏ]�悤�ɂ���
				g_Camera[nCount].posR.x = pPlayer->pos.x - sinf(g_Camera[nCount].fAngle)* -MOVE_CAMERA;
				g_Camera[nCount].posR.z = pPlayer->pos.z - cosf(g_Camera[nCount].fAngle)* -MOVE_CAMERA;*/
			}
			if (nCount == 1)
			{//�S�̃J����

				if (GetKeyboardPress(DIK_RSHIFT) == true)
				{
					g_Camera[nCount].fAngle -= 0.04f;
					g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
					g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;

				}
				if (GetKeyboardPress(DIK_NUMPAD1) == true)
				{
					g_Camera[nCount].fAngle += 0.04f;
					g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
					g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
				}

				g_Camera[nCount].posVDest.x = pEnemy[1].pos.x - sinf(pEnemy[1].rot.y);
				//g_Camera[nCount].posVDest.y = pEnemy[1].pos.y;
				g_Camera[nCount].posVDest.z = pEnemy[1].pos.z - cosf(pEnemy[1].rot.y);
				g_Camera[nCount].posRDest.x = pEnemy[1].pos.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
				//g_Camera[nCount].posRDest.y = pEnemy[1].pos.y;
				g_Camera[nCount].posRDest.z = pEnemy[1].pos.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;

				if (pEnemy[1].move.x > 0.7f || pEnemy[1].move.x < -0.7f || pEnemy[1].move.z > 0.7f || pEnemy[1].move.z < -0.7f)
				{// �ړ���
					if (g_Camera[nCount].nCntTimer < 30)
					{
						g_Camera[nCount].nCntTimer++;
					}

					fcof = 0.1f + (float)(g_Camera[nCount].nCntTimer * 0.001f);
				}
				else
				{// ��~��
					g_Camera[nCount].nCntTimer = 0;

					fcof = 0.09f;
				}

				// �l���
				g_Camera[nCount].posR.x += (g_Camera[nCount].posRDest.x - g_Camera[nCount].posR.x) * fcof;
				g_Camera[nCount].posR.z += (g_Camera[nCount].posRDest.z - g_Camera[nCount].posR.z) * fcof;
				g_Camera[nCount].posV.x += (g_Camera[nCount].posVDest.x - g_Camera[nCount].posV.x) * fcof;
				g_Camera[nCount].posV.z += (g_Camera[nCount].posVDest.z - g_Camera[nCount].posV.z) * fcof;

				/*if (GetKeyboardPress(DIK_RSHIFT) == true)
				{
				g_Camera[nCount].fAngle -= 0.05f;
				g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * g_Camera[nCount].fDistance;
				g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * g_Camera[nCount].fDistance;

				}
				if (GetKeyboardPress(DIK_NUMPAD1) == true)
				{
				g_Camera[nCount].fAngle += 0.05f;
				g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * g_Camera[nCount].fDistance;
				g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * g_Camera[nCount].fDistance;
				}

				//===================================
				//�����_���v���C���[�ɒǏ]�悤�ɂ���
				//===================================
				//for (int nCount1 = 0; nCount1 < 2; nCount1++)
				{
				g_Camera[nCount].posV.x = pEnemy[1].pos.x;
				g_Camera[nCount].posV.z = pEnemy[1].pos.z;
				//���_���v���C���[�ɒǏ]�悤�ɂ���
				g_Camera[nCount].posR.x = pEnemy[1].pos.x - sinf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
				g_Camera[nCount].posR.z = pEnemy[1].pos.z - cosf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
				}*/
			}
			if (nCount == 2)
			{//�^�C�g���̃J����
				g_Camera[nCount].posV = D3DXVECTOR3(0.0f, 50.0f, 0.0f);	//���_�̏����l
				g_Camera[nCount].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����_�̏����l
			}
		}
	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(CAMERATYPE CameraType, int nIndxCamera)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_Camera[nIndxCamera].nType = CameraType;

	//�r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_Camera[nIndxCamera].ViewPort);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera[nIndxCamera].mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH
	(
		&g_Camera[nIndxCamera].mtxProjection,
		D3DXToRadian(g_fCameraAngle),
		(float)g_Camera[nIndxCamera].ViewPort.Width / (float)g_Camera[nIndxCamera].ViewPort.Height,
		10.0f,
		10000
	);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera[nIndxCamera].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera[nIndxCamera].mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_Camera[nIndxCamera].mtxView,
		&g_Camera[nIndxCamera].posV,
		&g_Camera[nIndxCamera].posR,
		&g_Camera[nIndxCamera].vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera[nIndxCamera].mtxView);

}
//=============================================================================
//	�J�����̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_Camera[0];
}