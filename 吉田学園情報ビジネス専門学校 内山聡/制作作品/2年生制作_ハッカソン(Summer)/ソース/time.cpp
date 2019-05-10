//=============================================================================
//
// �^�C������ [time.cpp]
// Author : ��������
//
//=============================================================================
#include "time.h"		// �^�C���w�b�_�[
#include "game.h"		// �Q�[�����̃w�b�_�[
#include "sound.h"		// �T�E���h���̃w�b�_�[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIME			"data/TEXTURE/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_FRAME			"data/TEXTURE/frame_timer.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_COLON			"data/TEXTURE/colon.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_TEXTURE_RESULT		(3)								// �e�N�X�`���̎��
#define MAX_FRAME_TIME			(1)								// �^�C���̘g�̐�
#define MAX_COLON				(1)								// �R�����̐�
#define MAX_TIME				(6)								// �^�C���̍ő包��

#define MILLI_SECOND_POS_X		(1200)							// �~���b��X�̈ʒu
#define MILLI_SECOND_POS_Y		(40)							// �~���b��Y�̈ʒu
#define MILLI_SECOND_WIDTH		(15)							// �~���b�̃|���S���̕�
#define MILLI_SECOND_HEIGHT		(25)							// �~���b�̃|���S���̍���
#define TIME_WIDTH				(30)							// �^�C���̃|���S���̕�
#define TIME_HEIGHT				(50)							// �^�C���̃|���S���̍���
#define SECOND_POS_X			(1150)							// �b��X�̈ʒu
#define SECOND_POS_Y			(20)							// �b��Y�̈ʒu
#define MINUTE_POS_X			(1060)							// ����X�̈ʒu
#define MINUTE_POS_Y			(20)							// ����Y�̈ʒu

#define TIME_INTERVAL			(-35)							// �^�C���̔z�u�̊Ԋu
#define MILLI_SECOND_INTERVAL	(-20)							// �~���b�̔z�u�̊Ԋu

#define FRAME_POS_X				(1000)							// �t���[����X�̈ʒu
#define FRAME_POS_Y				(0)								// �t���[����Y�̈ʒu
#define FRAME_WIDTH				(260)							// �t���[���̃|���S���̕�
#define FRAME_HEIGHT			(75)							// �t���[���̃|���S���̍���
#define COLON_POS_X				(1085)							// �R������X�̈ʒu
#define COLON_POS_Y				(20)							// �R������Y�̈ʒu
#define COLON_WIDTH				(30)							// �R�����̃|���S���̕�
#define COLON_HEIGHT			(50)							// �R�����̃|���S���̍���

#define INIT_TIME				(0)							// �^�C���̏����l
#define TIME_SCORE				(100)							// �^�C���̓��T


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime[MAX_TEXTURE_RESULT];		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
int						g_nTime;								// �^�C��
char g_acTimeTextureInfo[MAX_TEXTURE_RESULT][MAX_CHAR] =
{// �e�N�X�`���̃A�h���X
	"data/TEXTURE/number001.png",		// �����̃e�N�X�`��
	"data/TEXTURE/frame_timer.png",		// �t���[���̃e�N�X�`��
	"data/TEXTURE/colon.png",			// �R�����̃e�N�X�`��
};


//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ������
	g_nTime = INIT_TIME;								// �^�C���̏�����

	// �e�N�X�`���̓ǂݍ���
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE_RESULT; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
								  g_acTimeTextureInfo[nCntTexture],	// �t�@�C���̖��O
								  &g_pTextureTime[nCntTexture]);	// �e�N�X�`���ւ̃|�C���^
	}

	// ���_���̍쐬
	MakeVertexTime(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE_RESULT; nCntTexture++)
	{// �e�N�X�`���̑��������[�v
		if (g_pTextureTime[nCntTexture] != NULL)
		{// �e�N�X�`���̕ϐ��ɉ��������Ă�Ƃ�
			g_pTextureTime[nCntTexture]->Release();
			g_pTextureTime[nCntTexture] = NULL;			//���g���̂Ă�
		}
	}


	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;			//���g���̂Ă�
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{
	VERTEX_2D *pVtx;					// ���_���̃|�C���^�ϐ�
	GAMESTATE GameState;				// �Q�[���̏�Ԃ��󂯎��ϐ�
	GameState = GetGameState();			// �Q�[���̏�Ԃ��擾

	if (GameState == GAMESTATE_NORMAL)
	{// �Q�[�����ʏ��Ԃ̎��̂݃^�C�������炷
		int nTimeTextur;						// �e�N�X�`���̈ʒu���v�Z���邽�߂̕ϐ�

		g_nTime++;								// �^�C���𑝂₷

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntTime = 0; nCntTime < MAX_TIME_SET_TYPE; nCntTime++)
		{// �Z�b�g�̎�ޕ����[�v
			nTimeTextur = 10;												// �e�N�X�`���̌��̌v�Z���邽�߂̒l��������
			for (int nCntTimeSet = 0; nCntTimeSet < TIME_SET; nCntTimeSet++)
			{// �����Z�b�g�������[�v
				if (nCntTime == TimeType_MilliSecond)
				{// �~���b�̎�
					// �e�N�X�`�����W�̐ݒ�
					pVtx[0].tex = D3DXVECTOR2((g_nTime % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2((g_nTime % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2((g_nTime % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2((g_nTime % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 1.0f);

				}
				else if (nCntTime == TimeType_Second)
				{// �b�̎�
					// �e�N�X�`�����W�̐ݒ�
					pVtx[0].tex = D3DXVECTOR2((g_nTime / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2((g_nTime / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2((g_nTime / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2((g_nTime / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 1.0f);
				}
				else if (nCntTime == TimeType_Minute)
				{// ���̎�
					// �e�N�X�`�����W�̐ݒ�
					pVtx[0].tex = D3DXVECTOR2((g_nTime / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2((g_nTime / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2((g_nTime / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2((g_nTime / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 1.0f);
				}

				pVtx += 4;													// �|�C���^��i�߂�
				nTimeTextur = nTimeTextur * 10;								// 10�{���Ď��̌��ɍ��킹��
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTime->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntTime;														// �J�E���^�[�ϐ�

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �^�C��8�����̃|���S���\��
	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTime[0]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
							   nCntTime * 4,												//�J�n���钸�_�̃C���f�b�N�X
							   2);															//�`�ʂ���v���~�e�B�u��
	}
	// �t���[���̕\��
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime[1]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
						   MAX_TIME * 4,													//�J�n���钸�_�̃C���f�b�N�X
						   2);

	// �R�����̕\��
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime[2]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		(MAX_TIME + 1) * 4,																	//�J�n���钸�_�̃C���f�b�N�X
		2);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nTimePos;			// �^�C���̈ʒu
	int nTimeTextur;		// �e�N�X�`���̈ʒu���v�Z���邽�߂̕ϐ�

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_TIME + MAX_FRAME_TIME + MAX_COLON),	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,																				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//--------------------------------------
	// �^�C���̒��_���̐ݒ�
	//--------------------------------------
	for (int nCntTime = 0; nCntTime < MAX_TIME_SET_TYPE; nCntTime++)
	{// �Z�b�g�̎�ޕ����[�v
		nTimePos = 0;																// �^�C���̊Ԋu��������
		nTimeTextur = 10;															// �e�N�X�`���̌��̌v�Z���邽�߂̒l��������

		for (int nCntTimeSet = 0; nCntTimeSet < TIME_SET; nCntTimeSet++)
		{// �����Z�b�g�������[�v

			if (nCntTime == TimeType_MilliSecond)
			{// �~���b�̎�
				nTimePos = nCntTimeSet * MILLI_SECOND_INTERVAL;						// �����̊Ԋu��������
				// ���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(MILLI_SECOND_POS_X + (nTimePos + 0.0f),					   MILLI_SECOND_POS_Y,				 0.0f);
				pVtx[1].pos = D3DXVECTOR3(MILLI_SECOND_POS_X + (nTimePos + 0.0f + MILLI_SECOND_WIDTH), MILLI_SECOND_POS_Y,				 0.0f);
				pVtx[2].pos = D3DXVECTOR3(MILLI_SECOND_POS_X + (nTimePos + 0.0f),					   MILLI_SECOND_POS_Y + MILLI_SECOND_HEIGHT, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(MILLI_SECOND_POS_X + (nTimePos + 0.0f + MILLI_SECOND_WIDTH), MILLI_SECOND_POS_Y + MILLI_SECOND_HEIGHT, 0.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((g_nTime % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_nTime % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_nTime % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_nTime % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 1.0f);
			}
			else if (nCntTime == TimeType_Second)
			{// �b�̎�
				nTimePos = nCntTimeSet * TIME_INTERVAL;								// �����̊Ԋu��������

				// ���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(SECOND_POS_X + (nTimePos + 0.0f),				 SECOND_POS_Y,				 0.0f);
				pVtx[1].pos = D3DXVECTOR3(SECOND_POS_X + (nTimePos + 0.0f + TIME_WIDTH), SECOND_POS_Y,				 0.0f);
				pVtx[2].pos = D3DXVECTOR3(SECOND_POS_X + (nTimePos + 0.0f),				 SECOND_POS_Y + TIME_HEIGHT, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(SECOND_POS_X + (nTimePos + 0.0f + TIME_WIDTH), SECOND_POS_Y + TIME_HEIGHT, 0.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((g_nTime / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_nTime / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_nTime / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_nTime / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 1.0f);
			}
			if (nCntTime == TimeType_Minute)
			{// ���̎�
				nTimePos = nCntTimeSet * TIME_INTERVAL;								// �����̊Ԋu��������

				// ���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(MINUTE_POS_X + (nTimePos + 0.0f),				 MINUTE_POS_Y,				 0.0f);
				pVtx[1].pos = D3DXVECTOR3(MINUTE_POS_X + (nTimePos + 0.0f + TIME_WIDTH), MINUTE_POS_Y,				 0.0f);
				pVtx[2].pos = D3DXVECTOR3(MINUTE_POS_X + (nTimePos + 0.0f),				 MINUTE_POS_Y + TIME_HEIGHT, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(MINUTE_POS_X + (nTimePos + 0.0f + TIME_WIDTH), MINUTE_POS_Y + TIME_HEIGHT, 0.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((g_nTime / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_nTime / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_nTime / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_nTime / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 1.0f);
			}


			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx += 4;													// �|�C���^��i�߂�
			nTimeTextur = nTimeTextur * 10;								// 10�{���Ď��̌��ɍ��킹��
		}
	}

	//--------------------------------------
	// �t���[���̒��_���̐ݒ�
	//--------------------------------------
	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(FRAME_POS_X,				 FRAME_POS_Y,				 0.0f);
	pVtx[1].pos = D3DXVECTOR3(FRAME_POS_X + FRAME_WIDTH, FRAME_POS_Y,				 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FRAME_POS_X,				 FRAME_POS_Y + FRAME_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(FRAME_POS_X + FRAME_WIDTH, FRAME_POS_Y + FRAME_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;													// �|�C���^��i�߂�

	//--------------------------------------
	// �R�����̒��_���̐ݒ�
	//--------------------------------------
	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(COLON_POS_X,				 COLON_POS_Y,				 0.0f);
	pVtx[1].pos = D3DXVECTOR3(COLON_POS_X + COLON_WIDTH, COLON_POS_Y,				 0.0f);
	pVtx[2].pos = D3DXVECTOR3(COLON_POS_X,				 COLON_POS_Y + COLON_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(COLON_POS_X + COLON_WIDTH, COLON_POS_Y + COLON_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// �^�C�����擾
//=============================================================================
int GetTime(void)
{
	return g_nTime;			// �^�C���̏���Ԃ�
}

//=============================================================================
// �^�C����������
//=============================================================================
void ResetTime(void)
{
	g_nTime = 0;			// �^�C����0�ɂ���
}