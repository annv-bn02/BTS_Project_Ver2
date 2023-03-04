#include "bts_task_io.h"

#define TEST_NTC 1
static void GetQueue_UartToIo(void);
static void SendEventUpdate_IoToSys(void);
static void SendEventControl_IoToSys(void);
static void SendQueueDevice_IoToUart(void);
static void SendQueueSensor_IoToUart(void);
static void Counter_Send_Data(uint16_t *counter);
static void GetEventControl_SysToIo(EventBits_t event);

/**
 * @brief IO Task funtion of RTOS system
 * 
 * @param p 
 */
void BTS_RTOS_Task_IO(void *p)
{
	EventBits_t event;
	uint16_t counter_send = 0;
	uint16_t counter_get_NTC = 0;
	BTS_Device_Init();
	Sensor_Smoke_Init();
	Sensor_NTC_Init();
	while(1)
	{	
		counter_get_NTC++;
		if(Sensor_Smoke_Get() == 1)
		{
			BTS_Sys_Debug("\nSmoke Warning\n");
		}
#if TEST_NTC 
		if(counter_get_NTC == 200)
		{
			counter_get_NTC = 0;
			Sensor_NTC_Get();
		}
#endif
		counter_send++;
		Counter_Send_Data(&counter_send);
		GetEventControl_SysToIo(event);
		vTaskDelay(TIME_DELAY_TASK_IO);
	}
}

/**
 * @brief When receive data control device, control device
 * 
 */
static void GetQueue_UartToIo(void)
{
	controlDeviceFrame_t data_frame;
	if(xQueueReceive(QueueTask.Uart.To_Io.Queue_Device, (void *)&data_frame, TIME_WAIT_QUEUE))
	{
		if(data_frame.name <= SIZE_LIST_DEVICE && data_frame.name > 0)
		{
#if DEBUG_ALL
			BTS_Sys_Debug("Name : %d - Value : %d\n",data_frame.name, data_frame.value);
#endif
			if(data_frame.value != 0)
			{
				if(BTS_Device_Control(data_frame.name - 1, device_status[data_frame.name - 1].on))
				{
#if DEBUG_ALL
					BTS_Sys_Debug("Control success");
#endif	
				}
				else
				{
#if DEBUG_ALL
					BTS_Sys_Debug("Control error");
#endif	
				}
			}
			else
			{
				if(BTS_Device_Control(data_frame.name - 1, device_status[data_frame.name - 1].off))
				{
#if DEBUG_ALL
					BTS_Sys_Debug("Control success");
#endif
				}
				else
				{
#if DEBUG_ALL
					BTS_Sys_Debug("Control error");
#endif
				}
			}
		}
	}
}

/**
 * @brief Send event update data of device and sensor to sys task
 * 
 */
static void SendEventUpdate_IoToSys(void)
{
	xEventGroupSetBits(EventTask.IO.To_Sys.EventGroup, EventTask.IO.To_Sys.EventBit_FlagHasDataUpdate);
	SendQueueDevice_IoToUart();
	SendQueueSensor_IoToUart();
}

/**
 * @brief Send event control data of device and sensor to sys task
 * 
 */
static void SendEventControl_IoToSys(void)
{
	xEventGroupSetBits(EventTask.IO.To_Sys.EventGroup, EventTask.IO.To_Sys.EventBit_FlagHasData);
	SendQueueDevice_IoToUart();
	SendQueueSensor_IoToUart();
}

/**
 * @brief Send data of device to transmission task
 * 
 */
static void SendQueueDevice_IoToUart(void)
{
	uint8_t count = 0;
	uint8_t array_data_device[DEFAULT_MAX_NUMBER_DEVICE];
	updateDeviceFrame_t frame_update_device;
	for(count = 0; count < DEFAULT_MAX_NUMBER_DEVICE; count++)
	{
		array_data_device[count] = count + 10;
	}
	
	for(count = 0; count < DEFAULT_MAX_NUMBER_DEVICE; count++)
	{
		frame_update_device.data[count] = array_data_device[count];
	}
	xSemaphoreTake(MutexTask.IO.Lock_Queue, portMAX_DELAY);
	xQueueSend(QueueTask.IO.To_Uart.Queue_Device, (void *)&frame_update_device, TIME_WAIT_QUEUE);
	xSemaphoreGive(MutexTask.IO.Lock_Queue);
}

/**
 * @brief Send data of sensor to transmission task
 * 
 */
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

/**
 * @brief Counter for automatic update data of device and sensor
 * 
 */
static void Counter_Send_Data(uint16_t *counter)
{
	if(*counter == COUNTER_UPDATE_DATA)
	{
		SendEventUpdate_IoToSys();
		*counter = 0;
	}
}

/**
 * @brief Get event control device from sys task
 * 
 * @param event 
 */
static void GetEventControl_SysToIo(EventBits_t event)
{
	//If IO has event from SYS, IO sends event to SYS  
	event = xEventGroupWaitBits(EventTask.Sys.To_IO.EventGroup, EventTask.Sys.To_IO.EventBit_FlagHasData, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask.Sys.To_IO.EventBit_FlagHasData)
	{
#if DEBUG_ALL
		BTS_Sys_Debug("Event Control SYSTEM to IO done\n");
#endif
		GetQueue_UartToIo();
		SendEventControl_IoToSys();
	}
	
}
