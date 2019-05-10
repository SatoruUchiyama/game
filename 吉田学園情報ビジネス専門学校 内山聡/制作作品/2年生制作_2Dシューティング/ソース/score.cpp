//==========================================================================-==
//
// Player���� [bg.cpp]
// Author : Satoru Uchiyama
//
//==========================================================================-==
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "scene2d.h"
#include "score.h"
#include "number.h"

CNumber *CScore::m_pNumber[8] = {};
int CScore::m_nKioku = 0;
//-----------------------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-----------------------------------------------------------------------------
CScore::CScore(): CScene(7)
{
	m_nKioku = 0;
}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CScore::~CScore()
{

}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT CScore::Init(void)
{
	//�^�C�v�̎d����
	//SetObjType(CScene::OBJTYPE_BG);

	for (int nCount = 0; nCount < MAX_TRUSS; nCount++)
	{
		m_pNumber[nCount] = new CNumber;
		m_pNumber[nCount]->Init(D3DXVECTOR3(1200.0f - nCount*40.0f, 50.0f, 0.0f));
		//m_pNumber[nCount]->CNumber::Create(D3DXVECTOR3(950.0f + nCount*50.0f, 40.0f, 0.0f));
	}
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TRUSS; nCount++)
	{
		if (m_pNumber[nCount] != NULL)
		{
			m_pNumber[nCount]->Uninit();
			m_pNumber[nCount] = NULL;
		}
	}
	Release();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CScore::Update(void)
{
	for (int nCount = 0; nCount < MAX_TRUSS; nCount++)
	{
		m_pNumber[nCount]->Update();
	}
}

void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_TRUSS; nCount++)
	{
		m_pNumber[nCount]->Draw();
	}
}

CScore *CScore::Create(D3DXVECTOR3 pos)
{
	CScore *pScore;
	pScore = new  CScore;

	pScore->Init();

	return pScore;
}

void CScore::AddScore(int nValue)
{
	int nKioku;
   	m_nKioku += nValue;
	nKioku = m_nKioku;
	for (int nCountScorePotato = 0; nCountScorePotato < 8; nCountScorePotato++)
	{
		m_pNumber[nCountScorePotato]->DrawScore(nKioku);
		nKioku /= 10;
	}

}
int CScore::GetScore(void)
{
	return m_nKioku;
}