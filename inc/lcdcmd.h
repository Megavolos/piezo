#ifndef LCDCMD_H
#define LCDCMD_H
	
	#include "stm32f10x.h"
	/*******************************************************************/
// Определяем адреса, по которым будем записывать данные
// Для записи данных
	#define LCD_DATA    			    ((uint32_t)0x60020000)    
	// Для записи команд
	#define LCD_REG   		  	    ((uint32_t)0x60000000)	
	void writeLCDCommand(unsigned int reg,unsigned int value);
	void writeLCDData(unsigned int data);	
	
	
#endif
