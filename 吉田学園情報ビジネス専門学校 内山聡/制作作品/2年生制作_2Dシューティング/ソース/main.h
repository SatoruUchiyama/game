//=============================================================================
//
// ���C������ [main.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"					//�T�E���h�����ŕK�v


//=============================================================================
// ���C�u�����t�@�C���̃����N
//=============================================================================
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dinput8.lib")
//#include "input.h"

//=============================================================================
//�w�b�_�[�ǂݍ���
//=============================================================================
#include "xaudio2.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCREEN_WIDTH	(1280)													// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)													// �E�C���h�E�̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define MAX_MODEL		(1500)													//Model�̍ő吔
#define MAX_PRIORITY_2		(8)													//Model�̍ő吔

//Player�̃}�N��
#define		MAX_SPEED			(1.3f)											//�v���C���[�̃X�s�[�h
#define		MAX_INERTIAL		(0.3f)											//�����̋���

#define		MAX_SPEED_ENEMY			(1.5f)										//�X�s�[�h
#define		MAX_INERTIAL_ENEMY		(0.5f)										//�����̋���
//�w�i�p�@�f�o�b�N
#define		MAX_SPEED_BG			(0.05f)										//�v���C���[�̃X�s�[�h
#define		MAX_INERTIAL_BG		(0.005f)										//�����̋���
//Bullet�̃}�N��
#define MAX_BULLET_LIFE				(50)										//�e�̎���

class CRenderer;
class CScene;
class CScene2d;
//=============================================================================
//	�v���g�^�C�v�錾
//=============================================================================
int GetFps(void);

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	//���W
	D3DXVECTOR3 pos;
	//
	float rhw;
	//�F
	D3DCOLOR col;
	//�e�N�X�`��
	D3DXVECTOR2 tex;
}VERTEX_2D;

#endif
