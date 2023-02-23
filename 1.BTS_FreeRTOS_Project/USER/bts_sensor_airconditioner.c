#include "bts_sensor_airconditioner.h"

void Sensor_AirCondition_Init(void)
{
	BTS_Config_GPIO_Sensor(SENSOR_CONDITIONER_STATUS);
}
	
uint8_t Sensor_AirCondition_Get(void)
{
	return 1;
}
