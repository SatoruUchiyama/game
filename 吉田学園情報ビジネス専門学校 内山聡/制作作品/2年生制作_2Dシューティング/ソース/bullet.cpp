//==========================================================================-==
//
// Player処理 [player.cpp]
// Author : satoru uchiyama
//
//==========================================================================-==
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"
#include "effect.h"
#include "enemy.h"
#include "game.h"
#include "item.h"
//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// グローバル変数:
//-----------------------------------------------------------------------------


LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//Textureの読み込み
HRESULT CBullet::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\pipo-hiteffect004.png", &m_pTexture);

	return S_OK;
}
//Textureの読み込み
void CBullet::Unlood(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//-----------------------------------------------------------------------------
// デフォルトコンストラクタ
//-----------------------------------------------------------------------------
CBullet::CBullet() : CScene2d(3)
{
	m_nLife = 0;
}
//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CBullet::~CBullet()
{

}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT CBullet::Init(D3DXVECTOR3 moveBullet, TYPE_BULLET type)
{
	CScene2d::SetLength(20.0f, 20.0f);
	CScene2d::Init();
	CScene2d::SetPos(moveBullet);
	CScene2d::SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	SetObjType(CScene::OBJTYPE_BULLET);		//タイプの仕分け

	m_nLife = MAX_BULLET_LIFE;
	m_BulletType = type;
	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CBullet::Update(void)
{
	bool Decision = false;
	CScore *pscore = CGame::GetScore();
	CScene2d::Update();
	D3DXVECTOR3 posBullet;

	posBullet = CScene2d::GetPos();
	//for (int nCountPriority = 0; nCountPriority < MAX_PRIORITY_2; nCountPriority++)
	//{
		for (int nCount = 0; nCount < MAX_MODEL; nCount++)
		{
			CScene2d *scene2d;
			scene2d = (CScene2d*)CScene::GetScene(nCount,4);

			if (scene2d != NULL)
			{
				CScene::OBJTYPE objType = scene2d->GetObjType();
				//Playerの弾なら
				if (m_BulletType == BULLET_TYPE_PLAYER)
				{
					//弾のスピード
					m_move.y = -8.0f;
					//弾が当たるオブジェクトタイプがEnemyなら
					if (objType == OBJTYPE_ENEMY)
					{
						D3DXVECTOR3 enemy;
						enemy = scene2d->GetPos();

						//あたり判定
						if (enemy.x - 20.0f < posBullet.x && enemy.x + 20.0f > posBullet.x &&
							enemy.y - 20.0f < posBullet.y && enemy.y + 20.0f > posBullet.y)
						{
							CEnemy*pEnemy = (CEnemy*)scene2d;
							pEnemy->HitEnemy(1);
							//弾が消えるか
							Decision = true;

							break;
						}
					}
				}

				//Enemyの弾なら
				if (m_BulletType == BULLET_TYPE_ENEMY)
				{
					//弾のスピード
					m_move.y = 5.0f;

					//弾が当たるオブジェクトタイプがPlayerなら
					if (objType == OBJTYPE_PLAYER)
					{

						D3DXVECTOR3 player;
						CPlayer *pPlayer = (CPlayer*)scene2d;

						player = scene2d->GetPos();
						//あたり判定
						if (player.x - (pPlayer->GetSize().x - 10.0f) < posBullet.x && player.x + (pPlayer->GetSize().x - 10.0f) > posBullet.x &&
							player.y - (pPlayer->GetSize().y - 10.0f) < posBullet.y && player.y + (pPlayer->GetSize().y - 10.0f) > posBullet.y)
						{
							CPlayer*pPlayer = (CPlayer*)scene2d;
							pPlayer->HitPlayer(1);
							//弾が消えるか
							Decision = true;

							break;
						}
					}
				}
				//プレイヤーの弾がアイテムに当たった時
				if (m_BulletType == BULLET_TYPE_PLAYER)
				{
					//弾のスピード
					m_move.y = -8.0f;
					//弾が当たるオブジェクトタイプがEnemyなら
					if (objType == OBJTYPE_ITEM)
					{
						D3DXVECTOR3 item;
						item = scene2d->GetPos();

						//あたり判定
						if (item.x - 20.0f < posBullet.x && item.x + 20.0f > posBullet.x &&
							item.y - 20.0f < posBullet.y && item.y + 20.0f > posBullet.y)
						{
							CItem*pItem = (CItem*)scene2d;
							pItem->HitItem(1, posBullet);
							//弾が消えるか
							Decision = true;

							break;
						}
					}
				}
			}
		}
	//}

	posBullet.y += m_move.y;

	CScene2d::SetPos(posBullet);

	switch (m_BulletType)
	{
	case BULLET_TYPE_PLAYER:
		CEffect::Create(posBullet, D3DXVECTOR3(300.0f, 300.0f, 0.0f), 15.0f, 10, D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f));
		break;
	case BULLET_TYPE_ENEMY:
		CEffect::Create(posBullet, D3DXVECTOR3(300.0f, 300.0f, 0.0f), 15.0f, 10, D3DXCOLOR(255.0f, 0.0f, 0.0f, 255.0f));
		break;
	default:
		break;
	}

	//画面の (下まで行ったら)消えるためにtrue
	if (posBullet.y < 0)
	{
		Decision = true;
	}
	//画面の (下まで行ったら)消えるためにtrue
	if (posBullet.y > 720)
	{
		Decision = true;
	}

	// Decisionがtrueなら消える
	if (Decision == true)
	{
 		Uninit();
	}
}

void CBullet::Draw(void)
{

	

	CScene2d::Draw();

	
}

CBullet *CBullet::Create(D3DXVECTOR3 moveC, TYPE_BULLET type)
{
	CBullet *pBullet;
	pBullet = new  CBullet;
	pBullet->Init(moveC, type);

	pBullet->BindTexture(m_pTexture);

	return pBullet;
}
