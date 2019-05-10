//=============================================================================
//
// ƒƒCƒ“ˆ— [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=====================================
//	ƒwƒbƒ_[“Ç‚İ‚İ
//=====================================
#include "main.h"

class CScore;
//=====================================
//	GAME(”wŒi)ƒNƒ‰ƒX
//=====================================
class CGame
{
public:
	CGame();
	~CGame();

	////Texture‚Ì“Ç‚İ‚İ
	//static HRESULT Lood(void);
	////Texture‚Ì”jŠü
	//static void Unlood(void);

	//”wŒi‚ÌƒNƒŠƒGƒCƒg
	static CGame*Create(void);
	//static CPlayer*GetPlayer(int nIdx);
	//	”wŒi‚Ì‰Šú‰»ˆ—
	HRESULT Init(void);
	//	”wŒi‚ÌI—¹ˆ—
	void Uninit(void);
	//	”wŒi‚ÌXVˆ—
	void Update(void);
	//	”wŒi‚Ì•`‰æˆ—
	void Draw(void);

	static CScore *GetScore(void) { return m_score; };
private:
	//static CPlayer *m_pPlayer[2];
	static CScore *m_score;
};
#endif