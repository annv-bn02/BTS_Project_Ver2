#include "bts_task_sys.h"


static void SendEventControl_SysToIo(void);
static void SendEventUpdate_SysToUart(void);
static void SendEventControl_SysToUart(void);
static void GetEventUpdate_IoToSys(EventBits_t event);
static void GetEventControl_IoToSys(EventBits_t event);
static void GetEventControl_UartToSys(EventBits_t event);

void BTS_RTOS_Task_SYS(void *p)
{
	EventBits_t event;
	while(1)
	{
		GetEventUpdate_IoToSys(event);
		GetEventControl_IoToSys(event);
		GetEventControl_UartToSys(event);
		vTaskDelay(TIME_DELAY_TASK_SYS/portTICK_RATE_MS);
	}
	
}

static void SendEventControl_SysToIo(void)
{
	xEventGroupSetBits(EventTask.Sys.To_IO.EventGroup, EventTask.Sys.To_IO.EventBit_FlagHasData);
}

static void SendEventUpdate_SysToUart(void)
{
	xEventGroupSetBits(EventTask.Sys.To_Uart.EventGroup, EventTask.Sys.To_Uart.EventBit_FlagHasDataUpdate);
}

static void SendEventControl_SysToUart(void)
{
	xEventGroupSetBits(EventTask.Sys.To_Uart.EventGroup, EventTask.Sys.To_Uart.EventBit_FlagHasData);
}

static void GetEventUpdate_IoToSys(EventBits_t event)
{
	//If SYS has event from IO, SYS sends event to UART 
	event = xEventGroupWaitBits(EventTask.IO.To_Sys.EventGroup, EventTask.IO.To_Sys.EventBit_FlagHasDataUpdate, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask.IO.To_Sys.EventBit_FlagHasDataUpdate)
	{
		BTS_Sys_Debug("Event Update IO to SYSTEM done\n");
		SendEventUpdate_SysToUart();
	}
}

static void GetEventControl_IoToSys(EventBits_t event)
{
	//If SYS has event from IO, SYS sends event to UART 
	event = xEventGroupWaitBits(EventTask.IO.To_Sys.EventGroup, EventTask.IO.To_Sys.EventBit_FlagHasData, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask.IO.To_Sys.EventBit_FlagHasData)
	{
		BTS_Sys_Debug("Event Control IO to SYSTEM done\n");
		SendEventControl_SysToUart();
	}
}

static void GetEventControl_UartToSys(EventBits_t event)
{
	//If SYS has event from UART, SYS sends event to IO 
	event = xEventGroupWaitBits(EventTask.Uart.To_Sys.EventGroup, EventTask.Uart.To_Sys.EventBit_FlagHasData, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask.Uart.To_Sys.EventBit_FlagHasData)
	{
		BTS_Sys_Debug("Event Control UART to SYSTEM done\n");
		SendEventControl_SysToIo();
	}
}
