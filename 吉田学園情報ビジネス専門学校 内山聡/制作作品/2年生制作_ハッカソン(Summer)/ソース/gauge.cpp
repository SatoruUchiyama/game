//=============================================================================
//
// �ϐg�Q�[�W���� [gauge.h]
// Author : Ishida Takuto
//
//=============================================================================
#include "gauge.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BAR_WIDTH_GAUGE		(500)		// �o�[�̕�
#define BAR_HEIGHT_GAUGE	(30)		// �o�[�̍���
#define NUM_TEXTURE_GAUGE	(1)			// �o�[�̃e�N�X�`����
#define NUM_POLYGON_GAUGE	(2)			// �|���S����
#define GAUGE_SPEED			(2)			// �Q�[�W�̑����̑��x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureGauge[NUM_TEXTURE_GAUGE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
Gauge g_Gauge[NUM_POLYGON_GAUGE];		// �Q�[�W�̍\����
int g_nGauge;				// ���݂̃Q�[�W�̒l
bool g_bGaugeColor;

//=============================================================================
// ����������
//=============================================================================
void InitGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// [0]�o�[�̌��̒����@[1]���݂̒l������
	for (int nCntGauge = 0; nCntGauge < NUM_POLYGON_GAUGE; nCntGauge++)
	{
		g_Gauge[nCntGauge].pos = D3DXVECTOR3(20.0f, 650.0f, 0.0f);
		g_Gauge[nCntGauge].nType = -1;
	}

	// �o�[�̒�����ݒ�
	g_Gauge[0].fLength = BAR_WIDTH_GAUGE;
	g_Gauge[1].fLength = BAR_WIDTH_GAUGE;

	g_Gauge[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_Gauge[1].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);

	// �Q�[�W�̒l
	g_nGauge = MAX_GAUGE;
	g_bGaugeColor = false;

	// ���_���̍쐬
	MakeVertexGauge(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitGauge(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < NUM_TEXTURE_GAUGE; nCntTexture++)
	{
		if (g_pTextureGauge[nCntTexture] != NULL)
		{
			g_pTextureGauge[nCntTexture]->Release();
			g_pTextureGauge[nCntTexture] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGauge(void)
{
	float fDestLength = (BAR_WIDTH_GAUGE * 1.0f) / ((MAX_GAUGE * 1.0f) / g_nGauge);		// �o�[�̒��������݂̒l���狁�߂�

	if (g_Gauge[1].fLength + 0.01f < fDestLength)
	{// �o�[�̒����@���@�ړI�̒���
		g_Gauge[1].fLength += GAUGE_SPEED;
	}
	else if (g_Gauge[1].fLength - 0.01f > fDestLength)
	{// �o�[�̒����@���@�ړI�̒���
		g_Gauge[1].fLength -= GAUGE_SPEED;
	}

	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Gauge[1].fLength >= BAR_WIDTH_GAUGE)
	{// �Q�[�W���ő�l�œ_��
		if (!g_bGaugeColor)
		{// �F�����Z���Ă���
			g_Gauge[1].col += D3DXCOLOR(0.02f, 0.02f, 0.02f, 0.0f);

			if (g_Gauge[1].col.b >= 1.0f)
			{// ���l�܂ŉ��Z����
				g_Gauge[1].col = D3DXCOLOR(2.0f, 1.7f, 1.0f, 1.0f);
				g_bGaugeColor = true;
			}
		}
		else
		{// �F�����Z���Ă���
			g_Gauge[1].col -= D3DXCOLOR(0.02f, 0.02f, 0.02f, 0.0f);

			if (g_Gauge[1].col.b <= 0.0f)
			{// ���l�܂Ō��Z����
				g_Gauge[1].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
				g_bGaugeColor = false;
			}
		}

		//���_�J���[
		pVtx[4 + 0].col = g_Gauge[1].col;
		pVtx[4 + 1].col = g_Gauge[1].col;
		pVtx[4 + 2].col = g_Gauge[1].col;
		pVtx[4 + 3].col = g_Gauge[1].col;
	}
	else
	{
		g_Gauge[1].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);

		//���_�J���[
		pVtx[4 + 0].col = g_Gauge[1].col;
		pVtx[4 + 1].col = g_Gauge[1].col;
		pVtx[4 + 2].col = g_Gauge[1].col;
		pVtx[4 + 3].col = g_Gauge[1].col;
	}

	//���_���W�̐ݒ�
	pVtx[4 + 1].pos = D3DXVECTOR3(g_Gauge[1].pos.x + g_Gauge[1].fLength, g_Gauge[1].pos.y, 0.0f);
	pVtx[4 + 3].pos = D3DXVECTOR3(g_Gauge[1].pos.x + g_Gauge[1].fLength, g_Gauge[1].pos.y + BAR_HEIGHT_GAUGE, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGauge->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGauge(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntGauge = 0; nCntGauge < NUM_POLYGON_GAUGE; nCntGauge++)
	{
		// �e�N�X�`���̐ݒ�
		if (g_Gauge[nCntGauge].nType >= 0)
		{// �e�N�X�`���̎w��
			pDevice->SetTexture(0, g_pTextureGauge[g_Gauge[nCntGauge].nType]);
		}
		else
		{// 0���Ⴂ�ƃe�N�X�`���𒣂�Ȃ�
			pDevice->SetTexture(0, NULL);

		}

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntGauge, 2);
	}
}

//=============================================================================
// �Q�[�W�̑���
//=============================================================================
void AddSubtractGauge(int nValue)
{
	g_nGauge += nValue;		// �Q�[�W�𑝌�������

	if (g_nGauge >= MAX_GAUGE)
	{// �ő�l�𒴂�����߂�
		g_nGauge = MAX_GAUGE;
	}
	else if (g_nGauge <= 0)
	{// �ŏ��l�𒴂�����߂�
		g_nGauge = 0;
	}
}

//=============================================================================
// ���݂̃Q�[�W�̎擾
//=============================================================================
int GetGauge(void)
{
	return g_nGauge;
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntGauge;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_POLYGON_GAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGauge,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntGauge = 0; nCntGauge < NUM_POLYGON_GAUGE; nCntGauge++)
	{
		//���_���W�̐ݒ�
		pVtx[(nCntGauge * 4) + 0].pos = D3DXVECTOR3(g_Gauge[nCntGauge].pos.x, g_Gauge[nCntGauge].pos.y, 0.0f);
		pVtx[(nCntGauge * 4) + 1].pos = D3DXVECTOR3(g_Gauge[nCntGauge].pos.x + BAR_WIDTH_GAUGE, g_Gauge[nCntGauge].pos.y, 0.0f);
		pVtx[(nCntGauge * 4) + 2].pos = D3DXVECTOR3(g_Gauge[nCntGauge].pos.x, g_Gauge[nCntGauge].pos.y + BAR_HEIGHT_GAUGE, 0.0f);
		pVtx[(nCntGauge * 4) + 3].pos = D3DXVECTOR3(g_Gauge[nCntGauge].pos.x + BAR_WIDTH_GAUGE, g_Gauge[nCntGauge].pos.y + BAR_HEIGHT_GAUGE, 0.0f);

		//1.0f�ŌŒ�
		pVtx[(nCntGauge * 4) + 0].rhw = 1.0f;
		pVtx[(nCntGauge * 4) + 1].rhw = 1.0f;
		pVtx[(nCntGauge * 4) + 2].rhw = 1.0f;
		pVtx[(nCntGauge * 4) + 3].rhw = 1.0f;

		//���_�J���[
		pVtx[(nCntGauge * 4) + 0].col = g_Gauge[nCntGauge].col;
		pVtx[(nCntGauge * 4) + 1].col = g_Gauge[nCntGauge].col;
		pVtx[(nCntGauge * 4) + 2].col = g_Gauge[nCntGauge].col;
		pVtx[(nCntGauge * 4) + 3].col = g_Gauge[nCntGauge].col;

		//�e�N�X�`�����W
		pVtx[(nCntGauge * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCntGauge * 4) + 1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[(nCntGauge * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[(nCntGauge * 4) + 3].tex = D3DXVECTOR2(0.1f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGauge->Unlock();
}
