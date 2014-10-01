#include "math_func.h"

uint32_t abs_diff (int32_t x, int32_t y)
{
	if (x>=y) {return (uint32_t)(x-y);}
	else return (uint32_t)(y-x);
} 
