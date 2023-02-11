/*
  ******************************************************************************
  * @file		test.h                                                              *
  * @author	    Nguyen Van An                                                *
  * @date		23/04/2022                                                      *
  ******************************************************************************
*/
	
#ifndef __TEST__
#define __TEST__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stdio.h"
#include "bts_sys.h"
void Print_Data_Message(uint8_t *arr, uint8_t length);
void Print_Data_Detect_Device(deviceFrameMsg_t frame);
void Print_Data_Detect_Sensor(sensorFrameMsg_t frame);

void test_BTS_Message_Create_Frame_Sensor_Request_NTC_Indoor(void);
void test_BTS_Message_Create_Frame_Sensor_Request_NTC_Outdoor(void);
void test_BTS_message_Create_Frame_Sensor_Request_Door(void);
void test_BTS_Message_Create_Frame_Sensor_Request_Smoke(void);
void test_BTS_Message_Create_Frame_Sensor_Request_Water(void);
void test_BTS_Message_Create_Frame_Sensor_Request_Conditioner_Status(void);

void test_BTS_Message_Create_Frame_Sensor_Response_NTC_Indoor(void);
void test_BTS_Message_Create_Frame_Sensor_Response_NTC_Outdoor(void);
void test_BTS_message_Create_Frame_Sensor_Response_Door(void);
void test_BTS_Message_Create_Frame_Sensor_Response_Smoke(void);
void test_BTS_Message_Create_Frame_Sensor_Response_Water(void);
void test_BTS_Message_Create_Frame_Sensor_Response_Conditioner_Status(void);

void test_BTS_Message_Create_Frame_Device_Request_Conditioner(void);
void test_BTS_Message_Create_Frame_Device_Request_Fan(void);
void test_BTS_Message_Create_Frame_Device_Request_Lamp(void);

void test_BTS_Message_Create_Frame_Device_Response_Success_Conditioner(void);
void test_BTS_Message_Create_Frame_Device_Response_Success_Fan(void);
void test_BTS_Message_Create_Frame_Device_Response_Success_Lamp(void);

void test_BTS_Message_Create_Frame_Device_Response_Error_Conditioner(void);
void test_BTS_Message_Create_Frame_Device_Response_Error_Fan(void);
void test_BTS_Message_Create_Frame_Device_Response_Error_Lamp(void);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
