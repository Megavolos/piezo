#ifndef LAYOUT_H
#define LAYOUT_H

#define Window1_label "Scope"
#define Window1_menu1_label "File"
//#define Window1_menu2_label "Edit"
#define Window1_menu1_line1_label "Open"

#include "stm32f10x.h"
typedef struct _Window1_with_menu
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
	char	window_label[20];
	char	menu1_label[10];
	#ifdef Window1_menu2 
	char	menu2_label[10];
	#endif
	#ifdef Window1_menu3 
	char	menu3_label[10];
	#endif
	#ifdef Window1_menu4 
	char	menu4_label[10];
	#endif
	#ifdef Window1_menu5 
	char	menu5_label[10];
	#endif	

} TWindow_with_menu;

typedef struct _Drop_down_menu1
{
	char line1_label[10];
	#ifdef Window1_menu1_line2_label
		char line2_label[10];
	#endif
	#ifdef Window1_menu1_line3_label
		char line3_label[10];
	#endif
	#ifdef Window1_menu1_line4_label
		char line4_label[10];
	#endif
	#ifdef Window1_menu1_line5_label
		char line5_label[10];
	#endif
	#ifdef Window1_menu1_line6_label
		char line6_label[10];
	#endif
	#ifdef Window1_menu1_line7_label
		char line7_label[10];
	#endif
	#ifdef Window1_menu1_line8_label
		char line8_label[10];
	#endif
	#ifdef Window1_menu1_line9_label
		char line9_label[10];
	#endif	
} TWindow1_menu1;

#ifdef Window1_menu2_label
typedef struct _Drop_down_menu2
{
	char line1_label[10];
	#ifdef Window1_menu1_line2_label
		char line2_label[10];
	#endif
	#ifdef Window1_menu1_line3_label
		char line3_label[10];
	#endif
	#ifdef Window1_menu1_line4_label
		char line4_label[10];
	#endif
	#ifdef Window1_menu1_line5_label
		char line5_label[10];
	#endif
	#ifdef Window1_menu1_line6_label
		char line6_label[10];
	#endif
	#ifdef Window1_menu1_line7_label
		char line7_label[10];
	#endif
	#ifdef Window1_menu1_line8_label
		char line8_label[10];
	#endif
	#ifdef Window1_menu1_line9_label
		char line9_label[10];
	#endif	
} TWindow1_menu2;
#endif

#endif
