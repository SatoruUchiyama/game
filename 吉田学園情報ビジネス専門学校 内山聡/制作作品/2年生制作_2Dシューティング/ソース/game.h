//=============================================================================
//
// C [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=====================================
//	wb_[Ηέέ
//=====================================
#include "main.h"

class CScore;
//=====================================
//	GAME(wi)NX
//=====================================
class CGame
{
public:
	CGame();
	~CGame();

	////TextureΜΗέέ
	//static HRESULT Lood(void);
	////TextureΜjό
	//static void Unlood(void);

	//wiΜNGCg
	static CGame*Create(void);
	//static CPlayer*GetPlayer(int nIdx);
	//	wiΜϊ»
	HRESULT Init(void);
	//	wiΜIΉ
	void Uninit(void);
	//	wiΜXV
	void Update(void);
	//	wiΜ`ζ
	void Draw(void);

	static CScore *GetScore(void) { return m_score; };
private:
	//static CPlayer *m_pPlayer[2];
	static CScore *m_score;
};
#endif