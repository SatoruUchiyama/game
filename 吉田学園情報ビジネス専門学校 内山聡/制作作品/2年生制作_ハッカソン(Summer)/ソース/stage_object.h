//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �X�e�[�W�̔z�u���̏��� [stage_object.h]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _STAGE_OBJ_H_
#define _STAGE_OBJ_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_STAGE_OBJINFO	(16)		// �t�@�C������ǂݍ��ރ��f���̍ő吔
#define MAX_STAGE_OBJ		(128)		// �\������ő吔

//*****************************************************************************
// �\����
//*****************************************************************************
// �t�@�C���ǂݍ��ݏ�� [�ő吔,���]
typedef struct
{
	int nTypeModel;						// �ǂݍ��ރ��f���̍ő吔
	int nMaxModel;						// �\�����郂�f���̍ő吔
}Stage_objInfo_Number;

// �t�@�C���ǂݍ��ݏ�� [���ʕ���]
typedef struct
{
	char pXFileName[MAX_CHAR];			// �ǂݍ��ރt�@�C����
	LPD3DXMESH pMesh;					// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;				// �}�e���A�����ւ̃|�C���^
	DWORD NumMat;						// �}�e���A���̐�
	LPDIRECT3DTEXTURE9 *pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 vtxMin;					// ���_���W�̍ŏ��l
	D3DXVECTOR3 vtxMax;					// ���_���W�̍ő�l
}Stage_objInfo;

// �I�u�W�F�N�g�̏��
typedef struct
{
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X
	float fHeight;						// ����
	float fRadius;						// ���a
	int nType;							// ���
#if _DEBUG
	int IdxLine;						// ���̎g�p�ԍ� [�C���f�b�N�X]
#endif
}Stage_obj;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitStage_obj(void);
void UninitStage_obj(void);
void UpdateStage_obj(void);
void DrawStage_obj(void);

bool CollisionStage_obj(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius, float fHeight);
/* �t�@�C���ǂݍ��� */
void LoadStage_obj(void);
void UnloadStage_obj(void);
Stage_obj *GetStage_obj(void);
Stage_objInfo *GetStage_objInfo(void);
int GetNumStage_obj(void);
#endif
