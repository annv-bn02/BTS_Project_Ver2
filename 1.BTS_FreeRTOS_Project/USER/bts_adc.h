#ifndef __ADC__
#define __ADC__
	
#ifdef __cplusplus
extern "C"{
#endif
#include "bts_sys.h"

void BTS_ADC_Init(void);
uint16_t BTS_ADC_Read(void);
	
#ifdef __cplusplus
}
#endif

#endif
