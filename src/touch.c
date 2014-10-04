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
	X=a;
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
	Y=b;   

	TCS_SET(1); 

	Y=4096-Y;
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
	
		delay_ms(50);
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
        d_in_y = (cali_A * in_x + cali_B * in_y + cali_C) / RESCALE_FACTOR;
        d_in_x = (cali_D * in_x + cali_E * in_y + cali_F) / RESCALE_FACTOR;
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
				u8  X;
				u16 Y;				
				unsigned int Color;
			};
			struct Point cpoint1, cpoint2, cpoint3;
			
			cpoint1.X=120;
			cpoint1.Y=32;
			cpoint1.Color=RED;
			
			cpoint2.X=216;
			cpoint2.Y=160;
			cpoint2.Color=GREEN;
			
			cpoint3.X=24;
			cpoint3.Y=288;
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

	
		
	

		
