//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �Q�[���{�ҏ��� [game.h]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �Q�[���̏�Ԃ̎��
typedef enum
{
	GAMESTATE_NONE = 0,		// �������Ă��Ȃ����
	GAMESTATE_START,		// �J�n���
	GAMESTATE_NORMAL,		// �ʏ���
	GAMESTATE_END,			// �I�����
	GAMESTATE_MAX
}GAMESTATE;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
void PauseRelease(void);
void SubLivePlayer(int nValue);
//void SetUpdateGame(bool flag);		// �X�V�t���O�̐ݒ�]
int GetNumLivePlayer(void);

#endif