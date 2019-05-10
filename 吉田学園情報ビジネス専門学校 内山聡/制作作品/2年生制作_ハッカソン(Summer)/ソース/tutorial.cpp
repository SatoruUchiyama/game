//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : Ishida Takuto
//
//=============================================================================
#include "game.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "light.h"
#include "meshDome.h"
#include "meshField.h"
#include "field.h"
#include "player.h"
#include "effect.h"
#include "gauge.h"
#include "particle.h"
#include "Gamepad.h"

#include "sound.h"
#include "UI.h"

#if _DEBUG
#include "line.h"
#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �Q�[���{�ҏ���������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitTutorial(void)
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
	// �t�B�[���h
	InitField();
	// �v���C���[
	InitPlayer();
	// �G�t�F�N�g
	InitEffect();
	// �p�[�e�B�N��
	InitParticle();
	// UI
	InitUI();

	//--- UI ---//
	// �X�^�~�i�Q�[�W
	InitGauge();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �Q�[���{�ҏI������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitTutorial(void)
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
	// �t�B�[���h
	UninitField();
	// �v���C���[
	UninitPlayer();
	// �G�t�F�N�g
	UninitEffect();
	// �p�[�e�B�N��
	UninitParticle();

	//--- UI ---//
	// �X�^�~�i�Q�[�W
	UninitGauge();
	// UI
	UninitUI();

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �Q�[���{�ҍX�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateTutorial(void)
{
	// �t�F�[�h���[�h�̎擾
	FADE pFade = GetFade();

	if (pFade == FADE_NONE)
	{// �t�F�[�h���������Ă��Ȃ��ꍇ
		if (GetKeyboardTrigger(DIK_RETURN) || GetGamapadKeyTrigger(ELECOM_START))
		{// ��ʑJ��
			SetFade(MODE_GAME);
		}
	}

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
	// �t�B�[���h
	UpdateField();
	// �v���C���[
	UpdatePlayer();
	// �G�t�F�N�g
	UpdateEffect();
	// �p�[�e�B�N��
	UpdateParticle();

	//--- UI ---//
	// �X�^�~�i�Q�[�W
	UpdateGauge();
	// UI
	UpdateUI();

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �Q�[���{�ҕ`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawTutorial(void)
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
	// �v���C���[
	DrawPlayer();
	// �t�B�[���h
	DrawField();
	// �G�t�F�N�g
	DrawEffect();
	// �p�[�e�B�N��
	DrawParticle();

	//--- UI ---//
	// �X�^�~�i�Q�[�W
	DrawGauge();
	// UI
	DrawUI();

}
