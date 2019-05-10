//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// ���C������ [main.h]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"						// �r���h���̌x���Ώ��p�}�N��

#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"						// ���͏����ɕK�v
#include "xinput.h"						// Xinput���͂ɕK�v
#include "xaudio2.h"					// �T�E���h�����ɕK�v

#include <math.h>
#include <time.h>

//*****************************************************************************
// ���C�u�����t�@�C��
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")			// �`�揈���ɕK�v
#pragma comment (lib, "d3dx9.lib")			// [d3d9.lib]�̊g�����C�u����
#pragma comment (lib, "dxguid.lib")			// DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment (lib, "winmm.lib")			// �V�X�e�������擾�ɕK�v
#pragma comment (lib, "dinput8.lib")		// ���͏����ɕK�v
#pragma comment(lib, "xinput.lib")			// Xinput���͂ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)	// �E�C���h�E�̍���

//#define SCREEN_WIDTH	(1980)	// �E�C���h�E�̕�
//#define SCREEN_HEIGHT	(1080)	// �E�C���h�E�̍���

// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@���x�N�g�� / ���_�J���[ / �e�N�X�`�����W)
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �t�@�C�����o�͏����p�}�N��
#define MAX_CHAR	(256)		// �ő啶����

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

// �R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_3D;

//--- ���[�h ---//
typedef enum
{
	MODE_TITLE = 0,		// �^�C�g��
	MODE_TUTORIAL,		// �`���[�g���A��
	MODE_GAME,			// �Q�[���{��
	MODE_RESULT,		// ����
	MODE_MAX
}MODE;

//--- �v���C���[�ԍ� ---//
typedef enum
{
	PLAYERINDEX_1 = 0,		// �v���C���[�P
	PLAYERINDEX_2,			// �v���C���[�Q
	PLAYERINDEX_3,			// �v���C���[�R
	PLAYERINDEX_4,			// �v���C���[�S
	PLAYERINDEX_MAX
}PLAYERINDEX;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

int GetFPS(void);
void SetNumPlayer(int nNumPlayer);		// �v���C���[���̐ݒ�
int GetNumPlayer(void);					// �v���C���[���̎擾

#endif