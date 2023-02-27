#include "bts_config_gpio.h"

#define NOT_USE_ADC 0

define_GpioPin_t gpio_pin_sensor[SIZE_LIST_SENSOR]=
{
	{GPIOC, GPIO_MODE_AIN,    GPIO_OSPEED_MAX,   GPIO_PIN_1, ADC_CHANNEL_11,  "NTC1 Pin"},
	{GPIOC, GPIO_MODE_AIN,    GPIO_OSPEED_MAX,   GPIO_PIN_2, ADC_CHANNEL_12,  "NTC2 Pin"},	
	{GPIOA, GPIO_MODE_IPU,    GPIO_OSPEED_50MHZ, GPIO_PIN_14, NOT_USE_ADC,  "Door Pin"},
	{GPIOC, GPIO_MODE_IPU,    GPIO_OSPEED_50MHZ, GPIO_PIN_4, NOT_USE_ADC, "Smoke Pin"},
	{GPIOA, GPIO_MODE_IPU,    GPIO_OSPEED_50MHZ, GPIO_PIN_15, NOT_USE_ADC, "Water Pin"},
	{GPIOC, GPIO_MODE_IPU,    GPIO_OSPEED_50MHZ, GPIO_PIN_10, NOT_USE_ADC, "AirCondition status Pin"},
};

define_GpioPin_t gpio_pin_device[SIZE_LIST_DEVICE]=
{
	{GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4, NOT_USE_ADC,  "AirCondition control Pin"},
	{GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6, NOT_USE_ADC, "Fan Pin"},
	{GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5, NOT_USE_ADC, "LAMP Pin"},	
};

define_status_device_t device_status[SIZE_LIST_DEVICE] =
{
	{0, 1},
	{1, 0},
	{0, 1},
};

/**
 * @brief Config for the gpio pin of sensor.
 * 
 * @param gpio_element : the position of the sensor in the sensor list.
 */
void BTS_Config_GPIO_Sensor(uint8_t gpio_element)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_AF);
	gpio_pin_remap_config(GPIO_SWJ_NONJTRST_REMAP, ENABLE);
	gpio_init(gpio_pin_sensor[gpio_element].port, gpio_pin_sensor[gpio_element].mode, gpio_pin_sensor[gpio_element].speed, gpio_pin_sensor[gpio_element].pin);
}

/**
 * @brief Config for the gpio pin of device.
 * 
 * @param gpio_element : the position of the device in the device list.
 */
void BTS_Config_GPIO_Device(uint8_t gpio_element)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_AF);
	gpio_pin_remap_config(GPIO_SWJ_NONJTRST_REMAP, ENABLE);
	gpio_init(gpio_pin_device[gpio_element].port, gpio_pin_device[gpio_element].mode, gpio_pin_device[gpio_element].speed, gpio_pin_device[gpio_element].pin);
}
