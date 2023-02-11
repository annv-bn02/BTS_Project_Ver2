 
/*
  ******************************************************************************
  * @file		Uart.h                                                              *
  * @author	Nguyen Quang Bien                                                  *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef __DEBUG_DETECT__
#define __DEBUG_DETECT__
#include "stm32f10x.h"
#include "stdio.h"
#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stdio.h"
#include "bts_message.h"
void BTS_Debug_Detect_Frame(void);
void Print_Data_Detect_Device(deviceFrameMsg_t frame);
void Print_Data_Detect_Sensor(sensorFrameMsg_t frame);
	 
#ifdef __cplusplus
}
#endif

#endif

