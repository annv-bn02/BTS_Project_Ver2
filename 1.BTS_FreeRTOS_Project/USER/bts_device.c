#include "bts_device.h"

void BTS_Device_Init(void)
{
	BTS_Config_GPIO_Device(DEVICE_CONDITIONER);
	BTS_Config_GPIO_Device(DEVICE_FAN);
	BTS_Config_GPIO_Device(DEVICE_LAMP);
	BTS_Device_Control(DEVICE_CONDITIONER, 1);
	BTS_Device_Control(DEVICE_FAN, 1);
	BTS_Device_Control(DEVICE_LAMP, 1);
}

uint8_t BTS_Device_Get(uint8_t name_device)
{
	return 1;
}

uint8_t BTS_Device_Control(uint8_t name_device, uint8_t status)
{
	gpio_bit_write(gpio_pin_device[name_device].port, gpio_pin_device[name_device].pin, status);
	return 1;
}