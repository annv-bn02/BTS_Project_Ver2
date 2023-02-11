
#ifndef __MESSAGE__
#define __MESSAGE__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "bts_convert.h"

#define BTS_MESSAGE_ARR 2
    /**************************************************************************************************************************************/
    //------------------------------------------------------//
    //   Các data mặc định của FrameSensor và FrameDevice   //
    //------------------------------------------------------//

/* Byte bắt đầu (mặc định) */
#define START_BYTE 0xAA55

/* Độ dài mặc định không đổi [StartFrame(2byte) + TypeMessage(2byte) + TypeDevice(2byte) = 6byte] */
#define LENGTH_DEFAULT 6

    /**************************************************************************************************************************************/
    //-------------------------------------//
    //   Tính Length of Data của Sensor    //
    //-------------------------------------//

/* Độ dài mặc định của Length_Sensor_Request (không có data) = CRC(2byte) + SensorName(2byte) = 3byte */
#define LENGTH_SENSOR_REQUEST 4

/* Số byte data của các loại Sensor */
#define LENGTH_SENSOR_DATA_NTC 4
#define LENGTH_SENSOR_DATA_DOOR 1
#define LENGTH_SENSOR_DATA_SMOKE 1
#define LENGTH_SENSOR_DATA_WATER 1
#define LENGTH_SENSOR_DATA_CONDITIONER_STATUS 1

/* Độ dài của Length_Sensor_Response (có data) = Length_Sensor_Request (không có data) + data */
#define LENGTH_SENSOR_RESPONSE_NTC LENGTH_SENSOR_REQUEST + LENGTH_SENSOR_DATA_NTC
#define LENGTH_SENSOR_RESPONSE_DOOR LENGTH_SENSOR_REQUEST + LENGTH_SENSOR_DATA_DOOR
#define LENGTH_SENSOR_RESPONSE_SMOKE LENGTH_SENSOR_REQUEST + LENGTH_SENSOR_DATA_SMOKE
#define LENGTH_SENSOR_RESPONSE_WATER LENGTH_SENSOR_REQUEST + LENGTH_SENSOR_DATA_WATER
#define LENGTH_SENSOR_RESPONSE_CONDITIONER_STATUS LENGTH_SENSOR_REQUEST + LENGTH_SENSOR_DATA_CONDITIONER_STATUS

    /**************************************************************************************************************************************/

    //-------------------------------------//
    //   Tính Length of Data của Device    //
    //-------------------------------------//

/* Độ dài mặc định của Length_Device_Request = CRC(2byte) + CommandType(1byte) + DeviceName(2byte) = 5byte */
#define LENGTH_DEVICE_REQUEST 5

/* Độ dài mặc định của Length_Device_Response = CRC(2byte) + CommandType(1byte) + DeviceName(2byte) + StatusDevice(1byte) = 6byte */
#define LENGTH_DEVICE_RESPONSE 6

    /**************************************************************************************************************************************/
/* Khai báo tên các loại bản tin*/
#define TYPE_MASSAGE_SIZE 4 /* Độ dài phần tử có trong type_message_e */
    typedef enum
    {
        TYPE_MESSAGE_SENSOR_REQUEST = 0x0001,
        TYPE_MESSAGE_SENSOR_RESPONSE = 0x0002,
        TYPE_MESSAGE_DEVICE_REQUEST = 0x0003,
        TYPE_MESSAGE_DEVICE_RESPONSE = 0x0004,
    } type_message_e;

/* Khai báo tên các loại cảm biến*/
#define TYPE_SENSOR_SIZE 5 /* Độ dài phần tử có trong type_sensor_e */
    typedef enum
    {
        TYPE_SENSOR_NTC = 0X0001,
        TYPE_SENSOR_DOOR = 0x0002,
        TYPE_SENSOR_SMOKE = 0x0003,
        TYPE_SENSOR_WATER = 0x0004,
        TYPE_SENSOR_CONDITIONER_STATUS = 0x0005,
    } type_sensor_e;

/* Khai báo tên các loại thiết bị*/
#define TYPE_DEVICE_SIZE 3 /* Độ dài phần tử có trong type_device_e */
    typedef enum
    {
        TYPE_DEVICE_CONDITIONER = 0x0001,
        TYPE_DEVICE_FAN = 0x0002,
        TYPE_DEVICE_LAMP = 0x0003,
    } type_device_e;

/* Khai báo tên các cảm biến theo từng loại*/
#define SENSOR_NAME_NTC 2 /* Độ dài phần tử có trong sensor_name_ntc_e */
    typedef enum
    {
        SENSOR_NAME_NTC_INDOOR = 0x0001,
        SENSOR_NAME_NTC_OUTDOOR = 0x0002,
    } sensor_name_ntc_e;

#define SENSOR_NAME_DOOR 2 /* Độ dài phần tử có trong sensor_name_door_e */
    typedef enum
    {
        SENSOR_NAME_DOOR_1 = 0x0001,
        SENSOR_NAME_DOOR_2 = 0x0002,
    } sensor_name_door_e;

#define SENSOR_NAME_SMOKE 2 /* Độ dài phần tử có trong sensor_name_smoke_e */
    typedef enum
    {
        SENSOR_NAME_SMOKE_1 = 0x0001,
        SENSOR_NAME_SMOKE_2 = 0x0002,
    } sensor_name_smoke_e;

#define SENSOR_NAME_WATER 2 /* Độ dài phần tử có trong sensor_name_water_e */
    typedef enum
    {
        SENSOR_NAME_WATER_1 = 0x0001,
        SENSOR_NAME_WATER_2 = 0x0002,
    } sensor_name_water_e;

#define SENSOR_NAME_CONDITIONER_STATUS 2 /* Độ dài phần tử có trong sensor_name_conditioner_status_e */
    typedef enum
    {
        SENSOR_NAME_CONDITIONER_STATUS_1 = 0x0001,
        SENSOR_NAME_CONDITIONER_STATUS_2 = 0x0002,
    } sensor_name_conditioner_status_e;

    /**************************************************************************************************************************************/

    /* Khai báo tên các lệnh gửi đến thiết bị*/
#define COMMAND_TYPE_SIZE 4 /* Độ dài phần tử có trong type_command_e */
    typedef enum
    {
        COMMAND_TYPE_SET = 0x01,
        COMMAND_TYPE_GET = 0x02,
        COMMAND_TYPE_DUTY = 0x03,
        COMMAND_TYPE_ERROR = 0x90,
    } type_command_e;

    /* Khai báo tên các thiết bị theo từng loại*/
#define LIST_CONDITIONER_SIZE 5 /* Độ dài phần tử có trong list_conditioner_e */
    typedef enum
    {
        DEVICE_CONDITIONER_1 = 0x01,
        DEVICE_CONDITIONER_2 = 0x02,
        DEVICE_CONDITIONER_3 = 0x03,
        DEVICE_CONDITIONER_4 = 0x04,
        DEVICE_CONDITIONER_ERROR = 0x90,
    } list_conditioner_e;

#define LIST_FAN_SIZE 5 /* Độ dài phần tử có trong list_fan_e */
    typedef enum
    {
        DEVICE_FAN_1 = 0x01,
        DEVICE_FAN_2 = 0x02,
        DEVICE_FAN_3 = 0x03,
        DEVICE_FAN_4 = 0x04,
        DEVICE_FAN_ERROR = 0x90,
    } list_fan_e;

#define LIST_LAMP_SIZE 5 /* Độ dài phần tử có trong list_lamp_e */
    typedef enum
    {
        DEVICE_LAMP_1 = 0x01,
        DEVICE_LAMP_2 = 0x02,
        DEVICE_LAMP_3 = 0x03,
        DEVICE_LAMP_4 = 0x04,
        DEVICE_LAMP_ERROR = 0x90,
    } list_lamp_e;
    /* Khai báo các trạng thái của thiết bị*/
#define STATUS_DEVICE_NOT_FAN 3 /* Độ dài phần tử có trong status_device_not_fan_e */
    typedef enum
    {
        STATUS_DEVICE_ON = 0x01,
        STATUS_DEVICE_OFF = 0x00,
        STATUS_DEVICE_ERROR = 0x90,
    } status_device_not_fan_e;

#define STATUS_DEVICE_FAN 3 /* Độ dài phần tử có trong status_device_fan_e */
    typedef enum
    {
        STATUS_DEVICE_FAN_ON = 0x00,
        STATUS_DEVICE_FAN_OFF = 0x01,
        STATUS_DEVICE_FAN_ERROR = 0x90,
    } status_device_fan_e;

    /**************************************************************************************************************************************/

    //-------------------------------------//
    //          Cấu trúc bản tin           //
    //-------------------------------------//

    /* Bản tin cập nhật cảm biến */
    // StartFrame-TypeMessage-TypeDevice-LenghtData-SensorName-Data[12byte]-CheckFrame//
    typedef struct
    {
        uint16_t StartFrame;
        uint16_t TypeMessage;
        uint16_t TypeDevice;
        uint16_t LengthData;
        uint16_t SensorName;
        uint8_t Data[12];
        uint16_t CheckFrame;
    } sensorFrameMsg_t;

    /*Bản tin điều khiển*/
    // StartFrame-TypeMessage-TypeDevice-LenghtData-DeviceName-CommandType-StatusDevice-CheckFrame//
    typedef struct
    {
        uint16_t StartFrame;
        uint16_t TypeMessage;
        uint16_t TypeDevice;
        uint16_t LengthData;
        uint16_t DeviceName;
        uint8_t CommandType;
        uint8_t StatusDevice; // Nên để 2byte cho trường hợp pwm
        uint16_t CheckFrame;
    } deviceFrameMsg_t;

    /**************************************************************************************************************************************/

    uint8_t BTS_Message_Create_Frame_Sensor(sensorFrameMsg_t Sensor_DataIn, uint8_t *Sensor_DataOut);
    uint8_t BTS_Message_Create_Frame_Device(deviceFrameMsg_t Device_DataIn, uint8_t *Device_DataOut);
    uint8_t BTS_Message_Detect_Frame_Sensor(uint8_t *Sensor_DataIn, sensorFrameMsg_t *Sensor_DataOut);
    uint8_t BTS_Message_Detect_Frame_Device(uint8_t *Device_DataIn, deviceFrameMsg_t *Device_DataOut);
#ifdef __cplusplus
}
#endif

#endif
