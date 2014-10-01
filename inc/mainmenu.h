#ifndef MAINMENU_H
#define MAINMENU_H

#define DRAG_DELAY 30000

#include "stm32f10x.h"
#include "font.h"
#include "primitives.h"
#include "touch.h"
#include "math_func.h"
#include "stdio.h"
#include "layout.h"

void drop_down_menu_init (TWindow1_menu1 *menu);

//menu_rect_init(...) инициализирует основной прямоугольник меню
void menu_rect_init(TWindow_with_menu *menu, u16 _beginX, u16 _endX,u16 _beginY, u16 _endY, char _bordered, char _bordercolor, char _borderthickness, char _filled, char _fillcolor, u8 _priority);
void draganddrop (TWindow_with_menu *menu);
void DrawWindowWithMenu(TWindow_with_menu *rect);
extern TWindow_with_menu Window1;
extern TWindow1_menu1 window1_menu1;



#endif
