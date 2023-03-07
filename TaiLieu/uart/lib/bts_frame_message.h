
#ifndef _FRAME_MESSAGE_H
#define _FRAME_MESSAGE_H


#include <stdint.h>
#include "bts_utilities.h"


#define RETRUN_ERROR -1

/* Byte bắt đầu (mặc định) */
#define START_BYTE 0xAA55

/* Độ dài mặc định không đổi [Start(2byte) + TypeMessage(2byte) + Length(2byte) = 6byte] */
#define DEFAULT_BYTE                            6 


#define DEFAULT_BYTE_CHECKSUM                   2           //  2byte checksum
#define DEFAULT_MAX_NUMBER_SENSOR               10          //  support max 10 sensors

#define DEFAULT_BYTE_CONTROL_DEVICE             2          //  List Device: 1byte, Value: 1 byte - 0 to 255
typedef struct
{
    uint16_t Start;
    uint16_t TypeMessage;
    uint16_t Length;
    uint8_t Data[(DEFAULT_MAX_NUMBER_SENSOR*4)];
    uint16_t Crc;
}messageFrameMsg_t;


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


class FrameMessage
{

public:
	int16_t CreateMessage(messageFrameMsg_t datain, uint8_t *dataout);
    int16_t DetectMessage(uint8_t *dataint, messageFrameMsg_t *dataout);
    int16_t DebugMessage(uint8_t *dataint);
private:
	uint16_t CheckSum(uint8_t *buf, uint8_t len);
	
};

#endif 
