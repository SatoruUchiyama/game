//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// ���b�V���h�[������ [meshDome.h]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _MESHDOME_H_
#define _MESHDOME_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MESHDOME	(2)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ���b�V���h�[���̎��
typedef enum
{
	MESHDOMETYPE_000 = 0,
	MESHDOMETYPE_001,
	MESHDOMETYPE_MAX,
}MESHDOMETYPE;

// �e�N�X�`���̏��
typedef struct
{
	char *pFilename;	// �t�@�C����
} meshDomeTexture;

// �`�����
typedef enum
{
	DRAWSIDE_BOTH = 0,	// ����
	DRAWSIDE_IN,		// ����
	DRAWSIDE_OUT		// �O��
}DRAWSIDE;

// ���b�V���h�[���̏��f�[�^
typedef struct
{
	D3DXVECTOR3		pos;			// �ʒu
	D3DXVECTOR3		rot;			// ����
	float			fRadius;		// ���a
	int				nNumSplitV;		// �c�����̃u���b�N��
	int				nNumSplitH;		// �������̃u���b�N��
	MESHDOMETYPE	TexType;		// �e�N�X�`���̎��
	D3DXVECTOR2		TexMoveSpeed;	// �e�N�X�`���ړ����x
	DRAWSIDE		DrawSide;		// �`�悷���
}meshDomeInfo;

// ���b�V���h�[���̏��
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	pIdxBuff;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXVECTOR3				pos;			// �ʒu
	D3DXVECTOR3				rot;			// ����
	D3DXMATRIX				mtxWorld;		// ���[���h�}�g���b�N�X
	float					fRadius;		// ���a
	int						nNumSplitV;		// �c�����̃u���b�N��
	int						nNumSplitH;		// �������̃u���b�N��
	int						nNumVertex;		// ���_��
	int						nNumIndex;		// �C���f�b�N�X��
	int						nNumPolygon;	// �|���S����
	MESHDOMETYPE			TexType;		// �e�N�X�`���̎��
	D3DXVECTOR2				TexMoveSpeed;	// �e�N�X�`���ړ����x
	DRAWSIDE				DrawSide;		// �`�悷���
}meshDome;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitmeshDome(void);
void UninitmeshDome(void);
void UpdatemeshDome(void);
void DrawmeshDome(void);

#endif
