//=============================================================================
//
// C [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//=====================================
//	wb_[Ηέέ
//=====================================
#include "main.h"


//=====================================
//	Bg(wi)NX
//=====================================
class CResult
{
public:
	CResult();
	~CResult();

	////TextureΜΗέέ
	//static HRESULT Lood(void);
	////TextureΜjό
	//static void Unlood(void);

	//wiΜNGCg
	static CResult*Create(void);

	//	wiΜϊ»
	HRESULT Init(void);
	//	wiΜIΉ
	void Uninit(void);
	//	wiΜXV
	void Update(void);
	//	wiΜ`ζ
	void Draw(void);
private:
};
#endif