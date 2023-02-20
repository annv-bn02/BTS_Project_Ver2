#ifndef __ADC__
#define __ADC__
	
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include "gd32f30x.h"
#include "gd32f30x_adc.h"

void BTS_ADC_Init(void);
uint16_t BTS_ADC_Read(void);
	
#ifdef __cplusplus
}
#endif

#endif