#include "mainmenu.h"



u32 touch_time_count=0;
u16 x_prev,y_prev;


void SetupRectangle (Rectangle *rect, u16 _beginX, u16 _endX,u16 _beginY, u16 _endY, char _bordered, u16 _bordercolor, char _borderthickness, char _filled, u16 _fillcolor, u8 _priority)
{
	rect->beginX=_beginX;
	rect->endX=_endX;
	rect->beginY=_beginY;
	rect->endY=_endY;
	rect->bordered=_bordered;
	rect->bordercolor=_bordercolor;
	rect->borderthickness=_borderthickness;
	rect->filled=_filled;
	rect->fillcolor=_fillcolor;
	rect->visible=TRUE;
	rect->rendered=FALSE;
	rect->priority=_priority;

}


void SetupGrid (Grid *grid, u16 _beginX, u16 _endX,u16 _beginY, u16 _endY, u16 _stepX, u16 _stepY, u16 gridcolor,  u16 backcolor, u8 _priority)
{
	grid->beginX=_beginX;
	grid->endX=_endX;
	grid->beginY=_beginY;
	grid->endY=_endY;
	grid->stepX=_stepX;
	grid->stepY=_stepY;
	grid->gridcolor=gridcolor;
	grid->backcolor=backcolor;
	grid->visible=TRUE;
	grid->rendered=FALSE;
	grid->priority=_priority;

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

void SetupString(String *str,u16 _beginX,u16	_beginY,char _label[10], u16 _fontcolor,u16 _backcolor)
{
	str->label[0]=_label[0];
	str->label[1]=_label[1];
	str->label[2]=_label[2];
	str->label[3]=_label[3];
	str->label[4]=_label[4];
	str->label[5]=_label[5];
	str->label[6]=_label[6];
	str->label[7]=_label[7];
	str->label[8]=_label[8];
	str->label[9]=_label[9];
	str->beginX=_beginX;
	str->beginY=_beginY;
	str->fontcolor=_fontcolor;
	str->backcolor=_backcolor;
	str->visible=VISIBLE;
	str->rendered=FALSE;

}
