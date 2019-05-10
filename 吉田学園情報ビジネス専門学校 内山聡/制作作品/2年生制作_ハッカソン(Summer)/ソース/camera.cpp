//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �J�������� [camera.cpp]
// Author :
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "camera.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_DRAW_DISTANCE			(5.0f)		// �J�����̕`��ł��鋗���̔{��
#define CAMERA_POSVX_DEFAULT			(0.0f)
#define CAMERA_POSVY_DEFAULT			(200.0f)
#define CAMERA_POSVZ_DEFAULT			(-300.0f)
#define CAMERA_POSRX_DEFAULT			(0.0f)
#define CAMERA_POSRY_DEFAULT			(0.0f)
#define CAMERA_POSRZ_DEFAULT			(0.0f)
#define CAMERA_SPEED					(1.0f)		// �J�����̈ړ����x
#define TURNING_SPEED					(0.2f)		// �J�����̐��񑬓x
#define CAMERA_POSR_PLAYER_DIRECTION	(30.0f)		// �����_�ƃv���C���[�̈ʒu�̊Ԋu
#define CAMERA_POSR_COMPLIANCESPEED		(0.1f)		// �����_�̊����̊���
#define CAMERA_POSV_COMPLIANCESPEED		(0.2f)		// ���_�̊����̊���
#define CAMERA_UPDATE_STANDARDSPEED		(0.01f)		// �J��������荞�݊J�n����v���C���[�̑��x�̊


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_camera;		// �J�����̏��

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �J�����̏���������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(CAMERA_POSVX_DEFAULT, CAMERA_POSVY_DEFAULT, CAMERA_POSVZ_DEFAULT);		// �����ʒu [���_]
	g_camera.posR = D3DXVECTOR3(CAMERA_POSRX_DEFAULT, CAMERA_POSRY_DEFAULT, CAMERA_POSRZ_DEFAULT);		// �����ʒu [�����_]
	g_camera.posVDest = D3DXVECTOR3(CAMERA_POSVX_DEFAULT, CAMERA_POSVY_DEFAULT, CAMERA_POSVZ_DEFAULT);
	g_camera.posRDest = D3DXVECTOR3(CAMERA_POSRX_DEFAULT, CAMERA_POSRY_DEFAULT, CAMERA_POSRZ_DEFAULT);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// ������x�N�g��
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���� [����]
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���� [�ړI]
	g_camera.fLength = g_camera.posR.z - g_camera.posV.z;		// ���_�ƒ����_�̋���
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �J�����̏I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitCamera(void)
{
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �J�����̍X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateCamera(void)
{
	// ���[�J���ϐ�
	D3DXVECTOR3	rotDivision;						// ��荞�ݏ����ɕK�v
	D3DXVECTOR3 posVDirection, posRDirection;		// �Ǐ]�����ɕK�v
	int nLength = 0;									// �J�����̋����ɕK�v

	MODE pMode = GetMode();
	if (pMode == MODE_GAME || pMode == MODE_TUTORIAL)
	{

		// �v���C���[�̈ʒu���擾
		Player pPlayer = *GetPlayer();

		//++++++++++++++++++++++++++++++++++++++++
		// �J�����̏���
		//++++++++++++++++++++++++++++++++++++++++
		// =====  �J������荞�ݏ���  ===== //
		// ��荞�ޏꏊ��ݒ� [�v���C���[�̌��]
		g_camera.rotDest = pPlayer.rot;

		// ����
		rotDivision.y = g_camera.rotDest.y - g_camera.rot.y;

		if (rotDivision.y > D3DX_PI)
		{
			rotDivision.y += -D3DX_PI * 2;
		}
		else if (rotDivision.y < -D3DX_PI)
		{
			rotDivision.y += D3DX_PI * 2;
		}

		// �����̍X�V
		g_camera.rot.y += rotDivision.y * TURNING_SPEED;

		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y += -D3DX_PI * 2;
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2;
		}

		// =====  �J�����Ǐ]����  ===== //
		// -----  �����_  ----- //
		// �v���C���[�̈ʒu����ɒ����_�̈ʒu [�ړI]�����߂�
		g_camera.posRDest.x = pPlayer.pos.x + sinf(-pPlayer.rot.y) * CAMERA_POSR_PLAYER_DIRECTION;
		g_camera.posRDest.y = pPlayer.pos.y;
		g_camera.posRDest.z = pPlayer.pos.z + cosf(-pPlayer.rot.y + D3DX_PI) * CAMERA_POSR_PLAYER_DIRECTION;

		// ����
		posRDirection = D3DXVECTOR3(g_camera.posRDest.x - g_camera.posR.x, g_camera.posRDest.y - g_camera.posR.y, g_camera.posRDest.z - g_camera.posR.z);

		// �ʒu�̍X�V
		g_camera.posR += posRDirection * CAMERA_POSR_COMPLIANCESPEED;

		// -----  ���_  ----- //
		// �����_�����Ɏ��_��Ǐ]������
		g_camera.posVDest.x = pPlayer.pos.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posVDest.y = pPlayer.pos.y + CAMERA_POSVY_DEFAULT;
		g_camera.posVDest.z = pPlayer.pos.z + cosf(g_camera.rot.y) * g_camera.fLength;

		// ����
		posVDirection = D3DXVECTOR3(g_camera.posVDest.x - g_camera.posV.x, g_camera.posVDest.y - g_camera.posV.y, g_camera.posVDest.z - g_camera.posV.z);

		// �ʒu�̍X�V
		g_camera.posV += posVDirection * CAMERA_POSV_COMPLIANCESPEED;

#if 0
		// =====  �J�������_���񏈗�  ===== //
		if (GetKeyboardPress(DIK_Z) == true)
		{// ���ɐ���
			g_camera.rot.y += TURNING_SPEED;

			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2;
			}
			g_camera.posVDest.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posVDest.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength;
		}
		else if (GetKeyboardPress(DIK_C) == true)
		{// �E�ɐ���
			g_camera.rot.y -= TURNING_SPEED;

			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2;
			}
			g_camera.posVDest.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posVDest.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength;
		}

		if (pGamePad->lZ > GAMEPAD_DEADZONE || pGamePad->lZ < -GAMEPAD_DEADZONE)
		{// �R���g���[���[Ver.
			g_camera.rot.y += pGamePad->lZ * 0.01f;

			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2;
			}
			g_camera.posVDest.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posVDest.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength;
		}
#endif
#if 0
		//++++++++++++++++++++++++++++++++++++++++
		// �ړ����� [�L�[����]
		//++++++++++++++++++++++++++++++++++++++++
		// -----  ���_�������_ [X&Z�����ړ�]  ----- //
		if (GetKeyboardPress(DIK_A) == true)
		{// �L�[(A)�������ꂽ�ꍇ(���ړ�)
			// ���_
			if (GetKeyboardPress(DIK_W) == true)
			{// ������(W)�������ꂽ(��)
				g_camera.posV.x += sinf((D3DX_PI * 0.75f) + g_camera.rot.y) * CAMERA_SPEED;
				g_camera.posV.z += cosf((D3DX_PI * 0.75f) + g_camera.rot.y) * CAMERA_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// ������(S)�������ꂽ(��)
				g_camera.posV.x += sinf((D3DX_PI * 0.25f) + g_camera.rot.y) * CAMERA_SPEED;
				g_camera.posV.z += cosf((D3DX_PI * 0.25f) + g_camera.rot.y) * CAMERA_SPEED;
			}
			else
			{// (A)�̂݉����ꂽ
				g_camera.posV.x += sinf((D3DX_PI * 0.5f) + g_camera.rot.y) * CAMERA_SPEED;
				g_camera.posV.z += cosf((D3DX_PI * 0.5f) + g_camera.rot.y) * CAMERA_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// �L�[(D)�������ꂽ�ꍇ(�E�ړ�)
			// ���_
			if (GetKeyboardPress(DIK_W) == true)
			{// ������(W)�������ꂽ(��)
				g_camera.posV.x += sinf((-D3DX_PI * 0.75f) + g_camera.rot.y) * CAMERA_SPEED;
				g_camera.posV.z += cosf((-D3DX_PI * 0.75f) + g_camera.rot.y) * CAMERA_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// ������(S)�������ꂽ(��)
				g_camera.posV.x += sinf((-D3DX_PI * 0.25f) + g_camera.rot.y) * CAMERA_SPEED;
				g_camera.posV.z += cosf((-D3DX_PI * 0.25f) + g_camera.rot.y) * CAMERA_SPEED;
			}
			else
			{// (D)�̂݉����ꂽ
				g_camera.posV.x += sinf((-D3DX_PI * 0.5f) + g_camera.rot.y) * CAMERA_SPEED;
				g_camera.posV.z += cosf((-D3DX_PI * 0.5f) + g_camera.rot.y) * CAMERA_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{// �L�[(W)�������ꂽ�ꍇ(��ړ�)
			// ���_
			g_camera.posV.x += sinf((D3DX_PI * 1.0f) + g_camera.rot.y) * CAMERA_SPEED;
			g_camera.posV.z += cosf((D3DX_PI * 1.0f) + g_camera.rot.y) * CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// �L�[(S)�������ꂽ�ꍇ(���ړ�)
			// ���_
			g_camera.posV.x += sinf((D3DX_PI * 0.0f) + g_camera.rot.y) * CAMERA_SPEED;
			g_camera.posV.z += cosf((D3DX_PI * 0.0f) + g_camera.rot.y) * CAMERA_SPEED;
		}
		// �����_
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * g_camera.fLength;
		// -----  �����_����  ----- //
		if (GetKeyboardPress(DIK_Q) == true)
		{// ���ɐ���
			g_camera.rot.y -= TURNING_SPEED;

			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2;
			}
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y - D3DX_PI) * g_camera.fLength;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y - D3DX_PI) * g_camera.fLength;
		}
		else if (GetKeyboardPress(DIK_E) == true)
		{// �E�ɐ���
			g_camera.rot.y += TURNING_SPEED;

			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2;
			}
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y - D3DX_PI) * g_camera.fLength;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y - D3DX_PI) * g_camera.fLength;
		}

		// ----- ���_ [Y�����ړ�]  ----- //
		if (GetKeyboardPress(DIK_T) == true)
		{
			g_camera.posV.y += CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_B) == true)
		{
			g_camera.posV.y += -CAMERA_SPEED;
		}

		// ----- �����_ [Y�����ړ�]  ----- //
		if (GetKeyboardPress(DIK_Y) == true)
		{
			g_camera.posR.y += -CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_N) == true)
		{
			g_camera.posR.y += CAMERA_SPEED;
		}
#endif

		// =====  �J�����̋����ύX  ===== //

		// =====  �J�����̃��Z�b�g  ===== //

	}
	else if (pMode == MODE_TITLE)
	{
		g_camera.posR.z += 1.0f;
		g_camera.posV.z += 1.0f;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �J�����̐ݒ菈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1000.0f * CAMERA_DRAW_DISTANCE);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �J�����̎擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Camera *GetCamera(void)
{
	return &g_camera;
}