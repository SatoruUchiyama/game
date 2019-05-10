//=============================================================================
//
// ポーズメニュー処理 [pauseselect.h]
// Author : 
//
//=============================================================================
#ifndef _PAUSESELECT_H_
#define _PAUSESELECT_H_

#include "main.h"
#include "scene.h"

class CScene2d;

//*****************************************************************************
// マクロ定義
//****************************************************************************
#define PAUSESELECT_POS_X			(200)						//頂点座標Xの移動量
#define PAUSESELECT_POS_Y			(50)						//頂点座標Yの移動量
#define TEX_LEFT				(0.0f)						//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)						//テクスチャ座標U右
#define TEX_TOP					(0.0f)						//テクスチャ座標V上
#define TEX_BOT					(1.0f)						//テクスチャ座標V下
#define MAX_PAUSEMENU			(3)							//ランキングの数

class CPauselogo : public CScene
{
public:
	typedef enum
	{
		SELECTMODE_CONTINUE = 0,		//続行状態
		SELECTMODE_RETRY,			//リトライ状態
		SELECTMODE_QUIT,			//終了
		SELECTMODE_MAX				//状態の総数
	}SELECTMODE;						//列挙型

	CPauselogo(int nPriority = 7);
	~CPauselogo();

	//Textureの読み込
	static HRESULT Lood(void);
	//Textureの破棄
	static void Unlood(void);
	//操作キャラのクリエイト
	static CPauselogo*Create(D3DXVECTOR3 pos,float fwidth, float fheight);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static SELECTMODE GetMode(void);
	int GetSelect(void);
private:
	D3DXVECTOR3 m_pos;
	float m_fwidth;
	float m_fheight;
	int	m_nSelect;
	static SELECTMODE m_Mode;
	D3DXCOLOR m_color[MAX_PAUSEMENU];
	CScene2d *m_apScene2D[MAX_PAUSEMENU];
	//テクスチャのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_PAUSEMENU];

	float m_fMenuPosY;
	// 頂点バッファへのポインタ
};
#endif