//=============================================================================
//
// ƒƒCƒ“ˆ— [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//=====================================
//	ƒwƒbƒ_[“Ç‚İ‚İ
//=====================================
#include "main.h"


//=====================================
//	Bg(”wŒi)ƒNƒ‰ƒX
//=====================================
class CResult
{
public:
	CResult();
	~CResult();

	////Texture‚Ì“Ç‚İ‚İ
	//static HRESULT Lood(void);
	////Texture‚Ì”jŠü
	//static void Unlood(void);

	//”wŒi‚ÌƒNƒŠƒGƒCƒg
	static CResult*Create(void);

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