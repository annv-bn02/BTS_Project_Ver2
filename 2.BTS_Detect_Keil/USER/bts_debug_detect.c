#include "bts_debug_detect.h"
#include "bts_convert.h"
#include "uart.h"

uint8_t array_out[50];
uint16_t type_message;
uint8_t bts_frame_lenght;

sensorFrameMsg_t frame_sensor_detect;
deviceFrameMsg_t frame_device_detect;

void BTS_Debug_Detect_Frame(void)
{
	bts_frame_lenght = UART1_Flag_Fsm();
	if(bts_frame_lenght != 0)
	{
		Flag1_Receive = 0;
		type_message = Bts_Convert_From_Bytes_To_Uint16(array_out[2],array_out[3]);
		switch(type_message)
		{
			case TYPE_MESSAGE_SENSOR_REQUEST:
				BTS_Message_Detect_Frame_Sensor(array_out, &frame_sensor_detect);
				Print_Data_Detect_Sensor(frame_sensor_detect);
				break;
			case TYPE_MESSAGE_SENSOR_RESPONSE:
				BTS_Message_Detect_Frame_Sensor(array_out, &frame_sensor_detect);
				Print_Data_Detect_Sensor(frame_sensor_detect);
				break;
			case TYPE_MESSAGE_DEVICE_REQUEST:
				BTS_Message_Detect_Frame_Device(array_out, &frame_device_detect);
				Print_Data_Detect_Device(frame_device_detect);
				break;
			case TYPE_MESSAGE_DEVICE_RESPONSE:
				BTS_Message_Detect_Frame_Device(array_out, &frame_device_detect);
				Print_Data_Detect_Device(frame_device_detect);
				break;
		}          
	} 
	bts_frame_lenght = 0;
}

/*
    @brief: Hàm in m?ng data du?c detect.
    @node: In l?n lu?t t?ng giá tr? trong struct data du?c detect c?a device .
    @param frame: Là struct data du?c detect.
    @retval: 0.
*/
void Print_Data_Detect_Device(deviceFrameMsg_t frame)
{
	printf("\n-----------------------------------------------------------------\n");
    printf("\t\t\tFrame Device Detect \n");
    printf("StartFrame   :%x\n", frame.StartFrame);
    printf("TypeMessage  :%x\n", frame.TypeMessage);
    printf("TypeDevice   :%x\n", frame.TypeDevice);
    printf("LengthData   :%d\n", frame.LengthData);
    printf("DeviceName   :%x\n", frame.DeviceName);
    printf("CommandType  :%x\n", frame.CommandType);
    if (frame.TypeMessage == TYPE_MESSAGE_DEVICE_RESPONSE)
    {
		printf("StatusDevice :%x\n", frame.StatusDevice);
    }
    printf("CheckFrame   :%x\n", frame.CheckFrame);
	printf("-----------------------------------------------------------------");
}

/*
    @brief: Hàm in m?ng data du?c detect.
    @node: In l?n lu?t t?ng giá tr? trong struct data du?c detect c?a sensor .
    @param frame: Là struct data du?c detect.
    @retval: 0.
*/
void Print_Data_Detect_Sensor(sensorFrameMsg_t frame)
{
	printf("\n-----------------------------------------------------------------\n");
    printf("\t\t\tFrame Sensor Detect \n");
    printf("StartFrame  : %x\n", frame.StartFrame);
    printf("TypeMessage : %x\n", frame.TypeMessage);
    printf("TypeDevice  : %x\n", frame.TypeDevice);
    printf("LengthData  : %d\n", frame.LengthData);
    switch (frame.TypeMessage)
    {
    case TYPE_MESSAGE_SENSOR_REQUEST:
		printf("SensorName  : %x\n", frame.SensorName);
        break;
    case TYPE_MESSAGE_SENSOR_RESPONSE:
        if (frame.TypeDevice == TYPE_SENSOR_NTC)
        {
            float data_float = Bts_Convert_From_Bytes_To_Float(frame.Data[0], frame.Data[1], frame.Data[2], frame.Data[3]);
			printf("Data        : %.3f\n", data_float);
        }
        else
        {
			printf("Data        : %d\n", frame.Data[0]);
        }
        break;
    }
    printf("CheckFrame  : %x\n", frame.CheckFrame);
	printf("-----------------------------------------------------------------");
}
