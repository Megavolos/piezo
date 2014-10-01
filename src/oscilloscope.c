#include "oscilloscope.h"

uint16_t ADC_Data, ADC_DataPrev; 
int y;
void oscilloscope(unsigned int scalex, unsigned int color)
{
	
	ADC_DataPrev=ADC_Data;				
	
	
	
		ADC1->CR2 |= ADC_CR2_SWSTART;
		while((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC)
		{
		}
	
	
	ADC_Data = ADC1->DR;	
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET){};
//	ADC_Data=ADC_GetConversionValue(ADC1);
	ADC_Data=ADC_Data/scalex;		
	DrawLine(y,y+1,ADC_DataPrev,ADC_Data,color);
	//delay(90000);
	y++;
	if(y==320)
	{
		y=0;
//		DrawGrid(GREED_STEP,GREED_COLOR,GREED_BACKGROUND);

	}
}

