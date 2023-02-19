#include "bts_sensor_smoke.h"

uint16_t count_smoke_stt, smoke_flag_old, smoke_flag_new = 0;
void Sensor_Smoke_Init(void)
{
	BTS_Config_GPIO_Sensor(SENSOR_SMOKE);
}	

uint8_t Sensor_Smoke_Get(void)
{
	smoke_flag_old = smoke_flag_new;
	if(gpio_input_bit_get(gpio_pin_sensor[SENSOR_SMOKE].port, gpio_pin_sensor[SENSOR_SMOKE].pin) == 0)
	{
		count_smoke_stt++;
		if(count_smoke_stt > 2)
		{
			count_smoke_stt = 3;
			smoke_flag_new = 1;
		}
	}
	else
	{
		smoke_flag_new = 0;
		count_smoke_stt = 0;
	}
	
	if(smoke_flag_new == 1 && smoke_flag_old == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
