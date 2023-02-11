#include "bts_task_io.h"

#define DEBUG_PRINT 2

void BTS_RTOS_Task_IO(void *p)
{
	EventBits_t event;
	uint8_t array_test_sensor_data[4] = {0x41,0x4b,0x00,0x00};
	uint8_t array_test_device_data[2] = { 0x03, 0x01};
	while(1)
	{
#if (DEBUG_PRINT == 1)
		if(vru16_uart3_flag_rx == 1)
		{
			vru16_uart3_flag_rx = 0;
//			BTS_SYSTEM_Debug_DataDetect();	
		}
#elif (DEBUG_PRINT == 2)
	//If IO has event from SYS, IO sends event to SYS  
	event = xEventGroupWaitBits(EventTask.Sys.To_IO.EventGroup, EventTask.Sys.To_IO.EventBit_FlagHasData, pdTRUE, pdFALSE, 10);
	if(event & EventTask.Sys.To_IO.EventBit_FlagHasData)
	{
//		xSemaphoreTake(MutexTask.IO.Lock_SendQueue, portMAX_DELAY);
//		xQueueSend(QueueTask.IO.To_Sys.Queue_Device, (void *)&array_test_device_data,10);
//		xQueueSend(QueueTask.IO.To_Sys.Queue_Sensor, (void *)&array_test_sensor_data,10);
		SmartBTS_USART0_SendString("Event SYS to IO done\n");
		xEventGroupSetBits(EventTask.IO.To_Sys.EventGroup, EventTask.IO.To_Sys.EventBit_FlagHasData);
//		xSemaphoreGive(MutexTask.IO.Lock_SendQueue);
	}
#endif
		vTaskDelay(1/portTICK_RATE_MS);
	}
}

