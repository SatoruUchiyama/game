//=============================================================================
//
// フェード処理 [fade.h]
// Author : 
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
class CManager;
class CFade
{
public:
	CFade();
	~CFade();
	//*************************************
	// フェードの状態
	//*************************************
	typedef enum
	{
		FADE_NONE = 0,		// 何もしていない状態
		FADE_IN,			// フェードイン状態
		FADE_OUT,			// フェードアウト状態
		FADE_MAX
	} FADE;

	//操作キャラのクリエイト
	static CFade*Create(void);
	//*****************************************************************************
	// プロトタイプ宣言
	//*****************************************************************************
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(CManager::MODE ModeNext);

	FADE Get(void);
	
	void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);
private:
	LPDIRECT3DTEXTURE9		m_pTextureFade = NULL;	// テクスチャへのポインタ
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade = NULL;	// 頂点バッファへのポインタ
	static FADE					m_fade;					// フェード状態
	static CManager::MODE					m_modeNext;				// 次のモード
	static D3DXCOLOR				m_colorFade;			// フェード色

};

#endif