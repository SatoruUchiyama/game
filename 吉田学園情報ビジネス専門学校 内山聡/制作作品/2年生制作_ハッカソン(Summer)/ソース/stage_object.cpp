//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �X�e�[�W�̔z�u���̏��� [stage_object.cpp]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "stage_object.h"
#include "matrixShadow.h"
#include "line.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LOAD_STAGE_OBJ_FILE "data/TEXTFILE/Stage_Object.txt"	// �ǂݍ��݃t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void ScanVertexStage_obj(LPDIRECT3DDEVICE9 pDevice);		// ���_���W�̍ő�l�E�ŏ��l

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Stage_objInfo_Number g_aStage_objInfo_Number;		// �t�@�C���ǂݍ��ݏ�� [���,�ő吔]
Stage_objInfo g_aStage_objInfo[MAX_STAGE_OBJ];		// �t�@�C���ǂݍ��ݏ�� [���ʕ���]
Stage_obj g_aStage_obj[MAX_STAGE_OBJ];				// �I�u�W�F�N�g�̏��

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitStage_obj(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//++++++++++++++++++++
	// ----- ������ -----
	//++++++++++++++++++++
	// �I�u�W�F�N�g�̏��
	for (int nCntStage_Obj = 0; nCntStage_Obj < MAX_STAGE_OBJ; nCntStage_Obj++)
	{
		g_aStage_obj[nCntStage_Obj].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu�̏����ݒ�
		g_aStage_obj[nCntStage_Obj].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����̏����ݒ�
		g_aStage_obj[nCntStage_Obj].fHeight = 0.0f;								// ����
		g_aStage_obj[nCntStage_Obj].fRadius = 0.0f;								// ���a
		g_aStage_obj[nCntStage_Obj].nType = 0;									// ���
#if _DEBUG
		g_aStage_obj[nCntStage_Obj].IdxLine = 0;								// ��
#endif
	}

	//--- �t�@�C���ǂݍ��� ---//
	LoadStage_obj();	// �I�u�W�F�N�g���

	//++++++++++++++++++++++++++++++
	// ----- X�t�@�C���ǂݍ��� -----
	//++++++++++++++++++++++++++++++
	for (int nCntStage_Obj = 0; nCntStage_Obj < g_aStage_objInfo_Number.nTypeModel; nCntStage_Obj++)
	{
		D3DXLoadMeshFromX(g_aStage_objInfo[nCntStage_Obj].pXFileName,		// �ǂݍ���X�t�@�C����
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aStage_objInfo[nCntStage_Obj].pBuffMat,		// �}�e���A�����|�C���^
			NULL,
			&g_aStage_objInfo[nCntStage_Obj].NumMat,		// �}�e���A�����̐�
			&g_aStage_objInfo[nCntStage_Obj].pMesh);		// ���b�V�����|�C���^

		//+++++++++++++++++++++++++++++++++++
		// ----- �e�N�X�`���̓ǂݍ��� -----
		//+++++++++++++++++++++++++++++++++++
		// X�t�@�C��������o�����}�e���A����������
		D3DXMATERIAL *pMat;

		// X�t�@�C������}�e���A�������擾
		pMat = (D3DXMATERIAL*)g_aStage_objInfo[nCntStage_Obj].pBuffMat->GetBufferPointer();

		// �e�N�X�`���̃|�C���^���}�e���A�����̐����z��
		g_aStage_objInfo[nCntStage_Obj].pTexture = new LPDIRECT3DTEXTURE9[(int)g_aStage_objInfo[nCntStage_Obj].NumMat];	// int�^�ɒ���

		// �擾�����t�@�C���������
		for (int nCntNumMat = 0; nCntNumMat < (int)g_aStage_objInfo[nCntStage_Obj].NumMat; nCntNumMat++)	// DWORD�^����int�^�ɕϊ�����
		{
			// �e�N�X�`���̃|�C���^������
			g_aStage_objInfo[nCntStage_Obj].pTexture[nCntNumMat] = NULL;

			// �e�N�X�`���t�@�C�����������Ă���ꍇ�A�ǂݍ���
			if (pMat[nCntNumMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntNumMat].pTextureFilename, &g_aStage_objInfo[nCntStage_Obj].pTexture[nCntNumMat]);
			}
		}
	}

	//++++++++++++++++++++++++++++++++++++++++
	// ----- ���_���W�̍ő�l�E�ŏ��l -----
	//++++++++++++++++++++++++++++++++++++++++
	ScanVertexStage_obj(pDevice);

	// ���[�h���擾
	MODE pMode = GetMode();

	if (pMode == MODE_GAME)
	{
		for (int nCntStage_Obj = 0; nCntStage_Obj < g_aStage_objInfo_Number.nMaxModel; nCntStage_Obj++)
		{
#if _DEBUG
			// ���̐ݒ�
			SetColisionLine(g_aStage_obj[nCntStage_Obj].pos, g_aStage_objInfo[g_aStage_obj[nCntStage_Obj].nType].vtxMax, g_aStage_objInfo[g_aStage_obj[nCntStage_Obj].nType].vtxMin);
#endif
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitStage_obj(void)
{
	//--- �ǂݍ��ݏ��̔j�� ---//
	UnloadStage_obj();	// �I�u�W�F�N�g���
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateStage_obj(void)
{
	// ���[�h���擾
	MODE pMode = GetMode();

	if (pMode == MODE_GAME)
	{
		for (int nCntStage_Obj = 0; nCntStage_Obj < g_aStage_objInfo_Number.nMaxModel; nCntStage_Obj++)
		{
#if _DEBUG
			// ���̈ړ�
			SetPositionLine(g_aStage_obj[nCntStage_Obj].IdxLine, g_aStage_obj[nCntStage_Obj].pos);
#endif
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawStage_obj(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								// �}�e���A���ւ̃|�C���^

	for (int nCntStage_Obj = 0; nCntStage_Obj < g_aStage_objInfo_Number.nMaxModel; nCntStage_Obj++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aStage_obj[nCntStage_Obj].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aStage_obj[nCntStage_Obj].rot.y, g_aStage_obj[nCntStage_Obj].rot.x, g_aStage_obj[nCntStage_Obj].rot.z);
		D3DXMatrixMultiply(&g_aStage_obj[nCntStage_Obj].mtxWorld,
			&g_aStage_obj[nCntStage_Obj].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_aStage_obj[nCntStage_Obj].pos.x, g_aStage_obj[nCntStage_Obj].pos.y, g_aStage_obj[nCntStage_Obj].pos.z);
		D3DXMatrixMultiply(&g_aStage_obj[nCntStage_Obj].mtxWorld,
			&g_aStage_obj[nCntStage_Obj].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aStage_obj[nCntStage_Obj].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_aStage_objInfo[g_aStage_obj[nCntStage_Obj].nType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aStage_objInfo[g_aStage_obj[nCntStage_Obj].nType].NumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̔��f
			pDevice->SetTexture(0, g_aStage_objInfo[g_aStage_obj[nCntStage_Obj].nType].pTexture[nCntMat]);

			// ���f��(�p�[�c)�̕`��
			g_aStage_objInfo[g_aStage_obj[nCntStage_Obj].nType].pMesh->DrawSubset(nCntMat);
#if 0
			// ���e����
			SetmatrixShadow(g_aStage_obj[nCntStage_Obj].mtxWorld, g_aStage_objInfo[g_aStage_obj[nCntStage_Obj].nType].pMesh,
				g_aStage_objInfo[g_aStage_obj[nCntStage_Obj].nType].NumMat, CheckShadowPosition(g_aStage_obj[nCntStage_Obj].pos));
#endif
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���_�̍ő�l�E�ŏ��l
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void ScanVertexStage_obj(LPDIRECT3DDEVICE9 pDevice)
{
	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	for (int nCntStage_Obj = 0; nCntStage_Obj < g_aStage_objInfo_Number.nTypeModel; nCntStage_Obj++)
	{
		// ���_�����擾
		nNumVtx = g_aStage_objInfo[nCntStage_Obj].pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aStage_objInfo[nCntStage_Obj].pMesh->GetFVF());

		// ���_�o�b�t�@�����b�N
		g_aStage_objInfo[nCntStage_Obj].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// ���_���W�̑��

			// X
			if (g_aStage_objInfo[nCntStage_Obj].vtxMin.x > vtx.x)
			{
				g_aStage_objInfo[nCntStage_Obj].vtxMin.x = vtx.x;
			}
			else if (g_aStage_objInfo[nCntStage_Obj].vtxMax.x < vtx.x)
			{
				g_aStage_objInfo[nCntStage_Obj].vtxMax.x = vtx.x;
			}

			// Z
			if (g_aStage_objInfo[nCntStage_Obj].vtxMin.z > vtx.z)
			{
				g_aStage_objInfo[nCntStage_Obj].vtxMin.z = vtx.z;
			}
			else if (g_aStage_objInfo[nCntStage_Obj].vtxMax.z < vtx.z)
			{
				g_aStage_objInfo[nCntStage_Obj].vtxMax.z = vtx.z;
			}

			// Y
			if (g_aStage_objInfo[nCntStage_Obj].vtxMin.y > vtx.y)
			{
				g_aStage_objInfo[nCntStage_Obj].vtxMin.y = vtx.y;
			}
			else if (g_aStage_objInfo[nCntStage_Obj].vtxMax.y < vtx.y)
			{
				g_aStage_objInfo[nCntStage_Obj].vtxMax.y = vtx.y;
			}

			pVtxBuff += sizeFVF;		// �T�C�Y���|�C���^��i�߂�
		}
		// ���_�o�b�t�@���A�����b�N
		g_aStage_objInfo[nCntStage_Obj].pMesh->UnlockVertexBuffer();
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I�u�W�F�N�g�̓����蔻��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool CollisionStage_obj(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius, float fHeight)
{
	// �I�u�W�F�N�g�ɏ���Ă��邩�ǂ���
	bool bOnTheObj = false;

	for (int nCntFieldStage_obj = 0; nCntFieldStage_obj < g_aStage_objInfo_Number.nMaxModel; nCntFieldStage_obj++)
	{
		/* X - Z */
		if (g_aStage_obj[nCntFieldStage_obj].pos.y + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.y <= pPos->y + fHeight &&
			pPos->y <= g_aStage_obj[nCntFieldStage_obj].pos.y + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.y)
		{// [Y]�͈͓̔��̏ꍇ
			if (g_aStage_obj[nCntFieldStage_obj].pos.x + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.x <= pPos->x + fRadius &&
				pPos->x - fRadius <= g_aStage_obj[nCntFieldStage_obj].pos.x + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.x)
			{// [X]�͈͓̔��̏ꍇ
				// [Z]�̓����蔻��
				if (pPosOld->z + fRadius <= g_aStage_obj[nCntFieldStage_obj].pos.z + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.z &&
					pPos->z + fRadius > g_aStage_obj[nCntFieldStage_obj].pos.z + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.z)
				{// Z [-]����Ԃ������ꍇ
					pMove->z = 0.0f;
					pPos->z = g_aStage_obj[nCntFieldStage_obj].pos.z + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.z - fRadius;
				}
				else if (pPosOld->z - fRadius >= g_aStage_obj[nCntFieldStage_obj].pos.z + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.z &&
					pPos->z - fRadius < g_aStage_obj[nCntFieldStage_obj].pos.z + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.z)
				{// Z [+]����Ԃ������ꍇ
					pMove->z = 0.0f;
					pPos->z = g_aStage_obj[nCntFieldStage_obj].pos.z + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.z + fRadius;
				}
			}
			if (g_aStage_obj[nCntFieldStage_obj].pos.z + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.z <= pPos->z + fRadius &&
				pPos->z - fRadius <= g_aStage_obj[nCntFieldStage_obj].pos.z + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.z)
			{// [Z]�͈͓̔��̏ꍇ
				// [X]�̓����蔻��
				if (pPosOld->x + fRadius <= g_aStage_obj[nCntFieldStage_obj].pos.x + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.x &&
					pPos->x + fRadius > g_aStage_obj[nCntFieldStage_obj].pos.x + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.x)
				{// X [-]����Ԃ������ꍇ
					pMove->x = 0.0f;
					pPos->x = g_aStage_obj[nCntFieldStage_obj].pos.x + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.x - fRadius;
				}
				else if (pPosOld->x - fRadius >= g_aStage_obj[nCntFieldStage_obj].pos.x + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.x &&
					pPos->x - fRadius < g_aStage_obj[nCntFieldStage_obj].pos.x + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.x)
				{// X [+]����Ԃ������ꍇ
					pMove->x = 0.0f;
					pPos->x = g_aStage_obj[nCntFieldStage_obj].pos.x + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.x + fRadius;
				}
			}

		}
		/* Y */
		if (g_aStage_obj[nCntFieldStage_obj].pos.x + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.x <= pPos->x + fRadius &&
			pPos->x - fRadius <= g_aStage_obj[nCntFieldStage_obj].pos.x + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.x &&
			g_aStage_obj[nCntFieldStage_obj].pos.z + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.z <= pPos->z + fRadius &&
			pPos->z - fRadius < g_aStage_obj[nCntFieldStage_obj].pos.z + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.z)
		{// [X - Z]�͈͓̔��̏ꍇ
				// [Y]�̓����蔻��
			if (pPosOld->y >= g_aStage_obj[nCntFieldStage_obj].pos.y + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.y &&
				pPos->y < g_aStage_obj[nCntFieldStage_obj].pos.y + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.y)
			{// Y [+]����Ԃ������ꍇ
				// ���n���
				bOnTheObj = true;
				pMove->y = 0.0f;
				pPos->y = g_aStage_obj[nCntFieldStage_obj].pos.y + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMax.y;
			}
			else if (pPosOld->y + fHeight <= g_aStage_obj[nCntFieldStage_obj].pos.y + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.y &&
				pPos->y + fHeight > g_aStage_obj[nCntFieldStage_obj].pos.y + g_aStage_objInfo[g_aStage_obj[nCntFieldStage_obj].nType].vtxMin.y)
			{// Y [-]����Ԃ������ꍇ
				pMove->y = 0.0f;
			}
		}
	}

	return bOnTheObj;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I�u�W�F�N�g�ǂݍ���
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LoadStage_obj(void)
{
	//--- �ǂݍ��ރI�u�W�F�N�g���̏����� ---//
	// �t�@�C���ǂݍ��ݏ�� [���,�ő吔] �̏�����
	g_aStage_objInfo_Number.nTypeModel = 0;		// �ǂݍ��ރ��f���̍ő吔
	g_aStage_objInfo_Number.nMaxModel = 0;		// �\�����郂�f���̍ő吔
	// �t�@�C���ǂݍ��ݏ�� [���ʕ���]
	for (int nCntStage_ObjInfo = 0; nCntStage_ObjInfo < MAX_STAGE_OBJINFO; nCntStage_ObjInfo++)
	{
		for (int nText = 0; nText < MAX_CHAR; nText++)
		{
			g_aStage_objInfo[nCntStage_ObjInfo].pXFileName[nText] = NULL;
		}
		g_aStage_objInfo[nCntStage_ObjInfo].pMesh = NULL;
		g_aStage_objInfo[nCntStage_ObjInfo].pBuffMat = NULL;
		g_aStage_objInfo[nCntStage_ObjInfo].NumMat = 0;
		g_aStage_objInfo[nCntStage_ObjInfo].pTexture = NULL;
		g_aStage_objInfo[nCntStage_ObjInfo].vtxMin = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);
		g_aStage_objInfo[nCntStage_ObjInfo].vtxMax = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	}

	// ���[�J���ϐ��錾
	FILE *pFile;				// �t�@�C���̃|�C���^
	char ReadText[256];			// �ǂݍ��񂾕���������Ă���
	char HeadText[256];			// ��r�p
	char DustBox[256];			// �g�p���Ȃ����̂����Ă���
	int nCntText = 0;

	// �t�@�C���I�[�v��
	pFile = fopen(LOAD_STAGE_OBJ_FILE, "r");		// �t�@�C�����J��[�ǂݍ��݌^]

	if (pFile != NULL)		// �t�@�C������ł͂Ȃ�
	{//�t�@�C�����J�����ꍇ
		while (strcmp(HeadText, "SCRIPT") != 0)
		{// "SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
			fgets(ReadText, sizeof(ReadText), pFile);
			sscanf(ReadText, "%s", HeadText);
		}

		if (strcmp(HeadText, "SCRIPT") == 0)
		{// "SCRIPT" ���ǂݎ�ꂽ�ꍇ�A�����J�n
			while (strcmp(HeadText, "END_SCRIPT") != 0)
			{// "END_SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
				fgets(ReadText, sizeof(ReadText), pFile);
				sscanf(ReadText, "%s", HeadText);

				if (strcmp(HeadText, "\n") == 0)
				{// ��4����̐擪�� [\n](���s) �̏ꍇ�������Ȃ�
					int nCnt = 0;
				}
				else if (strcmp(HeadText, "NUM_MODEL") == 0)
				{// �ǂݍ��ރ��f���̍ő吔
					sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_aStage_objInfo_Number.nTypeModel);
				}
				else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
				{// ���f���t�@�C����
					if (g_aStage_objInfo_Number.nTypeModel > nCntText)
					{// �ő吔�ȏ㏈�����Ȃ�
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, &g_aStage_objInfo[nCntText].pXFileName[0]);
						nCntText++;		// ���̏ꏊ�ɐi�߂�
					}
				}
				else if (strcmp(HeadText, "MODELSET") == 0)
				{// �z�u���
					while (strcmp(HeadText, "END_MODELSET") != 0)
					{// "END_MODELSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
						fgets(ReadText, sizeof(ReadText), pFile);
						sscanf(ReadText, "%s", HeadText);

						if (strcmp(HeadText, "TYPE") == 0)
						{// ���
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_aStage_obj[g_aStage_objInfo_Number.nMaxModel].nType);
						}
						else if (strcmp(HeadText, "POS") == 0)
						{// �ʒu
							sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox, &g_aStage_obj[g_aStage_objInfo_Number.nMaxModel].pos.x, &g_aStage_obj[g_aStage_objInfo_Number.nMaxModel].pos.y, &g_aStage_obj[g_aStage_objInfo_Number.nMaxModel].pos.z);
						}
						else if (strcmp(HeadText, "ROT") == 0)
						{// ����
							sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox, &g_aStage_obj[g_aStage_objInfo_Number.nMaxModel].rot.x, &g_aStage_obj[g_aStage_objInfo_Number.nMaxModel].rot.y, &g_aStage_obj[g_aStage_objInfo_Number.nMaxModel].rot.z);
						}
						else if (strcmp(HeadText, "HEIGHT") == 0)
						{// ����
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_aStage_obj[g_aStage_objInfo_Number.nMaxModel].fHeight);
						}
						else if (strcmp(HeadText, "RADIUS") == 0)
						{// ���a
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_aStage_obj[g_aStage_objInfo_Number.nMaxModel].fRadius);
						}
					}
					g_aStage_objInfo_Number.nMaxModel++;
				}
			}
			// �t�@�C���N���[�Y
			fclose(pFile);
		}
	}
	else
	{// �J���Ȃ������ꍇ
		MessageBox(NULL, "�X�e�[�W�z�u���t�@�C�����J���܂���ł����B", NULL, MB_OK);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I�u�W�F�N�g�j��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UnloadStage_obj(void)
{
	//--- �ǂݍ��񂾃I�u�W�F�N�g���̔j�� ---//
	// �t�@�C���ǂݍ��ݏ�� [���,�ő吔]
	g_aStage_objInfo_Number.nTypeModel = 0;		// �ǂݍ��ރ��f���̍ő吔
	g_aStage_objInfo_Number.nMaxModel = 0;		// �\�����郂�f���̍ő吔
	// �t�@�C���ǂݍ��ݏ�� [���ʕ���]
	for (int nCntStage_ObjInfo = 0; nCntStage_ObjInfo < MAX_STAGE_OBJINFO; nCntStage_ObjInfo++)
	{
		for (int nText = 0; nText < MAX_CHAR; nText++)
		{
			if (g_aStage_objInfo[nCntStage_ObjInfo].pXFileName[nText] != NULL)
			{
				g_aStage_objInfo[nCntStage_ObjInfo].pXFileName[nText] = NULL;
			}
		}
		if (g_aStage_objInfo[nCntStage_ObjInfo].pMesh != NULL)
		{// ���b�V�����ւ̃|�C���^
			g_aStage_objInfo[nCntStage_ObjInfo].pMesh->Release();
			g_aStage_objInfo[nCntStage_ObjInfo].pMesh = NULL;
		}
		if (g_aStage_objInfo[nCntStage_ObjInfo].pBuffMat != NULL)
		{// �}�e���A�����ւ̃|�C���^
			g_aStage_objInfo[nCntStage_ObjInfo].pBuffMat->Release();
			g_aStage_objInfo[nCntStage_ObjInfo].pBuffMat = NULL;
		}
		for (int nCntMat = 0; nCntMat < (int)g_aStage_objInfo[nCntStage_ObjInfo].NumMat; nCntMat++)
		{// �}�e���A���̐�
			if (g_aStage_objInfo[nCntStage_ObjInfo].pTexture[nCntMat] != NULL)
			{// �e�N�X�`���ւ̃|�C���^
				g_aStage_objInfo[nCntStage_ObjInfo].pTexture[nCntMat]->Release();
				g_aStage_objInfo[nCntStage_ObjInfo].pTexture[nCntMat] = NULL;
			}
		}
		g_aStage_objInfo[nCntStage_ObjInfo].NumMat = 0;
		g_aStage_objInfo[nCntStage_ObjInfo].vtxMin = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);
		g_aStage_objInfo[nCntStage_ObjInfo].vtxMax = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	}

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I�u�W�F�N�g�̎擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Stage_obj *GetStage_obj(void)
{
	return &g_aStage_obj[0];
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I�u�W�F�N�g�̎擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Stage_objInfo *GetStage_objInfo(void)
{
	return &g_aStage_objInfo[0];
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I�u�W�F�N�g�̑����̎擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int GetNumStage_obj(void)
{
	return g_aStage_objInfo_Number.nMaxModel;
}