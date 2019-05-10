//*****************************************************************************
//
//     スコアの処理[score.cpp]
//     Auther:Hodaka Niwa
//
//*****************************************************************************
#include "score.h"
#include "scene2D.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "textureManager.h"

//*****************************************************************************
//     マクロ定義
//*****************************************************************************
#define SCORE_FRAME_TEXTURE	"data/TEXTURE/GAME/UI/score.png"	// タイマーの枠テクスチャのパス

//=============================================================================
//    コンストラクタ
//=============================================================================
CScore::CScore(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 各種値のクリア
	for (int nCntScore = 0; nCntScore < SCORE_NUMBER_MAX; nCntScore++)
	{// スコアの桁数分繰り返し
		m_apNumber[nCntScore] = NULL;
	}
	m_pTexture = NULL;                          // 数字テクスチャへのポインタ
	m_nScore = 0;                               // スコア
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // スコアの座標
	m_Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);  // スコアの色
	m_fWidth = 0.0f;                            // スコアの数字ポリゴン１個分の高さ
	m_fHeight = 0.0f;                           // スコアの数字ポリゴン１個分の高さ
	m_pTextureManager = NULL;					 // テクスチャ管理クラス
	m_pFrame = NULL;							 // 枠
}

//=============================================================================
//    デストラクタ
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
//    生成処理
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nPriority)
{
	CScore *pScore = NULL;                 // スコアクラス型のポインタ
	int nIdxScene = CScene::GetNumAll();   // シーンクラスの生成した数を取得
	if (nIdxScene < MAX_SCENE)
	{// まだ生成できる
		if (pScore == NULL)
		{// メモリが空になっている
			pScore = new CScore(nPriority);
			if (pScore != NULL)
			{// メモリを確保できた
				// 各種値の設定
				pScore->SetPos(pos);        // スコアの座標
				pScore->SetCol(col);        // スコアの色
				pScore->SetWidth(fWidth);   // スコアの数字ポリゴン１つ分の幅
				pScore->SetHeight(fHeight); // スコアの数字ポリゴン１つ分の高さ

				if (FAILED(pScore->Init()))
				{// 初期化に失敗した
					return NULL;
				}
			}
			else
			{// メモリを確保できなかった
				return NULL;
			}
		}
		else
		{// メモリが空ではない
			return NULL;
		}
	}
	else
	{// これ以上生成できない
		return NULL;
	}

	return pScore;
}

//=============================================================================
//    初期化処理
//=============================================================================
HRESULT CScore::Init(void)
{
	// 各種値の初期化
	D3DXVECTOR3 NumberPos = m_Pos;    // 座標
	D3DXCOLOR NumberCol = m_Col;      // 色
	float fNumberWidth = m_fWidth;    // 幅
	float fNumberHeight = m_fHeight;  // 高さ
	int nNumber = 0;                  // 表示する数字の計算用
	m_nScore = 0;                     // スコア

	if (m_pFrame == NULL)
	{// メモリが確保できる状態である
		m_pFrame = CScene2D::Create(m_Pos - D3DXVECTOR3(m_fWidth + (m_fWidth * 0.5f * SCORE_NUMBER_MAX),0.0f,0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fWidth * SCORE_NUMBER_MAX, m_fHeight * 1.5f, 0.0f, 5);
		if (m_pFrame != NULL)
		{// メモリを確保できた
			LPDIRECT3DTEXTURE9 pTexture = NULL;
			D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), SCORE_FRAME_TEXTURE, &pTexture);
			m_pTextureManager = CTextureManager::Create(1);

			if (m_pTextureManager != NULL)
			{// テクスチャ管理クラスの生成に成功
				m_pTextureManager->BindTexture(pTexture, 0);
				m_pTextureManager->SetFileName(SCORE_FRAME_TEXTURE, 0);
				m_pFrame->BindTexture(m_pTextureManager->GetTexture(0));
				pTexture = NULL;
			}
		}
	}

	for (int nCntScore = 0; nCntScore < SCORE_NUMBER_MAX; nCntScore++)
	{// スコアの桁数分繰り返し
		if (m_apNumber[nCntScore] == NULL)
		{// メモリが確保できる状態にある
		    // 表示する数字の計算
			nNumber = m_nScore % ((int)powf(10.0f, (float)nCntScore) * 10) / (int)powf(10.0f, (float)nCntScore);

			// 数字ポリゴンのインスタンス生成処理
			m_apNumber[nCntScore] = CNumber::Create(NumberPos, NumberCol, fNumberWidth, fNumberHeight, 0.0f, CNumber::STATE_NONE, nNumber, 3, GetPriority());

			// 横に進める
			NumberPos.x -= m_fWidth + (m_fWidth * 0.5f);
		}
	}

	return S_OK;
}

//=============================================================================
//    終了処理
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < SCORE_NUMBER_MAX; nCntScore++)
	{// スコアの桁数分繰り返し
		if (m_apNumber[nCntScore] != NULL)
		{// メモリが確保されている
		    // 数字ポリゴンの終了処理
			m_apNumber[nCntScore]->Uninit();
			m_apNumber[nCntScore] = NULL;
		}
	}

	// テクスチャ管轄クラスを開放する
	if (m_pTextureManager != NULL)
	{
		m_pTextureManager->Uninit();

		// メモリの開放
		delete m_pTextureManager;
		m_pTextureManager = NULL;
	}

	// スコアの消去処理
	Release();
}

//=============================================================================
//    更新処理
//=============================================================================
void CScore::Update(void)
{

}

//=============================================================================
//    描画処理
//=============================================================================
void CScore::Draw(void)
{

}

//=============================================================================
//    スコアのテクスチャを設定する処理
//=============================================================================
void CScore::SetScoreTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;

	if (m_pTexture != NULL)
	{// テクスチャへのポインタが取得できた
		for (int nCntScore = 0; nCntScore < SCORE_NUMBER_MAX; nCntScore++)
		{// スコアの桁数分繰り返し
			if (m_apNumber[nCntScore] != NULL)
			{// メモリが確保されている
				m_apNumber[nCntScore]->BindTexture(pTexture);
			}
		}
	}
}

//=============================================================================
//    スコアの加算
//=============================================================================
void CScore::AddScore(int nScore)
{
	int nSetNumber;   // 表示する数字

	// スコアの加算
	m_nScore += nScore;

	// テクスチャ座標の切り替え処理
	for (int nCntScore = 0; nCntScore < SCORE_NUMBER_MAX; nCntScore++)
	{// スコアの桁数分繰り返し
	    // 表示する数字の計算
		nSetNumber = m_nScore % ((int)powf(10.0f, (float)nCntScore) * 10) / (int)powf(10.0f, (float)nCntScore);

		// 数字ポリゴンの数字設定処理
		m_apNumber[nCntScore]->SetNumber(nSetNumber);
	}
}

//=============================================================================
//    スコアの座標の設定
//=============================================================================
void CScore::SetPos(const D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//=============================================================================
//    スコアの取得
//=============================================================================
void CScore::SetCol(const D3DXCOLOR col)
{
	m_Col = col;
}

//=============================================================================
//    スコアの数字ポリゴン１つ分の幅の設定
//=============================================================================
void CScore::SetWidth(const float fWidth)
{
	m_fWidth = fWidth;
}

//=============================================================================
//    スコアの数字ポリゴン１つ分の高さの設定
//=============================================================================
void CScore::SetHeight(const float fHeight)
{
	m_fHeight = fHeight;
}

//=============================================================================
//    スコアの取得
//=============================================================================
void CScore::SetScore(const int nScore)
{
	m_nScore = nScore;

	// テクスチャ座標の切り替え処理
	int nSetNumber = 0; // 表示する数字の計算用
	for (int nCntScore = 0; nCntScore < SCORE_NUMBER_MAX; nCntScore++)
	{// スコアの桁数分繰り返し
	    // 表示する数字の計算
		nSetNumber = m_nScore % ((int)powf(10.0f, (float)nCntScore) * 10) / (int)powf(10.0f, (float)nCntScore);

		// 数字ポリゴンの数字設定処理
		m_apNumber[nCntScore]->SetNumber(nSetNumber);
	}
}

//=============================================================================
//    スコアの座標の取得
//=============================================================================
D3DXVECTOR3 CScore::GetPos(void)
{
	return m_Pos;
}

//=============================================================================
//    スコアの色の取得
//=============================================================================
D3DXCOLOR CScore::GetCol(void)
{
	return m_Col;
}

//=============================================================================
//    スコアの数字ポリゴン１つ分の幅の取得
//=============================================================================
float CScore::GetWidth(void)
{
	return m_fWidth;
}

//=============================================================================
//    スコアの数字ポリゴン１つ分の高さの取得
//=============================================================================
float CScore::GetHeight(void)
{
	return m_fHeight;
}

//=============================================================================
//    スコアの取得
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}