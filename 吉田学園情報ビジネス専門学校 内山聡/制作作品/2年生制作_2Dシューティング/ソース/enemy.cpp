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
#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "item.h"
#include "sound.h"
#include "fade.h"
//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_ENEMY] = {};
int CEnemy::nCountEnemyEnd = 0;
//-----------------------------------------------------------------------------
// デフォルトコンストラクタ
//-----------------------------------------------------------------------------
CEnemy::CEnemy():CScene2d(4)
{

}
//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CEnemy::~CEnemy()
{

}

HRESULT CEnemy::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\敵3.png", &m_pTexture[0]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\敵2.png", &m_pTexture[1]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\敵1.png", &m_pTexture[2]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\敵1.png", &m_pTexture[3]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\最強トリオ.png", &m_pTexture[4]);
	return S_OK;
}

void CEnemy::Unlood(void)
{
	for (int nCount = 0; nCount < MAX_ITEM; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------4
HRESULT CEnemy::Init(D3DXVECTOR3 posPlay,int nLife, D3DXVECTOR3 size)
{
	//CScene2d::SetLength(50.0f, 50.0f);
	m_nLife = nLife;
	CScene2d::Init();
	CScene2d::SetPos(D3DXVECTOR3(posPlay));
	CScene2d::SetSize(size);
	nCountEnemyEnd = 0;
	SetObjType(CScene::OBJTYPE_ENEMY);//タイプの仕分け
	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CEnemy::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CEnemy::Update(void)
{
	bool Decision = false;
	CInputKeyboard *pKeyboard = CManager::GetInput();
	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		m_posEnemy[nCount] = GetPos();
	}

	switch (m_EnemyType)
	{
	case ENEMY_TARGET_01:
		//	敵の移動処理
		m_move[m_EnemyType].x -= sinf(D3DX_PI) * 0.5f;
		m_move[m_EnemyType].y -= cosf(D3DX_PI) * 0.5f;

		//	敵が弾を撃つカウント
		m_nCountBullet_Enemy++;
		if (m_nCountBullet_Enemy == 60)
		{
			//	敵の弾のクリエイト	(敵の位置から)	(タイプはenemy)
			CBullet::Create(D3DXVECTOR3(m_posEnemy[m_EnemyType]), CBullet::BULLET_TYPE_ENEMY);
			m_nCountBullet_Enemy = 0;
		}
		m_move[m_EnemyType].x += (0.0f - m_move[m_EnemyType].x)*MAX_INERTIAL_ENEMY;
		m_move[m_EnemyType].y += (0.0f - m_move[m_EnemyType].y)*MAX_INERTIAL_ENEMY;
		//移動処理
		m_posEnemy[m_EnemyType] += m_move[m_EnemyType];

		break;
	case ENEMY_TARGET_02:
		//	敵の移動処理
		m_move[m_EnemyType].x -= sinf(D3DX_PI*0.5f) * MAX_SPEED_ENEMY;
		m_move[m_EnemyType].y -= cosf(D3DX_PI*0.5f) * MAX_SPEED_ENEMY;

		//	敵が弾を撃つカウント
		m_nCountBullet_Enemy++;
		if (m_nCountBullet_Enemy == 60)
		{
			//	敵の弾のクリエイト	(敵の位置から)	(タイプはenemy)
			CBullet::Create(D3DXVECTOR3(m_posEnemy[m_EnemyType]), CBullet::BULLET_TYPE_ENEMY);
			m_nCountBullet_Enemy = 0;
		}
		m_move[m_EnemyType].x += (0.0f - m_move[m_EnemyType].x)*MAX_INERTIAL_ENEMY;
		m_move[m_EnemyType].y += (0.0f - m_move[m_EnemyType].y)*MAX_INERTIAL_ENEMY;
		//移動処理
		m_posEnemy[m_EnemyType] += m_move[m_EnemyType];
		if (0  > m_posEnemy[m_EnemyType].x)
		{
			//m_posEnemy.x = m_posEnemy.x - SCREEN_WIDTH;
			Decision = true;
		}
		break;
	case ENEMY_TARGET_03:
		//	敵の移動処
		m_move[m_EnemyType].x += sinf(D3DX_PI*0.5) * MAX_SPEED_ENEMY;
		m_move[m_EnemyType].y += cosf(D3DX_PI*0.5) * MAX_SPEED_ENEMY;

		//	敵が弾を撃つカウント
		m_nCountBullet_Enemy++;
		if (m_nCountBullet_Enemy == 120)
		{
			//	敵の弾のクリエイト	(敵の位置から)	(タイプはenemy)
			CBullet::Create(D3DXVECTOR3(m_posEnemy[m_EnemyType]), CBullet::BULLET_TYPE_ENEMY);
			m_nCountBullet_Enemy = 0;
		}
		m_move[m_EnemyType].x += (0.0f - m_move[m_EnemyType].x)*MAX_INERTIAL_ENEMY;
		m_move[m_EnemyType].y += (0.0f - m_move[m_EnemyType].y)*MAX_INERTIAL_ENEMY;
		//移動処理
		m_posEnemy[m_EnemyType] += m_move[m_EnemyType];
		//あたり判定
		if (SCREEN_WIDTH  < m_posEnemy[m_EnemyType].x)
		{
			//m_posEnemy.x = m_posEnemy.x - SCREEN_WIDTH;
			Decision = true;
		}
	case ENEMY_TARGET_04:
		break;
	case ENEMY_TARGET_05:
		//	敵の移動処
		m_move[m_EnemyType].x += sinf(D3DX_PI*0.5) * MAX_SPEED_ENEMY;
		m_move[m_EnemyType].y += cosf(D3DX_PI*0.5) * MAX_SPEED_ENEMY;

		//	敵が弾を撃つカウント
		m_nCountBullet_Enemy++;
		if (m_nCountBullet_Enemy == 20)
		{
			//	敵の弾のクリエイト	(敵の位置から)	(タイプはenemy)
			CBullet::Create(D3DXVECTOR3(m_posEnemy[m_EnemyType]), CBullet::BULLET_TYPE_ENEMY);
			m_nCountBullet_Enemy = 0;
		}
		m_move[m_EnemyType].x += (0.0f - m_move[m_EnemyType].x)*MAX_INERTIAL_ENEMY;
		m_move[m_EnemyType].y += (0.0f - m_move[m_EnemyType].y)*MAX_INERTIAL_ENEMY;
		//移動処理
		m_posEnemy[m_EnemyType] += m_move[m_EnemyType];
		//あたり判定
		if (SCREEN_WIDTH < m_posEnemy[m_EnemyType].x)
		{
			m_posEnemy[m_EnemyType].x = m_posEnemy[m_EnemyType].x - SCREEN_WIDTH;
		}
		/*else if (0 > m_posEnemy[m_EnemyType].x)
		{
			m_posEnemy[m_EnemyType].x = SCREEN_WIDTH + m_posEnemy[m_EnemyType].x;
		}*/
		break;
	default:
		break;
	}

	////あたり判定
	//if (SCREEN_WIDTH < m_posEnemy[2].x)
	//{
	//	//m_posEnemy.x = m_posEnemy.x - SCREEN_WIDTH;
	//	Decision = true;
	//}
	//else if (0 > m_posEnemy[1].x)
	//{
	//	//m_posEnemy.x = SCREEN_WIDTH + m_posEnemy.x;
	//	Decision = true;
	//}
	if (m_posEnemy[m_EnemyType].y > 720.0f)
	{
		Decision = true;
	}

	CScene2d::SetPos(m_posEnemy[m_EnemyType]);
	// Decisionがtrueなら消える
	if (Decision == true)
	{
		Uninit();
	}
}

void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

void CEnemy::HitEnemy(int nDamage)
{
	m_nLife -= nDamage;
	CManager *psound = NULL;
	CFade *pFade = CManager::GetFade();
	if (m_nLife ==0)
	{
		if (m_EnemyType == 0)
		{
			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO1);
			//	爆発のクリエイト	(敵の位置で)
			CExplosion::Create(m_posEnemy[m_EnemyType]);
			//	スコアの加算
			CScore::AddScore(50);
			//	終了
			Uninit();
		}
		else if (m_EnemyType == 1)
		{
			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO1);
			//	爆発のクリエイト	(敵の位置で)
			CExplosion::Create(m_posEnemy[m_EnemyType]);
			//	スコアの加算
			CScore::AddScore(50);
			//	終了
			Uninit();
		}
		else if (m_EnemyType == 2)
		{
			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO1);
			//	爆発のクリエイト	(敵の位置で)
			CExplosion::Create(m_posEnemy[m_EnemyType]);
			//	アイテムのクリエイト	(敵の位置で)
			CItem::Create(m_posEnemy[m_EnemyType], CItem::ITEM_RECOVERY_01);
			//	スコアの加算
			CScore::AddScore(50);
			//	終了
			Uninit();
		}
		else if (m_EnemyType == 3)
		{
			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO1);
			//	爆発のクリエイト	(敵の位置で)
			CExplosion::Create(m_posEnemy[m_EnemyType]);
			//	終了
			Uninit();
		}
		else if (m_EnemyType == 4)
		{
			nCountEnemyEnd++;
			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO1);
			//	爆発のクリエイト	(敵の位置で)
			CExplosion::Create(m_posEnemy[m_EnemyType]);
			//
			CScore::AddScore(5000);
			if (nCountEnemyEnd == END_ENEMY)
			{
				pFade->Set(CManager::MODE_RESULT);
			}
			//	終了
			Uninit();
		}
	}
	else if(m_nLife <=100)
	{
		//	爆発のクリエイト	(敵の位置で)
		CExplosion::Create(m_posEnemy[m_EnemyType]);
	}
}

CEnemy *CEnemy::Create(D3DXVECTOR3 posC, ENEMY_TYPE type,int nLife, D3DXVECTOR3 size)
{
	CEnemy *pEnemy;
	pEnemy = new  CEnemy;
	pEnemy->Init(posC,nLife, size);
	pEnemy->m_EnemyType = type;
	pEnemy->BindTexture(m_pTexture[type]);


	return pEnemy;
}