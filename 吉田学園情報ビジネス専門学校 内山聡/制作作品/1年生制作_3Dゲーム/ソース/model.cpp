//=============================================================================
//
// ���f������ [model.cpp]
// Author : 
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "ballet.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ATARI				(200)
#define MAX_ATARI2				(80)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//LPD3DXMESH g_pMeshModel[POLYGON_MODEL] = {};
Model g_aModel[POLYGON_MODEL];
//int g_nIdxShadow;
//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	int nCount2;
	for (nCount2 = 0; nCount2 < POLYGON_MODEL; nCount2++)
	{
		g_aModel[nCount2].g_VtxMinModel = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_aModel[nCount2].g_VtxMaxModel = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
	}
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCount3 = 0; nCount3 < POLYGON_MODEL; nCount3++)
	{
		g_aModel[nCount3].ModelType = MODEL_NOMAL;
		g_aModel[nCount3].pos = D3DXVECTOR3(0, 0, 0);
		g_aModel[nCount3].rot = D3DXVECTOR3(0, 0, 0);
		g_aModel[nCount3].bUse = false;
	}

	//g_nIdxShadow = SetShadow(g_posModel, g_rotModel);
	// X�t�@�C���̓ǂݍ���		tanknsu.x		car000.x �Ȃ���2.x�Η�2.x
	D3DXLoadMeshFromX("date\\model\\�u������2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[0].g_pBuffMatModel, NULL, &g_aModel[0].g_nNumMatModel, &g_aModel[0].g_pMeshModel[0]);
	D3DXLoadMeshFromX("date\\model\\���H.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[1].g_pBuffMatModel, NULL, &g_aModel[1].g_nNumMatModel, &g_aModel[1].g_pMeshModel[1]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[2].g_pBuffMatModel, NULL, &g_aModel[2].g_nNumMatModel, &g_aModel[2].g_pMeshModel[2]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[3].g_pBuffMatModel, NULL, &g_aModel[3].g_nNumMatModel, &g_aModel[3].g_pMeshModel[3]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[4].g_pBuffMatModel, NULL, &g_aModel[4].g_nNumMatModel, &g_aModel[4].g_pMeshModel[4]);
//	D3DXLoadMeshFromX("date\\model\\�͂��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[5].g_pBuffMatModel, NULL, &g_aModel[5].g_nNumMatModel, &g_aModel[5].g_pMeshModel[5]);
	//D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[3].g_pBuffMatModel, NULL, &g_aModel[3].g_nNumMatModel, &g_aModel[3].g_pMeshModel[3]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[5].g_pBuffMatModel, NULL, &g_aModel[5].g_nNumMatModel, &g_aModel[5].g_pMeshModel[5]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[6].g_pBuffMatModel, NULL, &g_aModel[6].g_nNumMatModel, &g_aModel[6].g_pMeshModel[6]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[7].g_pBuffMatModel, NULL, &g_aModel[7].g_nNumMatModel, &g_aModel[7].g_pMeshModel[7]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[8].g_pBuffMatModel, NULL, &g_aModel[8].g_nNumMatModel, &g_aModel[8].g_pMeshModel[8]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[9].g_pBuffMatModel, NULL, &g_aModel[9].g_nNumMatModel, &g_aModel[9].g_pMeshModel[9]);

	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[10].g_pBuffMatModel, NULL, &g_aModel[10].g_nNumMatModel, &g_aModel[10].g_pMeshModel[10]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[11].g_pBuffMatModel, NULL, &g_aModel[11].g_nNumMatModel, &g_aModel[11].g_pMeshModel[11]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[12].g_pBuffMatModel, NULL, &g_aModel[12].g_nNumMatModel, &g_aModel[12].g_pMeshModel[12]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[13].g_pBuffMatModel, NULL, &g_aModel[13].g_nNumMatModel, &g_aModel[13].g_pMeshModel[13]);
	D3DXLoadMeshFromX("date\\model\\���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[14].g_pBuffMatModel, NULL, &g_aModel[14].g_nNumMatModel, &g_aModel[14].g_pMeshModel[14]);

	D3DXLoadMeshFromX("date\\model\\��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[15].g_pBuffMatModel, NULL, &g_aModel[15].g_nNumMatModel, &g_aModel[15].g_pMeshModel[15]);
	D3DXLoadMeshFromX("date\\model\\��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[16].g_pBuffMatModel, NULL, &g_aModel[16].g_nNumMatModel, &g_aModel[16].g_pMeshModel[16]);
	D3DXLoadMeshFromX("date\\model\\��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[17].g_pBuffMatModel, NULL, &g_aModel[17].g_nNumMatModel, &g_aModel[17].g_pMeshModel[17]);
	D3DXLoadMeshFromX("date\\model\\��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[18].g_pBuffMatModel, NULL, &g_aModel[18].g_nNumMatModel, &g_aModel[18].g_pMeshModel[18]);
	D3DXLoadMeshFromX("date\\model\\��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[19].g_pBuffMatModel, NULL, &g_aModel[19].g_nNumMatModel, &g_aModel[19].g_pMeshModel[19]);

	D3DXLoadMeshFromX("date\\model\\��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[20].g_pBuffMatModel, NULL, &g_aModel[20].g_nNumMatModel, &g_aModel[20].g_pMeshModel[20]);
	D3DXLoadMeshFromX("date\\model\\��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[21].g_pBuffMatModel, NULL, &g_aModel[21].g_nNumMatModel, &g_aModel[21].g_pMeshModel[21]);
	D3DXLoadMeshFromX("date\\model\\��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[22].g_pBuffMatModel, NULL, &g_aModel[22].g_nNumMatModel, &g_aModel[22].g_pMeshModel[22]);
	D3DXLoadMeshFromX("date\\model\\��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[23].g_pBuffMatModel, NULL, &g_aModel[23].g_nNumMatModel, &g_aModel[23].g_pMeshModel[23]);
	D3DXLoadMeshFromX("date\\model\\��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[24].g_pBuffMatModel, NULL, &g_aModel[24].g_nNumMatModel, &g_aModel[24].g_pMeshModel[24]);



	int nNumVtx;			//���_��
	DWORD sizeFVF;			//���_�t�H�[�}�b�g7�̃T�C�Y
	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

	for (int nCount = 0; nCount < POLYGON_MODEL; nCount++)
	{
		//���_�����擾
		nNumVtx = g_aModel[nCount].g_pMeshModel[nCount]->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[nCount].g_pMeshModel[nCount]->GetFVF());
		//���_�o�b�t�@�����b�N
		g_aModel[nCount].g_pMeshModel[nCount]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
			//
			if (vtx.x < g_aModel[nCount].g_VtxMinModel.x)
			{
				g_aModel[nCount].g_VtxMinModel.x = vtx.x;
			}
			if (vtx.z < g_aModel[nCount].g_VtxMinModel.z)
			{
				g_aModel[nCount].g_VtxMinModel.z = vtx.z;
			}
			if (vtx.y < g_aModel[nCount].g_VtxMinModel.y)
			{
				g_aModel[nCount].g_VtxMinModel.y = vtx.y;
			}

			//
			if (vtx.x > g_aModel[nCount].g_VtxMaxModel.x)
			{
				g_aModel[nCount].g_VtxMaxModel.x = vtx.x;
			}
			if (vtx.z > g_aModel[nCount].g_VtxMaxModel.z)
			{
				g_aModel[nCount].g_VtxMaxModel.z = vtx.z;
			}
			if (vtx.y > g_aModel[nCount].g_VtxMaxModel.y)
			{
				g_aModel[nCount].g_VtxMaxModel.y = vtx.y;
			}
			pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�

		}
		//���_�o�b�t�@���A�����b�N
		g_aModel[nCount].g_pMeshModel[nCount]->UnlockVertexBuffer();
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	for (int nCount = 0; nCount < POLYGON_MODEL; nCount++)
	{
		// ���b�V���̊J��
		if (g_aModel[nCount].g_pMeshModel[nCount] != NULL)
		{
			g_aModel[nCount].g_pMeshModel[nCount]->Release();
			g_aModel[nCount].g_pMeshModel[nCount] = NULL;
		}
		// �}�e���A���̊J��
		if (g_aModel[nCount].g_pBuffMatModel != NULL)
		{
			g_aModel[nCount].g_pBuffMatModel->Release();
			g_aModel[nCount].g_pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	/*Player *pPlayer;

	pPlayer = GetPlayer();*/
	
	//Trigger
	//SetPositionShadow(g_nIdxShadow, g_posModel);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCount = 0; nCount < POLYGON_MODEL; nCount++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aModel[nCount].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCount].rot.y, g_aModel[nCount].rot.x, g_aModel[nCount].rot.z);
		D3DXMatrixMultiply(&g_aModel[nCount].mtxWorld, &g_aModel[nCount].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aModel[nCount].pos.x, g_aModel[nCount].pos.y, g_aModel[nCount].pos.z);
		D3DXMatrixMultiply(&g_aModel[nCount].mtxWorld, &g_aModel[nCount].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCount].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_aModel[nCount].g_pBuffMatModel->GetBufferPointer();

		for(int nCntMat = 0;nCntMat<(int)g_aModel[nCount].g_nNumMatModel;nCntMat++)
		{
			if (g_aModel[nCount].bUse == true)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
				// ���f��(�p�[�c)�̕`��
				g_aModel[nCount].g_pMeshModel[nCount]->DrawSubset(nCntMat);
			}
		}
		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// �Z�b�g���f��
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int Type)
{
	int nCntModel;

	for (nCntModel = 0; nCntModel < POLYGON_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{
			g_aModel[nCntModel].pos = pos;
			g_aModel[nCntModel].rot = rot;
			g_aModel[nCntModel].bUse = true;
			g_aModel[nCntModel].Type = Type;

			break;
		}
	}
}
//=============================================================================
// ���f���̓����蔻��
//=============================================================================
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	int nCount;
	bool bLand = false;
	for (nCount = 0; nCount < POLYGON_MODEL; nCount++)
	{
		if (pPos->x > g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMinModel.x && pPos->x < g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMaxModel.x)
		{
			if (pPosold->z >= g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMaxModel.z && pPos->z < g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMaxModel.z)
			{
				pPos->z = g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMaxModel.z;
			}
			else if (pPosold->z <= g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMinModel.z && pPos->z > g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMinModel.z)
			{
				pPos->z = g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMinModel.z;
			}
		}
		if (pPos->z > g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMinModel.z && pPos->z < g_aModel[nCount].pos.z + g_aModel[nCount].g_VtxMaxModel.z)
		{
			if (pPosold->x >= g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMaxModel.x && pPos->x < g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMaxModel.x)
			{
				pPos->x = g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMaxModel.x;
			}
			else if (pPosold->x <= g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMinModel.x && pPos->x > g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMinModel.x)
			{
				pPos->x = g_aModel[nCount].pos.x + g_aModel[nCount].g_VtxMinModel.x;
			}
		}
	}
	return bLand;
}