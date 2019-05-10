//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���p ���l
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_		// 2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM [�^�C�g��]
	SOUND_LABEL_BGM001,			// BGM []
	SOUND_LABEL_BGM002,			// BGM [���U���g]
	SOUND_LABEL_BGM003,			// BGM []
	SOUND_LABEL_BGM004,			// BGM []
	SOUND_LABEL_BGM005,			// BGM [�Q�[��]
	SOUND_LABEL_BGM_WATER,		// ��

	SOUND_LABEL_SE_GONG_START,		// �S���O [�J�n]
	SOUND_LABEL_SE_GONG_END,		// �S���O [�I��]
	SOUND_LABEL_SE_BREAK,			// �K�[�h�j��
	SOUND_LABEL_SE_CUT00,			// �؂鉹00
	SOUND_LABEL_SE_CUT01,			// �؂鉹01
	SOUND_LABEL_SE_CUT02,			// �؂鉹02
	SOUND_LABEL_SE_CUT03,			// �؂鉹03
	SOUND_LABEL_SE_DECISION00,		// ���艹00
	SOUND_LABEL_SE_DECISION01,		// ���艹01
	SOUND_LABEL_SE_DECISION02,		// ���艹02
	SOUND_LABEL_SE_DECISION03,		// ���艹03
	SOUND_LABEL_SE_GRAB00,			// �͂މ�00
	SOUND_LABEL_SE_GRAB01,			// �͂މ�01
	SOUND_LABEL_SE_HIT000,			// �U���q�b�g��00
	SOUND_LABEL_SE_HIT001,			// �U���q�b�g��01
	SOUND_LABEL_SE_HIT002,			// �U���q�b�g��02
	SOUND_LABEL_SE_HIT003,			// �U���q�b�g��03
	SOUND_LABEL_SE_HIT004,			// �U���q�b�g��04
	SOUND_LABEL_SE_HORAGAI,			// �ق�L
	SOUND_LABEL_SE_KEYBOARD,		// �L�[�{�[�h��
	SOUND_LABEL_SE_PICOHAN00,		// �s�R�s�R�n���}�[00
	SOUND_LABEL_SE_PICOHAN01,		// �s�R�s�R�n���}�[01
	SOUND_LABEL_SE_SELECT00,		// �I����00
	SOUND_LABEL_SE_SELECT01,		// �I����01
	SOUND_LABEL_SE_SWING00,			// �U�鉹00
	SOUND_LABEL_SE_SWING01,			// �U�鉹01
	SOUND_LABEL_SE_SWING02,			// �U�鉹02
	SOUND_LABEL_SE_WATER,			// ������

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);				// �T�E���h�̏���������
void UninitSound(void);						// �T�E���h�̏I������
HRESULT PlaySound(SOUND_LABEL label);		// �T�E���h�̍Đ�����(label�ōĐ�����T�E���h���w��)
void StopSound(SOUND_LABEL label);			// �T�E���h�̒�~����(label�Œ�~����T�E���h���w��)
void StopSound(void);						// �T�E���h�̒�~����

#endif