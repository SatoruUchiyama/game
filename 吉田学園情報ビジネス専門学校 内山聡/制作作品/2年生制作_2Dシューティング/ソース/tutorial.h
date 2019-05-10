//=============================================================================
//
// ƒƒCƒ“ˆ— [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//=====================================
//	ƒwƒbƒ_[“Ç‚İ‚İ
//=====================================
#include "main.h"

//=====================================
//	Bg(”wŒi)ƒNƒ‰ƒX
//=====================================
class CTutorial
{
public:
	CTutorial();
	~CTutorial();

	//”wŒi‚ÌƒNƒŠƒGƒCƒg
	static CTutorial*Create(void);

	//	”wŒi‚Ì‰Šú‰»ˆ—
	HRESULT Init(void);
	//	”wŒi‚ÌI—¹ˆ—
	void Uninit(void);
	//	”wŒi‚ÌXVˆ—
	void Update(void);
	//	”wŒi‚Ì•`‰æˆ—
	void Draw(void);
private:
};
#endif