//=============================================================================
//
// メイン処理 [explosion.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"
#include "scene2d.h"

//====================================
//	マクロ定義
//====================================
#define MAX_COUNTER		(5)
#define MAX_PATTERN		(8)
#define UV_U			(0.125f)
#define UV_V			(1.0f)

//=====================================
//	Explosion(爆発)クラス
//=====================================
class CExplosion : public CScene2d
{
public:
	CExplosion();
	~CExplosion();

	//Textureの読み込み
	static HRESULT Lood(void);
	//テクスチャの破棄
	static void Unlood(void);

	//爆発のクリエイト
	static CExplosion*Create(D3DXVECTOR3 posExplosion);

	//ポリゴンの初期化処理
	HRESULT Init(D3DXVECTOR3 posExplosion);
	//ポリゴンの終了処理
	void Uninit(void);
	//ポリゴンの更新処理
	void Update(void);
	//ポリゴンの描画処理
	void Draw(void);
private:
	// 頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;
	//テクスチャののポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;
	//アニメーションのカウント
	int m_nCounterAnimation;
	//アニメーションのパターン
	int m_nPatternAnimation;
};
#endif