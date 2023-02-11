#ifndef __QUEUE_DEFINE__
#define __QUEUE_DEFINE__
	
#ifdef __cplusplus
extern "C"{
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*-----------------------------------(QUEUE LIST TASK SYS TO )-----------------------------------*/
typedef struct
{
	xQueueHandle Queue_Sensor;
	xQueueHandle Queue_Device;
}queueSysToUart_t;

typedef struct
{
	queueSysToUart_t To_Uart;
}queueSysTo_t;

/*-----------------------------------(QUEUE LIST TASK IO TO )-----------------------------------*/
typedef struct
{
	xQueueHandle Queue_Sensor;
	xQueueHandle Queue_Device;
}queueIOToSys_t;

typedef struct
{
	queueIOToSys_t To_Sys;
}queueIOTo_t;

/*-----------------------------------(QUEUE LIST TASK UART TO )-----------------------------------*/
typedef struct
{
	xQueueHandle Queue_Device;
}queueUartToSys_t;

typedef struct
{
	queueUartToSys_t To_Sys;
}queueUartTo_t;

/*-----------------------------------(QUEUE LIST ALL)-----------------------------------*/
typedef struct
{
	queueSysTo_t  Sys;
	queueUartTo_t Uart;
	queueIOTo_t IO;
}queueListValue_t;

#ifdef __cplusplus
}
#endif

#endif
