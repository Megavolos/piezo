#include "gui.h"
Rectangle top_rectangle,right_rectangle,buttons_right_frame,buttons_top_frame,red,green;
Grid grid;

void GUI_show()
{
	
	clr(0,320,0,240,WHITE);
	SetupRectangle(&top_rectangle,0,319,0 ,26,BORDERED,BLACK,1,FILLED,LIGHTGRAY1,1);
	DrawRectangle(&top_rectangle);
	SetupRectangle(&right_rectangle,283,319,26 ,239,BORDERED,BLACK,1,FILLED,LIGHTGRAY1,1);
	DrawRectangle(&right_rectangle);

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
	DrawLine(241,241,0,26,BLACK);
	TFT_ShowString(244,2,"RPMmc2",BLACK,LIGHTGRAY1);
	TFT_ShowString(244,13,"1200",RED,LIGHTGRAY1);
	TFT_ShowString(285,2,"Freq",BLACK,LIGHTGRAY1);
	TFT_ShowString(285,13,"10",RED,LIGHTGRAY1);

	TFT_ShowString(285,30,"t/div",BLACK,LIGHTGRAY1);
	TFT_ShowString(285,40,"100",BLACK,LIGHTGRAY1);
	TFT_ShowString(285,50,"ms",BLACK,LIGHTGRAY1);
	TFT_ShowString(285,70,"v/div",BLACK,LIGHTGRAY1);
	TFT_ShowString(285,80,"100",BLACK,LIGHTGRAY1);
	TFT_ShowString(285,90,"mv",BLACK,LIGHTGRAY1);
	TFT_ShowString(286,125,"Menu ",YELLOW,BLACK);
	TFT_ShowString(286,150,"Calc ",GOLD,BLACK);
	TFT_ShowString(286,175,"START",BLACK,GREEN);
	TFT_ShowString(290,200,"STEP",BLACK,GOLD);
	TFT_ShowString(290,225,"STOP",BLACK,RED);
	SetupGrid(&grid,0,283,26,239,10,10,BLUE,BLACK,1);
	DrawGrid(&grid);
//	GUI_Draw_right_control();
//	GUI_Draw_top_control();
}

void GUI_Draw_top_control()
{
	char i;
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
	SetupRectangle(&buttons_top_frame,45,red.endX,26 ,46,BORDERED,BLACK,1,NOT_FILLED,LIGHTGRAY1,1);
	buttons_top_frame.visible=VISIBLE;
	DrawRectangle(&buttons_top_frame);
	//DrawLine(red.endX,red.endX,0,46,BLACK);
}

void GUI_Draw_right_control()
{
	
	SetupRectangle(&red,261,283,26,46,NOT_BORDERED,BLACK,1,FILLED,RED,1);
	SetupRectangle(&green,261, 283,46,66,NOT_BORDERED,BLACK,1,FILLED,GREEN,1);
	DrawRectangle(&green);
	DrawRectangle(&red);	
	SetupRectangle(&buttons_right_frame,261,283,red.beginY,green.endY,BORDERED,BLACK,1,NOT_FILLED,GREEN,1);
	DrawRectangle(&buttons_right_frame);
	TFT_ShowChar(green.beginX+8,green.beginY+4,'-',BLACK,GREEN);
	TFT_ShowChar(red.beginX+8,red.beginY+4,'+',BLACK,RED);
	
	SetupRectangle(&red,261,283,66,86,NOT_BORDERED,BLACK,1,FILLED,RED,1);
	SetupRectangle(&green,261, 283,86,106,NOT_BORDERED,BLACK,1,FILLED,GREEN,1);
	DrawRectangle(&green);
	DrawRectangle(&red);	
	TFT_ShowChar(green.beginX+8,green.beginY+4,'-',BLACK,GREEN);
	TFT_ShowChar(red.beginX+8,red.beginY+4,'+',BLACK,RED);
	SetupRectangle(&buttons_right_frame,261,283,red.beginY,green.endY,BORDERED,BLACK,1,NOT_FILLED,GREEN,1);
	DrawRectangle(&buttons_right_frame);
	//SetupRectangle(&top,45,red.endX,26 ,46,BORDERED,BLACK,1,NOT_FILLED,LIGHTGRAY1,1);
	//top.visible=VISIBLE;
//	DrawRectangle(&top);
	//DrawLine(red.endX,red.endX,0,46,BLACK);
}
