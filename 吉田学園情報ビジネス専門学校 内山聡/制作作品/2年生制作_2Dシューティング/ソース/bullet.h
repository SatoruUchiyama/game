//=============================================================================
//
// メイン処理 [bullet.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"
#include "scene2d.h"

//=====================================
//	Bullet(弾)クラス
//=====================================
class CBullet : public CScene2d
{
public:

	//列挙型
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_ENEMY,
		BULLET_TYPE_PLAYER,
		BULLET_TYPE_MAX
	}TYPE_BULLET;

	CBullet();
	~CBullet();
	//Textureの読み込み
	static HRESULT Lood(void);
	//Textureの破棄
	static void Unlood(void);

	//弾のクリエイト
	static CBullet*Create(D3DXVECTOR3 moveC, TYPE_BULLET type);

	//	弾の初期化処理
	HRESULT Init(D3DXVECTOR3 moveBullet, TYPE_BULLET type);
	//	弾の終了処理
	void Uninit(void);			
	//	弾の更新処理
	void Update(void);
	//	弾の描画処理
	void Draw(void);

private:
	//Textureのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;
	//移動量
	D3DXVECTOR3 m_move;
	//弾の体力
	int m_nLife;
	//弾の区別(誰の弾か)
	TYPE_BULLET m_BulletType;
};
#endif