#ifndef _DEVICE_
#define _DEVICE_

#ifdef __cplusplus
    extern "C" {
#endif

#include "bts_sys.h"

void BTS_Device_Init(void);
uint8_t BTS_Device_Get(uint8_t name_device);
void BTS_Device_Control(uint8_t name_device, uint8_t status);

#ifdef __cplusplus
}
#endif

#endif
