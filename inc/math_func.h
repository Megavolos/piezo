#ifndef MATH_FUNC_H
#define MATH_FUNC_H
#include "stm32f10x.h"
uint32_t abs_diff (int32_t x, int32_t y);
void swap_u16(u16 *a,u16 *b);
void swap_int(int *a,int *b);
void swap_float(float *a,float *b);
int tg_line(int32_t x1, int32_t x2, int32_t y1,int32_t y2);
#endif
