//=============================================================================
//
// メイン処理 [manager.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"

//=====================================
//	前方宣言
//=====================================
class CInputKeyboard;
class CInputJoystick;
class CSound;
class CGame;
class CTitle;
class CResult;
class CRanking;
class CTutorial;
class CFade;
//=====================================
//	Managerクラス
//=====================================
class CManager
{
public:
	//構造体
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_TUTORIAL,
		MODE_MAX
	}MODE;

	CManager();
	~CManager();

	//初期化処理
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	//終了処理
	void Uninit(void);
	//更新処理
	void Update(void);
	//描画処理
	void Draw(void);

	//レンダラーの取得
	static CRenderer *GetRenderer(void);
	//インプットの取得
	static CInputKeyboard *GetInput(void) { return m_pInputKeyboard; };
	//
	static CInputJoystick *GetInputJoystick(void) { return m_pInputJoystick; };
	//サウンドの取得
	static CSound *GetCSound(void) { return m_psound; };
	static CFade *GetFade(void){ return m_pFade; };
	static MODE GetMode(void) { return m_mode; };
	//
	static void SetMode(MODE mode);
	static CRanking *GetRaning(void) { return m_pRanking; };
private:
	//
	static MODE m_mode;
	//Scene2dのポインタ
	CScene2d  *m_pScene2d;
	//レンダラーのポインタ
	static CRenderer *m_pRenderer;
	//キーボードのポインタ
	static CInputKeyboard *m_pInputKeyboard;
	//
	static CInputJoystick *m_pInputJoystick;
	//サウンドのポインタ
	static CSound *m_psound;

	static CGame *m_pGame;

	static CTitle *m_pTitle;

	static CFade *m_pFade;

	static CResult *m_pResult;

	static CRanking *m_pRanking;

	static CTutorial *m_pTutorial;
	//
};
#endif