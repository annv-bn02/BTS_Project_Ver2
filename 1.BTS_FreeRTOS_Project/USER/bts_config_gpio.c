#include "bts_config_gpio.h"

define_GpioPin_t gpio_pin_sensor[SIZE_LIST_SENSOR]=
{
	{GPIOC, GPIO_MODE_AIN,    GPIO_OSPEED_MAX,   GPIO_PIN_0,  "NTC1 Pin"},
	{GPIOC, GPIO_MODE_AIN,    GPIO_OSPEED_MAX,   GPIO_PIN_1,  "NTC2 Pin"},	
	{GPIOA, GPIO_MODE_IPU,    GPIO_OSPEED_50MHZ, GPIO_PIN_14, "Door Pin"},
	{GPIOC, GPIO_MODE_IPU,    GPIO_OSPEED_50MHZ, GPIO_PIN_11, "Smoke Pin"},
	{GPIOA, GPIO_MODE_IPU,    GPIO_OSPEED_50MHZ, GPIO_PIN_15, "Water Pin"},
	{GPIOC, GPIO_MODE_IPU,    GPIO_OSPEED_50MHZ, GPIO_PIN_10, "AirCondition status Pin"},
};

define_GpioPin_t gpio_pin_device[SIZE_LIST_DEVICE]=
{
	{GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4,  "AirCondition control Pin"},
	{GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6,  "Fan Pin"},
	{GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5,  "LAMP Pin"},	
};

define_status_device_t device_status[SIZE_LIST_DEVICE] =
{
	{0, 1},
	{1, 0},
	{0, 1},
};

void BTS_Config_GPIO_Sensor(uint8_t gpio_element)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_AF);
	gpio_pin_remap_config(GPIO_SWJ_NONJTRST_REMAP, ENABLE);
	gpio_init(gpio_pin_sensor[gpio_element].port, gpio_pin_sensor[gpio_element].mode, gpio_pin_sensor[gpio_element].speed, gpio_pin_sensor[gpio_element].pin);
}

void BTS_Config_GPIO_Device(uint8_t gpio_element)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_AF);
	gpio_pin_remap_config(GPIO_SWJ_NONJTRST_REMAP, ENABLE);
	gpio_init(gpio_pin_device[gpio_element].port, gpio_pin_device[gpio_element].mode, gpio_pin_device[gpio_element].speed, gpio_pin_device[gpio_element].pin);
}
