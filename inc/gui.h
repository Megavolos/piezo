#ifndef GUI_H
#define GUI_H


#include "stm32f10x.h"
#include "mainmenu.h"
#include "primitives.h"

void GUI_show(Variables *var);
void GUI_Draw_top_control(void);
void GUI_Draw_right_control(void);

extern Rectangle top_rectangle,right_rectangle,buttons_right_frame,buttons_top_frame;
extern Rectangle  minus_mode,plus_mode,minus_begin,plus_begin, minus_end,plus_end,minus_step,plus_step,minus_qty,plus_qty, minus_right1,plus_right1, minus_right2,plus_right2;
extern Grid grid, grid_top,grid_right;
extern String str_calc, str_menu, str_start, str_stop, str_step,str_right_line1, str_right_line4, str_right_line2, str_right_line3, str_right_line5,str_right_line6;
extern u8 menu;
#endif
