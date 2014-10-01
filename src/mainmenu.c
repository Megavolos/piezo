#include "mainmenu.h"


u32 touch_time_count=0;
u16 x_prev,y_prev;
void draganddrop ()
{
	char dx=0,dy=0;
	
  if ((d_in_x>=TopMenu.beginX)&&(d_in_x<=TopMenu.endX)&&(d_in_y>=TopMenu.beginY)&&(d_in_y<=TopMenu.endY)&&(DRAG_DELAY==(touch_time_count++)))
	{
		touch_time_count=0;
		dx=d_in_x-x_prev; 
		dy=d_in_y-y_prev;
		x_prev=d_in_x;
		y_prev=d_in_y;
	}
	TopMenu.beginX+=dx;
	TopMenu.endX+=dx;
	TopMenu.beginY+=dy;
	TopMenu.endY+=dy;
	DrawRectangle(&TopMenu);
}
