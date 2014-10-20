#include "gui.h"
Rectangle top_rectangle,right_rectangle,buttons_right_frame,buttons_top_frame;
Rectangle  minus_mode,plus_mode,minus_begin,plus_begin, minus_end,plus_end,minus_step,plus_step,minus_qty,plus_qty, minus_right1,plus_right1, minus_right2,plus_right2;
Grid grid, grid_top,grid_right;
String str_right_line3, str_right_line6, str_calc, str_menu, str_start, str_stop, str_step,str_right_line4, str_right_line1, str_right_line2, str_right_line3, str_right_line5,str_right_line6;
char menu_string[3][10];
void GUI_show(Variables *var)
{
	SetupGrid(&grid,0,283,26,239,10,10,BLUE,BLACK,1);
	var->line1=1;
	var->line2=grid.stepX;
	var->line3=3;
	var->line4=1;
	var->line5=grid.stepY;
	var->line6=3;
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
	sprintf(s,"%3d",var->line2);
	SetupString(&str_right_line2,285,40,s,BLACK,LIGHTGRAY1);

	SetupString(&str_right_line3,285,50," s",BLACK,LIGHTGRAY1);
	SetupString(&str_right_line4,285,70,"v/div",BLACK,LIGHTGRAY1);
	sprintf(s,"%3d",var->line5);
	SetupString(&str_right_line5,285,80,s,BLACK,LIGHTGRAY1);
	SetupString(&str_right_line6,285,90,"2v",BLACK,LIGHTGRAY1);

	
	

	SetupString(&str_menu,286,125,"Menu",YELLOW,BLACK);
	SetupString(&str_calc,286,150,"Calc ",GOLD,BLACK);
	SetupString(&str_start,286,175,"START",GREEN,BLACK);
	SetupString(&str_step,286,200,"STEP",BLACK,LIGHTGRAY1);
	SetupString(&str_stop,286,225,"STOP",BLACK,LIGHTGRAY1);	
	TFT_ShowString(str_right_line1.beginX,str_right_line1.beginY,(u8*)str_right_line1.label,str_right_line1.fontcolor,str_right_line1.backcolor);
	TFT_ShowString(str_right_line2.beginX,str_right_line2.beginY,(u8*)str_right_line2.label,str_right_line2.fontcolor,str_right_line2.backcolor);
	TFT_ShowString(str_right_line3.beginX,str_right_line3.beginY,(u8*)str_right_line3.label,str_right_line3.fontcolor,str_right_line3.backcolor);
	TFT_ShowString(str_right_line4.beginX,str_right_line4.beginY,(u8*)str_right_line4.label,str_right_line4.fontcolor,str_right_line4.backcolor);
	TFT_ShowString(str_right_line5.beginX,str_right_line5.beginY,(u8*)str_right_line5.label,str_right_line5.fontcolor,str_right_line5.backcolor);
	TFT_ShowString(str_right_line6.beginX,str_right_line6.beginY,(u8*)str_right_line6.label,str_right_line6.fontcolor,str_right_line6.backcolor);
	TFT_ShowString(str_menu.beginX,str_menu.beginY,(u8*)str_menu.label,str_menu.fontcolor,str_menu.backcolor);
	TFT_ShowString(str_calc.beginX,str_calc.beginY,(u8*)str_calc.label,str_calc.fontcolor,str_calc.backcolor);
	TFT_ShowString(str_start.beginX,str_start.beginY,(u8*)str_start.label,str_start.fontcolor,str_start.backcolor);
	TFT_ShowString(str_step.beginX,str_step.beginY,(u8*)str_step.label,str_step.fontcolor,str_step.backcolor);
	TFT_ShowString(str_stop.beginX,str_stop.beginY,(u8*)str_stop.label,str_stop.fontcolor,str_stop.backcolor);
	//sprintf(s,"%3d",grid.stepX);
	//TFT_ShowString(285,40,(u8*)s,BLACK,LIGHTGRAY1);
	//sprintf(s,"%3d",grid.stepY);
	//TFT_ShowString(285,80,(u8*)s,BLACK,LIGHTGRAY1);
	DrawGrid(&grid);
	SetupGrid(&grid_top,45,241,26,46,grid.stepX,grid.stepY,grid.gridcolor,grid.backcolor,1);
	SetupGrid(&grid_right,261,283,26,106,grid.stepX,grid.stepY,grid.gridcolor,grid.backcolor,1);
//	GUI_Draw_right_control();
//	GUI_Draw_top_control();
}

void GUI_Draw_top_control()
{
	SetupRectangle(&minus_mode,0, 22,26,46,NOT_BORDERED,BLACK,1,FILLED,GREEN,1); 															//- Mode
	DrawRectangle(&minus_mode);
	TFT_ShowChar(minus_mode.beginX+9,minus_mode.beginY+4,'-',BLACK,GREEN); 							//  "-"
	SetupRectangle(&plus_mode,22,45,26,46,NOT_BORDERED,BLACK,1,FILLED,RED,1);   															//+ Mode
	DrawRectangle(&plus_mode);
	TFT_ShowChar(plus_mode.beginX+9,plus_mode.beginY+4,'+',BLACK,RED);									//  "+"
	
	SetupRectangle(&minus_begin,plus_mode.endX,plus_mode.endX+25,26,46,NOT_BORDERED,BLACK,1,FILLED,GREEN,1);  //- Begin
	DrawRectangle(&minus_begin);
	TFT_ShowChar(minus_begin.beginX+9,minus_begin.beginY+4,'-',BLACK,GREEN); 	 					//  "-"
	SetupRectangle(&plus_begin,minus_begin.endX,minus_begin.endX+24,26,46,NOT_BORDERED,BLACK,1,FILLED,RED,1); //+ Begin
	DrawRectangle(&plus_begin);
	TFT_ShowChar(plus_begin.beginX+9,plus_begin.beginY+4,'+',BLACK,RED);								//  "+"

	SetupRectangle(&minus_end,plus_begin.endX,plus_begin.endX+25,26,46,NOT_BORDERED,BLACK,1,FILLED,GREEN,1);  //- End
	DrawRectangle(&minus_end);
	TFT_ShowChar(minus_end.beginX+9,minus_end.beginY+4,'-',BLACK,GREEN); 								//  "-"
	SetupRectangle(&plus_end,minus_end.endX,minus_end.endX+24,26,46,NOT_BORDERED,BLACK,1,FILLED,RED,1); 			//+ End
	DrawRectangle(&plus_end);
	TFT_ShowChar(plus_end.beginX+9,plus_end.beginY+4,'+',BLACK,RED);										//  "+"

	SetupRectangle(&minus_step,plus_end.endX,plus_end.endX+25,26,46,NOT_BORDERED,BLACK,1,FILLED,GREEN,1);  		//- Step
	DrawRectangle(&minus_step);
	TFT_ShowChar(minus_step.beginX+9,minus_step.beginY+4,'-',BLACK,GREEN); 			 				//  "-"
	SetupRectangle(&plus_step,minus_step.endX,minus_step.endX+24,26,46,NOT_BORDERED,BLACK,1,FILLED,RED,1); 		//+ Step
	DrawRectangle(&plus_step);
	TFT_ShowChar(plus_step.beginX+9,plus_step.beginY+4,'+',BLACK,RED);					 				//  "+"

	SetupRectangle(&minus_qty,plus_step.endX,plus_step.endX+25,26,46,NOT_BORDERED,BLACK,1,FILLED,GREEN,1);  	//- Qty
	DrawRectangle(&minus_qty);
	TFT_ShowChar(minus_qty.beginX+9,minus_qty.beginY+4,'-',BLACK,GREEN); 			 					//  "-"
	SetupRectangle(&plus_qty,minus_qty.endX,minus_qty.endX+24,26,46,NOT_BORDERED,BLACK,1,FILLED,RED,1); 			//+ Qty
	DrawRectangle(&plus_qty);
	TFT_ShowChar(plus_qty.beginX+9,plus_qty.beginY+4,'+',BLACK,RED);					 					//  "+"

	
	SetupRectangle(&buttons_top_frame,45,plus_qty.endX,26 ,46,BORDERED,BLACK,1,NOT_FILLED,LIGHTGRAY1,1);
	buttons_top_frame.visible=VISIBLE;
	DrawRectangle(&buttons_top_frame);
	//DrawLine(red.endX,red.endX,0,46,BLACK);
}

void GUI_Draw_right_control()
{
	SetupRectangle(&plus_right1,261, 283,26,46,NOT_BORDERED,BLACK,1,FILLED,RED,1); 														//+
	DrawRectangle(&plus_right1);
	TFT_ShowChar(plus_right1.beginX+8,plus_right1.beginY+4,'+',BLACK,RED); 							//  "+"
	SetupRectangle(&minus_right1,261,283,46,66,NOT_BORDERED,BLACK,1,FILLED,GREEN,1);   												//- 
	DrawRectangle(&minus_right1);
	TFT_ShowChar(minus_right1.beginX+8,minus_right1.beginY+4,'-',BLACK,GREEN);					//  "-"
	
	SetupRectangle(&plus_right2,261, 283,26,46,NOT_BORDERED,BLACK,1,FILLED,RED,1); 														//+
	DrawRectangle(&plus_right2);
	TFT_ShowChar(plus_right2.beginX+8,plus_right2.beginY+4,'+',BLACK,RED); 							//  "+"
	SetupRectangle(&minus_right2,261,283,46,66,NOT_BORDERED,BLACK,1,FILLED,GREEN,1);   												//- 
	DrawRectangle(&minus_right2);
	TFT_ShowChar(minus_right2.beginX+8,minus_right2.beginY+4,'-',BLACK,GREEN);					//  "-"
	
	SetupRectangle(&buttons_right_frame,261,283,26,106,BORDERED,BLACK,1,NOT_FILLED,GREEN,1);
	DrawRectangle(&buttons_right_frame);

}
