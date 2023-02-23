#ifndef _NTC_SENSOR_
#define _NTC_SENSOR_

#ifdef __cplusplus
    extern "C" {
#endif

#include "bts_sys.h"

void Sensor_NTC_Init(void);
uint8_t Sensor_NTC_Get(void);

#ifdef __cplusplus
}
#endif

#endif
