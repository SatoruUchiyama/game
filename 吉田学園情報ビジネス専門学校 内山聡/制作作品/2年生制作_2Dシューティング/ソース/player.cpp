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
#include "sound.h"
#include "score.h"
#include "explosion.h"
#include "game.h"
#include "fade.h"
//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

LPDIRECT3DTEXTURE9 CPlayer::m_pTexture[MAX_PLAYER] = {};
int CPlayer::m_nCount = 0;
//-----------------------------------------------------------------------------
// デフォルトコンストラクタ
//-----------------------------------------------------------------------------
CPlayer::CPlayer():CScene2d(4)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nCountBullet = 0;
	m_nLife = 0;

	m_size = D3DXVECTOR3(0.0f, 0.0f,0.0f);
}
//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{

}

HRESULT CPlayer::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\01.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\ビー.png", &m_pTexture[1]);
	return S_OK;
}
void CPlayer::Unlood(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
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
//-----------------------------------------------------------------------------
HRESULT CPlayer::Init(D3DXVECTOR3 posPlay)
{
	//CScene2d::SetLength(50.0f, 50.0f);
	m_nLife = 1;
	CScene2d::Init();
	CScene2d::SetPos(posPlay);
	m_nCount = 0;
	//CScene2d::SetSize(D3DXVECTOR3(30.0f, 30.0f, 0.0f));

	SetObjType(CScene::OBJTYPE_PLAYER);
	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CPlayer::Update(void)
{

	CScore *pscore = CGame::GetScore();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CInputJoystick *pJoystick = CManager::GetInputJoystick();
	CManager *psound = NULL;
	m_posPlayer = CScene2d::GetPos();

	if (pJoystick->GetPress(4) == true || pKeyboard->GetTrigger(DIK_C) == true)
	{
		if (m_typeParty == OBJTYPE_PLAYER_NORMAL)
		{
			m_typeParty = OBJTYPE_PLAYER_PARTY;
		}
	}
	else if (pJoystick->GetPress(5) == true || pKeyboard->GetTrigger(DIK_V) == true)
	{
		if (m_typeParty == OBJTYPE_PLAYER_PARTY)
		{
			m_typeParty = OBJTYPE_PLAYER_NORMAL;
		}
	}

	if (m_typeParty == OBJTYPE_PLAYER_NORMAL)
	{
		if (m_type == OBJTYPE_PLAYER_01)
		{
			//ジョイスティック操作
			if (pJoystick->GetJoystick(0) == true)
			{
				//Controllerの左スティック移動
				m_move.x += sinf(pJoystick->GetLeftAxiz()) * MAX_SPEED;
				m_move.y += cosf(pJoystick->GetLeftAxiz()) * MAX_SPEED;
			}
#if 1
			//キーボード操作
			//移動(左)
			if (pKeyboard->GetPress(DIK_A) == true)
			{
				m_move.x -= sinf(D3DX_PI*0.5) * MAX_SPEED;
				m_move.y -= cosf(D3DX_PI*0.5) * MAX_SPEED;
			}
			//移動(右)
			if (pKeyboard->GetPress(DIK_D) == true)
			{
				m_move.x += sinf(D3DX_PI*0.5) * MAX_SPEED;
				m_move.y += cosf(D3DX_PI*0.5) * MAX_SPEED;
			}
			//移動(上)
			if (pKeyboard->GetPress(DIK_W) == true)
			{
				m_move.x += sinf(D3DX_PI) * MAX_SPEED;
				m_move.y += cosf(D3DX_PI) * MAX_SPEED;
			}
			//移動(下)
			if (pKeyboard->GetPress(DIK_S) == true)
			{
				m_move.x -= sinf(D3DX_PI) * MAX_SPEED;
				m_move.y -= cosf(D3DX_PI) * MAX_SPEED;
			}
#endif
			//連射
			if (pJoystick->GetPress(6) == true)
			{
				m_nCountBullet++;
				if (m_nCountBullet == 10)
				{
					CBullet::Create(D3DXVECTOR3(m_posPlayer), CBullet::BULLET_TYPE_PLAYER);
					m_nCountBullet = 0;
					//pscore->AddScore(100);
					psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO2);
				}
			}
		}

		else if (m_type == OBJTYPE_PLAYER_02)
		{
			//ジョイスティック操作
			if (pJoystick->GetJoystick(1) == true)
			{
				//Controllerの左スティック移動
				m_move.x += sinf(pJoystick->GetRightAxiz()) * MAX_SPEED;
				m_move.y += cosf(pJoystick->GetRightAxiz()) * MAX_SPEED;
			}
#if 1
			//キーボード操作
			//移動(左)
			if (pKeyboard->GetPress(0xCB) == true)
			{
				m_move.x -= sinf(D3DX_PI*0.5) * MAX_SPEED;
				m_move.y -= cosf(D3DX_PI*0.5) * MAX_SPEED;
			}
			//移動(右)
			if (pKeyboard->GetPress(0xCD) == true)
			{
				m_move.x += sinf(D3DX_PI*0.5) * MAX_SPEED;
				m_move.y += cosf(D3DX_PI*0.5) * MAX_SPEED;
			}
			//移動(上)
			if (pKeyboard->GetPress(0xC8) == true)
			{
				m_move.x += sinf(D3DX_PI) * MAX_SPEED;
				m_move.y += cosf(D3DX_PI) * MAX_SPEED;
			}
			//移動(下)
			if (pKeyboard->GetPress(0xD0) == true)
			{
				m_move.x -= sinf(D3DX_PI) * MAX_SPEED;
				m_move.y -= cosf(D3DX_PI) * MAX_SPEED;
			}
#endif
			//連射
			if (pJoystick->GetPress(7) == true)
			{
				m_nCountBullet++;
				if (m_nCountBullet == 10)
				{
					CBullet::Create(D3DXVECTOR3(m_posPlayer), CBullet::BULLET_TYPE_PLAYER);
					m_nCountBullet = 0;
					//pscore->AddScore(100);
					psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO2);
				}
			}


		}
	}
	if (m_typeParty == OBJTYPE_PLAYER_PARTY)
	{
		//ジョイスティック操作
		if (pJoystick->GetJoystick(0) == true)
		{
			//Controllerの左スティック移動
			m_move.x += sinf(pJoystick->GetLeftAxiz()) * 2.0f;
			m_move.y += cosf(pJoystick->GetLeftAxiz()) * 2.0f;

			/*m_move.x += sinf(pJoystick->GetRightAxiz()) * MAX_SPEED;
			m_move.y += cosf(pJoystick->GetRightAxiz()) * MAX_SPEED;*/
		}

		//キーボード操作
		if (pKeyboard->GetPress(0xCB) == true)
		{
			m_move.x -= sinf(D3DX_PI*0.5) * MAX_SPEED;
			m_move.y -= cosf(D3DX_PI*0.5) * MAX_SPEED;
		}
		//移動(右)
		if (pKeyboard->GetPress(0xCD) == true)
		{
			m_move.x += sinf(D3DX_PI*0.5) * MAX_SPEED;
			m_move.y += cosf(D3DX_PI*0.5) * MAX_SPEED;
		}
		//移動(上)
		if (pKeyboard->GetPress(0xC8) == true)
		{
			m_move.x += sinf(D3DX_PI) * MAX_SPEED;
			m_move.y += cosf(D3DX_PI) * MAX_SPEED;
		}
		//移動(下)
		if (pKeyboard->GetPress(0xD0) == true)
		{
			m_move.x -= sinf(D3DX_PI) * MAX_SPEED;
			m_move.y -= cosf(D3DX_PI) * MAX_SPEED;
		}


		//連射
		if (pJoystick->GetPress(6) == true || pKeyboard->GetPress(DIK_SPACE) == true)
		{
			m_nCountBullet++;
			if (m_nCountBullet == 10)
			{
				CBullet::Create(D3DXVECTOR3(m_posPlayer.x -10, m_posPlayer.y, m_posPlayer.z), CBullet::BULLET_TYPE_PLAYER);
				CBullet::Create(D3DXVECTOR3(m_posPlayer.x +10, m_posPlayer.y, m_posPlayer.z), CBullet::BULLET_TYPE_PLAYER);
				m_nCountBullet = 0;
				//pscore->AddScore(100);
				psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO2);
			}
		}
		//ジョイスティック操作
	}

#if 0
	
	//移動(左)
	if (pKeyboard->GetPress(DIK_A) == true)
	{
		m_move.x -= sinf(D3DX_PI*0.5) * MAX_SPEED;
		m_move.y -= cosf(D3DX_PI*0.5) * MAX_SPEED;
	}
	//移動(右)
	if (pKeyboard->GetPress(DIK_D) == true)
	{
		m_move.x += sinf(D3DX_PI*0.5) * MAX_SPEED;
		m_move.y += cosf(D3DX_PI*0.5) * MAX_SPEED;
	}
	//移動(上)
	if (pKeyboard->GetPress(DIK_W) == true)
	{
		m_move.x += sinf(D3DX_PI) * MAX_SPEED;
		m_move.y += cosf(D3DX_PI) * MAX_SPEED;
	}
	//移動(下)
	if (pKeyboard->GetPress(DIK_S) == true)
	{
		m_move.x -= sinf(D3DX_PI) * MAX_SPEED;
		m_move.y -= cosf(D3DX_PI) * MAX_SPEED;
	}
	//移動(左)
	if (pJoystick->GetPress(0) == true)
	{
		m_move.x -= sinf(D3DX_PI*0.5) * MAX_SPEED;
		m_move.y -= cosf(D3DX_PI*0.5) * MAX_SPEED;
	}
	//移動(右)
	if (pJoystick->GetPress(2) == true)
	{
		m_move.x += sinf(D3DX_PI*0.5) * MAX_SPEED;
		m_move.y += cosf(D3DX_PI*0.5) * MAX_SPEED;
	}
	//移動(上)
	if (pJoystick->GetPress(3) == true)
	{
		m_move.x += sinf(D3DX_PI) * MAX_SPEED;
		m_move.y += cosf(D3DX_PI) * MAX_SPEED;
	}
	//移動(下)
	if (pJoystick->GetPress(1) == true)
	{
		m_move.x -= sinf(D3DX_PI) * MAX_SPEED;
		m_move.y -= cosf(D3DX_PI) * MAX_SPEED;
	}
#endif
	m_posPlayer += m_move;

	m_move.x += (0.0f - m_move.x)*MAX_INERTIAL;
	m_move.y += (0.0f - m_move.y)*MAX_INERTIAL;

	//あたり判定
	if (SCREEN_WIDTH < m_posPlayer.x)
	{
		m_posPlayer.x = m_posPlayer.x - SCREEN_WIDTH;
	}
	else if (0 > m_posPlayer.x)
	{
		m_posPlayer.x = SCREEN_WIDTH + m_posPlayer.x;
	}

	//あたり判定
	if (SCREEN_HEIGHT - 40 <= m_posPlayer.y)
	{
		m_posPlayer.y = SCREEN_HEIGHT - 40;
	}
	if (40 >= m_posPlayer.y)
	{
		m_posPlayer.y = 40;
	}
	//あたり判定
	//if (SCREEN_WIDTH - 20 < m_posPlayer.x)
	//{
	//	m_posPlayer.x = SCREEN_WIDTH - 20;
	//}
	//else if (20 > m_posPlayer.x)
	//{
	//	m_posPlayer.x = 20;//+ m_posPlayer.x;
	//}

	////あたり判定
	//if (SCREEN_HEIGHT - 20 <= m_posPlayer.y)
	//{
	//	m_posPlayer.y = SCREEN_HEIGHT - 20;
	//}
	//if (20 >= m_posPlayer.y)
	//{
	//	m_posPlayer.y = 20;
	//}
#if 0
	//単発
	if (pKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		CBullet::Create(D3DXVECTOR3(m_posPlayer));
	}
	//単発
	if (pKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		CBullet::Create(D3DXVECTOR3(m_posPlayer));
	}
#endif
	if (m_typeParty == OBJTYPE_PLAYER_NORMAL)
	{
		//連射
		if (pKeyboard->GetPress(DIK_SPACE) == true)
		{
			m_nCountBullet++;
			if (m_nCountBullet == 10)
			{
				CBullet::Create(D3DXVECTOR3(m_posPlayer), CBullet::BULLET_TYPE_PLAYER);
				m_nCountBullet = 0;
				//pscore->AddScore(100);
				psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO2);
			}
		}
	}
	
#if 0
	//連射
	if (pJoystick->GetPress(7) == true)
	{
		m_nCountBullet++;
		if (m_nCountBullet == 5)
		{
			CBullet::Create(D3DXVECTOR3(m_posPlayer), CBullet::BULLET_TYPE_PLAYER);
			m_nCountBullet = 0;
			//pscore->AddScore(100);
			psound->GetCSound()->PlaySound(SOUND_LABEL_SE_SHOT);
		}
	}
#endif
	CScene2d::SetSize(m_size);
	CScene2d::SetPos(m_posPlayer);
}

void CPlayer::Draw(void)
{
	CScene2d::Draw();
}
void CPlayer::HitPlayer(int nDamage)
{
	
	m_nLife -= nDamage;
	CFade *pFade = CManager::GetFade();
	if (m_nLife <= 0)
	{
		m_nCount++;

		//爆発のクリエイト
		CExplosion::Create(m_posPlayer);
		CScore::AddScore(1000);
		if (m_nCount == 2)
		{
			pFade->Set(CManager::MODE_RESULT);
		}
		Uninit();
	}
	else
	{
		CExplosion::Create(m_posPlayer);
	}
}
//	
CPlayer *CPlayer::Create(D3DXVECTOR3 posC, D3DXVECTOR3 size, PLAYER_TYPE type)
{
	CPlayer *pPlayer;
	pPlayer = new  CPlayer;
	pPlayer->Init(posC);
	pPlayer->m_size = size;
	pPlayer->m_type = type;
	pPlayer->BindTexture(m_pTexture[type]);

	return pPlayer;
}