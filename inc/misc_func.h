#ifndef MISC_FUNC_H
#define MISC_FUNC_H

#include "stm32f10x.h"

extern u8  fac_us;
extern u16 fac_ms;

void delay(uint32_t delayTime);
void delay_ms(u16 nms);
void delay_us(u32 Nus);


#endif
