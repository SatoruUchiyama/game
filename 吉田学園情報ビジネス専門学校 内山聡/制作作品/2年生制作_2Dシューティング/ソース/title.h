//=============================================================================
//
// C [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//=====================================
//	wb_[Ηέέ
//=====================================
#include "main.h"


//=====================================
//	Bg(wi)NX
//=====================================
class CTitle
{
public:
	CTitle();
	~CTitle();

	////TextureΜΗέέ
	//static HRESULT Lood(void);
	////TextureΜjό
	//static void Unlood(void);

	//wiΜNGCg
	static CTitle*Create(void);

	//	wiΜϊ»
	HRESULT Init(void);
	//	wiΜIΉ
	void Uninit(void);
	//	wiΜXV
	void Update(void);
	//	wiΜ`ζ
	void Draw(void);
private:
	int m_nTimeTitle;
};
#endif