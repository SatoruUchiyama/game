//=============================================================================
//
// ���C������ [manager.cpp]
// Author : 
//
//=============================================================================
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "sound.h"
#include "number.h"
#include "score.h"
#include "effect.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "ranking.h"
#include "tutorial.h"

CSound *CManager::m_psound = NULL;
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputJoystick *CManager::m_pInputJoystick = NULL;

CGame *CManager::m_pGame = NULL;
CTitle *CManager::m_pTitle = NULL;
CResult *CManager::m_pResult = NULL;
CFade *CManager::m_pFade = NULL;
CRanking *CManager::m_pRanking = NULL;
CTutorial *CManager::m_pTutorial = NULL;

CManager::MODE CManager::m_mode = MODE_TITLE;

//============================================================================
//�}�N����`
//============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	if (m_psound == NULL)
	{
		//�L�[�{�[�h�̓��I�m��
		m_psound = new CSound;
	}
	if (m_psound != NULL)
	{
		m_psound->InitSound(hWnd);
	}

	if (m_pRenderer == NULL)
	{
		//�����_���[�̓��I�m��
		m_pRenderer = new CRenderer;
	}
	if (m_pRenderer != NULL)
	{
		// ����������
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{//�t���X�N���[��
			return -1;
		}
	}


	if (m_pInputKeyboard == NULL)
	{
		//�L�[�{�[�h�̓��I�m��
		m_pInputKeyboard = new CInputKeyboard;
	}
	if (m_pInputKeyboard != NULL)
	{
		// ����������
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{//�t���X�N���[��
			return -1;
		}
	}


	if (m_pInputJoystick == NULL)
	{
		//�L�[�{�[�h�̓��I�m��
		m_pInputJoystick = new CInputJoystick;
	}
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->Init(hInstance, hWnd);
	}

	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create();

		m_pFade->Set(m_mode);
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	//�N���X�̔j��
	if (m_pInputKeyboard != NULL)
	{
		// �I������
		m_pInputKeyboard->Uninit();

		//�������̊J��
		delete m_pInputKeyboard;

		//NULL�ɂ���
		m_pInputKeyboard = NULL;
	}

	//�����_�����O�N���X�̔j��
	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();

		//�������̊J��
		delete m_pRenderer;

		//NULL�ɂ���
		m_pRenderer = NULL;
	}

	//�����_�����O�N���X�̔j��
	if (m_pFade != NULL)
	{
		// �I������
		m_pFade->Uninit();

		//�������̊J��
		delete m_pFade;

		//NULL�ɂ���
		m_pFade = NULL;
	}
	//�����_�����O�N���X�̔j��
	if (m_psound != NULL)
	{
		// �I������
		m_psound->UninitSound();

		//�������̊J��
		delete m_psound;

		//NULL�ɂ���
		m_psound = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{

	if (m_pInputJoystick != NULL)
	{
		// �L�[�{�[�h�̍X�V����
		m_pInputJoystick->Update();
	}
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�̍X�V����
		m_pInputKeyboard->Update();
	}

	switch (m_mode)
	{
	case MODE_TITLE:

		if (m_pTitle != NULL)
		{
			// �����_���[�̍X�V����
			m_pTitle->Update();
		}

		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			// �����_���[�̍X�V����
			m_pTutorial->Update();
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			// �����_���[�̍X�V����
			m_pGame->Update();
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			// �����_���[�̍X�V����
			m_pResult->Update();
		}
		break;
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			// �����_���[�̍X�V����
			m_pRanking->Update();
		}
		break;
	}
	
	if (m_pRenderer != NULL)
	{
		// �����_���[�̍X�V����
		m_pRenderer->Update();
	}

	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();
	}
}

void CManager::SetMode(MODE mode)
{
	CManager *psound = NULL;

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			psound->GetCSound()->StopSound(CSound::SOUND_LABEL_BGM000);
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			psound->GetCSound()->StopSound(CSound::SOUND_LABEL_BGM000);
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			psound->GetCSound()->StopSound(CSound::SOUND_LABEL_BGM000);
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;
	}

	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = new CTitle;
			
			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_BGM000);
			if (m_pTitle != NULL)
			{
				m_pTitle->Init();
			}
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = new CTutorial;

			if (m_pTutorial != NULL)
			{
				m_pTutorial->Init();
			}
		}
		break;
	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;

			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_BGM000);

			if (m_pGame != NULL)
			{
				m_pGame->Init();
			}
		}

		break;
	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;

			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_BGM000);

			if (m_pResult != NULL)
			{
				m_pResult->Init();
			}

		}
		break;
	case MODE_RANKING:
		if (m_pRanking == NULL)
		{
			m_pRanking = new CRanking;

			//psound->GetCSound()->PlaySound(SOUND_LABEL_SE_SHOT);

			if (m_pRanking != NULL)
			{
				m_pRanking->Init();
			}

		}
		break;
	}
}
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}
