#include "gui.h"
Rectangle top_rectangle,right_rectangle,buttons_right_frame,buttons_top_frame,red,green;
Grid grid, grid_top,grid_right;
String str_right_line3, str_right_line6, str_calc, str_menu, str_start, str_stop, str_step,str_right_line4, str_right_line1, str_right_line2, str_right_line3, str_right_line5,str_right_line6;
char menu_string[3][10];
void GUI_show(Variables *var)
{
	
	clr(0,320,0,240,WHITE);
	SetupRectangle(&top_rectangle,0,319,0 ,26,BORDERED,BLACK,1,FILLED,LIGHTGRAY1,1);
	DrawRectangle(&top_rectangle);
	SetupRectangle(&right_rectangle,283,319,26 ,239,BORDERED,BLACK,1,FILLED,LIGHTGRAY1,1);
	DrawRectangle(&right_rectangle);


  TFT_ShowString(2,2,(u8*)"Mode:",BLACK,LIGHTGRAY1);
	//TFT_ShowString(2,7,"Linear",BLACK,LIGHTGRAY1);
	TFT_ShowString(2,13,(u8*)"Eq.time",BLACK,LIGHTGRAY1);
	DrawLine(45,45,0,26,BLACK);
	TFT_ShowString(47,2,(u8*) "  Begin",BLACK,LIGHTGRAY1);
	TFT_ShowString(60,13,(u8*)"1000",BLACK,LIGHTGRAY1);
	DrawLine(94,94,0,26,BLACK);
	TFT_ShowString(107,2,(u8*)"End",BLACK,LIGHTGRAY1);
	TFT_ShowString(107,13,(u8*)"1200",BLACK,LIGHTGRAY1);
	DrawLine(143,143,0,26,BLACK);
	TFT_ShowString(157,2,(u8*)"Step",BLACK,LIGHTGRAY1);
	TFT_ShowString(157,13,(u8*)"1200",BLACK,LIGHTGRAY1);
	DrawLine(192,192,0,26,BLACK);
	TFT_ShowString(210,2,(u8*)"qty.",BLACK,LIGHTGRAY1);
	TFT_ShowString(210,13,(u8*)"10",BLACK,LIGHTGRAY1);
	DrawLine(241,241,0,26,BLACK);
	TFT_ShowString(244,2,(u8*)"RPMmc2",BLACK,LIGHTGRAY1);
	TFT_ShowString(244,13,(u8*)"1200",RED,LIGHTGRAY1);
	
	
	TFT_ShowString(285,2,(u8*)"Freq",BLACK,LIGHTGRAY1);
	TFT_ShowString(285,13,(u8*)"10",RED,LIGHTGRAY1);

  SetupString(&str_right_line1,285,30,"t/div",BLACK,LIGHTGRAY1);
	sprintf(s,"%3d",var->tdiv);
	SetupString(&str_right_line2,285,50,s,BLACK,LIGHTGRAY1);
	SetupString(&str_right_line3,285,50," s",BLACK,LIGHTGRAY1);
	SetupString(&str_right_line4,285,70,"v/div",BLACK,LIGHTGRAY1);
	SetupString(&str_right_line5,285,50," s",BLACK,LIGHTGRAY1);
	SetupString(&str_right_line6,285,90,"2v",BLACK,LIGHTGRAY1);
	TFT_ShowString(str_right_line1.beginX,str_right_line1.beginY,(u8*)str_right_line1.label,str_right_line1.fontcolor,str_right_line1.backcolor);
	TFT_ShowString(str_right_line4.beginX,str_right_line4.beginY,(u8*)str_right_line4.label,str_right_line4.fontcolor,str_right_line4.backcolor);

	
	

	SetupString(&str_menu,286,125,"Menu",YELLOW,BLACK);
	SetupString(&str_calc,286,150,"Calc ",GOLD,BLACK);
	SetupString(&str_start,286,175,"START",GREEN,BLACK);
	SetupString(&str_step,286,200,"STEP",BLACK,LIGHTGRAY1);
	SetupString(&str_stop,286,225,"STOP",BLACK,LIGHTGRAY1);	
	TFT_ShowString(str_right_line3.beginX,str_right_line3.beginY,(u8*)str_right_line3.label,str_right_line3.fontcolor,str_right_line3.backcolor);
	TFT_ShowString(str_right_line3.beginX,str_right_line3.beginY,(u8*)str_right_line3.label,str_right_line3.fontcolor,str_right_line3.backcolor);
	TFT_ShowString(str_right_line6.beginX,str_right_line6.beginY,(u8*)str_right_line6.label,str_right_line6.fontcolor,str_right_line6.backcolor);
	TFT_ShowString(str_menu.beginX,str_menu.beginY,(u8*)str_menu.label,str_menu.fontcolor,str_menu.backcolor);
	TFT_ShowString(str_calc.beginX,str_calc.beginY,(u8*)str_calc.label,str_calc.fontcolor,str_calc.backcolor);
	TFT_ShowString(str_start.beginX,str_start.beginY,(u8*)str_start.label,str_start.fontcolor,str_start.backcolor);
	TFT_ShowString(str_step.beginX,str_step.beginY,(u8*)str_step.label,str_step.fontcolor,str_step.backcolor);
	TFT_ShowString(str_stop.beginX,str_stop.beginY,(u8*)str_stop.label,str_stop.fontcolor,str_stop.backcolor);
	SetupGrid(&grid,0,283,26,239,10,10,BLUE,BLACK,1);
	sprintf(s,"%3d",grid.stepX);
	TFT_ShowString(285,40,(u8*)s,BLACK,LIGHTGRAY1);
	sprintf(s,"%3d",grid.stepY);
	TFT_ShowString(285,80,(u8*)s,BLACK,LIGHTGRAY1);
	DrawGrid(&grid);
	SetupGrid(&grid_top,45,241,26,46,grid.stepX,grid.stepY,grid.gridcolor,grid.backcolor,1);
	SetupGrid(&grid_right,261,283,26,106,grid.stepX,grid.stepY,grid.gridcolor,grid.backcolor,1);
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
