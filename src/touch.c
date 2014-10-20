#include "touch.h"
unsigned int X=0,Y=0;
//unsigned int Xs_1=0,Xs_2=0,Xs_3=0,Xs_4=0,Ys_1=0,Ys_2=0,Ys_3=0,Ys_4=0; //јЗВјґҐЧш±кЦµ
char s[10];
int32_t d_in_x=0, d_in_y=0; 
volatile int32_t cali_A, cali_B, cali_C, cali_D, cali_E, cali_F;






u8 read_once(void)
{	unsigned int a,b;
	TCS_SET(0); 
	delay_us(5);	   	 
	SPI_SendByte(CMD_RDY); 
	delay_us(5);	
	a=SPI_ReadByte(0);
	a=a<<8;
	a|=SPI_ReadByte(0);
	delay_us(5);	
	TCS_SET(1); 	 
	a>>=3; 
	Y=a;
	delay_us(15);	
	TCS_SET(0); 
	delay_us(5);	 
    SPI_SendByte(CMD_RDX);
	delay_us(5);	
	b=SPI_ReadByte(0);
	b=b<<8;
	b|=SPI_ReadByte(0);
	delay_us(5);	
	b>>=3; 
	X=b;   

	TCS_SET(1); 

	X=4096-X;
	if(X>100&&Y>100&&X<4000&&Y<4000)return 1;
	else return 0;			                 
}

u8 ReadTouchXY ()
	{
		u8 readcomplete=0; 
		float X1,Y1;
		u16 buffer_x[10];
		u16 buffer_y[10];
		u16 x1,x2,y1,y2,temp=0;
		u8 count=0;
		u8 count2=0;
		u8 t1=0;
	
		if (!top_rectangle.rendered) delay_ms(50);
		a=PEN;
		
		while (!a&&count<10)
		{
			if (read_once())
			{
				buffer_x[count]=X;
				buffer_y[count]=Y;
				count++;
			}
		}
					
					
		if(count==10)
		{
			do
			{
				t1=0;
				for(count2=0;count2<count-1;count2++)
				{
					if(buffer_x[count2]>buffer_x[count2+1])
					{
						temp=buffer_x[count2+1];
						buffer_x[count2+1]=buffer_x[count2];
						buffer_x[count2]=temp;
						t1=1;
					}  
				}
			}while(t1);
					
			do
			{
				t1=0;					
				for(count2=0;count2<count-1;count2++)
				{
					if(buffer_y[count2]>buffer_y[count2+1])
					{
						temp=buffer_y[count2+1];
						buffer_y[count2+1]=buffer_y[count2];
						buffer_y[count2]=temp;
						t1=1;
					}  
				}
			}while(t1);

			x1=buffer_x[3]; x2=buffer_x[4]; 	
			y1=buffer_y[3]; y2=buffer_y[4];    
			if(((x1>x2)&&(x1>x2+30))||((x2>x1)&&(x2>x1+30))||((y1>y2)&&(y1>y2+30))||((y2>y1)&&(y2>y1+30)));	 		  
			else
			{
				X1=(buffer_x[3]+buffer_x[4])/2;
				Y1=(buffer_y[3]+buffer_y[4])/2;	
				if(X1<=4096&&Y1<=4096) 
				{	
					X=X1;
					Y=Y1;
					readcomplete=1;
				}
			}
				 
			a=PEN;
			count=0;
			}
	if (readcomplete) 
	{
		return 1;
	}
	else
	{
		return 0;
	}
	}
	void touch_correct (uint32_t in_x,uint32_t in_y)
{
        d_in_x = (cali_A * in_x + cali_B * in_y + cali_C) / RESCALE_FACTOR;
        d_in_y = (cali_D * in_x + cali_E * in_y + cali_F) / RESCALE_FACTOR;
}
	void Calibrate ()
		{
			char complete=0;
			double temp1, temp2;
			double cal_A = 0.0, cal_B = 0.0, cal_C = 0.0, cal_D = 0.0, cal_E = 0.0, cal_F = 0.0;
			uint32_t xt1, xt2, xt3;
			uint32_t yt1, yt2, yt3;
			struct Point
			{
				u16  X;
				u16 Y;				
				unsigned int Color;
			};
			struct Point cpoint1, cpoint2, cpoint3;
			
			cpoint1.X=32;
			cpoint1.Y=120;
			cpoint1.Color=RED;
			
			cpoint2.X=160;
			cpoint2.Y=216;
			cpoint2.Color=GREEN;
			
			cpoint3.X=288;
			cpoint3.Y=24;
			cpoint3.Color=YELLOW;
			
			DrawCross(cpoint1.X,cpoint1.Y,20,cpoint1.Color);
			while (1)
			{
				if(_it1==1)
				{
					delay_ms(340);
					a=PEN;
					if(a==0)
					{
						while (a==0)
						{
							delay_us(10);
							ReadTouchXY();
							delay_us(10);
							xt1=X;
							yt1=Y;		
							sprintf(s,"%4d %4d",xt1,yt1);
							TFT_ShowString(32,90,(u8*)s, RED,LIGHTGRAY1);
							a=PEN;
							_it1=0;
							break;
						}
						break;
					}
					else _it1=0;
				}
			}
			_it1=0;
			DrawCross(cpoint2.X,cpoint2.Y,20,cpoint2.Color);
			while (1)
			{
				if(_it1==1)
				{
					delay_ms(340);
					a=PEN;
					if(a==0)
					{
						while (a==0)
						{
							delay_us(10);
							ReadTouchXY();
							delay_us(10);
							xt2=X;
							yt2=Y;		
							sprintf(s,"%4d %4d",xt2,yt2);
							TFT_ShowString(180,200,(u8*)s, GREEN,LIGHTGRAY1);
							a=PEN;
							_it1=0;
							break;
						}
						break;
					}
					else _it1=0;
				}
			}		
			_it1=0;	
			DrawCross(cpoint3.X,cpoint3.Y,20,cpoint3.Color);
			while (1)
			{
				if(_it1==1)
				{
					delay_ms(340);
					a=PEN;
					if(a==0)
					{
						while (a==0)
						{
							delay_us(10);
							ReadTouchXY();
							delay_us(10);
							xt3=X;
							yt3=Y;
							sprintf(s,"%4d %4d",xt3,yt3);
							TFT_ShowString(240,40,(u8*)s, BLUE,LIGHTGRAY1);
							a=PEN;
							_it1=0;
							complete=1;
							break;
						}
						break;
					}
					else _it1=0;
				}
			}
			if (complete==1)
			{
				//A
				temp1 = ((double) cpoint1.X * ((double) yt2 - (double) yt3)) + ((double) cpoint2.X * ((double) yt3 - (double) yt1)) + ((double) cpoint3.X * ((double) yt1 - (double) yt2));
				temp2 = ((double) xt1 * ((double) yt2 - (double) yt3)) + ((double) xt2 * ((double) yt3 - (double) yt1)) + ((double) xt3 * ((double) yt1 - (double) yt2));
				cal_A = temp1 / temp2;
				cali_A = (int32_t) ((double)cal_A * RESCALE_FACTOR);
				sprintf(s,"A=%4d",cali_A);
				TFT_ShowString(140,120,(u8*)s, GRED,LIGHTGRAY1);
				//B
				temp1 = (cal_A * ((double) xt3 - (double) xt2)) + (double) cpoint2.X - (double) cpoint3.X;
				temp2 = (double) yt2 - (double) yt3;
				cal_B = temp1 / temp2;
				cali_B = (int32_t) ((double)cal_B * RESCALE_FACTOR);
				sprintf(s,"B=%4d",cali_B);
				TFT_ShowString(140,130,(u8*)s, GRED,LIGHTGRAY1);
				//C
				cal_C = (double) cpoint3.X - (cal_A * (double) xt3) - (cal_B * (double) yt3);
				cali_C = (int32_t) (cal_C * RESCALE_FACTOR);
				sprintf(s,"C=%4d",cali_C);
				TFT_ShowString(140,140,(u8*)s, GRED,LIGHTGRAY1);
				//D
				temp1 = ((double) cpoint1.Y * ((double) yt2 - (double) yt3)) + ((double) cpoint2.Y * ((double) yt3 - (double) yt1)) + ((double) cpoint3.Y * ((double) yt1 - (double) yt2));
				temp2 = ((double) xt1 * ((double) yt2 - (double) yt3)) + ((double) xt2 * ((double) yt3 - (double) yt1)) + ((double) xt3 * ((double) yt1 - (double) yt2));
				cal_D = (double)temp1 / (double)temp2;
				cali_D = (int32_t) (cal_D * RESCALE_FACTOR);
				sprintf(s,"D=%4d",cali_D);
				TFT_ShowString(140,150,(u8*)s, GRED,LIGHTGRAY1);
				//E
				temp1 = (cal_D * ((double) xt3 - (double) xt2)) + (double) cpoint2.Y - (double) cpoint3.Y;
				temp2 = (double) yt2 - (double) yt3;
				cal_E = (double)temp1 / (double)temp2;
				cali_E = (int32_t) (cal_E * RESCALE_FACTOR);
				sprintf(s,"E=%4d",cali_E);
				TFT_ShowString(140,160,(u8*)s, GRED,LIGHTGRAY1);
				//F
				cal_F = (double) cpoint3.Y - cal_D * (double) xt3 - cal_E * (double) yt3;
				cali_F = (int32_t) (cal_F * RESCALE_FACTOR);
				sprintf(s,"F=%4d",cali_F);
				TFT_ShowString(140,170,(u8*)s, GRED,LIGHTGRAY1);
				
			  FlashSectorEarse(0);
				Save_int32_t(cali_A,0x00);
				Save_int32_t(cali_B,0x04);
				Save_int32_t(cali_C,0x08);
				Save_int32_t(cali_D,0x12);
				Save_int32_t(cali_E,0x16);
				Save_int32_t(cali_F,0x20);
				
			
			}
		}
void CalibrDataRead ()
{
	cali_A=Read_int32_t(0x00);
	cali_B=Read_int32_t(0x04);
	cali_C=Read_int32_t(0x08);
	cali_D=Read_int32_t(0x12);
	cali_E=Read_int32_t(0x16);
	cali_F=Read_int32_t(0x20);			
}	

char button_pressed(Rectangle *rect)
{
	if ((d_in_x>rect->beginX)&&(d_in_x<rect->endX)&&(d_in_y>rect->beginY)&&(d_in_y<rect->endY)) {return 1;}
	else return 0;
}

void line3_set1_draw(Variables *var, u16 fontcolor, u16 backcolor)
{
	switch (var->trange)
	{
		case 1:
			TFT_ShowString(285,50,(u8*)"us",fontcolor,backcolor);
		break;
		case 2:
			TFT_ShowString(285,50,(u8*)"ms",fontcolor,backcolor);
		break;
		case 3:
			TFT_ShowString(285,50,(u8*)" s",fontcolor,backcolor);
		break;
	}
	switch (var->vrange)
	{
		case 1:
			TFT_ShowString(285,90,(u8*)"mv",fontcolor,backcolor);
		break;
		case 2:
			TFT_ShowString(285,90,(u8*)" v",fontcolor,backcolor);
		break;
		case 3:
			TFT_ShowString(285,90,(u8*)"2v",fontcolor,backcolor);
		break;
	}
}

void line1_select(Variables *var)
{
	if (buttons_right_frame.visible==VISIBLE)
	{
		if (button_pressed(&plus_right1)&&(var->menu_set<2)&&(buttons_right_frame.visible==VISIBLE)) var->menu_set++;
		if (button_pressed(&minus_right1)&&(var->menu_set>1)&&(buttons_right_frame.visible==VISIBLE)) var->menu_set--;
		switch (var->menu_set)
		{
		case 1:
			TFT_ShowString(str_right_line1.beginX,str_right_line1.beginY,(u8*)"t/div",str_right_line1.backcolor,str_right_line1.fontcolor);
			TFT_ShowString(str_right_line4.beginX,str_right_line4.beginY,(u8*)"v/div",str_right_line4.backcolor,str_right_line4.fontcolor);
			sprintf(s,"%4d",var->tdiv);
			TFT_ShowString(285,40,(u8*)s,BLACK,LIGHTGRAY1);
			sprintf(s,"%4d",var->vdiv);
			TFT_ShowString(285,80,(u8*)s,BLACK,LIGHTGRAY1);
			line3_set1_draw(var,BLACK,LIGHTGRAY1);
		break;
		case 2:
			TFT_ShowString(str_right_line1.beginX,str_right_line1.beginY,(u8*)"g.stX",str_right_line1.backcolor,str_right_line1.fontcolor);
			TFT_ShowString(str_right_line4.beginX,str_right_line4.beginY,(u8*)"g.stY",str_right_line4.backcolor,str_right_line4.fontcolor);
			sprintf(s,"%4d",grid.stepX);
			TFT_ShowString(285,40,(u8*)s,BLACK,LIGHTGRAY1);
			sprintf(s,"%4d",grid.stepY);
			TFT_ShowString(285,80,(u8*)s,BLACK,LIGHTGRAY1);
			TFT_ShowString(285,50,(u8*)"px",BLACK,LIGHTGRAY1);
			TFT_ShowString(285,90,(u8*)"px",BLACK,LIGHTGRAY1);
		break;
		}
	}
}

void line2_select(Variables *var)
{
	if (buttons_right_frame.visible==VISIBLE)
	{
		if (var->menu_set==1)
		{
			TFT_ShowString(str_right_line1.beginX,str_right_line1.beginY,(u8*)"t/div",str_right_line1.fontcolor,str_right_line1.backcolor);
			TFT_ShowString(str_right_line4.beginX,str_right_line4.beginY,(u8*)"v/div",str_right_line4.fontcolor,str_right_line4.backcolor);
			if (button_pressed(&plus_right1) && (var->tdiv<3)) 
			{
				var->tdiv++;
				sprintf(s,"%4d",var->tdiv);
				TFT_ShowString(285,40,(u8*)s,LIGHTGRAY1,BLACK);
			}
			if (button_pressed(&minus_right1)&& (var->tdiv>1))
			{
				var->tdiv--;
				sprintf(s,"%4d",var->tdiv);
				TFT_ShowString(285,40,(u8*)s,LIGHTGRAY1,BLACK);
			}
			if (button_pressed(&plus_right2) && (var->vdiv<3))
			{
				var->vdiv++;
				sprintf(s,"%4d",var->vdiv);
				TFT_ShowString(285,80,(u8*)s,LIGHTGRAY1,BLACK);
			}
			if (button_pressed(&minus_right2)&& (var->vdiv>1))
			{
				var->vdiv--;			
				sprintf(s,"%4d",var->vdiv);
				TFT_ShowString(285,80,(u8*)s,LIGHTGRAY1,BLACK);
			}
		}
		if (var->menu_set==2)
		{
			TFT_ShowString(str_right_line1.beginX,str_right_line1.beginY,(u8*)"g.stX",str_right_line1.fontcolor,str_right_line1.backcolor);
			TFT_ShowString(str_right_line4.beginX,str_right_line4.beginY,(u8*)"g.stY",str_right_line4.fontcolor,str_right_line4.backcolor);

			if (button_pressed(&plus_right1)) 
			{
				grid.stepX++;
				grid_top.stepX=grid.stepX;
				grid_right.stepX=grid.stepX;
				sprintf(s,"%3d",grid.stepX);
				TFT_ShowString(285,40,(u8*)s,LIGHTGRAY1,BLACK);
				DrawGrid(&grid);
				GUI_Draw_right_control();
			}
			if (button_pressed(&minus_right1))
			{
				grid.stepX--;
				grid_top.stepX=grid.stepX;
				grid_right.stepX=grid.stepX;
				sprintf(s,"%3d",grid.stepX);
				TFT_ShowString(285,40,(u8*)s,LIGHTGRAY1,BLACK);
				DrawGrid(&grid);
				GUI_Draw_right_control();
			}
			if (button_pressed(&plus_right2))
			{
				grid.stepY++;
				grid_top.stepY=grid.stepY;
				grid_right.stepY=grid.stepY;
				sprintf(s,"%3d",grid.stepY);
				TFT_ShowString(285,80,(u8*)s,LIGHTGRAY1,BLACK);
				DrawGrid(&grid);
				GUI_Draw_right_control();
			}
			if (button_pressed(&minus_right2))
			{
				grid.stepY--;
				grid_top.stepY=grid.stepY;
				grid_right.stepY=grid.stepY;
				sprintf(s,"%3d",grid.stepY);
				TFT_ShowString(285,80,(u8*)s,LIGHTGRAY1,BLACK);
				DrawGrid(&grid);
				GUI_Draw_right_control();
			}
		}
	}
}

void line3_select(Variables *var)
{
	if (buttons_right_frame.visible==VISIBLE)
	{
		if (var->menu_set==1)
		{
			sprintf(s,"%3d",var->tdiv);
			TFT_ShowString(285,40,(u8*)s,BLACK,LIGHTGRAY1);
			sprintf(s,"%3d",var->vdiv);
			TFT_ShowString(285,80,(u8*)s,BLACK,LIGHTGRAY1);
			if (button_pressed(&plus_right1) && (var->trange<3)) var->trange++;
			if (button_pressed(&minus_right1)&& (var->trange>1)) var->trange--;
			if (button_pressed(&plus_right2) && (var->vrange<3)) var->vrange++;
			if (button_pressed(&minus_right2)&& (var->vrange>1)) var->vrange--;			
			line3_set1_draw(var,LIGHTGRAY1,BLACK);
		}
		if (var->menu_set==2)
		{
			sprintf(s,"%3d",grid.stepX);
			TFT_ShowString(285,40,(u8*)s,BLACK,LIGHTGRAY1);
			sprintf(s,"%3d",grid.stepY);
			TFT_ShowString(285,80,(u8*)s,BLACK,LIGHTGRAY1);
			TFT_ShowString(285,50,(u8*)"px",LIGHTGRAY1,BLACK);
			TFT_ShowString(285,90,(u8*)"px",LIGHTGRAY1,BLACK);
		}
	}

	
}

void line_not_selected(Variables *var)
{
	if (buttons_right_frame.visible==VISIBLE)
	{
		if (var->menu_set==1)
		{
			line3_set1_draw(var,BLACK,LIGHTGRAY1);
		}
		if (var->menu_set==2)
		{
			TFT_ShowString(285,50,(u8*)"px",BLACK,LIGHTGRAY1);
			TFT_ShowString(285,90,(u8*)"px",BLACK,LIGHTGRAY1);
		}
	}
}

void touch_control(Variables *var)
{
	char touched_once=1;
	delay_ms(20);
	a=PEN;
	if(a==0)
	{
		while (a==0)
		{
			if (touched_once)
			{
				ReadTouchXY();
				touch_correct(X,Y);
				if  ((d_in_x>=286)&&(d_in_y>=125)&&(d_in_y<=137))
				{
					var->counter++;	
					if (var->counter==5) var->counter=0;
				}
				if ((d_in_y<=26)&&(d_in_x>=45))
				{
					if (buttons_top_frame.visible==VISIBLE)
					{
						buttons_top_frame.visible=INVISIBLE;
						DrawGrid(&grid_top);
					}
					 else if (buttons_top_frame.visible==INVISIBLE)
					{
						buttons_top_frame.visible=VISIBLE;
						GUI_Draw_top_control();
					}
				}
				if (d_in_y>26)
				{					
					if ((d_in_x>=283) && (d_in_y<=106))
					{
						if (buttons_right_frame.visible==VISIBLE)
						{
							buttons_right_frame.visible=INVISIBLE;
							DrawGrid(&grid_right);
						}
						else if (buttons_right_frame.visible==INVISIBLE)
						{
							buttons_right_frame.visible=VISIBLE;
							GUI_Draw_right_control();
						}
					}
				}
				switch (var->counter)
				{
					case 1:
						line1_select(var);
						break;
					case 2:
						line2_select(var);
						break;
					case 3:
						line3_select(var);
						break;
					case 4:
						line_not_selected(var);
					break;
				}
				touched_once=0;
				a=PEN;
			}
		}
	}		
	_it1=0;		
}

	
		
	

		
