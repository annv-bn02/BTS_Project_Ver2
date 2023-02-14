#include "bts_task_io.h"

static void GetQueue_UartToIo(void);
static void SendEvent_IoToSys(void);
static void GetEvent_SysToIo(EventBits_t event);
static void SendQueueDevice_IoToUart(const uint8_t *data);
static void SendQueueSensor_IoToUart(const float *data);
void BTS_RTOS_Task_IO(void *p)
{
	EventBits_t event;
	while(1)
	{
		GetEvent_SysToIo(event);
		vTaskDelay(TIME_DELAY_TASK_IO/portTICK_RATE_MS);
	}
}

static void GetQueue_UartToIo(void)
{
	controlDeviceFrame_t data_frame;
	if(xQueueReceive(QueueTask.Uart.To_Io.Queue_Device, (void *)&data_frame, TIME_WAIT_QUEUE))
	{
		BTS_Sys_Debug("Name : %d - Value : %d\n",data_frame.name, data_frame.value);
	}
}

static void SendEvent_IoToSys(void)
{
	uint8_t count = 0;
	uint8_t array_data_device[DEFAULT_MAX_NUMBER_DEVICE];
	float array_data_sensor[DEFAULT_MAX_NUMBER_SENSOR];
	for(count = 0; count < DEFAULT_MAX_NUMBER_DEVICE; count++)
	{
		array_data_device[count] = count;
	}
	
	for(count = 0; count < DEFAULT_MAX_NUMBER_SENSOR; count++)
	{
		array_data_sensor[count] = 20.5 + count;
	}
	xEventGroupSetBits(EventTask.IO.To_Sys.EventGroup, EventTask.IO.To_Sys.EventBit_FlagHasData);
	SendQueueDevice_IoToUart(array_data_device);
	SendQueueSensor_IoToUart(array_data_sensor);
}

static void GetEvent_SysToIo(EventBits_t event)
{
	//If IO has event from SYS, IO sends event to SYS  
	event = xEventGroupWaitBits(EventTask.Sys.To_IO.EventGroup, EventTask.Sys.To_IO.EventBit_FlagHasData, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask.Sys.To_IO.EventBit_FlagHasData)
	{
		BTS_Sys_Debug("Event SYSTEM to IO done\n");
		GetQueue_UartToIo();
		SendEvent_IoToSys();
	}
}

static void SendQueueDevice_IoToUart(const uint8_t *data)
{
	uint8_t count = 0;
	updateDeviceFrame_t frame_update_device;
	for(count = 0; count < DEFAULT_MAX_NUMBER_DEVICE; count++)
	{
		frame_update_device.data[count] = data[count];
	}
	xQueueSend(QueueTask.IO.To_Uart.Queue_Device, (void *)&frame_update_device, TIME_WAIT_QUEUE);
}

static void SendQueueSensor_IoToUart(const float *data)
{
	uint8_t count = 0;
	updateSensorFrame_t frame_update_sensor;
	for(count = 0; count < DEFAULT_MAX_NUMBER_SENSOR; count++)
	{
		frame_update_sensor.data[count] = 20.5 + count;
	}
	xQueueSend(QueueTask.IO.To_Uart.Queue_Device, (void *)&frame_update_sensor, TIME_WAIT_QUEUE);
}
