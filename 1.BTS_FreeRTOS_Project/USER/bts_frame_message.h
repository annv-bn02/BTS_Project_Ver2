
#ifndef _FRAME_MESSAGE_H
#define _FRAME_MESSAGE_H

#ifdef __cplusplus
    extern "C" {
#endif

#include <stdint.h>
#include "bts_sys.h"

#define RETRUN_ERROR -1

/* Byte bắt đầu (mặc định) */
#define START_BYTE 0xAA55

/* Độ dài mặc định không đổi [Start(2byte) + TypeMessage(2byte) + Length(2byte) = 6byte] */
#define DEFAULT_BYTE                            6 


#define DEFAULT_BYTE_CHECKSUM                   2           							//  2byte checksum
#define DEFAULT_MAX_NUMBER_SENSOR               10          							//  support max 10 sensors
#define DEFAULT_MAX_NUMBER_DEVICE               (DEFAULT_MAX_NUMBER_SENSOR*4)          	//  support max 10 device

#define DEFAULT_BYTE_CONTROL_DEVICE             2          								//  List Device: 1byte, Value: 1 byte - 0 to 255
typedef struct
{
    uint16_t Start;
    uint16_t TypeMessage;
    uint16_t Length;
    uint8_t Data[(DEFAULT_MAX_NUMBER_SENSOR*4)];
    uint16_t Crc;
}messageFrameMsg_t;

typedef struct
{
	uint8_t name;
	uint8_t value;
}controlDeviceFrame_t;

typedef struct
{
	uint8_t data[DEFAULT_MAX_NUMBER_DEVICE];
}updateDeviceFrame_t;

typedef struct
{
	float data[DEFAULT_MAX_NUMBER_SENSOR];
}updateSensorFrame_t;

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
    DEVICE_CONDITIONER 		        = 0x01,
    DEVICE_FAN 				        = 0x02,
    DEVICE_LAMP 				    = 0x03,
}listDevice_e;


typedef enum
{
    TYPE_MESSAGE_UPDATE_SENSOR 	    = 0x0001,
    TYPE_MESSAGE_UPDATE_DEVICE 	    = 0x0002,
    TYPE_MESSAGE_CONTROL_DEVICE 	= 0x0003,
} typeMessageSensor_e;


    uint8_t* Bts_Convert_From_Float_To_Bytes(float data);

    int16_t DetectMessage(uint8_t *dataint, messageFrameMsg_t *dataout);
    int16_t DebugMessage(uint8_t *dataint);

	int16_t BTS_Frame_Creat_Sensor(float *datain, uint8_t *dataout);
	int16_t BTS_Frame_Creat_Device(uint8_t *datain, uint8_t *dataout);
	int16_t BTS_Frame_Control_Device(uint8_t name, uint8_t value, uint8_t *dataout);
	
#ifdef __cplusplus
}
#endif

#endif 
