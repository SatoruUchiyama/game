
//=============================================================================
//
// �w�i���� [rankinng.cpp]
// Author : uchiyama
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS		//�x�����Ȃ�����

#include "game.h"
#include "input.h"
#include"fade.h"
#include"player.h"
#include"ranking.h"
#include"time.h"
#include "sound.h"
#include "number.h"
#include "score.h"
#include "logo.h"
#include "bg.h"
#include "stdio.h"		//�t�@�C�����o�͂��邽�߂ɕK�v

CNumber *CRanking::m_apNumber[MAX_RANKING][MAX_NUMBER] = {};
int CRanking::m_RankScore[MAX_RANKING] = {};
//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define Rankinng_POS_WIDTH		(SCREEN_WIDTH)					//DirectX�̕�
#define Rankinng_POS_HEIGHT		(SCREEN_HEIGHT)					//DirectX�̍���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking()//�`�悷�鏇�ʂ����߂�
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{

}
//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CRanking::Init(void)
{
	CNumber::Lood();
	CBg::Lood();
	CLogo::Lood();

	int RankScore;
	LoadRanking();
	m_nTimeRanking = 0;
	//�w�i�̃N���G�C�g
	CBg::Create();
	CLogo::Create(D3DXVECTOR3(500.0f, 200.0f, 0.0f), CLogo::LOGO_TYPE_01,D3DXVECTOR3(400.0f,300.0f,0.0f));
	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{//���\�����邩

		RankScore = m_RankScore[nCntRank];

		for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
		{//��
		 //�������𓮓I�m��
			m_apNumber[nCntRank][nCnt] = new CNumber;
			m_apNumber[nCntRank][nCnt]->Init(D3DXVECTOR3(600.0f - (nCnt * 57.0f), 300.0f + (nCntRank* 70.0f), 0));
			m_apNumber[nCntRank][nCnt]->DrawScore(RankScore);
			RankScore /= 10;
		}
	}
	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CRanking::Uninit(void)
{
	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
		{
			//�I������
			m_apNumber[nCntRank][nCnt]->Uninit();


			//delete m_apNumber[nCntRank][nCnt];

			//NULL�ɂ���
			m_apNumber[nCntRank][nCnt] = NULL;
		}
	}
	CScene::ReleaseAll();
	CLogo::Unlood();
	CBg::Unlood();
	CNumber::Unlood();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CRanking::Update(void)
{
	CFade *pFade = CManager::GetFade();
	CInputJoystick *pJoystick = CManager::GetInputJoystick();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	//�L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = CManager::GetInput();
	m_nTimeRanking++;
	if (pJoystick->GetPress(11) == true || pKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		pFade->Set(CManager::MODE_TITLE);
	}
	else if (m_nTimeRanking % 600 == 0)
	{
		pFade->Set(CManager::MODE_TITLE);
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CRanking::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		for (int nCntRank = 0; nCntRank < MAX_NUMBER; nCntRank++)
		{
			//�`�揈��
			m_apNumber[nCntRank][nCnt]->Draw();
		}
	}
}

//=============================================================================
//�����L���O�̐�������
//=============================================================================
CRanking *CRanking::Create(void)
{
	CRanking *pRanking = {};

	if (pRanking == NULL)
	{//NULL��������

	 //�������̓��I�m��
		pRanking = new CRanking;

		if (pRanking != NULL)
		{//NULL����Ȃ�������

		 //�|���S���̏���������
			pRanking->Init();
		}
		else
		{
			MessageBox(0, "NULL�ł���", "�x��", MB_OK);
		}
	}
	else
	{
		MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);
	}

	return pRanking;
}

//=============================================================================
//�����L���O�̃Z�[�u����
//=============================================================================
void CRanking::SaveRanking(void)
{
	FILE *pFile;
	CGame *pGame = NULL;

	CScore *pScore = NULL;
	//*m_RankScore[0] = 0000;
	//m_RankScore[1] = 0000;
	//m_RankScore[2] = 0000;
	//m_RankScore[3] = 0000;
	//m_RankScore[4] = 0000;
	//m_RankScore[5] = 0000;*/

	int nCntTime;
	int Count;
	int Count2;
	int nData;
	int nScore = pScore->GetScore();

	for (nCntTime = 0; nCntTime < MAX_RANKING; nCntTime++)
	{
		m_RankScore[MAX_RANKING - 1] = nScore;

		for (Count = 0; Count < MAX_RANKING - 1; Count++)
		{
			for (Count2 = Count + 1; Count2 < MAX_RANKING; Count2++)
			{
				if (m_RankScore[Count2] > m_RankScore[Count])
				{
					nData = m_RankScore[Count];
					m_RankScore[Count] = m_RankScore[Count2];
					m_RankScore[Count2] = nData;
				}
			}
		}

		break;
	}

	pFile = fopen("ranking.bin", "wb");

	if (pFile != NULL)
	{
		fwrite(&m_RankScore, sizeof(int), MAX_RANKING, pFile);

		fclose(pFile);
	}
}

//=============================================================================
//�����L���O�̃��[�h����
//=============================================================================
void CRanking::LoadRanking(void)
{
	FILE *pFile;

	pFile = fopen("ranking.bin", "rb");

	if (pFile != NULL)
	{
		fread(&m_RankScore, sizeof(int), MAX_RANKING, pFile);

		fclose(pFile);
	}
}
