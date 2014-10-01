#ifndef TOUCH_H
#define TOUCH_H	

#define CMD_RDX 0X90  //0B10010000
#define CMD_RDY	0XD0  //0B11010000
#define TCS   (1<<7)  // PB7   
#define TCS_SET(x) GPIOB->BSRR=(x ? GPIO_BSRR_BS7:GPIO_BSRR_BR7)
#define PEN  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define RESCALE_FACTOR 1000000

#include "stm32f10x.h"	 
#include "misc_func.h"  
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "primitives.h"
#include "stdio.h"
#include "stm32f10x_exti.h"	
#include "sram.h"


//u16 SPI_SendByte(u8 byte);
//u16 SPI_ReadByte(u8 a);
u8 read_once(void);
extern unsigned int X,Y;
void Calibrate (void);
extern unsigned char a,_it0,_it1,_it2,_it3;
void touch_correct (uint32_t in_x,uint32_t in_y);
void CalibrDataRead (void);
u8 ReadTouchXY (void);
extern int32_t d_in_x, d_in_y; 
extern char s[10];




#endif
