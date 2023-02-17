#include "bts_sensor_smoke.h"

void Sensor_Smoke_Init(void)
{
	BTS_Config_GPIO_Sensor(SENSOR_SMOKE);
}	

uint8_t Sensor_Smoke_Get(void)
{
	return 1;
}
