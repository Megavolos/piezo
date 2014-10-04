#include "gui.h"

Rectangle top,red,green;

void GUI_show()
{
	char i;
	clr(0,320,0,240,WHITE);
	SetupRectangle(&top,0,319,0 ,26,BORDERED,BLACK,1,FILLED,LIGHTGRAY1,1);
	top.visible=VISIBLE;
	DrawRectangle(&top);
	SetupRectangle(&green,0, 22,26,46,NOT_BORDERED,BLACK,1,FILLED,GREEN,1);
	SetupRectangle(&red,22,45,26,46,NOT_BORDERED,BLACK,1,FILLED,RED,1);
	red.visible=VISIBLE;
	green.visible=VISIBLE;
	//DrawRectangle(&green);
	//DrawRectangle(&red);	
	for (i=0;i<4;i++)
	{
		green.beginX=red.endX;
		green.endX=green.beginX+25;
		red.beginX=green.endX;
		red.endX=red.beginX+24;
		DrawRectangle(&green);
		DrawLine(green.beginX,green.beginX,0,46,BLACK);
		DrawRectangle(&red);
		TFT_ShowChar(green.beginX+9,green.beginY+4,'-',BLACK,GREEN);
		TFT_ShowChar(red.beginX+9,red.beginY+4,'+',BLACK,RED);
	}
	SetupRectangle(&top,45,red.endX,26 ,46,BORDERED,BLACK,1,NOT_FILLED,LIGHTGRAY1,1);
	top.visible=VISIBLE;
	DrawRectangle(&top);
	DrawLine(red.endX,red.endX,0,46,BLACK);
  TFT_ShowString(2,2,"Mode:",BLACK,LIGHTGRAY1);
	//TFT_ShowString(2,7,"Linear",BLACK,LIGHTGRAY1);
	TFT_ShowString(2,13,"Eq.time",BLACK,LIGHTGRAY1);
	DrawLine(45,45,0,26,BLACK);
	TFT_ShowString(47,2, "  Begin",BLACK,LIGHTGRAY1);
	TFT_ShowString(60,13,"1000",BLACK,LIGHTGRAY1);
	TFT_ShowString(107,2,"End",BLACK,LIGHTGRAY1);
	TFT_ShowString(107,13,"1200",BLACK,LIGHTGRAY1);
	TFT_ShowString(157,2,"Step",BLACK,LIGHTGRAY1);
	TFT_ShowString(157,13,"1200",BLACK,LIGHTGRAY1);
	TFT_ShowString(210,2,"qty.",BLACK,LIGHTGRAY1);
	TFT_ShowString(210,13,"10",BLACK,LIGHTGRAY1);

}
