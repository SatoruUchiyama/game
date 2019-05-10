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
#include "logo.h"
#include "explosion.h"
#include "score.h"
//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

LPDIRECT3DTEXTURE9 CLogo::m_pTexture[MAX_LOGO] = {};

//-----------------------------------------------------------------------------
// デフォルトコンストラクタ
//-----------------------------------------------------------------------------
CLogo::CLogo() :CScene2d(4)
{

}
//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CLogo::~CLogo()
{

}

HRESULT CLogo::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\titl.png", &m_pTexture[0]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\ランキングロゴ.png", &m_pTexture[1]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\チュートリアル2.png", &m_pTexture[2]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\プレゼンテーション1.png", &m_pTexture[3]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\start.png", &m_pTexture[4]);

	return S_OK;
}
//
void CLogo::Unlood(void)
{
	for (int nCount = 0; nCount < MAX_LOGO; nCount++)
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
HRESULT CLogo::Init(D3DXVECTOR3 posPlay, D3DXVECTOR3 size)
{
	//CScene2d::SetLength(50.0f, 50.0f);
	m_nLife = 3;
	CScene2d::Init();
	CScene2d::SetPos(D3DXVECTOR3(posPlay));
	CScene2d::SetSize(size);
	//SetObjType(CScene::OBJTYPE_ENEMY);//タイプの仕分け
	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CLogo::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CLogo::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();
	m_pos = GetPos();

	switch (m_type)
	{
	case LOGO_TYPE_00:
		m_move[m_type].x -= sinf(D3DX_PI*0.5) * 13.0f;
		m_move[m_type].y -= cosf(D3DX_PI*0.5) * 13.0f;

		m_move[m_type].x += (0.0f - m_move[m_type].x)*MAX_INERTIAL_ENEMY;
		m_move[m_type].y += (0.0f - m_move[m_type].y)*MAX_INERTIAL_ENEMY;

		m_pos += m_move[m_type];
	default:
		break;
	}
	
	if (-600 > m_pos.x)
	{
		//m_pos.x = SCREEN_WIDTH + m_pos.x;
		m_pos.x = SCREEN_WIDTH+1500 + m_pos.x;
	}

	CScene2d::SetPos(m_pos);
}

void CLogo::Draw(void)
{
	CScene2d::Draw();
}

CLogo *CLogo::Create(D3DXVECTOR3 posC,LOGO_TYPE type, D3DXVECTOR3 size)
{
	CLogo *pLogo;
	pLogo = new  CLogo;
	pLogo->Init(posC, size);
	pLogo->m_type = type;

	pLogo->BindTexture(m_pTexture[type]);

	return pLogo;
}