//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �J�E���g�V�[������ [countScene.h]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _COUNTSCENE_H_
#define _COUNTSCENE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_COUNTSCENE	(1)		// �J�E���g�V�[���̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	char *pFilename;		// �t�@�C����
}CountSceneTexInfo;

//--- ��� ---//
typedef enum
{
	COUNTSCENETYPE_START = 0,		// �X�^�[�g
	COUNTSCENETYPE_GOAL,			// �S�[��
	COUNTSCENETYPE_MAX
}COUNTSCENETYPE;

//--- ��� ---//
typedef enum
{
	COUNTSCENESTATE_NONE = 0,		// �������Ă��Ȃ�
	COUNTSCENESTATE_IN,				// �J�E���g�V�[���C��
	COUNTSCENESTATE_WAIT,			// �J�E���g�V�[���ҋ@
	COUNTSCENESTATE_OUT,			// �J�E���g�V�[���A�E�g
	COUNTSCENESTATE_MAX
}COUNTSCENESTATE;

// ���
typedef struct
{
	D3DXCOLOR color;					// �F
	COUNTSCENETYPE type;				// ���
	COUNTSCENESTATE countSceneState;	// �J�E���g�V�[���̏��
	int countSceneStateCounter;			// ��ԃJ�E���^�[
}COUNTSCENE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitcountScene(void);
void UninitcountScene(void);
void UpdatecountScene(void);
void DrawcountScene(void);
void SetcountScene(COUNTSCENETYPE type);

#endif
