//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �v���C���[�̏��� [model.h]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LOADMODEL	(16)		// �ǂݍ��ރ��f���̍ő吔
#define MAX_MODEL		(16)		// �\�����郂�f���̍ő吔
#define MAX_KEYSET		(10)		// ���[�V�����������̍ő�L�[�Z�b�g��
#define MAX_STAMINA		(100)							// �X�^�~�i�̍ő�l
#define WATER_SPEED					(-0.07f)						// ���̗���̑��x

//*****************************************************************************
// �\����
//*****************************************************************************
//--- ���[�V�����̎�� ---//
typedef enum
{
	MOTION_NEUTRAL = 0,		// �j���[�g����
	MOTION_RIGHT,			// �E����
	MOTION_LEFT,			// ������
	MOTION_MAX
}MOTIONTYPE;

//--- �ǂݍ��񂾃��f���̍\���� ---//
typedef struct
{
	char				pXFileName[MAX_CHAR];			// �t�@�C����
	LPD3DXMESH			pMesh;							// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		pBuffMat;						// �}�e���A�����ւ̃|�C���^
	DWORD				NumMat;							// �}�e���A���̐�
	LPDIRECT3DTEXTURE9	*pTexture;						// �e�N�X�`���ւ̃|�C���^
}LoadModel;

//--- ���f���̍\���� ---//
typedef struct
{
	D3DXVECTOR3 pos;					// ���f���̈ʒu
	D3DXVECTOR3 rot;					// ���f���̌���
	D3DXMATRIX	mtxWorld;				// ���f���̃��[���h�}�g���b�N�X
	int			nType;					// ���f���̎��
	int			nIdxModelParent;		// �e���f���̃C���f�b�N�X
}Model;

//--- �v���C���[�̍\���� ---//
typedef struct
{
	D3DXVECTOR3 pos;					// ���݂̈ʒu
	D3DXVECTOR3 posOld;					// �O��̈ʒu
	D3DXVECTOR3 rot;					// ����
	D3DXVECTOR3 move;					// �ړ���
	float		MoveSpeed;				// �ړ����x
	D3DXMATRIX	mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMin;					// ���_���W�̍ŏ��l
	D3DXVECTOR3 vtxMax;					// ���_���W�̍ő�l
	float		fRadius;				// ���a
	float		fHeight;				// ����
	int			IdxLine;				// ���̎g�p�ԍ� [�C���f�b�N�X]
	float		fDestAngle;				// �ړI�̌���
	int			nStamina;				// �X�^�~�i
	bool		bRight;					// �E����
	bool		bLeft;					// ������
	/* ���f�� */
	int			nLoadParts;				// �ǂݍ��ރ��f���̐�
	int			nMaxParts;				// �g�p���邷�郂�f���̐�
	Model		aModel[MAX_MODEL];		// ���f���̏��
	/* ���[�V���� */
	MOTIONTYPE		nMotionTypeOld;		// �O���[�V�����̎��
	MOTIONTYPE		nMotionType;		// ���[�V�����̎��
	int				nFrameAll;			// ���[�V�����̍ő�t���[����
	int				nNowFrame;			// ���[�V�����̌��݂̃t���[����
}Player;

//--- �I�t�Z�b�g��� ---//
typedef struct
{
	D3DXVECTOR3 pos;			// ���f���̈ʒu
	D3DXVECTOR3 rot;			// ���f���̌���
}Offset;

//--- ���[�V�����̃L�[��� ---//
typedef struct
{
	int			frame;					// �t���[����
	D3DXVECTOR3 pos[MAX_MODEL];			// �ʒu
	D3DXVECTOR3 rot[MAX_MODEL];			// ����
}KeySet;

//--- ���[�V�����̍\���� ---//
typedef struct
{
	int			nLoop;					// ���[�v��� [0 : ���[�v���Ȃ�, 1 : ���[�v����]
	int			nNumKey;				// �L�[��
	KeySet		nKeySet[MAX_KEYSET];	// �L�[���
}Motion;

//--- �ǂݍ��񂾃L�����N�^�[�̍\���� ---//
typedef struct
{
	Motion Motion[MOTION_MAX];	// ���[�V�����̏��
	Offset Offset[MAX_MODEL];	// ���f���̃I�t�Z�b�g
}LoadMotion;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void SubStamina(void);
void HealStamina(void);

void LoadPlayer(void);
void UnloadPlayer(void);

Player *GetPlayer(void);
#endif
