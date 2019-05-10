//=============================================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author : 
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"
#include "player.h"
#include "fade.h"
#include "score.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_WALL			(1)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Billboard g_aBillboard[MAX_WALL];

// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureBillboard = NULL;
//���_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;
//�A�C�e���̃J�E���^�[
int nCoinCount;
int nCountPotatoCount = 0;
int nCountPotato= 0;

//=============================================================================
// ����������
//=============================================================================
void InitBillboard(void)
{
	int nCntBill;
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntBill = 0; nCntBill < MAX_WALL; nCntBill++)
	{
		g_aBillboard[nCntBill].pos = D3DXVECTOR3(0, 0, 0);
		g_aBillboard[nCntBill].rot = D3DXVECTOR3(0, 0, 0);
		g_aBillboard[nCntBill].move = D3DXVECTOR3(0, 0, 0);
		g_aBillboard[nCntBill].col =  D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aBillboard[nCntBill].g_nIdxShadow = 0;
		nCoinCount = 0;
		g_aBillboard[nCntBill].bUse = false;
	}

	D3DXCreateTextureFromFile			// �e�N�X�`���̓ǂݍ���
	(
		pDevice,
		"date\\TEXTURE\\thOVLTTVLV.png",
		&g_pTextureBillboard
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBillboard, NULL);


	VERTEX_3D*pVtx;								//���_���ւ̃|�C���^
												//�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBill = 0; nCntBill < MAX_WALL; nCntBill++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-20, 40, 0.0);
		pVtx[1].pos = D3DXVECTOR3(20, 40, 0.0);
		pVtx[2].pos = D3DXVECTOR3(-20, 0.0, 0.0);
		pVtx[3].pos = D3DXVECTOR3(20, 0.0, 0.0);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[1].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[2].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[3].nor = D3DXVECTOR3(0.0, 0.0, -1.0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);

		////�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
		
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBillboard(void)
{
	//// �e�N�X�`���̊J��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
	
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBillboard(void)
{
	int nCount = 0;
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCount; nCount < MAX_WALL; nCount++)
	{
		if (g_aBillboard[nCount].bUse == true)
		{
			//g_aBillboard[nCount].bUse = false;
			//Item�������@�X�R�A�����Z
			//Item�����ׂĎ������TIMER������
			if (g_aBillboard[nCount].pos.x - 20 < pPlayer->pos.x &&
				g_aBillboard[nCount].pos.x + 20 > pPlayer->pos.x &&
				g_aBillboard[nCount].pos.z - 20 < pPlayer->pos.z &&
				g_aBillboard[nCount].pos.z + 20 > pPlayer->pos.z )
			{
				AddScore(1000);
				g_aBillboard[nCount].bUse = false;
				nCoinCount--;
				if (nCoinCount == 0)
				{
					SetFade(MODE_RESULT);
				}
			}
		}
	}
	

	//nCountPotatoCount++;
	//if (nCountPotatoCount == 180) 
	//{
	//	//g_aBillboard[0].rot.z = (rand() % 50) * ((rand() % 80) - 1.0f);
	//	g_aBillboard[0].pos.z = (rand() % 10)* ((rand() % 80) + 1.0f);
	//	//g_aBillboard[0].pos.z =(rand() % 50) / -100.0f;
	//	nCountPotatoCount = 0;
	//}
	nCountPotato++;
	if (nCountPotato == 240)
	{
		//g_aBillboard[0].rot.z = (rand() % 50) * ((rand() % 80) - 1.0f);
		g_aBillboard[0].move.x = (rand() % 600 + 1) * 0.01f;
		g_aBillboard[0].move.z = (rand() % 600 + 1) * 0.01f;
		//g_aBillboard[0].pos.z =(rand() % 50) / -100.0f;
		nCountPotato = 0;
	}

	if (g_aBillboard[0].pos.x + g_aBillboard[0].move.x > 900 || g_aBillboard[0].pos.x + g_aBillboard[0].move.x < -100)
	{
		g_aBillboard[0].move.x *= -1;
	}
	if (g_aBillboard[0].pos.z + g_aBillboard[0].move.z > 100 || g_aBillboard[0].pos.z + g_aBillboard[0].move.z < -900)
	{
		g_aBillboard[0].move.z *= -1;
	}

	g_aBillboard[0].pos += g_aBillboard[0].move;

	if (GetKeyboardPress(DIK_W) == true)
	{
		g_aBillboard[0].pos.x += 5;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_aBillboard[0].pos.z -= 5;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	int nCntBillboard;
	int nCntBill;

	//�A���t�@�e�X�g����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntBillboard = 0; nCntBillboard < MAX_WALL; nCntBillboard++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		
		g_aBillboard[nCntBillboard].mtxWorld._11 = mtxView._11;
		g_aBillboard[nCntBillboard].mtxWorld._12 = mtxView._21;
		g_aBillboard[nCntBillboard].mtxWorld._13 = mtxView._31;
		g_aBillboard[nCntBillboard].mtxWorld._21 = mtxView._12;
		g_aBillboard[nCntBillboard].mtxWorld._22 = mtxView._22;
		g_aBillboard[nCntBillboard].mtxWorld._23 = mtxView._32;
		g_aBillboard[nCntBillboard].mtxWorld._31 = mtxView._13;
		g_aBillboard[nCntBillboard].mtxWorld._32 = mtxView._23;
		g_aBillboard[nCntBillboard].mtxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
		D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		for (nCntBill = 0; nCntBill < MAX_WALL; nCntBill++)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBillboard);

			if (g_aBillboard[nCntBillboard].bUse == true)
			{
				// �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCntBillboard, 2);
			}
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// �Z�b�g����
//=============================================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	int nCntItem;
//	VERTEX_3D *pVtx;

	//g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_WALL; nCntItem++)
	{

		if (g_aBillboard[nCntItem].bUse == false)
		{
			nCoinCount++;
			g_aBillboard[nCntItem].pos = pos;
			g_aBillboard[nCntItem].rot = rot;
			g_aBillboard[nCntItem].col = col;
			/*pVtx[nCntItem].pos = D3DXVECTOR3(g_aBillboard[nCntItem].pos.x - 30, g_aBillboard[nCntItem].pos.y - 30, 0.0f);
			pVtx[nCntItem].pos = D3DXVECTOR3(g_aBillboard[nCntItem].pos.x + 30, g_aBillboard[nCntItem].pos.y - 30, 0.0f);
			pVtx[nCntItem].pos = D3DXVECTOR3(g_aBillboard[nCntItem].pos.x - 30, g_aBillboard[nCntItem].pos.y, 0.0f);
			pVtx[nCntItem].pos = D3DXVECTOR3(g_aBillboard[nCntItem].pos.x + 30, g_aBillboard[nCntItem].pos.y, 0.0f);*/
			//g_aBillboard[nCntItem].g_nIdxShadow = SetShadow(g_aBillboard[nCntItem].pos, g_aBillboard[nCntItem].rot);
			g_aBillboard[nCntItem].bUse = true;
			break;
		}
		/*pVtx += 4;*/

	}
	//g_pVtxBuffBillboard->Unlock();
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}
//double Uniform(void) {
//	return (g_aBillboard[0].pos.z +=(double)rand() + 1.0f) / ((double)RAND_MAX + 2.0f);
//}

//double rand_Lnormal(double mu, double sigma) {
//	double z = mu + sigma*sqrt(-2.0*log(Uniform()))*sin(2.0*D3DX_PI*Uniform());//gauss random number
//	return exp(z);
//}

//double rand_gamma(double theta, double kappa) {
//
//	int int_kappa;
//	double frac_kappa;
//
//	int_kappa = (int)kappa;
//	frac_kappa = kappa - (double)int_kappa;
//
//	double u, uu;
//	double b, p, x_frac, x_int;
//	int i;
//
//	/*integer part*/
//	x_int = 0;
//	for (i = 0; i<int_kappa; i++) {
//		x_int += -log(Uniform()); // add expnential random number with mean 1
//	}
//
//	/*fractional part*/
//	if (fabs(frac_kappa) < 0.01) x_frac = 0;
//
//	else {
//		b = (exp(1.0) + frac_kappa) / exp(1.0);
//		while (1) {
//
//			u = Uniform();
//			p = b*u;
//
//			uu = Uniform();
//
//			if (p <= 1.0) {
//				x_frac = pow(p, 1.0 / frac_kappa);
//				if (uu <= exp(-x_frac)) break;
//			}
//
//			else {
//				x_frac = -log((b - p) / frac_kappa);
//				if (uu <= pow(x_frac, frac_kappa - 1.0)) break;
//			}
//
//		}
//	}
//
//	return (x_int + x_frac)*theta;
//}
int PotatoCoinGet(void)
{
	return nCoinCount;
}

//�r���{�[�h�̃|�C���^
Billboard *GetBillboard(void)
{
	return &g_aBillboard[0];
}