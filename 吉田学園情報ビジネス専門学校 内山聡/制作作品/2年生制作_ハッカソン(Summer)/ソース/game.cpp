//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �Q�[���{�ҏ��� [game.h]
// Author : Toshiharu Ueno
// Editor : Eisuke Sakagawa
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "game.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "light.h"
#include "meshDome.h"
#include "meshField.h"
#include "stage_object.h"
#include "object.h"
#include "field.h"
#include "player.h"
#include "petals.h"
#include "effect.h"
#include "gauge.h"
#include "particle.h"
#include "time.h"
#include "result.h"
#include "countScene.h"

#include "sound.h"

#if _DEBUG
#include "line.h"
#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;		// �Q�[���̏��
int g_nCounterGameState;					// ��ԊǗ��J�E���^�[
bool g_bPause;								// �|�[�Y��ʂ̏��

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �Q�[���{�ҏ���������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitGame(void)
{
	// �J����
	InitCamera();
	// ���C�g
	InitLight();
#if _DEBUG
	// ���C��
	InitLine();
#endif
	// ���b�V���h�[��
	InitmeshDome();
	// ���b�V���t�B�[���h
	InitmeshField();
	// �X�e�[�W�I�u�W�F�N�g
	InitStage_obj();
	// ����
	InitField();
	// �����I�u�W�F�N�g
	InitObject();
	// �v���C���[
	InitPlayer();
	// �G�t�F�N�g
	InitEffect();
	// �p�[�e�B�N��
	InitParticle();
	// �t����
	InitPetals();

	//--- UI ---//
	// �X�^�~�i�Q�[�W
	InitGauge();
	// �^�C��
	InitTime();
	// �J�E���g�V�[��
	InitcountScene();

	// �ϐ�
	g_gameState = GAMESTATE_START;		// �J�n��Ԃɐݒ�
	g_nCounterGameState = 0;			// �J�E���^�[�̏�����
	g_bPause = false;					// �|�[�Y��ʂ̉���
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �Q�[���{�ҏI������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitGame(void)
{

	// �J����
	UninitCamera();
	// ���C�g
	UninitLight();
#if _DEBUG
	// ���C��
	UninitLine();
#endif
	// ���b�V���h�[��
	UninitmeshDome();
	// ���b�V���t�B�[���h
	UninitmeshField();
	// �X�e�[�W�I�u�W�F�N�g
	UninitStage_obj();
	// ����
	UninitField();
	// �����I�u�W�F�N�g
	UninitObject();
	// �v���C���[
	UninitPlayer();
	// �G�t�F�N�g
	UninitEffect();
	// �p�[�e�B�N��
	UninitParticle();
	// �t����
	UninitPetals();

	//--- UI ---//
	// �X�^�~�i�Q�[�W
	UninitGauge();
	// �^�C��
	UninitTime();
	// �J�E���g�V�[��
	UninitcountScene();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �Q�[���{�ҍX�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateGame(void)
{
	// �t�F�[�h���[�h�̎擾
	FADE pFade = GetFade();

	if (pFade == FADE_NONE)
	{// �t�F�[�h���������Ă��Ȃ��ꍇ
		if (GetKeyboardTrigger(DIK_P))
		{// �|�[�Y��ʐؑ�
			g_bPause = g_bPause ? false : true;
			// �|�[�Y�̍��ڏ�����
			//InitPauseItem();
			// �T�E���h
			PlaySound(SOUND_LABEL_SE_DECISION01);
		}
	}

	if (g_bPause == false)
	{// �|�[�Y�O
		// �J����
		UpdateCamera();
		// ���C�g
		UpdateLight();
#if _DEBUG
		// ���C��
		UpdateLine();
#endif
		// ���b�V���h�[��
		UpdatemeshDome();
		// ���b�V���t�B�[���h
		UpdatemeshField();
		// �X�e�[�W�I�u�W�F�N�g
		UpdateStage_obj();
		// ����
		UpdateField();
		// �����I�u�W�F�N�g
		UpdateObject();
		// �v���C���[
		UpdatePlayer();
		// �G�t�F�N�g
		UpdateEffect();
		// �p�[�e�B�N��
		UpdateParticle();
		// �t����
		UpdatePetals();

		//--- UI ---//
		// �X�^�~�i�Q�[�W
		UpdateGauge();
		// �^�C��
		UpdateTime();
		// �J�E���g�V�[��
		UpdatecountScene();

		//*************************
		// �Q�[��������
		//*************************
		switch (g_gameState)
		{
		case GAMESTATE_START:		// �J�n���

			if (pFade == FADE_NONE)
			{// �t�F�[�h���������Ă��Ȃ��ꍇ

				// �J�E���^�[����
				g_nCounterGameState++;

				if (g_nCounterGameState >= 150)
				{
					// �J�E���g�V�[��
					SetcountScene(COUNTSCENETYPE_START);		// �X�^�[�g
					//// �T�E���h
					//PlaySound(SOUND_LABEL_SE_GONG_START);		// �S���O [�J�n]
					// �ʏ��Ԃɐݒ�
					g_gameState = GAMESTATE_NORMAL;
				}
			}
			break;

		case GAMESTATE_NORMAL:		// �ʏ���
			break;

		case GAMESTATE_END:			// �I�����

				RESULTSTATE state = GetResultState();

				if (g_nCounterGameState == 0)
			{

				if (state == RESULTSTATE_GAMECLEAR)
				{
					// �J�E���g�V�[��
					SetcountScene(COUNTSCENETYPE_GOAL);		// �S�[��
				}
			}

			// �J�E���^�[����
			g_nCounterGameState++;

			if (pFade == FADE_NONE)
			{// �t�F�[�h���������Ă��Ȃ�
				if (g_nCounterGameState >= 60)
				{// ��b��
					g_gameState = GAMESTATE_NONE;


					if (state == RESULTSTATE_GAMECLEAR)
					{
						//--- �^�C���̕ۑ� ---//
						SetRankTime(GetTime());
					}

					// �t�F�[�h�ڍs
					SetFade(MODE_RESULT);		// ���U���g���
				}
			}
			break;
		}

		// �����I�u�W�F�N�g�̈ʒu�ݒ�
		SetPosOldObject();
	}
	else
	{// �|�[�Y��
		// �|�[�Y
		//UpdatePause();
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �Q�[���{�ҕ`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawGame(void)
{
	// �J����
	SetCamera();		// ���C���J����
	// ���C��
#if _DEBUG
	DrawLine();
#endif
	// ���b�V���h�[��
	DrawmeshDome();
	// ���b�V���t�B�[���h
	DrawmeshField();
	// �X�e�[�W�I�u�W�F�N�g
	DrawStage_obj();
	// ����
	DrawField();
	// �����I�u�W�F�N�g
	DrawObject();
	// �v���C���[
	DrawPlayer();
	// �G�t�F�N�g
	DrawEffect();
	// �p�[�e�B�N��
	DrawParticle();
	// �t����
	DrawPetals();

	//--- UI ---//
	// �X�^�~�i�Q�[�W
	DrawGauge();
	// �^�C��
	DrawTime();
	// �J�E���g�V�[��
	DrawcountScene();

	if (g_bPause == true)
	{// �|�[�Y��
		// �|�[�Y
		//DrawPause();
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �Q�[���̏�Ԑݒ菈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetGameState(GAMESTATE state)
{
	g_gameState = state;		// ���̃Q�[���̏��
	g_nCounterGameState = 0;	// �Q�[����Ԃ̃J�E���^�[
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �Q�[���̏�Ԏ擾����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
GAMESTATE GetGameState(void)
{
	return g_gameState;		// �Q�[���̏�Ԃ�Ԃ�
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �|�[�Y��������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void PauseRelease(void)
{
	g_bPause = false;		// �|�[�Y��ʂ̉���
}