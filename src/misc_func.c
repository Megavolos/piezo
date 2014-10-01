#include "misc_func.h"
u8  fac_us;
u16 fac_ms;

void delay(uint32_t delayTime)
{	
    uint32_t i;
    for(i = 0; i < delayTime; i++);
}

void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//К±јдјУФШ
	SysTick->VAL =0x00;           //ЗеїХјЖКэЖч
	SysTick->CTRL=0x01 ;          //їЄКјµ№Кэ  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//µИґэК±јдµЅґп   
	SysTick->CTRL=0x00;       //№Ш±ХјЖКэЖч
	SysTick->VAL =0X00;       //ЗеїХјЖКэЖч	  	    
}   
//СУК±us								   
void delay_us(u32 Nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=Nus*fac_us; //К±јдјУФШ	  		 
	SysTick->VAL=0x00;        //ЗеїХјЖКэЖч
	SysTick->CTRL=0x01 ;      //їЄКјµ№Кэ 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//µИґэК±јдµЅґп   
	SysTick->CTRL=0x00;       //№Ш±ХјЖКэЖч
	SysTick->VAL =0X00;       //ЗеїХјЖКэЖч	    
}


