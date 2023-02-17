#include "bts_sensor_ntc.h"

void Sensor_NTC_Init(void)
{
	BTS_Config_GPIO_Sensor(SENSOR_NTC1);
	BTS_Config_GPIO_Sensor(SENSOR_NTC2);
}

uint8_t Sensor_NTC_Get(void)
{
	return 1;
}
