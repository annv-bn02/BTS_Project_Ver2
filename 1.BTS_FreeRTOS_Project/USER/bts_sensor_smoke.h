#ifndef _SMOKE_SENSOR_
#define _SMOKE_SENSOR_

#ifdef __cplusplus
    extern "C" {
#endif

#include "bts_sys.h"

void Sensor_Smoke_Init(void);
uint8_t Sensor_Smoke_Get(void);

#ifdef __cplusplus
}
#endif

#endif
