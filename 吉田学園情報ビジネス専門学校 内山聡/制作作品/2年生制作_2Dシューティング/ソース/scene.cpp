//==========================================================================-==
//
// �V�[������ [scene.cpp]
// Author : satoru uchiyama
//
//==========================================================================-==
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "scene2d.h"
//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//	�}�N����`
//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// �ÓI�����o�ϐ�
//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
CScene*CScene::m_apScene[MAX_PRIORITY_2][MAX_MODEL] = {};
int CScene::m_nNumAll = 0;

//*============================================================================
//	�R���X�g���N�^
//*============================================================================
CScene::CScene(int nPriority)
{

	//�V�[���̃J�E���g
	for (int nCountScene = 0; nCountScene < MAX_MODEL; nCountScene++)
	{
		if (m_apScene[nPriority][nCountScene] == NULL)
		{
			m_apScene[nPriority][nCountScene] = this;	//this �������g				m_nID = nCountScene;
			m_nNumAll++;
			m_objType = OBJTYPE_NOEN;

			m_nPriority = nPriority;
			m_nID = nCountScene;
			break;
		}
	}
	
}
//*============================================================================
//	�f�X�g���N�^
//*============================================================================
CScene::~CScene()
{

}
void CScene::ReleaseAll(void)
{
	//Priority�̃J�E���g
	for (int nCountPriority = 0; nCountPriority < MAX_PRIORITY_2; nCountPriority++)
	{
		//�V�[���̃J�E���g
		for (int nCountScene = 0; nCountScene < MAX_MODEL; nCountScene++)
		{
			if (m_apScene[nCountPriority][nCountScene] != NULL)
			{
				// �I������
				m_apScene[nCountPriority][nCountScene]->Uninit();

				//�������J��
				delete m_apScene[nCountPriority][nCountScene];

				m_apScene[nCountPriority][nCountScene] = NULL;
			}
		}
	}
	
}
void CScene::UpdateAll(void)
{
	//Priority�̃J�E���g
	for (int nCountPriority = 0; nCountPriority < MAX_PRIORITY_2; nCountPriority++)
	{
		//�V�[���̃J�E���g
		for (int nCountScene = 0; nCountScene < MAX_MODEL; nCountScene++)
		{
			if (m_apScene[nCountPriority][nCountScene] != NULL)
			{
				// �|���S���̍X�V����
				m_apScene[nCountPriority][nCountScene]->Update();
			}
		}
	}
}
void CScene::DrawAll(void)
{
	//Priority�̃J�E���g
	for (int nCountPriority = 0; nCountPriority < MAX_PRIORITY_2; nCountPriority++)
	{
		for (int nCountScene = 0; nCountScene < MAX_MODEL; nCountScene++)
		{
			if (m_apScene[nCountPriority][nCountScene] != NULL)
			{
				// �|���S���̕`�揈��
				m_apScene[nCountPriority][nCountScene]->Draw();
			}
		}
	}
}

void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nPriority;
		int nID;
		nPriority = m_nPriority;
		nID = m_nID;
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

CScene *CScene::GetScene(int nIndex,int nPriority)
{
	return m_apScene[nPriority][nIndex];
}