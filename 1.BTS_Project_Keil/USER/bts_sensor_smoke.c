#include "bts_sensor_smoke.h"

float smoke_flag = 0;

/**
 * @brief Config the smoke sensor.
 * 
 */
void Sensor_Smoke_Init(void)
{
	BTS_Config_GPIO_Sensor(SENSOR_SMOKE);
}	

/**
 * @brief Get the smoke sensor status.
 * 
 * 
 */
void Sensor_Smoke_Get(void)
{
	uint16_t count_smoke_stt;
	if(gpio_input_bit_get(gpio_pin_sensor[SENSOR_SMOKE].port, gpio_pin_sensor[SENSOR_SMOKE].pin) == 0)
	{
		count_smoke_stt++;
		if(count_smoke_stt >= COUNTER_SMOKE_WARNING)
		{
			count_smoke_stt = COUNTER_SMOKE_WARNING;
			smoke_flag = 1;
		}
	}
	else
	{
		smoke_flag = 0;
		count_smoke_stt = 0;
	}
}
