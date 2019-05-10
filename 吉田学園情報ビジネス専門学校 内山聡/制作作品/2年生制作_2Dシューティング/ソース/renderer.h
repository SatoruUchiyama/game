//=============================================================================
//
// メイン処理 [renderer.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"

class CPauselogo;
//=====================================
//	Rendererクラス
//=====================================
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	//レンダラーの初期化処理
	HRESULT Init(HWND hWnd, bool bWindow);
	//レンダラーの終了処理
	void Uninit(void);
	//レンダラーの更新処理
	void Update(void);
	//レンダラーの描画処理
	void Draw(void);

	//デバイスの取得
	//LPDIRECT3DDEVICE9 GetDevice(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; };
private:
#ifdef _DEBUG
	void DrawFPS(void);
#endif
	bool m_bPause;
	CPauselogo *m_pPauseLogo;
	// Direct3Dオブジェクト
	LPDIRECT3D9				m_pD3D = NULL;
	// Deviceオブジェクト(描画に必要)
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;

	//FPSのカウントをもらう
	int m_FpsCount;
#ifdef _DEBUG
	// フォントへのポインタ
	LPD3DXFONT				m_pFont = NULL;
#endif
};
#endif

