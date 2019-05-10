//=============================================================================
//
// �I�u�W�F�N�g�̏��� [object.h]
// Author : ��������
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"       // ���C�����̃w�b�_�[

#define MAX_OBJECT			(100)							// �I�u�W�F�N�g�̍ő吔
#define MAX_ADDRESS			(256)						// �A�h���X��ۑ��ł���ő啶����

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{// ���f���̍\����
	LPD3DXMESH			pMesh;							// ���b�V��(���_���̏W�܂�)���ւ̃|�C���^
	LPD3DXBUFFER		pBuffMat;						// �}�e���A�����ւ̃|�C���^
	DWORD				nNumMat;						// �}�e���A�����̐�
	char				cAddressModel[MAX_ADDRESS];		// ���f���̃A�h���X������ϐ�
	D3DXVECTOR3			vtxMin, vtxMax;					// ���f���̍ŏ��l�E�ő�l
	LPDIRECT3DTEXTURE9	*pTexture;						// �e�N�X�`���ւ̃|�C���^
}ObjectModel;

typedef struct
{// �����蔻��̃I�t�Z�b�g�̍\����
	D3DXVECTOR3			pos;							// �ʒu
	D3DXVECTOR3			rot;							// ����
	D3DXMATRIX			mtxWorld;						// ���[���h�}�g���b�N�X
	int					nIdxParent;						// �e���f���̃C���f�b�N�X
	float				fRadius;						// ���a
}COLLISION_OBJECT;

typedef struct
{// �I�u�W�F�N�g�̍\����
	D3DXVECTOR3			pos;				// �ʒu
	D3DXVECTOR3			posOld;				// �O��̈ʒu
	D3DXVECTOR3			move;				// �ʒu�̈ړ���
	D3DXVECTOR3			rot;				// ����
	D3DXVECTOR3			rotDest;			// �ړI�̌���
	D3DXMATRIX			mtxWorld;			// ���[���h�}�g���b�N�X
	int					nIdyShadow;			// �e�̔ԍ�
	int					nCollisionType;		// �����蔻��̃^�C�v	0:��` 1:���a 2:�~��
	float				fRadius;			// ���a
	bool				bUse;				// �g���Ă��邩�ǂ���
	COLLISION_OBJECT	Collision;			// �����蔻��̍\����

	int					nIdxModel;			// �g�p���郂�f��
}Object;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
void FlowingObject(Object *pObject);		// ����Ă�������
void LoopObject(Object *pObject);			// �Ō�܂ŗ��ꂽ��߂鏈��
bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius);
void CubeCollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius, int nIdxObject, bool *bHit);		// ��`�̔���
bool SphiaCollisionObject(D3DXVECTOR3 *pPos,float fRadius,int nIdxObject);													// �~�̔���
void CollisionObjectAttack(D3DXVECTOR3 *pPos, float fRadius);
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTypeModel, int nCollisionType);
void TextLoadObject(void);											// �I�u�W�F�N�g���̓ǂݍ���
void FileLodeObject(int nIdxObject);								// X�t�@�C���̓ǂݍ���
void MinMaxSearchObject(int nIdxObject);							// ���⍂���̍ŏ��ő匟��
void SetPosOldObject(void);											// �O��̈ʒu�̕ۑ�
Object *GetObjectModel(void);										// �I�u�W�F�N�g���̎擾

#endif
