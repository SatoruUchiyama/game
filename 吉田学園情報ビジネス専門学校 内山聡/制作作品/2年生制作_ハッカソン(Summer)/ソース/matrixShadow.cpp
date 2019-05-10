//=========================================================================================================================
//
// ���e���� [matrixShadow.cpp]
// Author :
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "matrixShadow.h"
#include "light.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************

//=========================================================================================================================
// ����������
//=========================================================================================================================
void InitmatrixShadow(void)
{

}

//=========================================================================================================================
// �I������
//=========================================================================================================================
void UninitmatrixShadow(void)
{

}

//=========================================================================================================================
// �X�V����
//=========================================================================================================================
void UpdatematrixShadow(void)
{

}

//=========================================================================================================================
// �`�揈��
//=========================================================================================================================
void DrawmatrixShadow(void)
{

}

//=========================================================================================================================
// �e�ݒ菈��
//=========================================================================================================================
void SetmatrixShadow(D3DXMATRIX &mtxWorld, LPD3DXMESH &pMesh, DWORD &nNumMat, D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DLIGHT9 Light = GetLight();
	D3DXVECTOR4 vLightDirection = D3DXVECTOR4(Light.Direction, 0.0f);

	//�e�p�̎ˉe�}�g���N�X���쐬
	D3DXMATRIX mmatrixShadow;
	D3DXVECTOR3 vPoint = pos;
	D3DXVECTOR3 vNormal(0.0f, -1.0f, 0.0f);
	D3DXPLANE GroundPlane;
	D3DXPlaneFromPointNormal(&GroundPlane, &vPoint, &vNormal);
	D3DXMatrixShadow(&mmatrixShadow, &vLightDirection, &GroundPlane);

	mmatrixShadow = mtxWorld * mmatrixShadow;

	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�e�p�}�e���A���̐ݒ�
	D3DMATERIAL9 Material;
	ZeroMemory(&Material, sizeof(D3DMATERIAL9));
	Material.Emissive.a = 1.0f;
	Material.Emissive.r = 0.1f;
	Material.Emissive.g = 0.1f;
	Material.Emissive.b = 0.1f;

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);			// ���u�����h���~

	//�e�Ƃ��ă����_�����O
	pDevice->SetTransform(D3DTS_WORLD, &mmatrixShadow);
	pDevice->SetMaterial(&Material);
	for (int nCntMat = 0; nCntMat < (int)nNumMat; nCntMat++)
	{
		pMesh->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);				// ���݂̃}�e���A���߂�

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// ���u�����h���s��
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �e�𓊉e����ʒu�𒲂ׂ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
D3DXVECTOR3 CheckShadowPosition(D3DXVECTOR3 pos)
{
	// �ꎞ�ۑ��p
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, -100000.0f, 0.0f);		// �ʒu
	float fRange = 1000000.0f;										// ����

#if 0
	// �I�u�W�F�N�g�����擾
	Stage_objInfo *pStage_objInfo = GetStage_objInfo();
	// �I�u�W�F�N�g���擾
	Stage_obj *pStage_obj = GetStage_obj();
	// �I�u�W�F�N�g�̑������擾
	int nNumStage_obj = GetNumStage_obj();

	for (int nCntObj = 0; nCntObj < nNumStage_obj; nCntObj++, pStage_obj++)
	{// �I�u�W�F�N�g�̑���
		if (pos.y >= pStage_obj->pos.y + (pStage_objInfo + pStage_obj->nType)->vtxMax.y)
		{// �v���C���[�̈ʒu[Y]�����Ⴂ�ʒu�ɂ���ꍇ
		 // �v���C���[�̈ʒu[X,Z]�ɂ��߂��I�u�W�F�N�g�𒲂ׂ�
			float fRangeX = pos.x - pStage_obj->pos.x;
			float fRangeZ = pos.z - pStage_obj->pos.z;
			float fNowRange = fRangeX * fRangeX + fRangeZ * fRangeZ;

			if (fRange > fNowRange)
			{// �ł��߂��ʒu�̃I�u�W�F�N�g�̈ʒu����
				position.x = pStage_obj->pos.x;
				position.z = pStage_obj->pos.z;
				position.y = pStage_obj->pos.y + (pStage_objInfo + pStage_obj->nType)->vtxMax.y;
			}
		}
	}
#endif

	return position;
}