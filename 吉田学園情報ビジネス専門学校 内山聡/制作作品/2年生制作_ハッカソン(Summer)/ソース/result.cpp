//*************************************************************
//
// �����L���O�̏���[result.cpp]
//  Authot : ��������
//
//*************************************************************
#include "main.h"				// ���C�����̃w�b�_�[
#include "game.h"				// �Q�[�����̃w�b�_�[
#include "result.h"				// �����L���O���̃w�b�_�[
#include "camera.h"				// �J�������̃w�b�_�[
#include "light.h"				// ���C�g���̃w�b�_�[
#include "meshField.h"			// ���b�V���t�B�[���h���̃w�b�_�[
#include "field.h"				// ���ʏ��̃w�b�_�[
#include "player.h"				// �v���C���[���̃w�b�_�[
#include "object.h"				// �I�u�W�F�N�g���̃w�b�_�[
#include "time.h"				// �^�C�����̃w�b�_�[
#include "fade.h"				// �t�F�[�h���̃w�b�_�[
#include "input.h"				// �L�[�{�[�h���͏��̃w�b�_�[
#include "Gamepad.h"			// �R���g���[���[���͏��̃w�b�_�[
#include "sound.h"				// �T�E���h���̃w�b�_�[
#if _DEBUG
#include "line.h"
#endif


//=============================================================
//�}�N����`
//=============================================================
// �~���b�̐ݒ�
#define RESULT_MILLI_SECOND_POS_X		(750)										// �~���b�̍�X���W
#define RESULT_MILLI_SECOND_POS_Y		(155)										// �~���b�̏�Y���W
#define RESULT_MILLI_SECOND_WIDTH		(25)										// �~���b�̕�
#define RESULT_MILLI_SECOND_HEIGHT		(45)										// �~���b�̍���
#define RESULT_MILLI_SECOND_INTERVAL	(-30)										// �~���b�̊Ԋu

// �b�̐ݒ�
#define RESULT_SECOND_POS_X				(660)										// �b�̍�X���W
#define RESULT_SECOND_POS_Y				(135)										// �b�̏�Y���W

// ���̐ݒ�
#define RESULT_MINUTE_POS_X				(540)										// ���̍�X���W
#define RESULT_MINUTE_POS_Y				(135)										// ���̏�Y���W

// ���E�b�̑傫���ƊԊu
#define RESULT_TIME_WIDTH				(50)										// ���E�b�̃|���S���̕�
#define RESULT_TIME_HEIGHT				(70)										// ���E�b�̃|���S���̍���
#define RESULT_TIME_INTERVAL			(-50)										// ���E�b�̊Ԋu

// �R�����̐ݒ�
#define RESULT_COLON_POS_X				(580)										// �R������X�̈ʒu
#define RESULT_COLON_POS_Y				(140)										// �R������Y�̈ʒu
#define RESULT_COLON_WIDTH				(40)										// �R�����̃|���S���̕�
#define RESULT_COLON_HEIGHT				(60)										// �R�����̃|���S���̍���

#define RESULT_INTERVAL					(110.0f)									// �����L���O�̊Ԋu

#define MAX_RESULT_TIME					(6)											// �^�C���̌���
#define MAX_RESULT_COLON				(5)											// �R�����̐�
#define MAX_RESULT_NUMBER				(5)											// ���ʂ̐�
#define MAX_RESULT						(MAX_RESULT_TIME * MAX_RESULT_NUMBER)		// �����L���O�^�C���̒��_��(�� * ���ʐ�)
#define RESULT_TAITLE_WIDTH				(480)										// �^�C�g���̕�
#define RESULT_TAITLE_HEIGHT			(100)										// �^�C�g���̍���
#define RESULT_TAITLE_POS_X				(SCREEN_WIDTH/2-RESULT_TAITLE_WIDTH/2)		// �^�C�g���̍�X���W
#define RESULT_TAITLE_POS_Y				(20)										// �^�C�g���̏�Y���W

#define RESULT_RANK_WIDTH				(200)										// ���ʂ̕�
#define RESULT_RANK_HEIGHT				(100)										// ���ʂ̍���
#define RESULT_RANK_POS_X				(250)										// ���ʂ̍�X���W
#define RESULT_RANK_POS_Y				(125)										// ���ʂ̏�Y���W
#define MAX_TEXTURE						(4)											// �e�N�X�`���̐�
#define FRASHING_TIMING					(2)											// �_�ł̐؂�ւ��̑��x
#define RESULT_END_TIME					(300)										// �����L���O���I���܂ł̃t���[����

//=============================================================
//�v���g�^�C�v�錾�錾
//=============================================================
void MakeVertexResult(LPDIRECT3DDEVICE9 pDevice);									// ���_�ݒ�

//=============================================================
//�O���[�o���ϐ��錾
//=============================================================
LPDIRECT3DTEXTURE9		g_apTextureResult[MAX_TEXTURE] ;							// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;									// ���_�o�b�t�@�ւ̃|�C���^
int						g_aRankTime[MAX_RESULT_NUMBER] = { 60 * 60,65 * 60,70 * 60,75 * 60,80 * 60 };	// �����L���O�̃X�R�A
bool					g_bResultIn;												// �����L���O�ɓ��������ǂ���
bool					g_bResultEnd;												// �����L���O���I��邩�ǂ���
short int				g_nResultCounter;											// �����L���O���I���܂ł̃J�E���^�[
char g_acResultTextureInfo[MAX_TEXTURE][MAX_CHAR] =
{
	"data/TEXTURE/number001.png",				// ����
	"data/TEXTURE/ranking_item_logo.png",		// ���S
	"data/TEXTURE/ranking_rank.png",			// ����
	"data/TEXTURE/colon.png",					// �R����
};

static RESULTSTATE g_state = RESULTSTATE_GAMECLEAR;



//===========================================================
//����������
//===========================================================
void InitResult(void)
{
	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

#if _DEBUG
	// ���C��
	InitLine();
#endif

	// ���b�V���t�B�[���h�̏���������
	InitmeshField();

	// �v���C���[�̏���������
	InitPlayer();

	// �I�u�W�F�N�g�̏���������
	InitObject();

	// ����
	InitField();

	LPDIRECT3DDEVICE9 pDevice;														//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̓ǂݍ���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{// �e�N�X�`���̑��������[�v
		D3DXCreateTextureFromFile(pDevice,								//3D�f�o�C�X�̃A�h���X
			g_acResultTextureInfo[nCntTexture],							//�ǂݍ��ރe�N�X�`���̃t�@�C����
			&g_apTextureResult[nCntTexture]);							//�e�N�X�`���̃|�C���^
	}

	// �ϐ��̏�����
	g_bResultIn = false;															// �����L���O�ɓ������ǂ����i������false�j
	g_nResultCounter = 0;															// �J�E���^�[�̏�����
	g_bResultEnd = false;															// �����L���O���I�����邩�ǂ���


	// ���_���̐ݒ�
	MakeVertexResult(pDevice);

	// BGM�Đ�
	PlaySound(SOUND_LABEL_BGM003);
}

//===========================================================
//�I������
//===========================================================
void UninitResult(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

#if _DEBUG
	// ���C��
	UninitLine();
#endif

	// ���b�V���t�B�[���h�̏I������
	UninitmeshField();

	// �I�u�W�F�N�g�̏I������
	UninitObject();

	// ����
	UninitField();

	int nCntTexture;						// �J�E���g�ϐ�

	for (nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureResult[nCntTexture] != NULL)
		{//�e�N�X�`���̕ϐ��ɉ��������Ă�Ƃ�
			g_apTextureResult[nCntTexture] -> Release();
			g_apTextureResult[nCntTexture] = NULL;			//���g���̂Ă�
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;			//���g���̂Ă�
	}

	// BGM & SE��~
	StopSound();
}

//===========================================================
//�X�V����
//===========================================================
void UpdateResult(void)
{
	VERTEX_2D *pVtx;									// �|�C���^�ϐ�
	int nTime = GetTime();								// ����̃X�R�A������ϐ�
	static bool bFlashing = false;						// �_�ł̐؂�ւ�(true = ��,false = ��)
	static int nCntFlashing = 0;						// �_�ł̃J�E���g�ϐ�
	int nNextVtx = (MAX_RESULT_TIME + 1) * 4;			// ���̒��_������ϐ�(�^�C���̌���+�R����)*���_��

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// �n�C�X�R�A�̈ʒu�����
	for (int nCntResult = 0; nCntResult < MAX_RESULT_NUMBER; nCntResult++)
	{// 1�ʂ����r���Ă���
		if (nTime >= g_aRankTime[nCntResult])
		{// ����̃X�R�A�������L���O���ゾ������
			g_bResultIn = true;												// �����L���O�ɓ�������true�ɂ���
			break;																// �n�C�X�R�A�̏ꏊ���������烋�[�v�𔲂�������
		}
		else
		{// �����L���O�O��������
			pVtx += nNextVtx;													// �|�C���^�����̃^�C���ɐi�߂�
		}
	}

	// �����L���O�ɓ��������̓_�ŏ���
	if (g_bResultIn == true)
	{// �����L���O�ɓ�������
		// 8�����F��ς���
		for (int nCntResultScore = 0; nCntResultScore < MAX_RESULT_TIME + 1; nCntResultScore++, pVtx += 4)
		{
			if (bFlashing == true)
			{// ��
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{// ��
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
			}
		}

		// �_�Ő؂�ւ�
		if (nCntFlashing % FRASHING_TIMING == 0)
		{
			bFlashing = bFlashing ? false : true;				// �؂�ւ�
		}
	}

	nCntFlashing++;												// �J�E���g��i�߂�

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	// ���U���g��ʂ̏I������
	if (g_bResultEnd == false)
	{// ���U���g��ʂ��ς��n�߂ĂȂ����
		if (GetKeyboardTrigger(DIK_RETURN)		== true ||
			GetKeyboardTrigger(DIK_SPACE)		== true ||
			GetGamapadKeyTrigger(ELECOM_A)		== true ||
			GetGamapadKeyTrigger(ELECOM_START)	== true)
		{// �G���^�[��������I��
			g_bResultEnd = true;								// true�ɂ��ĘA�ő΍�
			SetFade(MODE_TITLE);								// �t�F�[�h�̐ݒ�
		}
		if (g_nResultCounter > RESULT_END_TIME)
		{// �T�b�o������I��
			g_bResultEnd = true;								// true�ɂ��ĘA�ő΍�
			SetFade(MODE_TITLE);								// �t�F�[�h�̐ݒ�
		}
	}

	g_nResultCounter++;										// ���t���[�����Z����

	// �J�����̍X�V����
	UpdateCamera();

#if _DEBUG
	// ���C��
	UpdateLine();
#endif

	// �����I�u�W�F�N�g�̍X�V����
	//UpdateObject();

	// ���b�V���t�B�[���h�̍X�V����
	UpdatemeshField();

	// ����
	UpdateField();

	// �v���C���[�̍X�V����
	UpdatePlayer();
}

//===========================================================
//�`�揈��
//===========================================================
void DrawResult(void)
{
	// �J�����̐ݒ菈��
	SetCamera();

#if _DEBUG
	DrawLine();
#endif

	// ���b�V���t�B�[���h�̕`�揈��
	DrawmeshField();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �I�u�W�F�N�g�̕`�揈��
	DrawObject();

	// ����
	DrawField();

	int nCntTexture;																// �J�E���g�ϐ�
	int nCntVtx = 0;																// �`�悷��ŏ��̒��_������ϐ�

	//�f�o�C�X�̕ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();															//main.cpp����󂯎����g_aD3DDevice�̃A�h���X����

	// Z�o�b�t�@�̐ݒ�
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);								// "FALSE"�ŕ`��̏��Ԃ𖳎����āA��Ɏ�O�ɕ`�悷��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);								// "FALSE"�ŕ`�悷�鏇�Ԃ���������`�悷��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);							// �`�悷�鏇�Ԃ����߂�

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �X�R�A�̕`��
	for (int nCntResult = 0; nCntResult < MAX_RESULT_NUMBER; nCntResult++)
	{// �����L���O5���쐬

		for (int nCntTime = 0; nCntTime < MAX_TIME_SET_TYPE; nCntTime++)
		{// �Z�b�g�̎�ޕ����[�v
			for (int nCntTimeSet = 0; nCntTimeSet < TIME_SET; nCntTimeSet++)
			{// �����Z�b�g�������[�v
			 //�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureResult[0]);						//�u0�v��ς���ƃe�N�X�`����������B

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntVtx,														//�J�n���钸�_�̃C���f�b�N�X
					2);																//�`�ʂ���v���~�e�B�u��

				nCntVtx += 4;														// �`�悷�钸�_��i�߂�
			}
		}

		//--------------------------------------------
		// �R�����̕`��
		//--------------------------------------------

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureResult[3]);								//�u0�v��ς���ƃe�N�X�`����������B

																					//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntVtx,																//�J�n���钸�_�̃C���f�b�N�X
			2);																		//�`�ʂ���v���~�e�B�u��

		nCntVtx += 4;																// �`�悷�钸�_��i�߂�

	}
	// �^�C�g���̕`��
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureResult[1]);									//�u0�v��ς���ƃe�N�X�`����������B

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntVtx,																	//�J�n���钸�_�̃C���f�b�N�X
		2);																			//�`�ʂ���v���~�e�B�u��

	nCntVtx += 4;																	// �`�悷�钸�_��i�߂�


	// �����N�̕`��
	for (nCntTexture = 0; nCntTexture < MAX_RESULT_NUMBER; nCntTexture++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureResult[2]);								//�u0�v��ς���ƃe�N�X�`����������B

																					//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntVtx,																//�J�n���钸�_�̃C���f�b�N�X
			2);																		//�`�ʂ���v���~�e�B�u��

		nCntVtx += 4;																// �`�悷�钸�_��i�߂�

	}



	// Z�o�b�t�@�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//===========================================================
//�����L���O�̒��_�ݒ�
//===========================================================
void MakeVertexResult(LPDIRECT3DDEVICE9 pDevice)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;													//���_���ւ̃|�C���^
	int nCntResult;													// �����L���O�̃J�E���g�ϐ�
	float fResultInterval ;											// �����L���O�̊Ԋu
	int nScoreTextur = 10;												// �����̃e�N�X�`�������߂�v�Z�̕ϐ�
	int nCntRank;														// ���ʂ̃J�E���g�ϐ�
	int nTimePos;														// �^�C���̈ʒu
	int nTimeTextur;													// �^�C���̃e�N�X�`���̍��W���v�Z���邽�߂̕ϐ�
	float nRankTexture = 0.0f;											// ���ʂ̃e�N�X�`���̌v�Z�̕ϐ�


	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_RESULT + 1 + MAX_RESULT_NUMBER + MAX_RESULT_COLON),	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,																	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntResult = 0; nCntResult < MAX_RESULT_NUMBER; nCntResult++)
	{// �����L���O5���쐬
		fResultInterval = nCntResult * RESULT_INTERVAL;								// �����L���O�̊Ԋu

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
					nTimePos = nCntTimeSet * RESULT_MILLI_SECOND_INTERVAL;				// �Ԋu��������

					// ���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(RESULT_MILLI_SECOND_POS_X + (nTimePos + 0.0f),							   fResultInterval + RESULT_MILLI_SECOND_POS_Y, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(RESULT_MILLI_SECOND_POS_X + (nTimePos + 0.0f + RESULT_MILLI_SECOND_WIDTH), fResultInterval + RESULT_MILLI_SECOND_POS_Y, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(RESULT_MILLI_SECOND_POS_X + (nTimePos + 0.0f),							   fResultInterval + RESULT_MILLI_SECOND_POS_Y + RESULT_MILLI_SECOND_HEIGHT, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(RESULT_MILLI_SECOND_POS_X + (nTimePos + 0.0f + RESULT_MILLI_SECOND_WIDTH), fResultInterval + RESULT_MILLI_SECOND_POS_Y + RESULT_MILLI_SECOND_HEIGHT, 0.0f);

					// �e�N�X�`�����W�̐ݒ�
					pVtx[0].tex = D3DXVECTOR2((g_aRankTime[nCntResult] % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2((g_aRankTime[nCntResult] % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2((g_aRankTime[nCntResult] % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2((g_aRankTime[nCntResult] % 60 * 100 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 1.0f);
				}
				else if (nCntTime == TimeType_Second)
				{// �b�̎�
					nTimePos = nCntTimeSet * RESULT_TIME_INTERVAL;						// �Ԋu��������

					// ���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(RESULT_SECOND_POS_X + (nTimePos + 0.0f),						 fResultInterval + RESULT_SECOND_POS_Y, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(RESULT_SECOND_POS_X + (nTimePos + 0.0f + RESULT_TIME_WIDTH), fResultInterval + RESULT_SECOND_POS_Y, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(RESULT_SECOND_POS_X + (nTimePos + 0.0f),						 fResultInterval + RESULT_SECOND_POS_Y + RESULT_TIME_HEIGHT, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(RESULT_SECOND_POS_X + (nTimePos + 0.0f + RESULT_TIME_WIDTH), fResultInterval + RESULT_SECOND_POS_Y + RESULT_TIME_HEIGHT, 0.0f);

					// �e�N�X�`�����W�̐ݒ�
					pVtx[0].tex = D3DXVECTOR2((g_aRankTime[nCntResult] / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2((g_aRankTime[nCntResult] / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2((g_aRankTime[nCntResult] / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2((g_aRankTime[nCntResult] / 60 % 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 1.0f);
				}
				if (nCntTime == TimeType_Minute)
				{// ���̎�
					nTimePos = nCntTimeSet * RESULT_TIME_INTERVAL;						// �Ԋu��������

					// ���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(RESULT_MINUTE_POS_X + (nTimePos + 0.0f),						 fResultInterval + RESULT_MINUTE_POS_Y, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(RESULT_MINUTE_POS_X + (nTimePos + 0.0f + RESULT_TIME_WIDTH), fResultInterval + RESULT_MINUTE_POS_Y, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(RESULT_MINUTE_POS_X + (nTimePos + 0.0f),						 fResultInterval + RESULT_MINUTE_POS_Y + RESULT_TIME_HEIGHT, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(RESULT_MINUTE_POS_X + (nTimePos + 0.0f + RESULT_TIME_WIDTH), fResultInterval + RESULT_MINUTE_POS_Y + RESULT_TIME_HEIGHT, 0.0f);

					// �e�N�X�`�����W�̐ݒ�
					pVtx[0].tex = D3DXVECTOR2((g_aRankTime[nCntResult] / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2((g_aRankTime[nCntResult] / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2((g_aRankTime[nCntResult] / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2((g_aRankTime[nCntResult] / 60 / 60) % nTimeTextur / (nTimeTextur / 10) / 10.0f + 0.1f, 1.0f);
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

				pVtx += 4;																// �|�C���^��i�߂�
				nTimeTextur = nTimeTextur * 10;											// 10�{���Ď��̌��ɍ��킹��
			}
		}

		//--------------------------------------
		// �R�����̒��_���̐ݒ�
		//--------------------------------------

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(RESULT_COLON_POS_X,						 fResultInterval + RESULT_COLON_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(RESULT_COLON_POS_X + RESULT_COLON_WIDTH, fResultInterval + RESULT_COLON_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(RESULT_COLON_POS_X,						 fResultInterval + RESULT_COLON_POS_Y + RESULT_COLON_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(RESULT_COLON_POS_X + RESULT_COLON_WIDTH, fResultInterval + RESULT_COLON_POS_Y + RESULT_COLON_HEIGHT, 0.0f);

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

		pVtx += 4;																		// �|�C���^��i�߂�

		nScoreTextur = 10;																// �v�Z���錅�����ɖ߂�
	}

	// �^�C�g���̒��_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(RESULT_TAITLE_POS_X,							RESULT_TAITLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_TAITLE_POS_X+ RESULT_TAITLE_WIDTH,	RESULT_TAITLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_TAITLE_POS_X,							RESULT_TAITLE_POS_Y+ RESULT_TAITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_TAITLE_POS_X+ RESULT_TAITLE_WIDTH,	RESULT_TAITLE_POS_Y+ RESULT_TAITLE_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;																		// �|�C���^��i�߂�

	//--------------------------------------
	// ���ʂ̒��_���̐ݒ�
	//--------------------------------------
	for (nCntRank = 0; nCntRank < MAX_RESULT_NUMBER; nCntRank++)
	{
		fResultInterval = nCntRank * RESULT_INTERVAL;								// �����L���O�̊Ԋu

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(RESULT_RANK_POS_X					  + 0.0f, (RESULT_RANK_POS_Y + fResultInterval					   + 0.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(RESULT_RANK_POS_X + RESULT_RANK_WIDTH + 0.0f, (RESULT_RANK_POS_Y + fResultInterval					   + 0.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(RESULT_RANK_POS_X					  + 0.0f, (RESULT_RANK_POS_Y + fResultInterval + RESULT_RANK_HEIGHT + 0.0f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(RESULT_RANK_POS_X + RESULT_RANK_WIDTH + 0.0f, (RESULT_RANK_POS_Y + fResultInterval + RESULT_RANK_HEIGHT + 0.0f), 0.0f);


		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);

		////�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, nRankTexture + 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, nRankTexture + 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, nRankTexture + 0.2f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, nRankTexture + 0.2f);

		nRankTexture += 0.2f;														// ���̃e�N�X�`���̈ʒu�ɐi�߂�
		pVtx += 4;																	// �|�C���^��i�߂�

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();
}


//===========================================================
//�����L���O�̐ݒ�
//===========================================================
void SetRankTime(int nScore)
{
	int nAhead0;													// ����ւ��p�ϐ�0
	int nAhead1;													// ����ւ��p�ϐ�1
	int nCntRank = 0;												// ����ւ��J�E���g�ϐ�(0=�n�C�X�R�A,1<=����ȊO�̏���)

	for (int nCntResult = 0; nCntResult < MAX_RESULT_NUMBER; nCntResult++)
	{// 5�ʕ����[�v
		if (nScore < g_aRankTime[nCntResult])
		{// ����̃X�R�A�������L���O�����ゾ������
			if (nCntRank == 0)
			{// 5�ʂ�������
				nAhead0 = g_aRankTime[nCntResult];					// ���łɓ����Ă�X�R�A��ޔ�
				g_aRankTime[nCntResult] = nScore;					// �V�����n�C�X�R�A������
				nCntRank++;											// �J�E���g�����Z���ăn�C�X�R�A�ȊO�̏��ʂ̓���ւ���������
			}
			else
			{// 4�ʈȏゾ���������ւ�
				nAhead1 = g_aRankTime[nCntResult];					// ���łɓ����Ă�X�R�A��ޔ�
				g_aRankTime[nCntResult] = nAhead0;					// ��̏��ʂ������X�R�A������
				nAhead0 = nAhead1;									// �����̏��ʂ������X�R�A��ޔ����Ă���
			}
		}
	}
}

void SetResultState(RESULTSTATE state)
{
	g_state = state;
}

RESULTSTATE GetResultState(void)
{
	return g_state;
}