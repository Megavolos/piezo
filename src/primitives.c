#include "primitives.h"


u16 POINT_COLOR=RED;
u16 GREED_COLOR=BLUE;
u16 GREED_BACKGROUND=BLACK;
u16 GREED_STEP=20;




void TFT_ShowChar(u16 x,u16 y,u8 num, u16 color,  u16 bgrnd)
{       
#define MAX_CHAR_POSY 232
#define MAX_CHAR_POSX 319 
    u8 temp;
    u8 pos,t;      
    if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return;
    //Йи¶ЁТ»ёцЧЦ·ыЛщХјµДґуРЎ 
    //їЄ±ЩїХјд
	  
  writeLCDCommand(32, y);
  writeLCDCommand(33, y+11);
	
	writeLCDCommand(0x0050, y); // Horizontal GRAM Start Address
	writeLCDCommand(0x0051, y+11); // Horizontal GRAM End Address
	writeLCDCommand(0x0052, x); // Vertical GRAM Start Address
	writeLCDCommand(0x0053, x+5); // Vertical GRAM Start Address	 
	writeLCDCommand(32, y);
    writeLCDCommand(33, x);	// 
	*(uint16_t *) (LCD_REG) = 34;
   
   
   
	
 //  LCD_SetPos(x,x+5,y,y+11);//320x240
   
	
	num=num-' ';//µГµЅЖ«ТЖєуµДЦµ
	for(pos=0;pos<12;pos++)
	{
	    temp=asc2_1206[num][pos];
	    for(t=0;t<6;t++)
	    {                 
	        if(temp&0x01)writeLCDData(color);
	        else writeLCDData(bgrnd);//°ЧЙ«    
	        temp>>=1; 
	    }
	}
	writeLCDCommand(0x0050, 0);
	writeLCDCommand(0x0051, 239); // Horizontal GRAM End Address
	writeLCDCommand(0x0052, 0); // Vertical GRAM Start Address
	writeLCDCommand(0x0053, 319); // Vertical GRA

}  	 


void TFT_ShowString(u16 x,u16 y,const u8 *p, u16 color, u16 bgrnd)
{         
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=12;}
        if(y>MAX_CHAR_POSY){y=x=0;}
        TFT_ShowChar(x,y,*p, color, bgrnd);
        x+=6;
        p++;
    }  
}



void DrawGrid (Grid *grid)
{
	u16 i,j;
	for(i=grid->beginX;i<=grid->endX;i++)
	{
		for (j=grid->beginY;j<=grid->endY;j++)
		{
			if (!(j%grid->stepY) || !(i%grid->stepX))
			{
				plotpx(i,j,grid->gridcolor);
			}
			else
			{
				plotpx(i,j,grid->backcolor);
			}
		}
	}
	grid->rendered=TRUE;
}  
void clr(int x1, int x2, int y1, int y2, unsigned int color )
{
	int x;
	writeLCDCommand(32, x1);
  writeLCDCommand(33, y1);
  *(uint16_t *) (LCD_REG) = 34;
	 for (x=x1; x <= (x2*y2); x++)
	{
			    writeLCDData(color);
	
	}
	x=0;
}


 


void plotpx(unsigned int X, unsigned int Y, unsigned int color)
{
	
				writeLCDCommand(32, Y);
				writeLCDCommand(33, X);
				*(uint16_t *) (LCD_REG) = 34;
				writeLCDData(color);
};
void DrawLine(int x1, int x2, int y1, int y2, unsigned int color)
{
	int x,y,dy,dx,s1,s2,CF,t,i;
	x=x1;
	y=y1;
	//определяем знаки для s1 и s2.
	if ((x2-x1)>=0){s1=1;} else {s1=-1;}
	if ((y2-y1)>=0){s2=1;} else {s2=-1;}
	//находим dx и dy
	if (s1==1){dx=x2-x1;} else {dx=x1-x2;}
	if (s2==1){dy=y2-y1;} else {dy=y1-y2;}
	//решаем менять или нет между собой dx и dy 
	if (dy>dx)
	{
		int temp;
		temp=dx;
		dx=dy;
		dy=temp;
		CF=1; //ChangeFlag = True
	}
	else
	{
		CF=0;
	}
	t=2*dy-dx; //инициализация t
	for (i=0;i<dx;i++)
	{
		plotpx(x,y,color);
		while (t>=0)
		{
			if (CF)
				x+=s1;
			else
				y+=s2;
			t=t-2*dx;
		}
		if (CF)
			y+=s2;
		else
		{
			x+=s1;
		}
		t=t+2*dy;
	}
	i=0;
	};
		
void DrawCross(u16 X, u16 Y, u16 L,unsigned int color)
{
	u16 x1_line1,x2_line1;
	u16 y1_line2,y2_line2;
	x1_line1=X-(L/2);
	x2_line1=X+(L/2);
	y1_line2=Y-(L/2);
	y2_line2=Y+(L/2);
	while (x1_line1<=x2_line1)
	{
		plotpx(x1_line1,Y,color);
		x1_line1++;
	}
	while (y1_line2<=y2_line2)
	{
		plotpx(X,y1_line2,color);
		y1_line2++;
	}	
}	

	
