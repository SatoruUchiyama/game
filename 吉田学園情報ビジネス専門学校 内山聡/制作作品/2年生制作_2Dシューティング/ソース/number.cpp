//==========================================================================-==
//
// Player処理 [bg.cpp]
// Author : Satoru Uchiyama
//
//==========================================================================-==
#include "main.h"
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------


LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;
//-----------------------------------------------------------------------------
// デフォルトコンストラクタ
//-----------------------------------------------------------------------------
CNumber::CNumber()
{

}
//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CNumber::~CNumber()
{

}
//Textureの読み込み
HRESULT CNumber::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\number999.png", &m_pTexture);

	return S_OK;
}
//Textureの読み込み
void CNumber::Unlood(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

HRESULT CNumber::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager manager;
	pDevice = manager.GetRenderer()->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 /**(MAX_TRUSS *4)*/, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_2D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

#if 1//Texture無回転
	// 頂点情報を設定
	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - 25.0f, pos.y- 35.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 25.0f, pos.y- 35.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 25.0f, pos.y+ 35.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 25.0f, pos.y+ 35.0f, 0.0f);
	
#endif
	/*pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2, 0.0f);
*/
	// テクスチャの生成
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// 頂点バッファの生成
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	m_pVtxBuff->Unlock();

	return S_OK;
}

void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void CNumber::Update(void)
{
	/*VERTEX_2D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2, 0.0f);

	m_pVtxBuff->Unlock();*/
}

void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager manager;
	pDevice = manager.GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void CNumber::DrawScore(int nKioku)
{
	VERTEX_2D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nKioku % 10)*0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nKioku % 10)*0.1f + 0.1f, 1.0f);
	m_pVtxBuff->Unlock(); 
}