//=============================================================================
//
// ƒƒCƒ“ˆ— [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//=====================================
//	ƒwƒbƒ_[“Ç‚İ‚İ
//=====================================
#include "main.h"


//=====================================
//	Bg(”wŒi)ƒNƒ‰ƒX
//=====================================
class CTitle
{
public:
	CTitle();
	~CTitle();

	////Texture‚Ì“Ç‚İ‚İ
	//static HRESULT Lood(void);
	////Texture‚Ì”jŠü
	//static void Unlood(void);

	//”wŒi‚ÌƒNƒŠƒGƒCƒg
	static CTitle*Create(void);

	//	”wŒi‚Ì‰Šú‰»ˆ—
	HRESULT Init(void);
	//	”wŒi‚ÌI—¹ˆ—
	void Uninit(void);
	//	”wŒi‚ÌXVˆ—
	void Update(void);
	//	”wŒi‚Ì•`‰æˆ—
	void Draw(void);
private:
	int m_nTimeTitle;
};
#endif