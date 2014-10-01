#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "stm32f10x.h"
#include "font.h"
#include "lcdcmd.h"


//цвета в формате 16bpp (RGB565 aka R5G6B5 aka 5R6G5B)

#define RED	  0XF800
#define GREEN 0X07E0
#define BLUE  0X001F  
#define BRED  0XF81F
#define GRED  0XFFE0
#define GBLUE 0X07FF
#define BLACK 0  
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ROYALBLUE 0x435C
#define GREED_BEGINX 0
#define GREED_BEGINY 49

extern u16 POINT_COLOR;
extern u16 GREED_COLOR;
extern u16 GREED_BACKGROUND;
extern u16 GREED_STEP;
typedef struct _Rectangle
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

} Rectangle;

void plotpx(unsigned int X, unsigned int Y, unsigned int color); 
void DrawGrid (u16 beginx, u16 beginy,u16 step, u16 Color, u16 BgrColor);
void TFT_ShowString(u16 x,u16 y,const u8 *p, u16 color);
void TFT_ShowChar(u16 x,u16 y,u8 num, u16 color);
void clr(int x1, int x2, int y1, int y2, unsigned int color );
void DrawLine(int x1, int x2, int y1, int y2, unsigned int color);
void DrawCross(u16 X, u16 Y, u16 L,unsigned int color);
void DrawRectangle(Rectangle *rect);
	






#endif
