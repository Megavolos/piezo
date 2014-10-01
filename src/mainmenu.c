#include "mainmenu.h"



u32 touch_time_count=0;
u16 x_prev,y_prev;


void menu_rect_init (TWindow_with_menu *menu, u16 _beginX, u16 _endX,u16 _beginY, u16 _endY, char _bordered, char _bordercolor, char _borderthickness, char _filled, char _fillcolor, u8 _priority)
{
	menu->beginX=_beginX;
	menu->endX=_endX;
	menu->beginY=_beginY;
	menu->endY=_endY;
	menu->bordered=_bordered;
	menu->bordercolor=_bordercolor;
	menu->borderthickness=_borderthickness;
	menu->filled=_filled;
	menu->fillcolor=_fillcolor;
	menu->visible=FALSE;
	menu->rendered=FALSE;
	menu->priority=_priority;
	sprintf(menu->window_label,Window1_label);
	sprintf(menu->menu1_label,Window1_menu1_label);
}


void drop_down_menu_init (TWindow1_menu1 *menu)
{
	sprintf(menu->line1_label,Window1_menu1_line1_label);
}

void draganddrop (TWindow_with_menu *menu)
{
	char dx=0,dy=0;
	
  if ((d_in_x>=menu->beginX)&&(d_in_x<=menu->endX)&&(d_in_y>=menu->beginY)&&(d_in_y<=menu->endY)&&(DRAG_DELAY==(touch_time_count++)))
	{
		touch_time_count=0;
		dx=d_in_x-x_prev; 
		dy=d_in_y-y_prev;
		x_prev=d_in_x;
		y_prev=d_in_y;
	}
	menu->beginX+=dx;
	menu->endX+=dx;
	menu->beginY+=dy;
	menu->endY+=dy;
	DrawWindowWithMenu(menu);
}

void DrawWindowWithMenu(TWindow_with_menu *rect)
{
	u16 temp,i;
	//******************************//
	//Рисовать будем слева направо. //
	//Проверяем слеванаправость :)  //
	//******************************//	
	if (rect->endX < rect->beginX)
	{
		temp=rect->endX;
		rect->endX=rect->beginX;
		rect->beginX=temp;
	}
	if (rect->endY < rect->beginY)
	{
		temp=rect->endY;
		rect->endY=rect->beginY;
		rect->beginY=temp;
	}
	if ((rect->bordered==FALSE)&(rect->filled==FALSE)) return; //если нет заливки и нет краев, то нечего рисовать
	if (rect->visible==FALSE) return;
	//************************Если просто края без заливки*****************************
	if ((rect->bordered==TRUE)&(rect->filled==FALSE))          
	{
		for (i=0;i<rect->borderthickness;i++)
		{
			DrawLine(rect->beginX,rect->endX,rect->beginY+i,rect->beginY+i,rect->bordercolor); //рисуем левую грань
			DrawLine(rect->beginX,rect->endX,rect->endY-i,rect->endY-i,rect->bordercolor);     //рисуем правую грань
			DrawLine(rect->beginX+i,rect->beginX+i,rect->beginY,rect->endY,rect->bordercolor);
			DrawLine(rect->endX-i,rect->endX-i,rect->beginY,rect->endY+1,rect->bordercolor);
		}
	}
	//*********************************************************************************

  //************************Если просто заливка без краев****************************	
	if ((rect->bordered==FALSE)&(rect->filled==TRUE))
	{
		for (i=rect->beginY;i<rect->endY;i++)
		{
			for (temp=rect->beginX;temp<rect->endX;temp++)
			{
				plotpx(temp,i,rect->fillcolor);
			}
		}
	}
	//*********************************************************************************
	
	//****************************Если заливка с краями********************************
	if ((rect->bordered==TRUE)&(rect->filled==TRUE))
	{
		for (i=0;i<rect->borderthickness;i++)
		{
			DrawLine(rect->beginX,rect->endX,rect->beginY+i,rect->beginY+i,rect->bordercolor); //рисуем верхнюю грань
			DrawLine(rect->beginX,rect->endX,rect->endY-i,rect->endY-i,rect->bordercolor);     //рисуем нижнюю грань
			DrawLine(rect->beginX+i,rect->beginX+i,rect->beginY,rect->endY,rect->bordercolor); //рисуем левую
			DrawLine(rect->endX-i,rect->endX-i,rect->beginY,rect->endY+1,rect->bordercolor);     //правую
		}
		for (i=rect->beginY+rect->borderthickness;i<=rect->endY-rect->borderthickness;i++)
		{
			for (temp=rect->beginX+rect->borderthickness;temp<=rect->endX-+rect->borderthickness;temp++)
			{
				plotpx(temp,i,rect->fillcolor);
			}
		}		
	}	
	//*********************************************************************************
	
}
