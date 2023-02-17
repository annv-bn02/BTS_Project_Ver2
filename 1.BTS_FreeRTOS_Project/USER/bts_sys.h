#ifndef __SYS__
#define __SYS__
	
#ifdef __cplusplus
extern "C"{
#endif

#include "gd32f30x.h"
#include "gd32f30x_gpio.h"
#include "gd32f30x_eval.h"

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include "croutine.h"
#include "event_groups.h"
#include "stream_buffer.h"

#include "string.h"

#include "bts_uart.h"
#include "bts_uart3.h"
#include "bts_task_io.h"
#include "bts_task_sys.h"
#include "bts_task_msg_transmission.h"

#include "bts_event_define.h"
#include "bts_mutex_define.h"

#include "bts_queue_define.h"
#include "bts_convert.h"
#include "bts_frame_message.h"
#include "bts_get_message.h"
#include "bts_config_gpio.h"

#include "bts_automatic_control.h"
#include "bts_device.h"

#include "bts_sensor_airconditioner.h"
#include "bts_sensor_smoke.h"
#include "bts_sensor_door.h"
#include "bts_sensor_ntc.h"
#include "bts_sensor_water.h"

extern volatile eventListValue_t EventTask;
extern volatile mutexListValue_t MutexTask;
extern volatile queueListValue_t QueueTask;

#define TIME_DELAY_TASK_MSG 	1
#define TIME_DELAY_TASK_IO 		1
#define TIME_DELAY_TASK_SYS 	1

#define TIME_WAIT_EVENT_ALL		9
#define TIME_WAIT_QUEUE			(portTickType)0
/*
				Time update data
	TIME_DELAY_TASK_IO = TIME_DELAY_TASK_SYS + TIME_WAIT_EVENT_ALL(1 get event) = 1 + 9*1 = 10
	TIME_UPDATE_DATA = (COUNTER_UPDATE_DATA * TIME_DELAY_TASK_IO) = (2000 * 10) = 20000 mS 
*/
#define COUNTER_UPDATE_DATA 		2000 	

/*
				TimeOut Get Message
	TIME_DELAY_TASK_MSG = TIME_DELAY_TASK_MSG + TIME_WAIT_EVENT_ALL(2 get event) = 1 + 9*2 = 19
	TIMEOUT GET MESSAGE = (COUNTER_TIMEOUT * TIME_DELAY_TASK_MSG) = (2 * 19) = 38 mS 
*/
#define COUNTER_TIMEOUT 	2 	

#define DEBUG_TASK_MSG_NEW_MESSAGE 1
#define DEBUG_TASK_MSG_CREATE_MESSAGE_DEVICE 1
#define DEBUG_TASK_MSG_CREATE_MESSAGE_SENSOR 1



void BTS_Sys_EventInit(void);
void BTS_Sys_Init(void);

void BTS_SysMutexInit(void);
void BTS_Sys_QueueInit(void);
	
void BTS_Sys_Debug(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
