#include "mainmenu.h"



u32 touch_time_count=0;
u16 x_prev,y_prev;


void SetupRectangle (Rectangle *menu, u16 _beginX, u16 _endX,u16 _beginY, u16 _endY, char _bordered, u16 _bordercolor, char _borderthickness, char _filled, u16 _fillcolor, u8 _priority)
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

}





void DrawRectangle(Rectangle *rect)
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
	if ((rect->bordered==FALSE)&(rect->filled==FALSE)) {rect->rendered=FALSE; return;} //если нет заливки и нет краев, то нечего рисовать
	if (rect->visible==FALSE) {rect->rendered=FALSE; return;}
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
	rect->rendered=TRUE;
}
