#ifndef ___CONFIG_DEVICE__
#define ___CONFIG_DEVICE__
	
#ifdef __cplusplus
extern "C"{
#endif

#include "bts_sys.h"

#define SIZE_LIST_SENSOR 6
typedef enum 
{
    SENSOR_NTC1 				 = 0,
    SENSOR_NTC2 				    ,
    SENSOR_DOOR 				    ,
    SENSOR_SMOKE 				    ,
    SENSOR_WATER 				    ,
    SENSOR_CONDITIONER_STATUS 	    ,
}listSensor_e;

#define SIZE_LIST_DEVICE 3
typedef enum 
{
    DEVICE_CONDITIONER 		        = 0x00,
    DEVICE_FAN 				        = 0x01,
    DEVICE_LAMP 				    = 0x02,
}listDevice_e;

typedef struct
{
	uint32_t port;
	uint32_t mode;
	uint32_t speed; 
	uint32_t pin;
	char *name;
}define_GpioPin_t;

typedef struct
{
	uint8_t on;
	uint8_t off;
}define_status_device_t;

extern define_GpioPin_t gpio_pin_sensor[SIZE_LIST_SENSOR];
extern define_GpioPin_t gpio_pin_device[SIZE_LIST_DEVICE];
extern define_status_device_t device_status[SIZE_LIST_DEVICE];

void BTS_Config_GPIO_Sensor(uint8_t gpio_element);
void BTS_Config_GPIO_Device(uint8_t gpio_element);

#ifdef __cplusplus
}
#endif

#endif
