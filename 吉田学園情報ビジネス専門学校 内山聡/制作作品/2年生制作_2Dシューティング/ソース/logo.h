//=============================================================================
//
// メイン処理 [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"
#include "scene2d.h"


#define MAX_LOGO (5)
//=====================================
//	Enemy(敵)クラス		CScene2dの派生
//=====================================
class CLogo : public CScene2d
{
public:
	//列挙型
	typedef enum
	{
		LOGO_TYPE_00,
		LOGO_TYPE_01,
		LOGO_TYPE_02,
		LOGO_TYPE_03,
		LOGO_TYPE_04,
		LOGO_TYPE_MAX
	}LOGO_TYPE;
	CLogo();
	~CLogo();

	//Textureの読み込み
	static HRESULT Lood(void);
	//Textureの破棄
	static void Unlood(void);

	//背景のクリエイト
	static CLogo*Create(D3DXVECTOR3 posC, LOGO_TYPE type, D3DXVECTOR3 size);

	//敵の初期化処理
	HRESULT Init(D3DXVECTOR3 posPlay, D3DXVECTOR3 size);
	//敵の終了処理
	void Uninit(void);
	//敵の更新処理
	void Update(void);
	//敵の描画処理
	void Draw(void);

private:
	//Textureのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_LOGO];
	//移動量
	D3DXVECTOR3 m_move[MAX_LOGO];
	//座標
	D3DXVECTOR3 m_pos;
	//カウンター
	int m_nCount;
	//敵の体力
	int m_nLife;
	//
	LOGO_TYPE m_type;
	//
	D3DXVECTOR3 m_size;
};


#endif

