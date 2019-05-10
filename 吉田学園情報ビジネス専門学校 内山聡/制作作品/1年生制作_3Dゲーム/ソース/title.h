#pragma once

#ifndef _TITLE_H_
#define _TITLE_H_

typedef enum
{
	TITLE_NOMAL,			//
	TITLE_PIKARI,
	TITLE_MAX
}TITLE;

void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);


#endif // !_POLYGON_H_