//=============================================================================
//
// メイン処理 [number.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//=====================================
//	ヘッダー読み込み
//=====================================
#include "main.h"
#include "scene.h"

//=====================================
//	マクロ定義
//=====================================
//=====================================
//	前方宣言
//=====================================
class CNumber;

//=====================================
//	Scoreクラス
//=====================================
class CScore :public  CScene
{
public:
	CScore();
	~CScore();

	//スコアの初期化処理
	HRESULT Init(void);
	//スコアの終了処理
	void Uninit(void);
	//スコアの更新処理
	void Update(void);
	//スコアの描画処理
	void Draw(void);
	int GetScore(void);
	//スコアのクリエイト
	static CScore *Create(D3DXVECTOR3 pos);

	static void AddScore(int nValue);

//	void SetScore(int nScore);
	//int GetScore(void);
private:
	//Numberのポインタ
	static CNumber *m_pNumber[8];
	//
	int m_nScore;

	//番号の記憶
	static int m_nKioku;
};
#endif