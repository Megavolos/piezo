#include "init.h"



void TIM3_init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM3->PSC=100;
	TIM3->ARR=5000;
	TIM3->DIER |= TIM_DIER_UIE; 
	TIM3->CR1 |= TIM_CR1_CEN; 
	NVIC_EnableIRQ(TIM3_IRQn);
	
}

void LCD_init()
{
    FSMC_NORSRAMInitTypeDef  fsmc;
    FSMC_NORSRAMTimingInitTypeDef fsmcTiming;
    GPIO_InitTypeDef  gpio;
	
		//ADC_InitTypeDef adc_ini;
 
    // Включаем тактирование портов
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE , ENABLE);

    // И тактирование FSMC					   	 
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    RCC->CFGR &= ~RCC_CFGR_ADCPRE;
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV2;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    // Инициализация пинов, задейстованных в общении по FSMC
    gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
 
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio);
 
    gpio.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
 
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio);
 
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOD, &gpio);
 
    // Здесь у нас Reset
    gpio.GPIO_Pin = GPIO_Pin_1 ; 	 
    GPIO_Init(GPIOE, &gpio);  	
 
    // CS
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Pin = GPIO_Pin_7; 
    GPIO_Init(GPIOD, &gpio);
 
    // RS
    gpio.GPIO_Pin = GPIO_Pin_11 ; 	  
    GPIO_Init(GPIOD, &gpio); 
		

    // CS -> 1
    // Reset -> 0
    // RD -> 1
    // RW -> 1
    GPIO_SetBits(GPIOD, GPIO_Pin_7);			
    GPIO_ResetBits(GPIOE, GPIO_Pin_1);		
    GPIO_SetBits(GPIOD, GPIO_Pin_4);		    
    GPIO_SetBits(GPIOD, GPIO_Pin_5);			
 
    // Настройка FSMC
    fsmcTiming.FSMC_AddressSetupTime = 0x02;
    fsmcTiming.FSMC_AddressHoldTime = 0x00;
    fsmcTiming.FSMC_DataSetupTime = 0x05;
    fsmcTiming.FSMC_BusTurnAroundDuration = 0x00;
    fsmcTiming.FSMC_CLKDivision = 0x00;
    fsmcTiming.FSMC_DataLatency = 0x00;
    fsmcTiming.FSMC_AccessMode = FSMC_AccessMode_B;
 
    fsmc.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    fsmc.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    fsmc.FSMC_MemoryType = FSMC_MemoryType_NOR;
    fsmc.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    fsmc.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    fsmc.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    fsmc.FSMC_WrapMode = FSMC_WrapMode_Disable;
    fsmc.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    fsmc.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    fsmc.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    fsmc.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    fsmc.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    fsmc.FSMC_ReadWriteTimingStruct = &fsmcTiming;
    fsmc.FSMC_WriteTimingStruct = &fsmcTiming;	   
 
    FSMC_NORSRAMInit(&fsmc); 
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);	
	 // Глобальный Reset дисплея
    GPIO_ResetBits(GPIOE, GPIO_Pin_1);
    delay(0x0FFFFF);					   
    GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 	 
    delay(0x0FFFFF);
 
    // Пляски с  бубном от китайских товарищей	
    writeLCDCommand(0x0000,0x0001);
    delay(10);
 
    writeLCDCommand(0x0015,0x0010);
    writeLCDCommand(0x0011,0x0040);
    writeLCDCommand(0x0010,0x1628);
    writeLCDCommand(0x0012,0x0000);
    writeLCDCommand(0x0013,0x104d);
    delay(10);
    writeLCDCommand(0x0012,0x0010);
    delay(10);
    writeLCDCommand(0x0010,0x2620);
    writeLCDCommand(0x0013,0x344d);
    delay(10);
 
    writeLCDCommand(0x0001,0x0000);
    writeLCDCommand(0x0002,0x0300);
    writeLCDCommand(0x0003,0x1038);
    writeLCDCommand(0x0008,0x0604);
    writeLCDCommand(0x0009,0x0000);
    writeLCDCommand(0x000A,0x0008);
 
    writeLCDCommand(0x0041,0x0002);
    writeLCDCommand(0x0060,0x2700);
    writeLCDCommand(0x0061,0x0001);
    writeLCDCommand(0x0090,0x0182);
    writeLCDCommand(0x0093,0x0001);
    writeLCDCommand(0x00a3,0x0010);
    delay(10);
 
    // Настройки гаммы
    writeLCDCommand(0x30,0x0000);		
    writeLCDCommand(0x31,0x0502);		
    writeLCDCommand(0x32,0x0307);		
    writeLCDCommand(0x33,0x0305);		
    writeLCDCommand(0x34,0x0004);		
    writeLCDCommand(0x35,0x0402);		
    writeLCDCommand(0x36,0x0707);		
    writeLCDCommand(0x37,0x0503);		
    writeLCDCommand(0x38,0x1505);		
    writeLCDCommand(0x39,0x1505);
    delay(10);
 
    // Включение дисплея
    writeLCDCommand(0x0007,0x0001);
    delay(10);
    writeLCDCommand(0x0007,0x0021);
    writeLCDCommand(0x0007,0x0023);
    delay(10);
    writeLCDCommand(0x0007,0x0033);
    delay(10);
    writeLCDCommand(0x0007,0x0133);
}

void SPI_init (void)
{	
//инициализация SPI1 
	SPI_InitTypeDef  SPI_InitStructure;	
    GPIO_InitTypeDef  gpio;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 ,ENABLE);
	//Настраиваем SPI1 : 	 SCK  | 		MISO		|	   MOSI	 ;
	//Для тачпала:     		 CLK 	| 		DOUT 		| 	 DIN	 ;
	//Для SRAM:     		  	C	  |   		Q		  |  		D	   ;
		gpio.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		gpio.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOA, &gpio);
	//Настраиваем PA4 для Chip Select (CS) SRAM	
		gpio.GPIO_Pin = GPIO_Pin_4;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		gpio.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOA, &gpio);
	//Заранее выключаем память
		 NotSelect_Flash();
	//Задаем режим работы SPI1	 
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(SPI1, &SPI_InitStructure);
  
  /* Enable SPI2  */
  SPI_Cmd(SPI1, ENABLE);   
}

void ADC_init (void)
{
    GPIO_InitTypeDef  gpio;

	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpio); 
	
	ADC1->SQR3 = ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_3;
	ADC1->CR2 = ADC_CR2_EXTSEL_0 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_2 | ADC_CR2_EXTTRIG;
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->CR2 |= ADC_CR2_RSTCAL;
	while ((ADC1->CR2 & ADC_CR2_RSTCAL) == ADC_CR2_RSTCAL)
	{
	}
	
	ADC1->CR2 |= ADC_CR2_CAL;
	while ((ADC1->CR2 & ADC_CR2_RSTCAL) == ADC_CR2_CAL)	
	{
	}

}
 
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFIOEN,ENABLE);
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the EXTI9_5 Interrupt */
  

  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn  ;

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0f;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0f;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	

  
} 

 void delay_init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;//СЎФсДЪІїК±ЦУ HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}				
 
/*******************************************************************/
void EXTI_init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);		 //Прерывание с тачскрина

  /* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}
