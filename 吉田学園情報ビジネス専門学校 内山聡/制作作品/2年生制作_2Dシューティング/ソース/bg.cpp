//==========================================================================-==
//
// 背景処理 [bg.cpp]
// Author : Satoru Uchiyama
//
//==========================================================================-==

//=============================================================================
//	ヘッダー読み込み
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bg.h"
#include "scene2d.h"


LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_BG_TEXTURE] = {};

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CBg::CBg() :CScene(0)
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
//	テクスチャのロード
//=============================================================================
HRESULT CBg::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_0.jpg", &m_pTexture[0]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_kumo_kage.png", &m_pTexture[1]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\styBG_kumo_kage_01.png", &m_pTexture[2]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\bg5.png", &m_pTexture[3]);

	return S_OK;
}
//=============================================================================
//	テクスチャの廃棄
//=============================================================================
void CBg::Unlood(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBg::Init(void)
{
	SetObjType(CScene::OBJTYPE_BG);		//タイプの仕分け

	//	座標の設定
	m_pScene2d[0]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pScene2d[1]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pScene2d[2]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pScene2d[3]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	
	//	サイズの設定
	m_pScene2d[0]->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pScene2d[1]->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pScene2d[2]->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pScene2d[3]->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	m_texBase[0] = 0.0f;
	m_texBase[1] = 0.0f;
	m_texBase[2] = 0.0f;
	m_texBase[3] = 0.0f;
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		if (m_pScene2d[nCount] != NULL)
		{
			m_pScene2d[nCount]->Uninit();
			m_pScene2d[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBg::Update(void)
{
	D3DXVECTOR2 BgTexPos[4*MAX_BG_TEXTURE];		//	テクスチャの頂点情報

	int nCount2 = 0;							//	背景の枚数分のカウント

	//	背景の移動スピード
	m_texBase[0] -= SPEED_BG_00;
	m_texBase[1] -= SPEED_BG_01;
	m_texBase[2] -= SPEED_BG_02;
	m_texBase[3] -= SPEED_BG_03;

	//	背景の座標更新
	for (nCount2 = 0; nCount2 < MAX_BG_TEXTURE; nCount2++)
	{
		BgTexPos[nCount2 + 0] = D3DXVECTOR2(0.0f, m_texBase[nCount2]);
		BgTexPos[nCount2 + 1] = D3DXVECTOR2(1.0f, m_texBase[nCount2]);
		BgTexPos[nCount2 + 2] = D3DXVECTOR2(0.0f, m_texBase[nCount2] + 1.0f);
		BgTexPos[nCount2 + 3] = D3DXVECTOR2(1.0f, m_texBase[nCount2] + 1.0f);

		m_pScene2d[nCount2]->SetBgTexPos(&BgTexPos[0]);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBg::Draw(void)
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CBg *CBg::Create(void)
{
	CBg *pBg;
	pBg = new  CBg;
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		pBg->m_pScene2d[nCount] = new CScene2d(0);
		pBg->m_pScene2d[nCount]->Init();
		pBg->m_pScene2d[nCount]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		pBg->m_pScene2d[nCount]->SetSize(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		pBg->m_pScene2d[nCount]->BindTexture(m_pTexture[nCount]);
	}
	pBg->Init();

	return pBg;
}