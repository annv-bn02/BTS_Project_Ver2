#include "bts_sys.h"
#include <stdarg.h>

volatile eventListValue_t EventTask;
volatile mutexListValue_t MutexTask;
volatile queueListValue_t QueueTask;

void BTS_Sys_SendChar(char data);
void BTS_Sys_SendString(char *text);

void BTS_Sys_EventInit(void)
{
	EventTask.Sys.To_Uart.EventGroup = xEventGroupCreate();
	EventTask.Sys.To_Uart.EventBit_FlagHasData = (1<<0);
	
	EventTask.Sys.To_IO.EventGroup = xEventGroupCreate();
	EventTask.Sys.To_IO.EventBit_FlagHasData = (2<<0);
	
	EventTask.Uart.To_Sys.EventGroup = xEventGroupCreate();
	EventTask.Uart.To_Sys.EventBit_FlagHasData = (3<<0);
	
	EventTask.IO.To_Sys.EventGroup = xEventGroupCreate();
	EventTask.IO.To_Sys.EventBit_FlagHasData = (4<<0);
	
}

void BTS_SysMutexInit(void)
{
	MutexTask.SYS.Lock_SendChar = xSemaphoreCreateMutex();
	MutexTask.SYS.Lock_SendQueue = xSemaphoreCreateMutex();
	MutexTask.IO.Lock_SendQueue = xSemaphoreCreateMutex();
	MutexTask.UART.Lock_SendQueue = xSemaphoreCreateMutex();
}

void BTS_Sys_QueueInit(void)
{
	QueueTask.Uart.To_Sys.Queue_Device = xQueueCreate(2 , sizeof(uint8_t));
	
	QueueTask.Sys.To_Uart.Queue_Sensor = xQueueCreate(4, sizeof(uint8_t));
	QueueTask.Sys.To_Uart.Queue_Device = xQueueCreate(2, sizeof(uint8_t));
	
	QueueTask.IO.To_Sys.Queue_Sensor = xQueueCreate(4, sizeof(uint8_t));
	QueueTask.IO.To_Sys.Queue_Device = xQueueCreate(2, sizeof(uint8_t));
}

void BTS_Sys_Init(void)
{
	BTS_SysMutexInit();
	BTS_Sys_EventInit();
	BTS_Sys_QueueInit();
}

void BTS_Sys_Debug(const char *format, ...) 
{
	char arr[100];
	va_list args;
	va_start(args, format);
	while (*format != '\0') 
	{
		if (*format == '%') 
		{
			format++;
			switch (*format)
			{
				case 'd':
					sprintf(arr, "%d", va_arg(args, int));
					BTS_Sys_SendString(arr);
					break;
				case 's':
					sprintf(arr, "%s", va_arg(args, char *));
					BTS_Sys_SendString(arr);
					break;
				case 'f':
					sprintf(arr, "%f", va_arg(args, float));
					BTS_Sys_SendString(arr);
					break;
				case 'x':
					sprintf(arr, "%x", va_arg(args, int));
					BTS_Sys_SendString(arr);
					break;
				default:
					BTS_Sys_SendString("printf error!!!\n");
					break;
			}
		} 
		else 
		{
		  BTS_Sys_SendChar(*format);
		}
		format++;
	}
	va_end(args);
}

void BTS_Sys_SendChar(char data)
{
	xSemaphoreTake(MutexTask.SYS.Lock_SendChar, portMAX_DELAY);
	SmartBTS_USART3_SendChar((uint8_t)data);
	xSemaphoreGive(MutexTask.SYS.Lock_SendChar);
}

void BTS_Sys_SendString(char *text)
{
	while(*text)
	{
		BTS_Sys_SendChar((uint8_t)*text);
		text++;
	}
}

void BTS_SYSTEM_Debug_DataDetect(void)
{
	sensorFrameMsg_t bts_frame_sensor_value_debug;
	deviceFrameMsg_t bts_frame_device_value_debug;
	uint16_t type_message;
	type_message = Bts_Convert_From_Bytes_To_Uint16(vru8_bts_uart_fsm_array_out[2],vru8_bts_uart_fsm_array_out[3]);
	switch(type_message)
	{
		case TYPE_MESSAGE_SENSOR_REQUEST:
			BTS_Message_Detect_Frame_Sensor(vru8_bts_uart_fsm_array_out, &bts_frame_sensor_value_debug);
			break;
		case TYPE_MESSAGE_SENSOR_RESPONSE:
			BTS_Message_Detect_Frame_Sensor(vru8_bts_uart_fsm_array_out, &bts_frame_sensor_value_debug);
			break;
		case TYPE_MESSAGE_DEVICE_REQUEST:
			BTS_Message_Detect_Frame_Device(vru8_bts_uart_fsm_array_out, &bts_frame_device_value_debug);
			break;
		case TYPE_MESSAGE_DEVICE_RESPONSE:
			BTS_Message_Detect_Frame_Device(vru8_bts_uart_fsm_array_out, &bts_frame_device_value_debug);
			break;
	}
	if(type_message <= 2)
	{
		float data_float;
		BTS_Sys_Debug("\n-----------------------------------------------------\n");
		BTS_Sys_Debug("\t\t\tFrame Sensor Detect \n");
		BTS_Sys_Debug("StartFrame  : %x\n", bts_frame_sensor_value_debug.StartFrame);
		BTS_Sys_Debug("TypeMessage : %x\n", bts_frame_sensor_value_debug.TypeMessage);
		BTS_Sys_Debug("TypeDevice  : %x\n", bts_frame_sensor_value_debug.TypeDevice);
		BTS_Sys_Debug("LengthData  : %d\n", bts_frame_sensor_value_debug.LengthData);
		switch (bts_frame_sensor_value_debug.TypeMessage)
		{
		case TYPE_MESSAGE_SENSOR_REQUEST:
			BTS_Sys_Debug("SensorName  : %x\n", bts_frame_sensor_value_debug.SensorName);
			break;
		case TYPE_MESSAGE_SENSOR_RESPONSE:
			if (bts_frame_sensor_value_debug.TypeDevice == TYPE_SENSOR_NTC)
			{
				data_float = Bts_Convert_From_Bytes_To_Float(bts_frame_sensor_value_debug.Data[0], bts_frame_sensor_value_debug.Data[1],
				bts_frame_sensor_value_debug.Data[2], bts_frame_sensor_value_debug.Data[3]);
				BTS_Sys_Debug("Data        : %f \n", data_float);
			}
			else     
			{
				BTS_Sys_Debug("Data        : %d\n", bts_frame_sensor_value_debug.Data[0]);
			}
			break;
		}
		BTS_Sys_Debug("CheckFrame  : %x\n", bts_frame_sensor_value_debug.CheckFrame);
		BTS_Sys_Debug("-----------------------------------------------------\n");
	}
	else
	{
		BTS_Sys_Debug("\n-----------------------------------------------------\n");
		BTS_Sys_Debug("\t\t\tFrame Device Detect \n");
		BTS_Sys_Debug("StartFrame   :%x\n", bts_frame_device_value_debug.StartFrame);
		BTS_Sys_Debug("TypeMessage  :%x\n", bts_frame_device_value_debug.TypeMessage);
		BTS_Sys_Debug("TypeDevice   :%x\n", bts_frame_device_value_debug.TypeDevice);
		BTS_Sys_Debug("LengthData   :%d\n", bts_frame_device_value_debug.LengthData);
		BTS_Sys_Debug("DeviceName   :%x\n", bts_frame_device_value_debug.DeviceName);
		BTS_Sys_Debug("CommandType  :%x\n", bts_frame_device_value_debug.CommandType);
		if (bts_frame_device_value_debug.TypeMessage == TYPE_MESSAGE_DEVICE_RESPONSE)
		{
			BTS_Sys_Debug("StatusDevice :%x\n", bts_frame_device_value_debug.StatusDevice);
		}
		BTS_Sys_Debug("CheckFrame   :%x\n", bts_frame_device_value_debug.CheckFrame);
		BTS_Sys_Debug("-----------------------------------------------------\n");
	}
}
