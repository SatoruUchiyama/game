//=============================================================================
//
// メイン処理 [manager.cpp]
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
//マクロ定義
//============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	if (m_psound == NULL)
	{
		//キーボードの動的確保
		m_psound = new CSound;
	}
	if (m_psound != NULL)
	{
		m_psound->InitSound(hWnd);
	}

	if (m_pRenderer == NULL)
	{
		//レンダラーの動的確保
		m_pRenderer = new CRenderer;
	}
	if (m_pRenderer != NULL)
	{
		// 初期化処理
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{//フルスクリーン
			return -1;
		}
	}


	if (m_pInputKeyboard == NULL)
	{
		//キーボードの動的確保
		m_pInputKeyboard = new CInputKeyboard;
	}
	if (m_pInputKeyboard != NULL)
	{
		// 初期化処理
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{//フルスクリーン
			return -1;
		}
	}


	if (m_pInputJoystick == NULL)
	{
		//キーボードの動的確保
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
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	//クラスの破棄
	if (m_pInputKeyboard != NULL)
	{
		// 終了処理
		m_pInputKeyboard->Uninit();

		//メモリの開放
		delete m_pInputKeyboard;

		//NULLにする
		m_pInputKeyboard = NULL;
	}

	//レンダリングクラスの破棄
	if (m_pRenderer != NULL)
	{
		// 終了処理
		m_pRenderer->Uninit();

		//メモリの開放
		delete m_pRenderer;

		//NULLにする
		m_pRenderer = NULL;
	}

	//レンダリングクラスの破棄
	if (m_pFade != NULL)
	{
		// 終了処理
		m_pFade->Uninit();

		//メモリの開放
		delete m_pFade;

		//NULLにする
		m_pFade = NULL;
	}
	//レンダリングクラスの破棄
	if (m_psound != NULL)
	{
		// 終了処理
		m_psound->UninitSound();

		//メモリの開放
		delete m_psound;

		//NULLにする
		m_psound = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{

	if (m_pInputJoystick != NULL)
	{
		// キーボードの更新処理
		m_pInputJoystick->Update();
	}
	if (m_pInputKeyboard != NULL)
	{
		// キーボードの更新処理
		m_pInputKeyboard->Update();
	}

	switch (m_mode)
	{
	case MODE_TITLE:

		if (m_pTitle != NULL)
		{
			// レンダラーの更新処理
			m_pTitle->Update();
		}

		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			// レンダラーの更新処理
			m_pTutorial->Update();
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			// レンダラーの更新処理
			m_pGame->Update();
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			// レンダラーの更新処理
			m_pResult->Update();
		}
		break;
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			// レンダラーの更新処理
			m_pRanking->Update();
		}
		break;
	}
	
	if (m_pRenderer != NULL)
	{
		// レンダラーの更新処理
		m_pRenderer->Update();
	}

	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// 描画処理
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
