//=============================================================================
//
// メイン処理 [explosion.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"
#include "scene2d.h"

//====================================
//	マクロ定義
//====================================

//=====================================
//	Explosion(爆発)クラス
//=====================================
class CEffect : public CScene2d
{
public:
	CEffect();
	~CEffect();

	//Textureの読み込み
	static HRESULT Lood(void);
	//テクスチャの破棄
	static void Unlood(void);

	//爆発のクリエイト
	static CEffect*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRadius, int Life, D3DXCOLOR color);

	//ポリゴンの初期化処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRadius,int Life, D3DXCOLOR color);
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

	D3DXVECTOR3 m_Pos;
	int m_Life;
	float m_fRadius;
};
#endif