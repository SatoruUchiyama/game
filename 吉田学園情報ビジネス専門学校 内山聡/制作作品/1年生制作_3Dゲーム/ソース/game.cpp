//=============================================================================
//
// �Q�[����� [game.cpp]
// Author : storu utiyama
//
//
//	1�{�u�̎�𓮂���
//	2�����̃A�C�e���������_���ړ�
//	3�{�u�̖ڐ����A�C�e���Ɍ�����
//	
//	
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "ballet.h"
#include "meshField.h"
#include "meshWall.h"
#include "meshcylinder.h"
#include "explosion.h"
#include "effect.h"
#include "player.h"
#include "fade.h"
#include "pause.h"
#include "score.h"
#include "time.h"
#include "enemy.h"
#include "item.h"
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
GAMESTATE g_gamestate = GAMESTATE_NONE;
int nCounterGameState;
bool g_bPause;
//=============================================================================
// ����������
//=============================================================================
void InitGame(void)
{
	InitScore();				//�X�R�A�̏���������
	InitTime();					//
	InitCamera();				// �J�����̏���������
	InitLight();				//���C�g�̏���������	
	InitShadow();				//�e�̏���������
	InitMeshField();			//���̏���������
	InitMeshWall();				//�ǂ̏���������
	//InitMeshCylinder();		//�~���̏���������
	//InitPolygon();			//�|���S���̏���������
	//InitWall();				//�ǂ̏���������
	InitExplosion();			//�����̏���������
	InitBillboard();			//�r���{�[�h(��)�̏���������
	InitEffect();				//�G�t�F�N�g��
	InitBallet();				//�e�̏���������
	InitPause();				//�|�[�Y��ʂ̏�������������
	InitModel();
	InitItem();
	InitEnemy();
	InitModel();
	InitPlayer();

	//						�ǂ��Z�b�g
	//SetWall(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	//SetWall(D3DXVECTOR3(0.0, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.0f, 0.0f));
	//SetWall(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//						�r���{�[�h�̃Z�b�g
	/*SetBillboard(D3DXVECTOR3(800.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetBillboard(D3DXVECTOR3(750.0f, 0.0f, -160.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, -170.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));*/
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, -850.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	//						���f���̃Z�b�g
	SetModel(D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetModel(D3DXVECTOR3(-60.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	SetModel(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
	//SetModel(D3DXVECTOR3(-100.0f, 0.0f, 80.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(50.0f, 0.0f, -160.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	
	//���
	SetModel(D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(800.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(650.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(450.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(250.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);

	SetModel(D3DXVECTOR3(300.0f, 0.0f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(800.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(650.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(450.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(250.0f, 0.0f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);

	//��
	SetModel(D3DXVECTOR3(0.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(200.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(400.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(600.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(800.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);

	SetModel(D3DXVECTOR3(0.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, 16.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(200.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, 16.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(400.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, 16.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(600.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, 16.0f, 0.0f), 3);
	SetModel(D3DXVECTOR3(800.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, 16.0f, 0.0f), 3);



	SetItem(D3DXVECTOR3(50.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	//						�G�̃Z�b�g
	/*SetEnemy(D3DXVECTOR3(600.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(550.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(450.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(100.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 4);
	*/
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(500.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 4);

	SetEnemy(D3DXVECTOR3(830.0f, 0.0f, -850.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(-50.0f, 0.0f, -850.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(830.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(-50.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 4);

	//
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 550, SCREEN_HEIGHT / 2 - 350, 0.0f), 30.0f, 40.0f);
	//
	Settime(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 350, 0.0f), 30.0f, 40.0f);
	
	
	GAMESTATE g_gamestate = GAMESTATE_NORMAL;
	nCounterGameState = 0;
	g_bPause = false;
}
//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	//
	//�X�R�A�̏I������
	UninitScore();
	//
	UninitTime();
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// ���̐����̏I������
	UninitMeshField();

	// �ǂ̐����̏I������
	UninitMeshWall();

	// �~���̏I������
	//UninitMeshCylinder();

	
	// �|���S���̏I������
	//UninitPolygon();

	// �e�̏I������
	UninitShadow();

	//�����̏���
	UninitExplosion();

	// �r���{�[�h(��)�̏I������
	UninitBillboard();

	//�G�t�F�N�g�̏���
	UninitEffect();

	// �e�̏I������
	UninitBallet();

	// �v���C���[�̏I������
	UninitModel();

	UninitItem();
	//
	UninitEnemy();
	UninitPlayer();

	UninitPause();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}
	
	//
	if (g_bPause == false)
	{  
		UpdateScore();			//�X�R�A�̍X�V����
		UpdateTime();			//�^�C���̍X�V����
		UpdateCamera();			//�J�����̍X�V����
		UpdateLight();			//���C�g�̍X�V����
		UpdateMeshField();		//���̐����̍X�V����
		UpdateMeshWall();		//�ǂ̐����̍X�V����
		UpdateMeshCylinder();	//�~���̐����̍X�V����
		//UpdatePolygon();		//�|���S���̍X�V����
		//UpdateWall();			//�ǂ̍X�V����
		UpdateShadow();			//�e�̐����̍X�V����
		UpdateExplosion();		//�����̍X�V����
		UpdateBillboard();		//�r���{�[�h(��)�̍X�V����
		UpdateEffect();			//�G�t�F�N�g�̍X�V����
		UpdateBallet();			//�e�̍X�V����
		UpdateModel();			//�v���C���[�̍X�V����
		UpdateItem();			//�A�C�e���̍X�V����
		UpdateEnemy();			//�G�̍X�V����
		UpdatePlayer();			//�v���C���[�̍X�V����

		//========================
		//�Q�[���X�e�[�g
		//========================
		switch (g_gamestate)
		{
		case GAMESTATE_NORMAL:
			break;
		case GAMESTATE_END:
			nCounterGameState++;//�t�F�[�h�J�E���g
			if (nCounterGameState >= 60)//�t�F�[�h���鎞��
			{
				g_gamestate = GAMESTATE_NORMAL;
				SetFade(MODE_RESULT);
			}
		}
	}
	else
	{
		UpdatePause();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	//
	SetCamera(CAMERARASTATE_GAME);

	DrawScore();
	DrawTime();
	DrawMeshField();
	DrawMeshWall();
	//DrawPolygon();// �|���S���̕`�揈��
	//DrawWall();
	DrawShadow();
	DrawModel();
	DrawItem();
	DrawEnemy();
	DrawExplosion();
	DrawEffect();
	DrawPlayer();
	DrawBallet();
	DrawBillboard();
	//DrawMeshCylinder();
	//DrawPause();

	if (g_bPause == true)
	{
		DrawPause();
	}
}

void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	//nCounterGameState = 0;
}
GAMESTATE GetGameState(void)
{
	return g_gamestate;
}