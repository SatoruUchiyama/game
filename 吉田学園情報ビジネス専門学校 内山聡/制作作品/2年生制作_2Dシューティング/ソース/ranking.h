
//*****************************************************************************
//
//	背景の処理（bg,h）
//	Author : uchiyama
//
//*****************************************************************************
#ifndef _RANKING_H_
#define _RANKING_H_

#include "scene.h"
#define MAX_RANKING   (6)
#define MAX_NUMBER    (6)
class CNumber;
//クラス（シーンの派生クラス）
class CRanking
{
public:
	CRanking();											//コンストラクタ
	~CRanking();										//デストラクタ

	HRESULT Init(void);									//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理

														//静的メンバ関数
	static CRanking *Create(void);
	static void SaveRanking(void);
	static void LoadRanking(void);

private:
	static CNumber *m_apNumber[MAX_RANKING][MAX_NUMBER]; //スコアを何個表示するか：桁を何個にするか

	D3DXVECTOR3				m_move;						// ポリゴンの位置
	D3DXCOLOR				m_col;						// ポリゴンの位置
	static int m_RankScore[MAX_RANKING];
	int m_nTimeRanking;
	static int m_nType;
};
#endif