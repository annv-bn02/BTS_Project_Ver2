#include "bts_task_io.h"

#define TEST_UPDATE 1

static void GetQueue_UartToIo(void);
static void SendEventUpdate_SysToIo(void);
static void SendEventControl_SysToIo(void);
static void SendQueueDevice_IoToUart(void);
static void SendQueueSensor_IoToUart(void);
static void Counter_Send_Data(uint16_t *counter);
static void GetEventControl_SysToIo(EventBits_t event);
void BTS_RTOS_Task_IO(void *p)
{
	EventBits_t event;
	uint16_t counter_send = 0;
	BTS_Device_Init();
	while(1)
	{	
#if (TEST_UPDATE == 1)
		counter_send++;
		Counter_Send_Data(&counter_send);
#endif
		GetEventControl_SysToIo(event);
		vTaskDelay(TIME_DELAY_TASK_IO);
	}
}

static void GetQueue_UartToIo(void)
{
	controlDeviceFrame_t data_frame;
	if(xQueueReceive(QueueTask.Uart.To_Io.Queue_Device, (void *)&data_frame, TIME_WAIT_QUEUE))
	{
		BTS_Sys_Debug("Name : %d - Value : %d\n",data_frame.name, data_frame.value);
		if(data_frame.value != 0)
		{
			if(BTS_Device_Control(data_frame.name - 1, device_status[data_frame.name - 1].on))
			{
				BTS_Sys_Debug("Control success");
			}
			else
			{
				BTS_Sys_Debug("Control error");
			}
		}
		else
		{
			if(BTS_Device_Control(data_frame.name - 1, device_status[data_frame.name - 1].off))
			{
				BTS_Sys_Debug("Control success");
			}
			else
			{
				BTS_Sys_Debug("Control error");
			}
		}
	}
}

static void SendEventUpdate_SysToIo(void)
{
	xEventGroupSetBits(EventTask.IO.To_Sys.EventGroup, EventTask.IO.To_Sys.EventBit_FlagHasDataUpdate);
	SendQueueDevice_IoToUart();
	SendQueueSensor_IoToUart();
}

static void SendEventControl_SysToIo(void)
{
	xEventGroupSetBits(EventTask.IO.To_Sys.EventGroup, EventTask.IO.To_Sys.EventBit_FlagHasData);
	SendQueueDevice_IoToUart();
	SendQueueSensor_IoToUart();
}

static void SendQueueDevice_IoToUart(void)
{
	uint8_t count = 0;
	uint8_t array_data_device[DEFAULT_MAX_NUMBER_DEVICE];
	updateDeviceFrame_t frame_update_device;
	for(count = 0; count < DEFAULT_MAX_NUMBER_DEVICE; count++)
	{
		array_data_device[count] = count;
	}
	
	for(count = 0; count < DEFAULT_MAX_NUMBER_DEVICE; count++)
	{
		frame_update_device.data[count] = array_data_device[count];
	}
	xSemaphoreTake(MutexTask.IO.Lock_Queue, portMAX_DELAY);
	xQueueSend(QueueTask.IO.To_Uart.Queue_Device, (void *)&frame_update_device, TIME_WAIT_QUEUE);
	xSemaphoreGive(MutexTask.IO.Lock_Queue);
}

static void SendQueueSensor_IoToUart(void)
{
	uint8_t count = 0;
	float array_data_sensor[DEFAULT_MAX_NUMBER_SENSOR];
	updateSensorFrame_t frame_update_sensor;
	for(count = 0; count < DEFAULT_MAX_NUMBER_SENSOR; count++)
	{
		array_data_sensor[count] = 25.5 + count;
	}
	
	for(count = 0; count < DEFAULT_MAX_NUMBER_SENSOR; count++)
	{
		frame_update_sensor.data[count] = array_data_sensor[count];
	}
	xSemaphoreTake(MutexTask.IO.Lock_Queue, portMAX_DELAY);
	xQueueSend(QueueTask.IO.To_Uart.Queue_Device, (void *)&frame_update_sensor, TIME_WAIT_QUEUE);
	xSemaphoreGive(MutexTask.IO.Lock_Queue);
}

static void Counter_Send_Data(uint16_t *counter)
{
	if(*counter == COUNTER_UPDATE_DATA)
	{
		SendEventUpdate_SysToIo();
		*counter = 0;
	}
}

static void GetEventControl_SysToIo(EventBits_t event)
{
	//If IO has event from SYS, IO sends event to SYS  
	event = xEventGroupWaitBits(EventTask.Sys.To_IO.EventGroup, EventTask.Sys.To_IO.EventBit_FlagHasData, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask.Sys.To_IO.EventBit_FlagHasData)
	{
		BTS_Sys_Debug("Event Control SYSTEM to IO done\n");
		GetQueue_UartToIo();
		SendEventControl_SysToIo();
	}
}
