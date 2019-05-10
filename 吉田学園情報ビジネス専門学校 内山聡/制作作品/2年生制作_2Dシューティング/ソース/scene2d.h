//=============================================================================
//
// メイン処理 [scene2d.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"
#include "scene.h"

//=====================================
//	マクロ定義
//=====================================
#define MAX_WIDTH		(300)		 //大きさ

//=====================================
//	CScene2dクラス
//=====================================
class CScene2d : public CScene
{
public:
	CScene2d(int nPriority = 3);
	~CScene2d();

	//ポリゴンの初期化処理
	HRESULT Init(void);
	//ポリゴンの終了処理
	void Uninit(void);
	//ポリゴンの更新処理
	void Update(void);
	//ポリゴンの描画処理
	void Draw(void);

	//Scene2dのクリエイト
	//static CScene2d*Create(D3DXVECTOR3 posd);
	//座標を取得
	D3DXVECTOR3 GetPos(void);
	//テクスチャの貼り付け
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	//配置処理
	void SetPos(D3DXVECTOR3 pos);
	//カラー変更
	void SetColor(D3DXCOLOR color);
	//サイズの設定
	void SetSize(D3DXVECTOR3 sizeBg);
	//爆発の配置
	void SetExplosion(int PatternAnimation);
	//テクスチャの配置
	void SetBgTexPos(D3DXVECTOR2 *pBgTexPos);
	//ポリゴンの長さ
	void SetLength(float fwidth, float fheight);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; };
private:
	// テクスチャへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;
	// 頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;
	//角度
	float m_fAngle;
	//長さ
	float m_fLength;

	// 回転
	D3DXVECTOR3				m_rotPolygon;
	// ポリゴンの位置
	D3DXVECTOR3				m_posPolygon;
	//大きさ
	D3DXVECTOR3				m_sizePolygon;
	//幅
	float m_fwidth;
	//高さ
	float m_fheight;

	//タイマー
	int						m_nTime;
	float					m_nCnt;
};
#endif