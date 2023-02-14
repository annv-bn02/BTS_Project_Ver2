#include "bts_task_sys.h"


static void SendEvent_SysToIo(void);
static void SendEvent_SysToUart(void);
static void GetEvent_IoToSys(EventBits_t event);
static void GetEvent_UartToSys(EventBits_t event);

void BTS_RTOS_Task_SYS(void *p)
{
	EventBits_t event;
	while(1)
	{
		GetEvent_UartToSys(event);
		GetEvent_IoToSys(event);
		vTaskDelay(TIME_DELAY_TASK_SYS/portTICK_RATE_MS);
	}
	
}

static void SendEvent_SysToIo(void)
{
	xEventGroupSetBits(EventTask.Sys.To_IO.EventGroup, EventTask.Sys.To_IO.EventBit_FlagHasData);
}

static void SendEvent_SysToUart(void)
{
	xEventGroupSetBits(EventTask.Sys.To_Uart.EventGroup, EventTask.Sys.To_Uart.EventBit_FlagHasData);
}

static void GetEvent_IoToSys(EventBits_t event)
{
	//If SYS has event from IO, SYS sends event to UART 
	event = xEventGroupWaitBits(EventTask.IO.To_Sys.EventGroup, EventTask.IO.To_Sys.EventBit_FlagHasData, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask.IO.To_Sys.EventBit_FlagHasData)
	{
		BTS_Sys_Debug("Event IO to SYSTEM done\n");
		SendEvent_SysToUart();
	}
}

static void GetEvent_UartToSys(EventBits_t event)
{
	//If SYS has event from UART, SYS sends event to IO 
	event = xEventGroupWaitBits(EventTask.Uart.To_Sys.EventGroup, EventTask.Uart.To_Sys.EventBit_FlagHasData, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask.Uart.To_Sys.EventBit_FlagHasData)
	{
		BTS_Sys_Debug("Event UART to SYSTEM done\n");
		SendEvent_SysToIo();
	}
}
