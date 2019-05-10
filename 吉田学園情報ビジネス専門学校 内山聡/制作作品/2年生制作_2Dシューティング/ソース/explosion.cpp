//==========================================================================-==
//
// Player処理 [player.cpp]
// Author : satoru uchiyama
//
//==========================================================================-==
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// グローバル変数:
//-----------------------------------------------------------------------------


LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;


HRESULT CExplosion::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\explosion000.png", &m_pTexture);

	return S_OK;
}
void CExplosion::Unlood(void)
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
CExplosion::CExplosion():CScene2d(6)
{

}
//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CExplosion::~CExplosion()
{

}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT CExplosion::Init(D3DXVECTOR3 posExplosion)
{
	//CScene2d::SetLength(30.0f, 30.0f);
	CScene2d::Init();
	CScene2d::SetPos(posExplosion);
	CScene2d::SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	SetObjType(CScene::OBJTYPE_EXPLOSION);//タイプの仕分け
	SetExplosion(0);
	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CExplosion::Update(void)
{
	m_nCounterAnimation++;
	if ((m_nCounterAnimation % 5) == 0)
	{
		m_nPatternAnimation = (m_nPatternAnimation + 1) % 8;
		SetExplosion(m_nPatternAnimation);
		if (m_nPatternAnimation >= 8 - 1)
		{
			Uninit();
		}
	}
}

void CExplosion::Draw(void)
{
	CScene2d::Draw();
}

CExplosion *CExplosion::Create(D3DXVECTOR3 posExplosion)
{
	CExplosion *pExplosion;
	pExplosion = new  CExplosion;
	pExplosion->Init(posExplosion);

	pExplosion->BindTexture(m_pTexture);

	return pExplosion;
}
