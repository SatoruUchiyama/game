//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �v���C���[�̏��� [player.cpp]
// Author :
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "player.h"
#include "input.h"
#include "Gamepad.h"
#include "camera.h"
#include "line.h"
#include "object.h"

#include "particle.h"
#include "sound.h"
#include "gauge.h"
#include "result.h"

#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_FILE					"data/TEXTFILE/player.txt"		// �t�@�C����
#define PLAY_MOTION					(true)							// ���[�V���� [On,Off]
#define MOTIONBREADFRAME			(10)							// ���[�V�����u�����h�̃t���[����

#define PLAYER_ROT_SPEED			(0.3f)							// ��]�̑��x

#define MODEL_MOVESPEED				(1.5f)							// ���f���̈ړ����x
#define PLAYER_RUN_STADBY_STD		(fabs(WATER_SPEED) + 0.1f)		// �v���C���[�̈ړ���Ԃ𔻒f����
#define MODEL_ANGLESPEED			(0.07f)							// ���f���̕����]�����x
#define PLAYER_MOVEACCELERATION		(0.15f)							// ��������
#define GRAVITY						(0.3f)							// �d��

#define DEC_STAMINA					(5)								// �X�^�~�i�̌�����
#define HEAL_STAMINA				(1)								// �X�^�~�i�̉񕜗�
#define HEAL_SPEED					(2)								// �X�^�~�i�̉񕜑��x

#define GOAL_POSITION				(3000.0f)						// �S�[���ʒu

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void PlayerMotion(void);		// �v���C���[���[�V����
void CulFrame(void);			// �t���[���v�Z

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LoadModel	g_LoadPlayer[MAX_MODEL];		// �ǂݍ��񂾃��f���̏��
LoadMotion	g_Motion;						// �ǂݍ��񂾃��[�V�������
Player		g_aPlayer;						// �v���C���[�̏��
int			g_nCounterKeySet;				// �L�[�Z�b�g�̃J�E���^�[
int			g_nCounterFrame;				// �t���[�����̃J�E���^�[
int			g_nMotionBlendFrame;			// ���[�V�����u�����h�p�̃t���[����
D3DXVECTOR3	g_PosDiff[MAX_MODEL];			// �P�t���[��������̍��� [Pos]
D3DXVECTOR3	g_RotDiff[MAX_MODEL];			// �P�t���[��������̍��� [Rot]
int g_nHealStaminaCounter = 0;				// �X�^�~�i�̉񕜃J�E���^�[

D3DXVECTOR3 g_Water;						// ���̏��

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//++++++++++++++++++++
	// ----- ������ -----
	//++++++++++++++++++++
	//--- �v���C���[�̏�� ---//
	g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���݂̈ʒu
	g_aPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �O��̈ʒu
	g_aPlayer.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);		// ����
	g_aPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ���
	g_aPlayer.MoveSpeed = 0.0f;								// �ړ����x
	g_aPlayer.fRadius = 0.0f;								// ���a
	g_aPlayer.fHeight = 0.0f;								// ����
	g_aPlayer.IdxLine = 0;									// ���̎g�p�ԍ� [�C���f�b�N�X]
	g_aPlayer.fDestAngle = D3DX_PI;							// �ړI�̌���
	g_aPlayer.nStamina = MAX_STAMINA;						// �X�^�~�i��
	g_aPlayer.bRight = false;								// �E����
	g_aPlayer.bLeft = false;								// ������
	/* ���f�� */
	g_aPlayer.nMaxParts = 0;								// �g�p���邷�郂�f���̐�

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̏��
		g_aPlayer.aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���f���̈ʒu
		g_aPlayer.aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���f���̌���
		g_aPlayer.aModel[nCntModel].nType = 0;												// ���f���̎��
		g_aPlayer.aModel[nCntModel].nIdxModelParent = -1;									// �e���f���̃C���f�b�N�X
	}
	/* ���[�V���� */
	g_aPlayer.nMotionTypeOld = MOTION_MAX;			// �O���[�V�����̎��
	g_aPlayer.nMotionType = MOTION_NEUTRAL;			// ���[�V�����̎��
	g_aPlayer.nFrameAll = 0;						// ���[�V�����̍ő�t���[����
	g_aPlayer.nNowFrame = 0;						// ���[�V�����̌��݂̃t���[����


	g_nCounterKeySet = 0;							// �L�[�Z�b�g�̃J�E���^�[
	g_nCounterFrame = 0;							// �t���[�����̃J�E���^�[
	g_nMotionBlendFrame = 0;						// ���[�V�����u�����h�p�̃t���[����

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̍ő吔
		g_PosDiff[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �P�t���[��������̍��� [Pos]
		g_RotDiff[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �P�t���[��������̍��� [Rot]
	}

	g_Water = D3DXVECTOR3(0.0f, 0.0f, WATER_SPEED);		// ���̏��

	//++++++++++++++++++++++++++++++
	// ----- �t�@�C���ǂݍ��� -----
	//++++++++++++++++++++++++++++++
	LoadPlayer();
#if 1
	//++++++++++++++++++++++++++++++
	// ----- X�t�@�C���ǂݍ��� -----
	//++++++++++++++++++++++++++++++
	for (int nCntModel = 0; nCntModel < g_aPlayer.nLoadParts; nCntModel++)
	{// �ǂݍ��ރ��f���̍ő吔
		D3DXLoadMeshFromX(g_LoadPlayer[nCntModel].pXFileName,		// �ǂݍ���X�t�@�C����
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_LoadPlayer[nCntModel].pBuffMat,		// �}�e���A�����|�C���^
			NULL,
			&g_LoadPlayer[nCntModel].NumMat,		// �}�e���A�����̐�
			&g_LoadPlayer[nCntModel].pMesh);		// ���b�V�����|�C���^

	// -----  �e�N�X�`���̓ǂݍ���  ----- //
		D3DXMATERIAL *pMat;// X�t�@�C��������o�����}�e���A����������

		//	 X�t�@�C������}�e���A�������擾
		pMat = (D3DXMATERIAL*)g_LoadPlayer[nCntModel].pBuffMat->GetBufferPointer();

		// �e�N�X�`���̃|�C���^���}�e���A�����̐����z��
		g_LoadPlayer[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[(int)g_LoadPlayer[nCntModel].NumMat];	// int�^�ɒ���

		// �擾�����t�@�C���������
		for (int nCntNumMat = 0; nCntNumMat < (int)g_LoadPlayer[nCntModel].NumMat; nCntNumMat++)	// DWORD�^����int�^�ɕϊ�����
		{
			// �e�N�X�`���̃|�C���^������
			g_LoadPlayer[nCntModel].pTexture[nCntNumMat] = NULL;

			// �e�N�X�`���t�@�C�����������Ă���ꍇ�A�ǂݍ���
			if (pMat[nCntNumMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntNumMat].pTextureFilename, &g_LoadPlayer[nCntModel].pTexture[nCntNumMat]);
			}
		}
	}
#endif

#if _DEBUG
	// ���C��
	g_aPlayer.IdxLine = SetColisionLine2(g_aPlayer.pos, g_aPlayer.fRadius, g_aPlayer.fHeight);
#endif
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// ���b�V���̊J��
		if (g_LoadPlayer[nCntModel].pMesh != NULL)
		{
			g_LoadPlayer[nCntModel].pMesh->Release();
			g_LoadPlayer[nCntModel].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_LoadPlayer[nCntModel].pBuffMat != NULL)
		{
			g_LoadPlayer[nCntModel].pBuffMat->Release();
			g_LoadPlayer[nCntModel].pBuffMat = NULL;
		}

		// �e�N�X�`���̊J��
		for (int nTex = 0; nTex < (int)g_LoadPlayer[nCntModel].NumMat; nTex++)
		{
			if (g_LoadPlayer[nCntModel].pTexture[nTex] != NULL)
			{
				g_LoadPlayer[nCntModel].pTexture[nTex]->Release();
				g_LoadPlayer[nCntModel].pTexture[nTex] = NULL;
			}
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdatePlayer(void)
{
	float fAngle;	// ���f���̌����ƖړI�̕����̍���

	MODE pMode = GetMode();

	if (pMode == MODE_GAME || pMode == MODE_TUTORIAL)
	{
		// �Q�[���̏�Ԃ��擾
		GAMESTATE gameState = GetGameState();
		// �J�����̎擾


		Camera *pCamera = GetCamera();
		// �O��̈ʒu���L��
		g_aPlayer.posOld = g_aPlayer.pos;
		// �O��̃��[�V�������L��
		g_aPlayer.nMotionTypeOld = g_aPlayer.nMotionType;

		//++++++++++++++++++++++++++++++++++++++++
		// �X�^�~�i
		//++++++++++++++++++++++++++++++++++++++++
		// �X�^�~�i�̉�
		HealStamina();

		//++++++++++++++++++++++++++++++++++++++++
		// �ړ� & ����
		//++++++++++++++++++++++++++++++++++++++++
		if (gameState == GAMESTATE_NORMAL || pMode == MODE_TUTORIAL)
		{
			if (g_aPlayer.nStamina >= DEC_STAMINA)
			{// �X�^�~�i������ʈȏ゠��ꍇ
				if (GetKeyboardTrigger(DIK_A) || GetGamapadKeyTrigger(ELECOM_LB))
				{// ���𑆂�[�O]
					g_aPlayer.move.x += sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * g_aPlayer.MoveSpeed;
					g_aPlayer.move.z += cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * g_aPlayer.MoveSpeed;

					// �ړI�̕���
					//g_aPlayer.fDestAngle = (-D3DX_PI * 0.85f);
					g_aPlayer.fDestAngle += (PLAYER_ROT_SPEED);

					// �X�^�~�i�̌���
					SubStamina();

					// �p�[�e�B�N��
					SetParticleEmitter(g_aPlayer.pos, 1);		// �I�[���𑆂����Ԃ�

					// �t���O
					g_aPlayer.bLeft = true;
					g_aPlayer.bRight = false;
				}
				else if (GetKeyboardTrigger(DIK_D) || GetGamapadKeyTrigger(ELECOM_RB))
				{// �E�𑆂�[�O]
					g_aPlayer.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * g_aPlayer.MoveSpeed;
					g_aPlayer.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * g_aPlayer.MoveSpeed;

					// �ړI�̕���
					//g_aPlayer.fDestAngle = (D3DX_PI * 0.85f);
					g_aPlayer.fDestAngle -= (PLAYER_ROT_SPEED);

					// �X�^�~�i�̌���
					SubStamina();

					// �p�[�e�B�N��
					SetParticleEmitter(g_aPlayer.pos, 1);		// �I�[���𑆂����Ԃ�

					// �t���O
					g_aPlayer.bRight = true;
					g_aPlayer.bLeft = false;
				}
				if (GetKeyboardTrigger(DIK_Z) || GetGamapadKeyTrigger(ELECOM_LT))
				{// ���𑆂�[���]
					g_aPlayer.move.x -= sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * g_aPlayer.MoveSpeed;
					g_aPlayer.move.z -= cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * g_aPlayer.MoveSpeed;

					// �ړI�̕���
					//g_aPlayer.fDestAngle = (-D3DX_PI * 0.85f);
					g_aPlayer.fDestAngle -= (PLAYER_ROT_SPEED);

					// �X�^�~�i�̌���
					SubStamina();

					// �p�[�e�B�N��
					SetParticleEmitter(g_aPlayer.pos, 1);		// �I�[���𑆂����Ԃ�

					// �t���O
					g_aPlayer.bLeft = true;
					g_aPlayer.bRight = false;
				}
				else if (GetKeyboardTrigger(DIK_C) || GetGamapadKeyTrigger(ELECOM_RT))
				{// �E�𑆂�[���]
					g_aPlayer.move.x -= sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * g_aPlayer.MoveSpeed;
					g_aPlayer.move.z -= cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * g_aPlayer.MoveSpeed;

					// �ړI�̕���
					//g_aPlayer.fDestAngle = (D3DX_PI * 0.85f);
					g_aPlayer.fDestAngle += (PLAYER_ROT_SPEED);

					// �X�^�~�i�̌���
					SubStamina();

					// �p�[�e�B�N��
					SetParticleEmitter(g_aPlayer.pos, 1);		// �I�[���𑆂����Ԃ�

					// �t���O
					g_aPlayer.bRight = true;
					g_aPlayer.bLeft = false;
				}
			}

			// --------------- ���� --------------- //
			// �ړI�̌����̒���
			if (g_aPlayer.fDestAngle > D3DX_PI)
			{
				g_aPlayer.fDestAngle -= D3DX_PI * 2;
			}
			else if (g_aPlayer.fDestAngle < -D3DX_PI)
			{
				g_aPlayer.fDestAngle += D3DX_PI * 2;
			}

			// �����̒���
			fAngle = g_aPlayer.fDestAngle - g_aPlayer.rot.y;

			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}
			else if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2;
			}

			g_aPlayer.rot.y += fAngle * MODEL_ANGLESPEED;

			if (g_aPlayer.rot.y > D3DX_PI)
			{
				g_aPlayer.rot.y -= D3DX_PI * 2;
			}
			else if (g_aPlayer.rot.y < -D3DX_PI)
			{
				g_aPlayer.rot.y += D3DX_PI * 2;
			}
			//++++++++++++++++++++++++++++++++++++++++
			// �d��
			//++++++++++++++++++++++++++++++++++++++++
			g_aPlayer.move.y -= GRAVITY;

			//++++++++++++++++++++++++++++++++++++++++
			// ���̗���
			//++++++++++++++++++++++++++++++++++++++++
			g_aPlayer.move += g_Water;

			//--- �I���ʒu ---//
			if (g_aPlayer.pos.z >= GOAL_POSITION)
			{
				//
				SetResultState(RESULTSTATE_GAMECLEAR);

				// �Q�[���I��
				SetGameState(GAMESTATE_END);

				// �t���O��߂�
				g_aPlayer.bLeft = false;
				g_aPlayer.bRight = false;
			}
			else if (g_aPlayer.pos.z <= -200.0f)
			{
				//
				SetResultState(RESULTSTATE_GAMEOVER);

				// �Q�[���I��
				SetGameState(GAMESTATE_END);

				// �t���O��߂�
				g_aPlayer.bLeft = false;
				g_aPlayer.bRight = false;
			}
		}

		//++++++++++++++++++++++++++++++++++++++++
		// �ʒu�̍X�V
		//++++++++++++++++++++++++++++++++++++++++
		g_aPlayer.pos += g_aPlayer.move;

		if (g_aPlayer.posOld.y >= 0.0f && g_aPlayer.pos.y < 0.0f)
		{
			g_aPlayer.pos.y = 0.0f;
		}

		// ��������
		g_aPlayer.move.x += (0.0f - g_aPlayer.move.x) * PLAYER_MOVEACCELERATION;			// �������銄�� [x����]
		g_aPlayer.move.z += (0.0f - g_aPlayer.move.z) * PLAYER_MOVEACCELERATION;			// �������銄�� [z����]
		//g_aPlayer.move.y += (0.0f - g_aPlayer.move.y) * PLAYER_MOVEACCELERATION;			// �������銄�� [y����]

		//++++++++++++++++++++++++++++++++++++++++
		// �����蔻��
		//++++++++++++++++++++++++++++++++++++++++
		if (pMode != MODE_TUTORIAL)
		{
			bool bFlowingObject = CollisionObject(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, g_aPlayer.fRadius);

			if (bFlowingObject)
			{
				// �p�[�e�B�N��
				SetParticleEmitter(g_aPlayer.pos, 2);		// �Փ�
			}
		}

		if (g_aPlayer.pos.x <= -500.0f)
		{
			g_aPlayer.pos.x = -500.0f;
		}
		else if (g_aPlayer.pos.x >= 500.0f)
		{

			g_aPlayer.pos.x = 500.0f;
		}
		//++++++++++++++++++++++++++++++++++++++++
		// �e, ���̈ړ�
		//++++++++++++++++++++++++++++++++++++++++
#if _DEBUG
		SetPositionLine(g_aPlayer.IdxLine, g_aPlayer.pos);			// ���C���̍X�V
#endif

		//++++++++++++++++++++++++++++++++++++++++
		// ���[�V����
		//++++++++++++++++++++++++++++++++++++++++
		if (!g_aPlayer.bRight  && !g_aPlayer.bLeft)
		{// �ҋ@
			g_aPlayer.nMotionType = MOTION_NEUTRAL;
		}
		if (g_aPlayer.bLeft)
		{// ������
			g_aPlayer.nMotionType = MOTION_LEFT;

			if (g_aPlayer.nMotionType != g_aPlayer.nMotionTypeOld)
			{
				CulFrame();
			}

			if (g_aPlayer.nNowFrame == g_aPlayer.nFrameAll)
			{// �Ō�܂ōĐ����ꂽ�ꍇ
				g_aPlayer.bLeft = false;
			}
		}
		if (g_aPlayer.bRight)
		{// �E����
			g_aPlayer.nMotionType = MOTION_RIGHT;

			if (g_aPlayer.nMotionType != g_aPlayer.nMotionTypeOld)
			{
				CulFrame();
			}

			if (g_aPlayer.nNowFrame == g_aPlayer.nFrameAll)
			{// �Ō�܂ōĐ����ꂽ�ꍇ
				g_aPlayer.bRight = false;
			}
		}

		// ���[�V����
#if PLAY_MOTION
		PlayerMotion();
#endif
	}
	else if (pMode == MODE_RESULT)
	{
		RESULTSTATE state = GetResultState();

		if (state == RESULTSTATE_GAMEOVER)
		{
			g_aPlayer.rot.z = D3DX_PI;
		}

		g_aPlayer.pos.z = -200.0f;
		g_aPlayer.pos.y = -20.0f;

		// �ߋ��̃��[�V����
		g_aPlayer.nMotionTypeOld = g_aPlayer.nMotionType;

		// �ҋ@���[�V����
		g_aPlayer.nMotionType = MOTION_NEUTRAL;

		// ���[�V����
		PlayerMotion();
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;						// �}�e���A���ւ̃|�C���^
	D3DXMATRIX			mtxParent;					// �e�̃}�g���b�N�X

	//============================
	// -----  �v���C���[  ----- //
	//============================
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aPlayer.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_aPlayer.rot.y, g_aPlayer.rot.x, g_aPlayer.rot.z);
	D3DXMatrixMultiply(&g_aPlayer.mtxWorld,
		&g_aPlayer.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		g_aPlayer.pos.x, g_aPlayer.pos.y, g_aPlayer.pos.z);
	D3DXMatrixMultiply(&g_aPlayer.mtxWorld,
		&g_aPlayer.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer.mtxWorld);

	//============================
	// -----  ���f��  ----- //
	//============================
	// �������킹��}�g���b�N�X�̐ݒ�
	for (int nCntModel = 0; nCntModel < g_aPlayer.nMaxParts; nCntModel++)
	{
		if (g_aPlayer.aModel[nCntModel].nIdxModelParent == -1)
		{
			mtxParent = g_aPlayer.mtxWorld;
		}
		else
		{
			mtxParent = g_aPlayer.aModel[g_aPlayer.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aPlayer.aModel[nCntModel].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aPlayer.aModel[nCntModel].rot.y, g_aPlayer.aModel[nCntModel].rot.x, g_aPlayer.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_aPlayer.aModel[nCntModel].mtxWorld,
			&g_aPlayer.aModel[nCntModel].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_aPlayer.aModel[nCntModel].pos.x, g_aPlayer.aModel[nCntModel].pos.y, g_aPlayer.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_aPlayer.aModel[nCntModel].mtxWorld,
			&g_aPlayer.aModel[nCntModel].mtxWorld, &mtxTrans);

		// �e���f���̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&g_aPlayer.aModel[nCntModel].mtxWorld,
			&g_aPlayer.aModel[nCntModel].mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer.aModel[nCntModel].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_LoadPlayer[g_aPlayer.aModel[nCntModel].nType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_LoadPlayer[g_aPlayer.aModel[nCntModel].nType].NumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̔��f
			pDevice->SetTexture(0, 0);

			// ���f��(�p�[�c)�̕`��
			g_LoadPlayer[g_aPlayer.aModel[nCntModel].nType].pMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���C���[���[�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void PlayerMotion(void)
{
#if 1
	//++++++++++++++++++++++++++++++
	// ���[�V�����̏�����
	//++++++++++++++++++++++++++++++
	if (g_aPlayer.nMotionTypeOld != g_aPlayer.nMotionType)
	{// ���[�V�������O��ƈقȂ�
		// �L�[�t���[��
		g_nCounterKeySet = 0;
		// �t���[����
		g_nCounterFrame = 0;
		// ���[�V�����u�����h�̃t���[���������߂�
		g_nMotionBlendFrame = MOTIONBREADFRAME;
		// �t���[�����̌v�Z
		CulFrame();
	}

	//++++++++++++++++++++++++++++++
	// �L�[�̐ؑ�
	//++++++++++++++++++++++++++++++
	switch (g_Motion.Motion[g_aPlayer.nMotionType].nLoop)
	{// ���[�V�����̎�ނ̃��[�v��
	case 0:		// ���[�v���Ȃ�
		if (g_nCounterFrame == g_nMotionBlendFrame && g_Motion.Motion[g_aPlayer.nMotionType].nNumKey == g_nCounterKeySet + 1)
		{// �ŏI�t���[���@&& �ŏI�L�[�ɂȂ���
			// �t���[����������
			g_nCounterFrame = 0;
			// �L�[�Z�b�g��i�߂�
			g_nCounterKeySet = g_Motion.Motion[g_aPlayer.nMotionType].nNumKey - 1;		// �Ō�̃L�[�Z�b�g��ݒ肷��
			// �����t���[���������߂�
			g_nMotionBlendFrame = g_Motion.Motion[g_aPlayer.nMotionType].nKeySet[g_nCounterKeySet].frame;
		}
		else if (g_nCounterFrame == g_nMotionBlendFrame && g_Motion.Motion[g_aPlayer.nMotionType].nNumKey != g_nCounterKeySet)
		{// �Ō�̃t���[�� && �ŏI�L�[�ł͂Ȃ�
		 // �t���[����������
			g_nCounterFrame = 0;
			// �L�[�Z�b�g��i�߂�
			g_nCounterKeySet = (g_nCounterKeySet + 1) % g_Motion.Motion[g_aPlayer.nMotionType].nNumKey;
			// �����t���[���������߂�
			g_nMotionBlendFrame = g_Motion.Motion[g_aPlayer.nMotionType].nKeySet[g_nCounterKeySet].frame;
		}
		break;

	case 1:		// ���[�v����
		if (g_nCounterFrame == g_nMotionBlendFrame)
		{// �Ō�̃t���[��
			// �t���[����������
			g_nCounterFrame = 0;
			// �L�[�Z�b�g��i�߂�
			g_nCounterKeySet = (g_nCounterKeySet + 1) % g_Motion.Motion[g_aPlayer.nMotionType].nNumKey;
			// �����t���[���������߂�
			g_nMotionBlendFrame = g_Motion.Motion[g_aPlayer.nMotionType].nKeySet[g_nCounterKeySet].frame;
		}
		break;
	}

	if (g_nCounterFrame == 0)
	{// �ŏ��̃t���[���ɂȂ�����A���̃L�[�Z�b�g�Ƃ̍����v�Z
		for (int nCntParts = 0; nCntParts < MAX_MODEL; nCntParts++)
		{
			// �e�p�[�c�̈ʒu�̍��� = ([��]�̃L�[�Z�b�g�̊e�p�[�c�̈ʒu + �e�p�[�c�̏����I�t�Z�b�g[�ʒu]) - [����]�̊e�p�[�c�̈ʒu
			g_PosDiff[nCntParts] = (g_Motion.Motion[g_aPlayer.nMotionType].nKeySet[g_nCounterKeySet].pos[nCntParts] + g_Motion.Offset[nCntParts].pos) - g_aPlayer.aModel[nCntParts].pos;
			// �e�p�[�c�̌����̍��� = [��]�̃L�[�Z�b�g�̊e�p�[�c�̌��� + �e�p�[�c�̏����I�t�Z�b�g[����] - [����]�̊e�p�[�c�̌���
			g_RotDiff[nCntParts] = g_Motion.Motion[g_aPlayer.nMotionType].nKeySet[g_nCounterKeySet].rot[nCntParts] + g_Motion.Offset[nCntParts].rot - g_aPlayer.aModel[nCntParts].rot;

			// �������t���[�����Ŋ���
			// �P�t���[��������̍��� = (�e�p�[�c�̈ʒu[x]�̍��� / [��]�̃L�[�Z�b�g�̃t���[����, �e�p�[�c�̈ʒu[y]�̍��� / [��]�̃L�[�Z�b�g�̃t���[����, �e�p�[�c�̈ʒu[z]�̍��� / [��]�̃L�[�Z�b�g�̃t���[����)
			g_PosDiff[nCntParts] = D3DXVECTOR3(g_PosDiff[nCntParts].x / g_nMotionBlendFrame, g_PosDiff[nCntParts].y / g_nMotionBlendFrame, g_PosDiff[nCntParts].z / g_nMotionBlendFrame);
			g_RotDiff[nCntParts] = D3DXVECTOR3(g_RotDiff[nCntParts].x / g_nMotionBlendFrame, g_RotDiff[nCntParts].y / g_nMotionBlendFrame, g_RotDiff[nCntParts].z / g_nMotionBlendFrame);
		}
	}

	//++++++++++++++++++++++++++++++
	// ���[�V�����X�V
	//++++++++++++++++++++++++++++++
	for (int nCntParts = 0; nCntParts < MAX_MODEL; nCntParts++)
	{
		g_aPlayer.aModel[nCntParts].pos += g_PosDiff[nCntParts];
		g_aPlayer.aModel[nCntParts].rot += g_RotDiff[nCntParts];

		if (g_aPlayer.aModel[nCntParts].rot.x > D3DX_PI)
		{
			g_aPlayer.aModel[nCntParts].rot.x -= D3DX_PI * 2;
		}
		else if (g_aPlayer.aModel[nCntParts].rot.x < -D3DX_PI)
		{
			g_aPlayer.aModel[nCntParts].rot.x += D3DX_PI * 2;
		}
		if (g_aPlayer.aModel[nCntParts].rot.y > D3DX_PI)
		{
			g_aPlayer.aModel[nCntParts].rot.y -= D3DX_PI * 2;
		}
		else if (g_aPlayer.aModel[nCntParts].rot.y < -D3DX_PI)
		{
			g_aPlayer.aModel[nCntParts].rot.y += D3DX_PI * 2;
		}
		if (g_aPlayer.aModel[nCntParts].rot.y > D3DX_PI)
		{
			g_aPlayer.aModel[nCntParts].rot.z -= D3DX_PI * 2;
		}
		else if (g_aPlayer.aModel[nCntParts].rot.z < -D3DX_PI)
		{
			g_aPlayer.aModel[nCntParts].rot.z += D3DX_PI * 2;
		}
	}
	// �t���[�����̉��Z
	g_nCounterFrame++;

	if (g_aPlayer.nNowFrame < g_aPlayer.nFrameAll)
	{
		// ���݂̃t���[���������Z
		g_aPlayer.nNowFrame++;
	}
#endif
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�^�~�i�̌���
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SubStamina(void)
{
	if (g_aPlayer.nStamina >= DEC_STAMINA)
	{// �X�^�~�i������ʈȏ゠��ꍇ
		// �X�^�~�i�̌���
		g_aPlayer.nStamina -= DEC_STAMINA;
	}

	//--- �Q�[�W ---//
	AddSubtractGauge(-DEC_STAMINA);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�^�~�i�̉�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void HealStamina(void)
{
	// �X�^�~�i�񕜃J�E���^�̉��Z
	g_nHealStaminaCounter++;

	if (g_nHealStaminaCounter % HEAL_SPEED == 0)
	{// �񕜃^�C�~���O�̏ꍇ
		if (g_aPlayer.nStamina < MAX_STAMINA)
		{// �X�^�~�i�̍ő�l�ȉ��̏ꍇ

			g_aPlayer.nStamina += HEAL_STAMINA;

			// �J�E���^���Z�b�g
			g_nHealStaminaCounter = 0;

			//--- �Q�[�W ---//
			AddSubtractGauge(HEAL_STAMINA);
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���[�V�����̃t���[�����v�Z
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void CulFrame(void)
{
	// ���݂̃t���[���������Z�b�g
	g_aPlayer.nNowFrame = 0;
	// ���[�V�����̑��t���[���������Z�b�g
	g_aPlayer.nFrameAll = 0;
	// ���[�V�����̑��t���[�������v�Z
	for (int nCntKey = 0; nCntKey < g_Motion.Motion[g_aPlayer.nMotionType].nNumKey; nCntKey++)
	{
		g_aPlayer.nFrameAll += g_Motion.Motion[g_aPlayer.nMotionType].nKeySet[nCntKey].frame;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���C���[�̓ǂݍ���
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LoadPlayer(void)
{
	//--- �ǂݍ��񂾃��f���̏�� ---//
	for (int nCntModel = 0; nCntModel < MAX_LOADMODEL; nCntModel++)
	{// ���f���̍ő吔
		for (int nText = 0; nText < MAX_CHAR; nText++)
		{
			g_LoadPlayer[nCntModel].pXFileName[nText] = NULL;		// �t�@�C����
		}
		g_LoadPlayer[nCntModel].pMesh = NULL;					// ���b�V�����ւ̃|�C���^
		g_LoadPlayer[nCntModel].pBuffMat = NULL;				// �}�e���A�����ւ̃|�C���^
		g_LoadPlayer[nCntModel].NumMat = 0;						// �}�e���A���̐�
		g_LoadPlayer[nCntModel].pTexture = NULL;				// �e�N�X�`���ւ̃|�C���^
	}

	//--- �ǂݍ��񂾃��[�V������� ---//
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̍ő吔
		g_Motion.Offset[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �I�t�Z�b�g[�ʒu]
		g_Motion.Offset[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �I�t�Z�b�g[����]
	}
	for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
	{// ���[�V�����̎��
		g_Motion.Motion[nCntMotion].nLoop;				// ���[�v��� [0 : ���[�v���Ȃ�, 1 : ���[�v����]
		g_Motion.Motion[nCntMotion].nNumKey = 0;		// �L�[��
		/* �L�[��� */
		for (int nNumKeySet = 0; nNumKeySet < MAX_KEYSET; nNumKeySet++)
		{// �L�[�Z�b�g�̍ő吔
			g_Motion.Motion[nCntMotion].nKeySet[nNumKeySet].frame = 0;				// �t���[����
			for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
			{// ���f���̍ő吔
				g_Motion.Motion[nCntMotion].nKeySet[nNumKeySet].pos[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
				g_Motion.Motion[nCntMotion].nKeySet[nNumKeySet].rot[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
			}
		}
	}

#if 1
	// ���[�J���ϐ��錾
	FILE *pFile;				// �t�@�C���̃|�C���^
	char ReadText[256];			// �ǂݍ��񂾕���������Ă���
	char HeadText[256];			// ��r�p
	char DustBox[256];			// �g�p���Ȃ����̂����Ă���
	int nCntText = 0;			// ���f���t�@�C����
	int nCntModel = 0;			// ���f����
	int nCntMotion = 0;			// ���[�V������
	int nCntKeySet = 0;			// �L�[�Z�b�g��

	// �t�@�C���I�[�v��
	pFile = fopen(PLAYER_FILE, "r");		// �t�@�C�����J��[�ǂݍ��݌^]

	if (pFile != NULL)		// �t�@�C������ł͂Ȃ�
	{//�t�@�C�����J�����ꍇ
		while (strcmp(HeadText, "SCRIPT") != 0)
		{// "SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
			fgets(ReadText, sizeof(ReadText), pFile);
			sscanf(ReadText, "%s", &HeadText);
		}

		if (strcmp(HeadText, "SCRIPT") == 0)
		{// "SCRIPT" ���ǂݎ�ꂽ�ꍇ�A�����J�n
			while (strcmp(HeadText, "END_SCRIPT") != 0)
			{// "END_SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
				fgets(ReadText, sizeof(ReadText), pFile);
				sscanf(ReadText, "%s", &HeadText);

				if (strcmp(HeadText, "\n") == 0)
				{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�
					int nCnt = 0;
				}
				else if (strcmp(HeadText, "NUM_MODEL") == 0)
				{// �ǂݍ��ރ��f���̍ő吔
					sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_aPlayer.nLoadParts);
				}
				else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
				{// ���f���t�@�C����
					if (g_aPlayer.nLoadParts > nCntText)
					{// �ő吔�ȏ㏈�����Ȃ�
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, &g_LoadPlayer[nCntText].pXFileName[0]);
						nCntText++;
					}
				}
				else if (strcmp(HeadText, "CHARACTERSET") == 0)
				{//--- �L�����N�^�[��� ---//
					while (strcmp(HeadText, "END_CHARACTERSET") != 0)
					{// "END_CHARACTERSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
						fgets(ReadText, sizeof(ReadText), pFile);
						sscanf(ReadText, "%s", &HeadText);

						if (strcmp(HeadText, "MOVE") == 0)
						{// �ړ���
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_aPlayer.MoveSpeed);
						}
						else if (strcmp(HeadText, "POS") == 0)
						{// �ړ���
							sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox, &g_aPlayer.pos.x, &g_aPlayer.pos.y, &g_aPlayer.pos.z);
						}
						else if (strcmp(HeadText, "RADIUS") == 0)
						{// ���a
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_aPlayer.fRadius);
						}
						else if (strcmp(HeadText, "HEIGHT") == 0)
						{// ����
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_aPlayer.fHeight);
						}
						else if (strcmp(HeadText, "NUM_PARTS") == 0)
						{// �v���C���[�P�̂ɑ΂��郂�f���̎g�p��
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_aPlayer.nMaxParts);
						}
						else if (strcmp(HeadText, "PARTSSET") == 0)
						{//--- ���f���̔z�u��� ---//
							if (g_aPlayer.nMaxParts > nCntModel)
							{
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{// "END_PARTSSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "INDEX") == 0)
									{// ����
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_aPlayer.aModel[nCntModel].nType);
									}
									else if (strcmp(HeadText, "PARENT") == 0)
									{// �e�̃C���f�b�N�X
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_aPlayer.aModel[nCntModel].nIdxModelParent);
									}
									else if (strcmp(HeadText, "POS") == 0)
									{// �ʒu
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox, &g_aPlayer.aModel[nCntModel].pos.x, &g_aPlayer.aModel[nCntModel].pos.y, &g_aPlayer.aModel[nCntModel].pos.z);
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox, &g_Motion.Offset[nCntModel].pos.x, &g_Motion.Offset[nCntModel].pos.y, &g_Motion.Offset[nCntModel].pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{// ����
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox, &g_aPlayer.aModel[nCntModel].rot.x, &g_aPlayer.aModel[nCntModel].rot.y, &g_aPlayer.aModel[nCntModel].rot.z);
									}
								}
								nCntModel++;		// ���f������i�߂�
							}
						}
					}
				}
				else if (strcmp(HeadText, "MOTIONSET") == 0)
				{//--- ���[�V������� ---//
					nCntModel = 0;		// ���f�����̃��Z�b�g

					while (strcmp(HeadText, "END_MOTIONSET") != 0)
					{// "END_MOTIONSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
						fgets(ReadText, sizeof(ReadText), pFile);
						sscanf(ReadText, "%s", &HeadText);

						if (strcmp(HeadText, "LOOP") == 0)
						{// ���[�v���
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nLoop);
						}
						else if (strcmp(HeadText, "NUM_KEY") == 0)
						{// �L�[��
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nNumKey);
						}
						else if (strcmp(HeadText, "KEYSET") == 0)
						{// �L�[�Z�b�g
							while (strcmp(HeadText, "END_KEYSET") != 0)
							{// "END_KEYSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
								fgets(ReadText, sizeof(ReadText), pFile);
								sscanf(ReadText, "%s", &HeadText);

								if (strcmp(HeadText, "FRAME") == 0)
								{// �t���[����
									sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nKeySet[nCntKeySet].frame);
								}
								else if (strcmp(HeadText, "KEY") == 0)
								{// �L�[
									while (strcmp(HeadText, "END_KEY") != 0)
									{// "END_KEY" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
										fgets(ReadText, sizeof(ReadText), pFile);
										sscanf(ReadText, "%s", &HeadText);

										if (strcmp(HeadText, "POS") == 0)
										{// �ʒu
											sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nKeySet[nCntKeySet].pos[nCntModel].x, &g_Motion.Motion[nCntMotion].nKeySet[nCntKeySet].pos[nCntModel].y, &g_Motion.Motion[nCntMotion].nKeySet[nCntKeySet].pos[nCntModel].z);
										}
										else if (strcmp(HeadText, "ROT") == 0)
										{// ����
											sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nKeySet[nCntKeySet].rot[nCntModel].x, &g_Motion.Motion[nCntMotion].nKeySet[nCntKeySet].rot[nCntModel].y, &g_Motion.Motion[nCntMotion].nKeySet[nCntKeySet].rot[nCntModel].z);
										}
									}
									nCntModel++;		// ���f������i�߂�
								}
							}
							nCntKeySet++;		// �L�[�Z�b�g����i�߂�
							nCntModel = 0;		// ���f�����̃��Z�b�g
						}
					}
					nCntMotion++;			// ���[�V�����̎�ނ�i�߂�
					nCntKeySet = 0;			// �L�[�Z�b�g���̃��Z�b�g
				}
			}
		}
		// �t�@�C���N���[�Y
		fclose(pFile);
#if 0
		MessageBox(NULL, "�L�����N�^�[���t�@�C���𐳂����ǂݍ��݂܂����B", NULL, MB_OK);
#endif
	}
	else
	{// �J���Ȃ������ꍇ
		MessageBox(NULL, "�L�����N�^�[���t�@�C�����J���܂���ł����B", NULL, MB_OK);
	}
#endif
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���C���[�̔j��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UnloadPlayer(void)
{

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���C���[�̎擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Player *GetPlayer(void)
{
	return &g_aPlayer;
}