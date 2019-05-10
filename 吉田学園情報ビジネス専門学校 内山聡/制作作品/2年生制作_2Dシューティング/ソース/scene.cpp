//==========================================================================-==
//
// シーン処理 [scene.cpp]
// Author : satoru uchiyama
//
//==========================================================================-==
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "scene2d.h"
//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//	マクロ定義
//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// 静的メンバ変数
//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
CScene*CScene::m_apScene[MAX_PRIORITY_2][MAX_MODEL] = {};
int CScene::m_nNumAll = 0;

//*============================================================================
//	コンストラクタ
//*============================================================================
CScene::CScene(int nPriority)
{

	//シーンのカウント
	for (int nCountScene = 0; nCountScene < MAX_MODEL; nCountScene++)
	{
		if (m_apScene[nPriority][nCountScene] == NULL)
		{
			m_apScene[nPriority][nCountScene] = this;	//this 自分自身				m_nID = nCountScene;
			m_nNumAll++;
			m_objType = OBJTYPE_NOEN;

			m_nPriority = nPriority;
			m_nID = nCountScene;
			break;
		}
	}
	
}
//*============================================================================
//	デストラクタ
//*============================================================================
CScene::~CScene()
{

}
void CScene::ReleaseAll(void)
{
	//Priorityのカウント
	for (int nCountPriority = 0; nCountPriority < MAX_PRIORITY_2; nCountPriority++)
	{
		//シーンのカウント
		for (int nCountScene = 0; nCountScene < MAX_MODEL; nCountScene++)
		{
			if (m_apScene[nCountPriority][nCountScene] != NULL)
			{
				// 終了処理
				m_apScene[nCountPriority][nCountScene]->Uninit();

				//メモリ開放
				delete m_apScene[nCountPriority][nCountScene];

				m_apScene[nCountPriority][nCountScene] = NULL;
			}
		}
	}
	
}
void CScene::UpdateAll(void)
{
	//Priorityのカウント
	for (int nCountPriority = 0; nCountPriority < MAX_PRIORITY_2; nCountPriority++)
	{
		//シーンのカウント
		for (int nCountScene = 0; nCountScene < MAX_MODEL; nCountScene++)
		{
			if (m_apScene[nCountPriority][nCountScene] != NULL)
			{
				// ポリゴンの更新処理
				m_apScene[nCountPriority][nCountScene]->Update();
			}
		}
	}
}
void CScene::DrawAll(void)
{
	//Priorityのカウント
	for (int nCountPriority = 0; nCountPriority < MAX_PRIORITY_2; nCountPriority++)
	{
		for (int nCountScene = 0; nCountScene < MAX_MODEL; nCountScene++)
		{
			if (m_apScene[nCountPriority][nCountScene] != NULL)
			{
				// ポリゴンの描画処理
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