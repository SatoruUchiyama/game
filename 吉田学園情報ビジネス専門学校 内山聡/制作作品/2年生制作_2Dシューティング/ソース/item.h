//=============================================================================
//
// メイン処理 [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"
#include "scene2d.h"


#define MAX_X	(-15.0f)			//移動量
#define MAX_Y	(-30.0f)			//移動量
#define MAX_ITEM		(3)			//アイテムの種類
//=====================================
//	Enemy(敵)クラス		CScene2dの派生
//=====================================
class CItem : public CScene2d
{
public:
	//列挙型
	typedef enum
	{
		ITEM_RECOVERY_01,		//	小回復
		ITEM_RECOVERY_02,		//	中回復
		ITEM_RECOVERY_03,		//	大回復
		ITEM_MAX
	}ITEM_TYPE;
	CItem();
	~CItem();

	//Textureの読み込み
	static HRESULT Lood(void);

	//Textureの破棄
	static void Unlood(void);

	//背景のクリエイト
	static CItem*Create(D3DXVECTOR3 posC, ITEM_TYPE type);

	//敵の初期化処理
	HRESULT Init(D3DXVECTOR3 posPlay);

	//敵の終了処理
	void Uninit(void);

	//敵の更新処理
	void Update(void);

	//敵の描画処理
	void Draw(void);

	//ダメージ処理
	void HitItem(int nDamage,D3DXVECTOR3 pos);

private:
	//Textureのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ITEM];
	//移動量
	D3DXVECTOR3 m_move;
	//座標
	D3DXVECTOR3 m_posItem;
	//カウンター
	int m_nCountEnemy;
	//タイプのメンバ
	ITEM_TYPE m_type;
	//敵の体力
	int m_nLife;
};


#endif

