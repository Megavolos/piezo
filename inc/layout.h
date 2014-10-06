#ifndef LAYOUT_H
#define LAYOUT_H



#include "stm32f10x.h"
typedef struct 
{
	u16 beginX;
	u16 endX;
	u16 beginY;
	u16 endY;
	u8	bordered;
	u16 bordercolor;
	u16 borderthickness;
	u8	filled;
	u16 fillcolor;
	u8  visible;
	u8  rendered;
	u8  priority;
	
} Rectangle;

 typedef struct
{
	u16 beginX;
	u16 endX;
	u16 beginY;
	u16 endY;
	u8 	stepX;
	u8	stepY;
	u16	gridcolor;
	u16	backcolor;
	u8  visible;
	u8  rendered;
	u8  priority;	
	
}Grid;


#endif
