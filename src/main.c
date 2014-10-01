/*******************************************************************/
#include "main.h"
unsigned char a=0,_it0=0,_it1=0,_it2=0,_it3=0;
unsigned char	num=0;

void EXTI9_5_IRQHandler(void)
{ //һŜֱޓׁȡPEN?	 
  //GPIO_ResetBits(GPIOB, GPIO_Pin_5);   
  if(EXTI_GetITStatus(EXTI_Line6) != RESET)
  {
   //  GPIO_ResetBits(GPIOB, GPIO_Pin_5);   								 	 	   			    
    //א׏۳ғʱӔлԽֶ֯ìʹփӉҹ˽ߝټ׼ȷ  
   	//delay_ms(100);
	a=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6); 
	_it1=1;


    EXTI_ClearITPendingBit(EXTI_Line6);
  }
}
 


/*void TIM3_IRQHandler(void)
{
//	u8 d0,d1,d2,d3;
	TIM3->SR &= ~TIM_SR_UIF; //Сбрасываем флаг UIF
//	oscilloscope(20,YELLOW);
	
if (_it1==1)
	{
		TFT_ShowString(10,10,"Yes");
		_it1=0;
	}
	else
	{
	TFT_ShowString(10,10,"No-");
	}
}

*/

	
/*******************************************************************/
int main()
{
//		unsigned int j;
  
 

	  
	LCD_init();
	SPI_init();
	ADC_init();
	NVIC_Configuration();
	EXTI_init();
	delay_init(72);
	
	
	

		
// Начальный и конечный адреса по горизонтали
        writeLCDCommand(0x0050, 0); 
        writeLCDCommand(0x0051, 239); 
        // Начальный и конечный адреса по вертикали
        writeLCDCommand(0x0052, 0); 
        writeLCDCommand(0x0053, 319);		
	clr(0,320,0,240,BLACK);
	//Calibrate();
  CalibrDataRead();
	
	//DrawGrid(GREED_BEGINX,GREED_BEGINX,GREED_STEP,GREED_COLOR,GREED_BACKGROUND);
//TIM3_init();

   while(1)
	{
		
		
	ReadTouchXY();
	touch_correct(X,Y);

	//sprintf(s,"%4d %4d",d_in_x, d_in_y);
	//TFT_ShowString(0,100,(u8*)s, BRED);	
	//plotpx(d_in_x, d_in_y, BLUE);

}
}
