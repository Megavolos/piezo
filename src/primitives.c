#include "primitives.h"


u16 POINT_COLOR=RED;
u16 GREED_COLOR=BLUE;
u16 GREED_BACKGROUND=BLACK;
u16 GREED_STEP=20;




void TFT_ShowChar(u16 x,u16 y,u8 num, u16 color)
{       
#define MAX_CHAR_POSX 232
#define MAX_CHAR_POSY 304 
    u8 temp;
    u8 pos,t;      
    if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return;
    //Йи¶ЁТ»ёцЧЦ·ыЛщХјµДґуРЎ 
    //їЄ±ЩїХјд
	  
  writeLCDCommand(32, x);
  writeLCDCommand(33, x+11);
	
	writeLCDCommand(0x0050, x); // Horizontal GRAM Start Address
	writeLCDCommand(0x0051, x+11); // Horizontal GRAM End Address
	writeLCDCommand(0x0052, y); // Vertical GRAM Start Address
	writeLCDCommand(0x0053, y+5); // Vertical GRAM Start Address	 
	writeLCDCommand(32, x);
    writeLCDCommand(33, y);	// 
	*(uint16_t *) (LCD_REG) = 34;
   
   
   
	
 //  LCD_SetPos(x,x+5,y,y+11);//320x240
   
	
	num=num-' ';//µГµЅЖ«ТЖєуµДЦµ
	for(pos=0;pos<12;pos++)
	{
	    temp=asc2_1206[num][pos];
	    for(t=0;t<6;t++)
	    {                 
	        if(temp&0x01)writeLCDData(color);
	        else writeLCDData(0x0);//°ЧЙ«    
	        temp>>=1; 
	    }
	}
	writeLCDCommand(0x0050, 0);
	writeLCDCommand(0x0051, 239); // Horizontal GRAM End Address
	writeLCDCommand(0x0052, 0); // Vertical GRAM Start Address
	writeLCDCommand(0x0053, 319); // Vertical GRA

}  	 


void TFT_ShowString(u16 x,u16 y,const u8 *p, u16 color)
{         
    while(*p!='\0')
    {       
        if(y>MAX_CHAR_POSY){y=0;x+=12;}
        if(x>MAX_CHAR_POSX){x=y=0;}
        TFT_ShowChar(x,y,*p, color);
        y+=6;
        p++;
    }  
}

void DrawGrid (u16 beginx, u16 beginy,u16 step, u16 Color, u16 BgrColor)
{
	unsigned int x1=0,y1=0,x;
	y1=beginy;
	x1=beginx;

	writeLCDCommand(32, beginy);
  writeLCDCommand(33, beginx);
	*(uint16_t *) (LCD_REG) = 34;
	for (x=0; x <= ((320-(beginx+1))*(240-(beginy+1))) ; x++)
	{
		if ((!(x1%step)||(!(y1%step)))) 
		{
			writeLCDData(Color);
		}
		else
		{
			writeLCDData(BgrColor);
		}
		x1++;
		if (x1==320) 
		{
			y1++;
			x1=0;
		}
		if (y1==240)
		{
			y1=0;
		}
		
	}
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
	if ((rect->bordered==FALSE)&(rect->filled==FALSE)) return; //если нет заливки и нет краев, то нечего рисовать
	if (rect->visible==FALSE) return;
	//************************Если просто края без заливки*******************************************
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
	//***********************************************************************************************

  //************************Если просто заливка без краев******************************************	
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
	//***********************************************************************************************
	
	//****************************Если заливка с краями**********************************************
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
	
	
	//***********************************************************************************************
	
}
	
