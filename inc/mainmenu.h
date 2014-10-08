#ifndef MAINMENU_H
#define MAINMENU_H


#include "stm32f10x.h"
#include "font.h"
#include "primitives.h"
#include "touch.h"
#include "math_func.h"
#include "stdio.h"
#include "layout.h"
#define FILLED 1
#define NOT_FILLED 0
#define BORDERED 1
#define NOT_BORDERED 0
#define VISIBLE 1
#define INVISIBLE 0


//menu_rect_init(...) инициализирует основной прямоугольник меню
void SetupRectangle (Rectangle *menu, u16 _beginX, u16 _endX,u16 _beginY, u16 _endY, char _bordered, u16 _bordercolor, char _borderthickness, char _filled, u16 _fillcolor, u8 _priority);
void SetupGrid (Grid *grid, u16 _beginX, u16 _endX,u16 _beginY, u16 _endY, u16 _stepX, u16 _stepY, u16 gridcolor,  u16 backcolor, u8 _priority);
void DrawRectangle(Rectangle *rect);
void SetupString(String *str,u16 _beginX,u16	_beginY,char _label[10], u16 _fontcolor,u16 _backcolor);


#endif
