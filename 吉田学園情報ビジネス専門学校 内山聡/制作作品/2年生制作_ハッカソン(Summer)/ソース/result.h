//*************************************************************
//
// �����L���O�̏���[result.h]
//  Authot : ��������
//
//*************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//=============================================================
// �����L���O�̍\����
//=============================================================

typedef enum
{
	RESULTSTATE_GAMECLEAR = 0,
	RESULTSTATE_GAMEOVER,
	RESULTSTATE_MAX
}RESULTSTATE;


//=============================================================
//�v���g�^�C�v�錾
//=============================================================
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetRankTime(int nScore);

void SetResultState(RESULTSTATE state);
RESULTSTATE GetResultState(void);
#endif