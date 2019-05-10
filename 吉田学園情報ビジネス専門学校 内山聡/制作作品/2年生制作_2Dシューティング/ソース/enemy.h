//=============================================================================
//
// メイン処理 [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
//ヘッダー読み込み
//=============================================================================
#include "main.h"
#include "scene2d.h"

#define END_ENEMY (3)

#define MAX_ENEMY		(5)			//アイテムの種類
//=============================================================================
//	Enemy(敵)クラス		CScene2dの派生
//=============================================================================
class CEnemy : public CScene2d
{
public:
	//列挙型
	typedef enum
	{
		ENEMY_TARGET_01,		//移動パターン
		ENEMY_TARGET_02,		//移動パターン
		ENEMY_TARGET_03,		//アイテムが出る敵
		ENEMY_TARGET_04,		//チュートリアル用
		ENEMY_TARGET_05,
		ENEMY_MAX
	}ENEMY_TYPE;

	CEnemy();
	~CEnemy();

	//	Textureの読み込み
	static HRESULT Lood(void);

	//	Textureの破棄
	static void Unlood(void);

	//	背景のクリエイト
	static CEnemy*Create(D3DXVECTOR3 posC, ENEMY_TYPE type,int nLife,D3DXVECTOR3 size);

	//	敵の初期化処理
	HRESULT Init(D3DXVECTOR3 posPlay,int nLife, D3DXVECTOR3 size);

	//	敵の終了処理
	void Uninit(void);

	//	敵の更新処理
	void Update(void);

	//	敵の描画処理
	void Draw(void);

	//	ダメージ処理
	void HitEnemy(int nDamage);

private:
	//	Textureのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ENEMY];
	//	移動量
	D3DXVECTOR3 m_move[MAX_ENEMY];
	//	座標
	D3DXVECTOR3 m_posEnemy[MAX_ENEMY];

	//	カウンター
	int m_nCountEnemy;

	//	敵の体力
	int m_nLife;

	//敵のタイプ
	ENEMY_TYPE m_EnemyType;

	static int nCountEnemyEnd;
	//	敵の弾
	int m_nCountBullet_Enemy;
};


#endif

