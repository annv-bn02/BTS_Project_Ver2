#include "bts_sensor_door.h"

void Sensor_Door_Init(void)
{
	BTS_Config_GPIO_Sensor(SENSOR_DOOR);
}
uint8_t Sensor_Door_Get(void)
{
	return 1;
}
