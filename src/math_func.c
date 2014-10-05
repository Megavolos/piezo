#include "math_func.h"

uint32_t abs_diff (int32_t x, int32_t y)
{
	if (x>=y) {return (uint32_t)(x-y);}
	else return (uint32_t)(y-x);
} 

void swap_u16(u16 *a,u16 *b)
{
	u16 *t;
	*t = *a;
  *a = *b;
  *b = *t;
}

void swap_int(int *a,int *b)
{
	int *t;
	*t = *a;
  *a = *b;
  *b = *t;
}


void swap_float(float *a,float *b)
{
	float *t;
	*t = *a;
  *a = *b;
  *b = *t;
}


int tg_line(int32_t x1, int32_t x2, int32_t y1,int32_t y2)
{
	if (y2 != y1) 
	{
		return ((x2-x1)/(y2-y1));
  }
  else
  {
		return 0;
  }
 
}
