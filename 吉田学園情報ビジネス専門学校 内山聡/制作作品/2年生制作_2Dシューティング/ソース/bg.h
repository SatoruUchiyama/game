//=============================================================================
//
// メイン処理 [bg.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//=====================================
//	マクロ定義
//=====================================
#define MAX_BG_TEXTURE		(4)			//	BGのテクスチャの最大数
#define SPEED_BG_00			(0.0002f)	//	1枚目のテクスチャスピード
#define SPEED_BG_01			(0.0005f)	//	2枚目のテクスチャスピード
#define SPEED_BG_02  		(0.001f)	//	3枚目のテクスチャスピード
#define SPEED_BG_03			(0.004f)	//	4枚目のテクスチャスピード
//=====================================
//	ヘッダー読み込み
//=====================================
#include "main.h"
#include "scene.h"

//=====================================
//	前方宣言
//=====================================
class CScene2D;

//=====================================
//	Bg(背景)クラス
//=====================================
class CBg : public CScene
{
public:
	CBg();
	~CBg();

	//Textureの読み込み
	static HRESULT Lood(void);
	//Textureの破棄
	static void Unlood(void);

	//背景のクリエイト
	static CBg*Create(void);

	//	背景の初期化処理
	HRESULT Init(void);
	//	背景の終了処理
	void Uninit(void);
	//	背景の更新処理
	void Update(void);
	//	背景の描画処理
	void Draw(void);
private:
	//Textureのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BG_TEXTURE];
	CScene2d *m_pScene2d[MAX_BG_TEXTURE];
	float m_texBase[MAX_BG_TEXTURE];

	//移動量
	D3DXVECTOR3 m_move;
};
#endif