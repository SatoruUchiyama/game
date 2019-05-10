#pragma once

#ifndef _TITLEMAIN_H_
#define _TITLEMAIN_H_

typedef enum
{
	TITLEMAIN_NOMAL,			//
	TITLEMAIN_PIKARI,
	TITLEMAIN_MAX
}TITLEMAIN;

void InitTitleMain(void);
void UninitTitleMain(void);
void UpdateTitleMain(void);
void DrawTitleMain(void);


#endif // !_POLYGON_H_#pragma once
