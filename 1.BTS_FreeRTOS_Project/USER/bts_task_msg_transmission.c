#include "bts_task_msg_transmission.h"



void BTS_RTOS_Task_Msg(void *p)
{
	EventBits_t event;
	uint8_t* array_test_sensor_data;
	uint8_t* array_test_device_data;
	float data_sensor;
	while(1)
	{
		if(vru16_uart3_flag_rx == 1)
		{
			vru16_uart3_flag_rx = 0;
			TimeOut_Wait = 0;
			BTS_SYSTEM_Debug_DataDetect();	
		}
		if(vru16_uart0_flag_rx == 1)
		{
			vru16_uart0_flag_rx = 0;
			SmartBTS_USART0_SendString("Start test event\n");
			test_BTS_Message_Create_Frame_Sensor_Request_NTC_Indoor();
			xEventGroupSetBits(EventTask.Uart.To_Sys.EventGroup, EventTask.Uart.To_Sys.EventBit_FlagHasData);
		}
		
		//If UART has event from SYS, end event progress;
		event = xEventGroupWaitBits(EventTask.Sys.To_Uart.EventGroup, EventTask.Sys.To_Uart.EventBit_FlagHasData, pdTRUE, pdFALSE, 10);
		if(event & EventTask.Sys.To_Uart.EventBit_FlagHasData)
		{
//			xSemaphoreTake(MutexTask.UART.Lock_SendQueue, portMAX_DELAY);
//			if(xQueueReceive(QueueTask.Sys.To_Uart.Queue_Sensor, &array_test_sensor_data, 10))
//			{
//				data_sensor = Bts_Convert_From_Bytes_To_Float(array_test_sensor_data[0],array_test_sensor_data[1],array_test_sensor_data[2],array_test_sensor_data[3]);
//				BTS_Sys_Debug("%f ",data_sensor);
//			}
			SmartBTS_USART0_SendString("Event IO to SYS done\n");
			SmartBTS_USART0_SendString("End test event\n");
//			xSemaphoreGive(MutexTask.UART.Lock_SendQueue);
		}
//		if(xQueueReceive(QueueTask.Sys.To_Uart.Queue_Device, &array_test_device_data,10))
//		{
//			SmartBTS_USART0_SendString("Receive data device from sys\n");
//		}

		
		if(TimeOut_Wait == 1)
		{
			if(TimeOut_Count == 20)
			{
				TimeOut_Wait = 0;
				SmartBTS_USART3_FSM_TimeOut();
			}
			TimeOut_Count++;
		}
		vTaskDelay(1/portTICK_RATE_MS);
	}
}


