//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// ���b�V���t�B�[���h(�C���f�b�N�X�o�b�t�@�g�p)�̏��� [meshField.h]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MESHFIELD		(16)			// ���b�V���t�B�[���h�̍ő吔
#define MESH_WIDTH			(50.0f)			// 1�����̃��b�V���̕�
#define MESH_DEPTH			(50.0f)			// 1�����̃��b�V���̉��s

//*****************************************************************************
// ���b�V���t�B�[���h�̍\����
//*****************************************************************************
// ���b�V���t�B�[���h�̎��
typedef enum
{
	 MESHFIELDTYPE_000 = 0,
	MESHFIELDTYPE_MAX
}MESHFIELDTYPE;

// �e�N�X�`���̏��
typedef struct
{
	char *pFilename;		// �e�N�X�`����
}meshFieldTexture;

// ���b�V���t�B�[���h�̏��f�[�^
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	int nNumSplitX;			// X�����̕�����
	int nNumSplitZ;			// Z�����̕�����
	float fWidth;			// ��
	float fDepth;			// ���s
}meshFieldInfo;

// ���b�V���t�B�[���h�̏��
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X
	int nNumSplitX;						// X�����̕�����
	int nNumSplitZ;						// Z�����̕�����
	float fWidth;						// ��
	float fDepth;						// ���s
	int nNumVertex;						// ���_��
	int nNumIndex;						// �C���f�b�N�X��
	int nNumPolygon;					// �|���S����
}meshField;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitmeshField(void);
void UninitmeshField(void);
void UpdatemeshField(void);
void DrawmeshField(void);
#endif
