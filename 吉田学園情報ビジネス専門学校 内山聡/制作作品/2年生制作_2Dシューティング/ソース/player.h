//=============================================================================
//
// メイン処理 [player.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"
#include "scene2d.h"

#define MAX_PLAYER		(2)
//=====================================
//	Player(操作キャラ)クラス
//=====================================
class CPlayer : public CScene2d
{
public:
	//列挙型
	typedef enum
	{
		OBJTYPE_PLAYER_01 = 0,
		OBJTYPE_PLAYER_02,
		OBJTYPE_MAX
	}PLAYER_TYPE;
	//列挙型
	typedef enum
	{
		OBJTYPE_PLAYER_NORMAL = 0,
		OBJTYPE_PLAYER_PARTY,
		OBJTYPE_MAX2
	}PLAYER_PARTY_TYPE;

	CPlayer();
	~CPlayer();

	//Textureの読み込み
	static HRESULT Lood(void);
	//Textureの破棄
	static void Unlood(void);

	//操作キャラのクリエイト
	static CPlayer*Create(D3DXVECTOR3 posC , D3DXVECTOR3 size, PLAYER_TYPE type);

	//プレイヤーの初期化処理
	HRESULT Init(D3DXVECTOR3 posPlay);
	//プレイヤーの終了処理
	void Uninit(void);
	//プレイヤーの更新処理
	void Update(void);
	//プレイヤーの描画処理
	void Draw(void);
	//ダメージ処理
	void HitPlayer(int nDamage);

	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	//テクスチャのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_PLAYER];
	D3DXVECTOR3 m_move;					//移動量
	D3DXVECTOR3 m_posPlayer;			//座標
	int m_nCountBullet;					//弾の撃つスピードをコントロール
	int m_nLife;
	PLAYER_TYPE m_type;
	PLAYER_PARTY_TYPE m_typeParty;
	D3DXVECTOR3 m_size;
	static int m_nCount;
};
#endif

