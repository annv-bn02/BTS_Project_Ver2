#ifndef __TIMER__
#define __TIMER__
	
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include "gd32f30x.h"
#include "gd32f30x_timer.h"	

void Timer_Init(void);
void Timer_delay(uint32_t time);
	
#ifdef __cplusplus
}
#endif

#endif
