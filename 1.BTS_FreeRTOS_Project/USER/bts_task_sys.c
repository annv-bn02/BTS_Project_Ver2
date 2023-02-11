#include "bts_task_sys.h"

#define DEBUG_PRINT 2

void BTS_RTOS_Task_SYS(void *p)
{
	EventBits_t event;
	
	uint8_t* array_test_sensor_data;
	uint8_t* array_test_device_data;
	float data_sensor; 
	while(1)
	{
#if (DEBUG_PRINT == 1)
		
		if(vru16_uart3_flag_rx == 1)
		{
			vru16_uart3_flag_rx = 0;
//			xSemaphoreTake(MutexTask.SYS.Lock_Debug_Detect, portMAX_DELAY);
			BTS_SYSTEM_Debug_DataDetect();	
//			xSemaphoreGive(MutexTask.SYS.Lock_Debug_Detect);
		}
		
#elif (DEBUG_PRINT == 2)
		//If SYS has event from UART, SYS sends event to IO 
		event = xEventGroupWaitBits(EventTask.Uart.To_Sys.EventGroup, EventTask.Uart.To_Sys.EventBit_FlagHasData, pdTRUE, pdFALSE, 10);
		if(event & EventTask.Uart.To_Sys.EventBit_FlagHasData)
		{
			SmartBTS_USART0_SendString("Event UART to SYS done\n");
			xEventGroupSetBits(EventTask.Sys.To_IO.EventGroup, EventTask.Sys.To_IO.EventBit_FlagHasData);
		}
		
		//If SYS has event from IO, SYS sends event to UART 
		event = xEventGroupWaitBits(EventTask.IO.To_Sys.EventGroup, EventTask.IO.To_Sys.EventBit_FlagHasData, pdTRUE, pdFALSE, 10);
		if(event & EventTask.IO.To_Sys.EventBit_FlagHasData)
		{
//			xSemaphoreTake(MutexTask.SYS.Lock_SendQueue, portMAX_DELAY);
	
//			if(xQueueReceive(QueueTask.IO.To_Sys.Queue_Sensor, &array_test_sensor_data, 10 ))
//			{
//				data_sensor = Bts_Convert_From_Bytes_To_Float(array_test_sensor_data[0],array_test_sensor_data[1],array_test_sensor_data[2],array_test_sensor_data[3]);
//				BTS_Sys_Debug("%f ",data_sensor);
//				xQueueSend(QueueTask.Sys.To_Uart.Queue_Sensor, &array_test_sensor_data, 10);
//			}
			SmartBTS_USART0_SendString("Event IO to SYS done\n");
			xEventGroupSetBits(EventTask.Sys.To_Uart.EventGroup, EventTask.Sys.To_Uart.EventBit_FlagHasData);
//			xSemaphoreGive(MutexTask.SYS.Lock_SendQueue);
		}
//		if(xQueueReceive(QueueTask.IO.To_Sys.Queue_Device, &array_test_device_data, 10 ))
//		{
//			xQueueSend(QueueTask.Sys.To_Uart.Queue_Device, &array_test_device_data, 10);
//		}
		

#endif
		vTaskDelay(1/portTICK_RATE_MS);
	}
	
}
