//=============================================================================
//
// メイン処理 [number.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//=====================================
//	ヘッダー読み込み
//=====================================
#include "main.h"

//=====================================
//	マクロ定義
//=====================================
#define MAX_TRUSS		(8)
//=====================================
//	Number(数字処理)クラス
//=====================================
class CNumber
{
public:
	CNumber();
	~CNumber();

	//テクスチャの読み込み
	static HRESULT Lood(void);
	//テクスチャの破棄
	static void Unlood(void);

	//数字の初期化処理
	HRESULT Init(D3DXVECTOR3 pos);
	//数字の終了処理
	void Uninit(void);
	//数字の更新処理
	void Update(void);
	//数字の描画処理
	void Draw(void);
	void DrawScore(int nKioku);
	//数字のセット
	//void SetNumber(int nNumber);
private:
	// テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture;
	// 頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
};
#endif