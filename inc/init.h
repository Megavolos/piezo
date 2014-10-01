	#ifndef INIT_H
	#define INIT_H

	#include "stm32f10x_gpio.h"
	#include "stm32f10x_fsmc.h"
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_adc.h"
	#include "stm32f10x.h"
	#include "stm32f10x_tim.h"
	#include "stm32f10x_exti.h"	
	#include "misc.h"
	#include "misc_func.h"
	#include "lcdcmd.h"
	#include "stm32f10x_spi.h"
	// Макросы выбора чипа памяти. Активный ноль. 
		#define Select_Flash()     GPIO_ResetBits(GPIOA, GPIO_Pin_4)
		#define NotSelect_Flash()    GPIO_SetBits(GPIOA, GPIO_Pin_4)
	


	void TIM3_init(void);
	void delay(uint32_t delayTime);
	void NVIC_Configuration(void);
	void SPI_init (void);
	void ADC_init (void);
	void LCD_init(void);
	void EXTI_init(void);
	void delay_init(u8 SYSCLK);




	#endif
