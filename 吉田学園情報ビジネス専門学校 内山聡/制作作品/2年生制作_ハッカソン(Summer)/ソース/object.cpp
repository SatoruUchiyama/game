//=============================================================================
//
// �I�u�W�F�N�g�̏��� [object.cpp]
// Author : ��������
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS		// �t�@�C���ǂݍ��݂ŕK�v
#include <stdio.h>					// �t�@�C���ǂݍ��݂ŕK�v
#include <string.h>					// �t�@�C���ǂݍ��݂ŕK�v

#include "object.h"					// �I�u�W�F�N�g���̃w�b�_�[
//#include "shadow.h"				// �e���̃w�b�_�[
//#include "explosion.h"			// �������̃w�b�_�[
//#include "particle.h"				// �p�[�e�B�N�����̃w�b�_�[
#include "game.h"					// �Q�[�����̃w�b�_�[
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OPEN_FILE_NAME						("data/TEXTFILE/model.txt")		// X�t�@�C���̃A�h���X
#define MAX_OBJECT_MODEL					(40)						// ���f���̎�ނ̍ő吔
//#define MAX_CHAR							(256)						// ��x�ɓǂݍ��߂镶����
#define OBJECT_FLOWING_SPEED				(WATER_SPEED)						// �����X�s�[�h
#define OBJECT_INERTIA_XZ					(0.15f)						// �����̌W��
#define OBJECT_MAX_DEPTH					(4000.0f)					// ��ԉ��̍��W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ObjectModel			g_ObjectModel[MAX_OBJECT_MODEL];		// ���f���̃|�C���^��A�h���X�̏��
Object				g_Object[MAX_OBJECT];					// �I�u�W�F�N�g�̏��
int					g_nMaxModel;							// ���f���̐�
int					g_nMaxTexture;							// �e�N�X�`���̐�

//=============================================================================
// ����������
//=============================================================================
void InitObject(void)
{
	// �I�u�W�F�N�g�̏�����
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{// �I�u�W�F�N�g�̑��������[�v
		g_Object[nCntObject].pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu�̏�����
		g_Object[nCntObject].posOld			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �O��̈ʒu�̏�����
		g_Object[nCntObject].move			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu�̈ړ��ʂ̏�����
		g_Object[nCntObject].rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �����̏�����
		g_Object[nCntObject].rotDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړI�̌�����������
		g_Object[nCntObject].nCollisionType = 0;											// �����蔻��̃^�C�v��������
		g_Object[nCntObject].fRadius		= 0.0f;											// ���a��������
		g_Object[nCntObject].bUse			= false;										// �g���ĂȂ���Ԃɏ�����

		// �����蔻��̕ϐ��̏�����
		g_Object[nCntObject].Collision.nIdxParent = -1;										// �I�t�Z�b�g�̈ʒu�̐e��ݒ�
		g_Object[nCntObject].Collision.pos.x = 0.0f;										// �I�t�Z�b�g�̂���̈ʒu��ݒ�
		g_Object[nCntObject].Collision.pos.y = 20.0f;										// �I�t�Z�b�g�̂���̈ʒu��ݒ�
		g_Object[nCntObject].Collision.pos.z = 0.0f;										// �I�t�Z�b�g�̂���̈ʒu��ݒ�
		g_Object[nCntObject].Collision.fRadius = 20.0f;										// ���a
	}

	// �I�u�W�F�N�g�̓ǂݍ���
	TextLoadObject();
}

//=============================================================================
// �I������
//=============================================================================
void UninitObject(void)
{
	for (int nCntModel = 0; nCntModel < MAX_OBJECT_MODEL; nCntModel++)
	{// ���f���̐������[�v

		// ���b�V���̊J��
		if (g_ObjectModel[nCntModel].pMesh != NULL)
		{// ���g�������Ă���
			g_ObjectModel[nCntModel].pMesh->Release();
			g_ObjectModel[nCntModel].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_ObjectModel[nCntModel].pBuffMat != NULL)
		{// ���g�������Ă���
			g_ObjectModel[nCntModel].pBuffMat->Release();
			g_ObjectModel[nCntModel].pBuffMat = NULL;
		}

		// �e�N�X�`���̊J��
		for (int nCntMat = 0; nCntMat < (int)g_ObjectModel[nCntModel].nNumMat; nCntMat++)
		{// �}�e���A���̐������[�v
			if (g_ObjectModel[nCntModel].pTexture[nCntMat] != NULL)
			{
				g_ObjectModel[nCntModel].pTexture[nCntMat]->Release();
				g_ObjectModel[nCntModel].pTexture[nCntMat] = NULL;
			}
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObject(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{// �I�u�W�F�N�g�̑��������[�v
		if (g_Object[nCntObject].bUse == true)
		{// �I�u�W�F�N�g���g���Ă�����
			// ����Ă�������
			FlowingObject(&g_Object[nCntObject]);

			// ���[�v����
			LoopObject(&g_Object[nCntObject]);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̏�����
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;							// �K�w�\���p�̃}�g���b�N�X
	D3DMATERIAL9 matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								// �}�e���A���f�[�^�ւ̃|�C���^

	//Z�o�b�t�@��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			// �����ŕ`�揇�𐮓ڂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);		// ���ڂ��鏇�̊��ݒ�


	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{// ���f���̐������[�v

		if (g_Object[nCntObject].bUse == true)
		{// �I�u�W�F�N�g���g���Ă���Ƃ�

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Object[nCntObject].mtxWorld);

			// ��](����)�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Object[nCntObject].rot.y,
				g_Object[nCntObject].rot.x,
				g_Object[nCntObject].rot.z);								// �Q�[���𐧍삷��Ƃ��͈�Ԏg���x����������

			D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorld,				// �Q�ԖڂƂR�Ԗڂ̈������|���Z���ꂽ�l����Ԗڂ̈����ɑ�����Ă���
				&g_Object[nCntObject].mtxWorld,
				&mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Object[nCntObject].pos.x,									// �ʒu��X���W�������Ă���
				g_Object[nCntObject].pos.y,
				g_Object[nCntObject].pos.z);

			D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorld,				// �Q�ԖڂƂR�Ԗڂ̈������|���Z���ꂽ�l����Ԗڂ̈����ɑ�����Ă���
				&g_Object[nCntObject].mtxWorld,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD,
				&g_Object[nCntObject].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_ObjectModel[g_Object[nCntObject].nIdxModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ObjectModel[g_Object[nCntObject].nIdxModel].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				if (g_ObjectModel[g_Object[nCntObject].nIdxModel].pTexture[nCntMat] != (LPDIRECT3DTEXTURE9)0xcdcdcdcd)
				{// �A�h���X��Ƀe�N�X�`�������݂���Ƃ�
					pDevice->SetTexture(0, g_ObjectModel[g_Object[nCntObject].nIdxModel].pTexture[nCntMat]);
				}
				// �I�u�W�F�N�g�̕`��
				g_ObjectModel[g_Object[nCntObject].nIdxModel].pMesh->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);


			//------------------------------------------------------------
			// �����蔻��̃��[���h�}�g���b�N�X�̐ݒ�
			//------------------------------------------------------------
			mtxParent = g_Object[nCntObject].mtxWorld;		// �e�̃��[���h�}�g���b�N�X����

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Object[nCntObject].Collision.mtxWorld);

			// ��](����)�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Object[nCntObject].Collision.rot.y,
				g_Object[nCntObject].Collision.rot.x,
				g_Object[nCntObject].Collision.rot.z);								// �Q�[���𐧍삷��Ƃ��͈�Ԏg���x����������

			D3DXMatrixMultiply(&g_Object[nCntObject].Collision.mtxWorld,			// �Q�ԖڂƂR�Ԗڂ̈������|���Z���ꂽ�l����Ԗڂ̈����ɑ�����Ă���
							   &g_Object[nCntObject].Collision.mtxWorld,
							   &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans,
								  g_Object[nCntObject].Collision.pos.x,				// �ʒu��X���W�������Ă���
								  g_Object[nCntObject].Collision.pos.y,
								  g_Object[nCntObject].Collision.pos.z);

			D3DXMatrixMultiply(&g_Object[nCntObject].Collision.mtxWorld,			// �Q�ԖڂƂR�Ԗڂ̈������|���Z���ꂽ�l����Ԗڂ̈����ɑ�����Ă���
							   &g_Object[nCntObject].Collision.mtxWorld,
							   &mtxTrans);

			D3DXMatrixMultiply(&g_Object[nCntObject].Collision.mtxWorld,			// �e�Ǝq�̃}�g���b�N�X���������킹��
							   &g_Object[nCntObject].Collision.mtxWorld,
							   &mtxParent);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD,&g_Object[nCntObject].Collision.mtxWorld);

		}
	}

	////Z�o�b�t�@��L���ɂ���
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);			// �����֌W�Ȃ������I�Ɏ�O�ɕ`�悷��
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		// �����ŕ`�揇�𐮓ڂ���

}

//=============================================================================
// �I�u�W�F�N�g�̗���鏈��
//=============================================================================
void FlowingObject(Object *pObject)
{
	// �����ړ���
	pObject->move.x += sinf(D3DX_PI * 1.0f) * -OBJECT_FLOWING_SPEED;
	pObject->move.z += cosf(D3DX_PI * 1.0f) * -OBJECT_FLOWING_SPEED;

	// ����
	pObject->move.x += (0.0f - pObject->move.x) * 0.1f;
	pObject->move.z += (0.0f - pObject->move.z) * 0.1f;

	// �I�u�W�F�N�g�̈ړ�
	pObject->pos += pObject->move;
}

//=============================================================================
// �Ō�܂ŗ��ꂽ��߂鏈��
//=============================================================================
void LoopObject(Object *pObject)
{
	if (pObject->pos.z < 0.0f)
	{// �Ō�܂ŗ��ꂽ��
		pObject->pos.z	  = OBJECT_MAX_DEPTH;		// ��ԉ��ɖ߂�
		pObject->posOld.z = OBJECT_MAX_DEPTH;		// ��ԉ��ɖ߂�
	}
}

//=============================================================================
// �I�u�W�F�N�g�̓����蔻��̏���
//=============================================================================
bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius)
{
	bool bHit = false;					// �I�u�W�F�N�g�ɓ����������ǂ���

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{// ���f���̐������[�v
		if (g_Object[nCntObject].bUse == true)
		{// �I�u�W�F�N�g���g���Ă���Ƃ�
			//----------------------------------------------------------
			// ���ꂼ��̓����蔻��
			//----------------------------------------------------------
			if (g_Object[nCntObject].nCollisionType == 0)
			{// ��`�̓����蔻��
				 CubeCollisionObject(pPos, pPosOld, pMove, fRadius, nCntObject,&bHit);
			}
			//----------------------------------------------------------
			// ���a(����)�̓����蔻��
			//----------------------------------------------------------
			else if(g_Object[nCntObject].nCollisionType == 1)
			{// ���a�̓����蔻��
				bHit = SphiaCollisionObject(pPos, fRadius, nCntObject);
			}
		}
	}
	return bHit;			// ���n�������ǂ�����Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̋�`�̓����蔻��
//=============================================================================
void CubeCollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius, int nIdxObject, bool *bHit)
{
	if (g_Object[nIdxObject].pos.y + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.y > pPos->y + fRadius &&
		g_Object[nIdxObject].pos.y + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.y <= pPos->y + fRadius)
	{// �v���C���[���I�u�W�F�N�g�͈͓̔��Ȃ�

		// �u���b�N�̓����蔻��
		if (g_Object[nIdxObject].posOld.x + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.x < pPosOld->x + fRadius &&
			g_Object[nIdxObject].posOld.x + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.x > pPosOld->x - fRadius)
		{// �I�u�W�F�N�g��X���͈͓̔��ɓ�������

			// �I�u�W�F�N�g�����
			if (g_Object[nIdxObject].posOld.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.z >= pPos->z + fRadius &&
				g_Object[nIdxObject].pos.z	  + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.z <  pPos->z + fRadius)
			{// �I�u�W�F�N�g��������̔���
				pPos->z = g_Object[nIdxObject].pos.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.z - fRadius;			// �I�u�W�F�N�g�̈ʒu��߂�
				*bHit = true;		// ���������t���O��Ԃ�
			}
			else if (g_Object[nIdxObject].posOld.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.z <= pPos->z - fRadius &&
				g_Object[nIdxObject].pos.z		   + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.z >  pPos->z - fRadius)
			{// �I�u�W�F�N�g����O����̔���
				pPos->z = g_Object[nIdxObject].pos.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.z + fRadius;			// �I�u�W�F�N�g�̈ʒu��߂�
				*bHit = true;		// ���������t���O��Ԃ�
			}

			if (g_Object[nIdxObject].posOld.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.z >= pPosOld->z + fRadius &&
				g_Object[nIdxObject].pos.z	  + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.z < pPos->z	 + fRadius)
			{// �I�u�W�F�N�g��������̔���
				pPos->z = g_Object[nIdxObject].pos.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.z - fRadius;			// �I�u�W�F�N�g�̈ʒu��߂�
				*bHit = true;		// ���������t���O��Ԃ�
			}
			else if (g_Object[nIdxObject].posOld.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.z <= pPosOld->z - fRadius &&
					 g_Object[nIdxObject].pos.z	   + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.z > pPos->z	  - fRadius)
			{// �I�u�W�F�N�g����O����̔���
				pPos->z = g_Object[nIdxObject].pos.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.z + fRadius;			// �I�u�W�F�N�g�̈ʒu��߂�
				*bHit = true;		// ���������t���O��Ԃ�
			}

		}
		if (g_Object[nIdxObject].posOld.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.z < pPosOld->z + fRadius &&
			g_Object[nIdxObject].posOld.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.z > pPosOld->z - fRadius)
		{// Z�����I�u�W�F�N�g�͈͓̔���������
			if (g_Object[nIdxObject].posOld.x + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.x >= pPosOld->x + fRadius &&
				g_Object[nIdxObject].pos.x	  + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.x < pPos->x	 + fRadius)
			{// ������̔���
				pPos->x = g_Object[nIdxObject].pos.x + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.x - fRadius;			// �I�u�W�F�N�g�̈ʒu��߂�
				*bHit = true;		// ���������t���O��Ԃ�
			}
			else if (g_Object[nIdxObject].posOld.x + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.x <= pPosOld->x - fRadius &&
					 g_Object[nIdxObject].pos.x	   + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.x > pPos->x	  - fRadius)
			{// �E����̔���
				pPos->x = g_Object[nIdxObject].pos.x + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.x + fRadius;			// �I�u�W�F�N�g�̈ʒu��߂�
				*bHit = true;		// ���������t���O��Ԃ�
			}
		}
	}
	if (g_Object[nIdxObject].pos.x + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.x < pPos->x + fRadius &&
		g_Object[nIdxObject].pos.x + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.x > pPos->x - fRadius &&
		g_Object[nIdxObject].pos.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMin.z < pPos->z + fRadius &&
		g_Object[nIdxObject].pos.z + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.z > pPos->z - fRadius)
	{// �I�u�W�F�N�g�͈͓̔���������
		if (g_Object[nIdxObject].pos.y + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.y <= pPosOld->y &&
			g_Object[nIdxObject].pos.y + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.y > pPos->y)
		{// �ォ��̔���
			pPos->y = g_Object[nIdxObject].pos.y + g_ObjectModel[g_Object[nIdxObject].nIdxModel].vtxMax.y;							// �I�u�W�F�N�g�̈ʒu��߂�
			pMove->y = 0.0f;																										// �������x��0.0�ɖ߂�
			*bHit = true;		// ���������t���O��Ԃ�
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�̔��a�̓����蔻��
//=============================================================================
bool SphiaCollisionObject(D3DXVECTOR3 *pPos, float fRadius, int nIdxObject)
{
	bool bHit = false;

	// �����蔻��̍��W�̋����̌v�Z
	float posX = (g_Object[nIdxObject].pos.x - pPos->x);	// (�G�̑̂̓����蔻��̍��W�|�U���̓����蔻��̍��W)��2�悷��
	float posZ = (g_Object[nIdxObject].pos.z - pPos->z);	// (�G�̑̂̓����蔻��̍��W�|�U���̓����蔻��̍��W)��2�悷��
	float fPosLenght = (posX * posX) + (posZ * posZ);		// ���ꂼ���2�悵�ċ������v�Z

	// �����蔻��̔��a�̋����̌v�Z
	float fRadiusLenght = (g_Object[nIdxObject].fRadius + fRadius) * (g_Object[nIdxObject].fRadius + fRadius);			// (�{�b�N�X�̔��a�|�U���̔��a)��2�悵�ċ������v�Z

	// ���W�̋����Ɣ��a�̋����̔�r
	if (fPosLenght  <  fRadiusLenght &&
		fPosLenght  > -fRadiusLenght )
	{// ���a�̋������A���W�̋����̂ق���������������
		float fPosAngle = atan2f(pPos->x - g_Object[nIdxObject].pos.x,										// �G�ƃL�����̈ʒu�̊p�x���v�Z
								 pPos->z - g_Object[nIdxObject].pos.z);

		pPos->x = g_Object[nIdxObject].pos.x + (sinf(fPosAngle)*(g_Object[nIdxObject].fRadius + fRadius));	// �L�����̈ʒu�����炷
		pPos->z = g_Object[nIdxObject].pos.z + (cosf(fPosAngle)*(g_Object[nIdxObject].fRadius + fRadius));	// �L�����̈ʒu�����炷

		bHit = true;		// ���������t���O�𗧂Ă�
	}

	return bHit;
}

//=============================================================================
// �I�u�W�F�N�g�̍U���̓����蔻��̏���
//=============================================================================
void CollisionObjectAttack(D3DXVECTOR3 *pPos, float fRadius)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{// ���f���̐������[�v
		if (g_Object[nCntObject].bUse == true)
		{// �I�u�W�F�N�g���g���Ă���Ƃ�

			// �����̌v�Z
			float posX = (g_Object[nCntObject].Collision.mtxWorld._41 - pPos->x);		// (�I�u�W�F�N�g�̈ʒu�|�U���ƈʒu)��2�悷��
			float posY = (g_Object[nCntObject].Collision.mtxWorld._42 - pPos->y);		// (�I�u�W�F�N�g�̈ʒu�|�U���ƈʒu)��2�悷��
			float posZ = (g_Object[nCntObject].Collision.mtxWorld._43 - pPos->z);		// (�I�u�W�F�N�g�̈ʒu�|�U���ƈʒu)��2�悷��
			float fPosLenght = (posX * posX) + (posY * posY) + (posZ * posZ);			// �I�u�W�F�N�g�ƍU���̋������v�Z

			// ���a�̌v�Z
			float fRadiusLenght = (g_Object[nCntObject].Collision.fRadius + fRadius) * (g_Object[nCntObject].Collision.fRadius + fRadius);			// (�I�u�W�F�N�g�̔��a�|�U���̔��a)��2�悵�ċ������v�Z

			// �U���ƃI�u�W�F�N�g�̓����蔻��
			if (fPosLenght  < fRadiusLenght &&
				fPosLenght  > -fRadiusLenght)
			{// �I�u�W�F�N�g�ƍU���̋��������A�I�u�W�F�N�g�̔��a+�e�̔��a�̂ق����傫��������
				g_Object[nCntObject].bUse = false;											// �I�u�W�F�N�g���폜
				//SetExplosion(D3DXVECTOR3(g_Object[nCntObject].Collision.mtxWorld._41,
				//						 g_Object[nCntObject].Collision.mtxWorld._42,
				//						 g_Object[nCntObject].Collision.mtxWorld._43));		// ������ݒu

				//DeleteShadow(g_Object[nCntObject].nIdyShadow);								// �e���폜
			}
		}
	}
}


//=============================================================================
// �I�u�W�F�N�g�̐ݒ�
//=============================================================================
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTypeModel, int nCollisionType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̏�����
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;							// �K�w�\���p�̃}�g���b�N�X

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{// ���f���̐������[�v
		if (g_Object[nCntObject].bUse == false)
		{// ���f�����g���Ă��Ȃ��Ƃ�
			g_Object[nCntObject].pos			= pos;								// �ʒu��ݒ�
			g_Object[nCntObject].posOld			= pos;								// �O��ʒu��ݒ�
			g_Object[nCntObject].rot			= rot;								// ������ݒ�
			g_Object[nCntObject].nIdxModel		= nTypeModel;						// �g�p���f����ݒ�
			g_Object[nCntObject].nCollisionType = nCollisionType;					// �����蔻��̃^�C�v��ݒ�

			// ���a�̐ݒ�
			if (g_Object[nCntObject].nCollisionType != 0)
			{// �����蔻��̃^�C�v�����a��������
				g_Object[nCntObject].fRadius = g_ObjectModel[nTypeModel].vtxMax.x;	// X�̍ő�l�𔼌a�Ƃ��Đݒ�
			}
			else
			{// ��`
				g_Object[nCntObject].fRadius = 0.0f;								// 0.0f�Őݒ�
			}

			g_Object[nCntObject].bUse = true;																	// �g���Ă����Ԃɐݒ�

			//----------------------------------------------------------------------------
			// ���[���h�}�g���N�X�̐ݒ�
			//----------------------------------------------------------------------------

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Object[nCntObject].mtxWorld);

			// ��](����)�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Object[nCntObject].rot.y,
				g_Object[nCntObject].rot.x,
				g_Object[nCntObject].rot.z);								// �Q�[���𐧍삷��Ƃ��͈�Ԏg���x����������

			D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorld,				// �Q�ԖڂƂR�Ԗڂ̈������|���Z���ꂽ�l����Ԗڂ̈����ɑ�����Ă���
				&g_Object[nCntObject].mtxWorld,
				&mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Object[nCntObject].pos.x,									// �ʒu��X���W�������Ă���
				g_Object[nCntObject].pos.y,
				g_Object[nCntObject].pos.z);

			D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorld,				// �Q�ԖڂƂR�Ԗڂ̈������|���Z���ꂽ�l����Ԗڂ̈����ɑ�����Ă���
				&g_Object[nCntObject].mtxWorld,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD,
				&g_Object[nCntObject].mtxWorld);

			mtxParent = g_Object[nCntObject].mtxWorld;						// �e�̃��[���h�}�g���b�N�X����

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Object[nCntObject].Collision.mtxWorld);

			// ��](����)�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Object[nCntObject].Collision.rot.y,
				g_Object[nCntObject].Collision.rot.x,
				g_Object[nCntObject].Collision.rot.z);									// �Q�[���𐧍삷��Ƃ��͈�Ԏg���x����������

			D3DXMatrixMultiply(&g_Object[nCntObject].Collision.mtxWorld,				// �Q�ԖڂƂR�Ԗڂ̈������|���Z���ꂽ�l����Ԗڂ̈����ɑ�����Ă���
				&g_Object[nCntObject].Collision.mtxWorld,
				&mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Object[nCntObject].Collision.pos.x,									// �ʒu��X���W�������Ă���
				g_Object[nCntObject].Collision.pos.y,
				g_Object[nCntObject].Collision.pos.z);

			D3DXMatrixMultiply(&g_Object[nCntObject].Collision.mtxWorld,				// �Q�ԖڂƂR�Ԗڂ̈������|���Z���ꂽ�l����Ԗڂ̈����ɑ�����Ă���
				&g_Object[nCntObject].Collision.mtxWorld,
				&mtxTrans);

			D3DXMatrixMultiply(&g_Object[nCntObject].Collision.mtxWorld,				// �e�Ǝq�̃}�g���b�N�X���������킹��
				&g_Object[nCntObject].Collision.mtxWorld,
				&mtxParent);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Object[nCntObject].Collision.mtxWorld);

			break;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g���̓ǂݍ���
//=============================================================================
void TextLoadObject(void)
{
	FILE *pFile = fopen(OPEN_FILE_NAME, "r");		// �ǂݍ��ރe�L�X�g�t�@�C���̃A�h���X

	// �ǂݍ��ނ��߂̕ϐ��錾
	char acLine[MAX_CHAR];							// 1�s�ۂ��ƋL�����邽�߂̕ϐ�
	char acData[MAX_CHAR];							// �ꕔ�̕����L�����邽�߂̕ϐ�

	int nCntModel = 0;								// �ǂݍ��ރ��f�����J�E���g����ϐ�
	int nTypeModel;									// �g�p���郂�f���̔ԍ�������ϐ�
	int nTypeCollision;								// �����蔻��̃^�C�v������ϐ�
	D3DXVECTOR3 pos;								// �ʒu������ϐ�
	D3DXVECTOR3 rot;								// ����������ϐ�

	if (pFile != NULL)
	{// �k���`�F�b�N

		while (fgets(&acLine[0], MAX_CHAR, pFile) != NULL)
		{
			sscanf(&acLine[0], "%s", &acData);				// �����f�[�^�ɃR�s�[

			if (strcmp(acData, "NUM_MODEL") == 0)
			{// NUM_MODEL����������
				sscanf(&acLine[0], "%s %s %d", &acData[0], &acData[0], &g_nMaxModel);	// ���f���̐����擾
			}
			else if (strcmp(acData, "MODEL_FILENAME") == 0)
			{// MODEL_FILENAME����������
				sscanf(&acLine[0], "%s %s %s",
									&acData[0],
									&acData[0],
									&g_ObjectModel[nCntModel].cAddressModel[0]);	// ���f���̃A�h���X���擾
				FileLodeObject(nCntModel);		// �t�@�C����ǂݍ���
				MinMaxSearchObject(nCntModel);	// �ŏ��ő������
				nCntModel++;					// �J�E���g��i�߂Ď��ɔ�����
			}
			else if (strcmp(acData, "MODELSET") == 0)
			{// MODELSET����������
				nTypeCollision = 0;										// �����蔻��̃^�C�v��������

				while (strcmp(acData, "END_MODELSET") != 0)
				{// END_MODELSET��������܂Ń��[�v����
					fgets(&acLine[0], MAXCHAR, pFile);					// �s���擾
					sscanf(&acLine[0], "%s", &acData);					// �f�[�^���R�s�[

					if (strcmp(acData, "TYPE") == 0)
					{// TYPE����������
						sscanf(&acLine[0], "%s %s %d", &acData[0], &acData[0], &nTypeModel);					// �g�p���郂�f���̔ԍ����擾
					}
					else if (strcmp(acData, "POS") == 0)
					{// POS����������
						sscanf(&acLine[0], "%s %s %f %f %f", &acData[0], &acData[0], &pos.x, &pos.y, &pos.z);	// �ʒu���擾
					}
					else if (strcmp(acData, "ROT") == 0)
					{// ROT����������
						sscanf(&acLine[0], "%s %s %f %f %f", &acData[0], &acData[0], &rot.x, &rot.y, &rot.z);	// �������擾
						rot.x = (D3DX_PI * 2 / 360 * rot.x);													// 3.14��2�{����360�x�Ŋ�����1�x���̒l���o���āA�e�L�X�g�̊p�x�ɂ���
						rot.y = (D3DX_PI * 2 / 360 * rot.y);													// 3.14��2�{����360�x�Ŋ�����1�x���̒l���o���āA�e�L�X�g�̊p�x�ɂ���
						rot.z = (D3DX_PI * 2 / 360 * rot.z);													// 3.14��2�{����360�x�Ŋ�����1�x���̒l���o���āA�e�L�X�g�̊p�x�ɂ���
					}
					else if (strcmp(acData, "COLLISION_TYPE") == 0)
					{// ROT����������
						sscanf(&acLine[0], "%s %s %d", &acData[0], &acData[0], &nTypeCollision);				// �����蔻��̃^�C�v���擾
					}

				}

				// �I�u�W�F�N�g�̐ݒu
				SetObject(pos, rot, nTypeModel, nTypeCollision);
			}

		}
			fclose(pFile);								// �J�����t�@�C�������
	}
}

//=============================================================================
// X�t�@�C���̓ǂݍ���
//=============================================================================
void FileLodeObject(int nIdxObject)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();				// �f�o�C�X�̎擾
	D3DXMATERIAL *pMat;										// �}�e���A���f�[�^�ւ̃|�C���^

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(g_ObjectModel[nIdxObject].cAddressModel,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ObjectModel[nIdxObject].pBuffMat,
		NULL,
		&g_ObjectModel[nIdxObject].nNumMat,
		&g_ObjectModel[nIdxObject].pMesh);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_ObjectModel[nIdxObject].pBuffMat->GetBufferPointer();

	g_ObjectModel[nIdxObject].pTexture = new LPDIRECT3DTEXTURE9[g_ObjectModel[nIdxObject].nNumMat];		// �}�e���A�����e�ʂ𑝂₷

	for (int nCntMat = 0; nCntMat < (int)g_ObjectModel[nIdxObject].nNumMat; nCntMat++)
	{// �}�e���A���̐������[�v
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// �e�N�X�`���̃A�h���X�����݂��Ă�����
			D3DXCreateTextureFromFile(pDevice,											// 3D�f�o�C�X�̃A�h���X
				pMat[nCntMat].pTextureFilename,					// �ǂݍ��ރe�N�X�`���̃t�@�C���̃A�h���X
				&g_ObjectModel[nIdxObject].pTexture[nCntMat]);		// �e�N�X�`���̃|�C���^�ɃA�h���X�ɐݒ肷��
		}
		else
		{// �e�N�X�`���̃A�h���X���Ȃ��Ȃ�
			g_ObjectModel[nIdxObject].pTexture[nCntMat] = NULL;							// NULL�ɐݒ肷��
		}
	}
}

//=============================================================================
// ���⍂���̍ŏ��ő匟��
//=============================================================================
void MinMaxSearchObject(int nIdxObject)
{
	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	// ���_�����擾
	nNumVtx = g_ObjectModel[nIdxObject].pMesh->GetNumVertices();

	// ���_�t�H�[�}�b�g���擾
	sizeFVF = D3DXGetFVFVertexSize(g_ObjectModel[nIdxObject].pMesh->GetFVF());

	// ���_�o�b�t�@�����b�N
	g_ObjectModel[nIdxObject].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{// ���_�������[�v
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// ���_���W�̑��

														// �ŏ��l�Ɣ�r
		if (g_ObjectModel[nIdxObject].vtxMin.x > vtx.x)
		{// �������Ă���ŏ��l��x�����������l��������
			g_ObjectModel[nIdxObject].vtxMin.x = vtx.x;						// �ŏ��l��x����
		}
		if (g_ObjectModel[nIdxObject].vtxMin.y > vtx.y)
		{// �������Ă���ŏ��l��y�����������l��������
			g_ObjectModel[nIdxObject].vtxMin.y = vtx.y;						// �ŏ��l��y����
		}
		if (g_ObjectModel[nIdxObject].vtxMin.z > vtx.z)
		{// �������Ă���ŏ��l��y�����������l��������
			g_ObjectModel[nIdxObject].vtxMin.z = vtx.z;						// �ŏ��l��z����
		}

		// �ő�l�Ɣ�r
		if (g_ObjectModel[nIdxObject].vtxMax.x < vtx.x)
		{// �������Ă���ő�l��x�����傫���l��������
			g_ObjectModel[nIdxObject].vtxMax.x = vtx.x;						// �ő�l��x����
		}
		if (g_ObjectModel[nIdxObject].vtxMax.y < vtx.y)
		{// �������Ă���ő�l��x�����傫���l��������
			g_ObjectModel[nIdxObject].vtxMax.y = vtx.y;						// �ő�l��y����
		}
		if (g_ObjectModel[nIdxObject].vtxMax.z < vtx.z)
		{// �������Ă���ő�l��x�����傫���l��������
			g_ObjectModel[nIdxObject].vtxMax.z = vtx.z;						// �ő�l��z����
		}

		pVtxBuff += sizeFVF;												// �|�C���^���T�C�Y���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_ObjectModel[nIdxObject].pMesh->UnlockVertexBuffer();

}

//=============================================================================
// �I�u�W�F�N�g�̑O��ʒu�̕ۑ�
//=============================================================================
void SetPosOldObject(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{// �I�u�W�F�N�g�̑��������[�v
		if (g_Object[nCntObject].bUse == true)
		{
			g_Object[nCntObject].posOld = g_Object[nCntObject].pos;		// �O��̈ʒu�̕ۑ�
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g���̎擾
//=============================================================================
Object *GetObjectModel(void)
{
	return &g_Object[0];
}