//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �f�o�b�O���O�\������ [Debug_Log.cpp]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "Debug_Log.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPD3DXFONT		g_pFont = NULL;				// �t�H���g�ւ̃|�C���^
PLAYERINDEX		g_nPlayer = PLAYERINDEX_1;	// �\������v���C���[�̏��

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitDebug_Log(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �f�o�b�O�\���p�t�H���g��ݒ�
	// pDevice         : �f�o�C�X�ւ̃|�C���^
	// Height          : �����̍���
	// Width           : �����̕�
	// Weight          : �t�H���g�̑���
	// MipLevels       : �~�b�v�}�b�v���x����
	// Italic          : �C�^���b�N�t�H���g
	// CharSet         : �t�H���g�̕����Z�b�g
	// OutputPrecision : ���ۂ̃t�H���g�ƖړI�̃t�H���g�̃T�C�Y����ѓ����̈�v���@���w��
	// Quality         : ���ۂ̃t�H���g�ƖړI�̃t�H���g�Ƃ̈�v���@���w��
	// PitchAndFamily  : �s�b�`�ƃt�@�~���C���f�b�N�X
	// pFacename       : �t�H���g�̖��O��ێ����镶����
	// ppFont          : �t�H���g�ւ̃|�C���^
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitDebug_Log(void)
{
	if (g_pFont != NULL)
	{// �f�o�b�O�\���p�t�H���g�̊J��
		g_pFont->Release();
		g_pFont = NULL;
	}
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateDebug_Log(void)
{

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawDebug_Log(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[1024 * 3];		// ��������i�[����
	int nStr = 0;			// ������̍ŏI�ʒu��ۑ�����
	// FPS���擾
	int nFPS = GetFPS();
	// �J���������擾
	Camera *pCamera = GetCamera();
	// �v���C���[�����擾
	Player *pPlayer = GetPlayer();

	//--- FPS �\�� ---//
	// ���������
	wsprintf(&aStr[0], "FPS:%d\n", nFPS);

	//--- �t�B�[���h��� ---//
	// ������̈ʒu�ŏI��i�߂�
	nStr = strlen(aStr);
	// ���������
	wsprintf(&aStr[nStr], "\n//--- �J���� ---//\n");
	// ������̈ʒu�ŏI��i�߂�
	nStr = strlen(aStr);
	// ���������
	wsprintf(&aStr[nStr], "���_ �@: (%d ,%d, %d)\n",(int)pCamera->posV.x, (int)pCamera->posV.y, (int)pCamera->posV.z);
	// ������̈ʒu�ŏI��i�߂�
	nStr = strlen(aStr);
	// ���������
	wsprintf(&aStr[nStr], "�����_ : (%d ,%d, %d)\n", (int)pCamera->posR.x, (int)pCamera->posR.y, (int)pCamera->posR.z);
	// ������̈ʒu�ŏI��i�߂�
	nStr = strlen(aStr);
	// ���������
	wsprintf(&aStr[nStr], "�J�����̌��� : %d\n", (int)(pCamera->rot.y * 100));

	//--- �v���C���[��� ---//
	// ������̈ʒu�ŏI��i�߂�
	nStr = strlen(aStr);
	// ���������
	wsprintf(&aStr[nStr], "�v���C���[�̈ʒu : (%d ,%d ,%d)\n", (int)pPlayer->pos.x, (int)pPlayer->pos.y, (int)pPlayer->pos.z);
	// ������̈ʒu�ŏI��i�߂�
	nStr = strlen(aStr);
	// ���������
	wsprintf(&aStr[nStr], "�v���C���[�̌��� : (%d ,%d ,%d)\n", (int)(pPlayer->rot.x * 100), (int)(pPlayer->rot.y * 100), (int)(pPlayer->rot.z * 100));
	// ������̈ʒu�ŏI��i�߂�
	nStr = strlen(aStr);
	// ���������
	wsprintf(&aStr[nStr], "���݂̃t���[���� : [ %d : %d ]\n", pPlayer->nNowFrame, pPlayer->nFrameAll);
	// ������̈ʒu�ŏI��i�߂�
	nStr = strlen(aStr);
	// ���������
	wsprintf(&aStr[nStr], "�������t���O : %d\n", pPlayer->bLeft);
	// ������̈ʒu�ŏI��i�߂�
	nStr = strlen(aStr);
	// ���������
	wsprintf(&aStr[nStr], "�E�����t���O : %d\n", pPlayer->bRight);

	// �e�L�X�g�`��
	// hDC      : �f�o�C�X�R���e�L�X�g�̃n���h��
	// lpString : �`�悷�镶����ւ̃|�C���^
	// nCount   : ������̕�����
	// lpRect   : �����`�̈�
	// uFormat  : �e�L�X�g�̐��`���@���w��
	//g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}
