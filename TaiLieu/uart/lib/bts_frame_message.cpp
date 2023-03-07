
#include "bts_frame_message.h"

uint8_t array_size_data_sensor[SIZE_LIST_SENSOR] = {4, 4, 1, 1, 1, 1};

static uint16_t Bytes_To_Uint16(uint8_t data1, uint8_t data2)
{
    data_format_uint8_16_t input_convert;
    input_convert.bytes[0] = data1;
    input_convert.bytes[1] = data2;

    return input_convert.data_uint16;
}

static float Bytes_To_Float(uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3)
{
    data_format_float_bytes input_convert;
    input_convert.bytes[3] = data0;
    input_convert.bytes[2] = data1;
    input_convert.bytes[1] = data2;
    input_convert.bytes[0] = data3;
     return input_convert.data_float;
}
int16_t FrameMessage::CreateMessage(messageFrameMsg_t datain, uint8_t *dataout)
{
    uint8_t *data_sensor_temp;
    uint16_t count_arr = 0;
    messageFrameMsg_t *frame_message_temp;

    if(datain.Start != START_BYTE)
    {
        return RETRUN_ERROR;
    }
    
    /*dùng con trỏ frame_sensor_temp trỏ đến Sensor_DataIn*/
    frame_message_temp = &datain;
    /*ép kiểu frame_sensor_temp về kiểu uint8_t, mục đích để chuyển từ struct -> arr*/
    data_sensor_temp = (uint8_t *)frame_message_temp;

    switch (datain.TypeMessage)
    {
       
        case TYPE_MESSAGE_UPDATE_SENSOR:
        case TYPE_MESSAGE_UPDATE_DEVICE:
            /**
             * @brief 
             * if type message is updated sensor -> length is 40bytes because supported max is 10 sensors, one sensor using 4 bytes(float).
             * if type message is updated device -> length is 40bytes because supported max is 40 Devices, one device using 1 bytes(unsigned char).
             */ 
            datain.Length =  (DEFAULT_MAX_NUMBER_SENSOR * 4) + DEFAULT_BYTE_CHECKSUM;
        break;

        case TYPE_MESSAGE_CONTROL_DEVICE:
          /**
             * @brief 
             * if type message is control device -> length is 2 bytes
             * 1 byte for Name Device
             * 1 byte for value control
             */ 
            datain.Length =  DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE_CHECKSUM;
        break;
        default:
            return RETRUN_ERROR;
        break;
    }
    
    datain.Crc = CheckSum(data_sensor_temp, (DEFAULT_BYTE + (datain.Length - DEFAULT_BYTE_CHECKSUM)));

    for (count_arr = 0; count_arr < (DEFAULT_BYTE + datain.Length - DEFAULT_BYTE_CHECKSUM); count_arr++)
    {
        dataout[count_arr] = data_sensor_temp[count_arr];
    }
    /*Ghi giá trị checksum tính được vào cuối mảng*/
    dataout[count_arr]      = (datain.Crc & 0xff);
    dataout[count_arr + 1]  = ((datain.Crc >> 8) & 0xff);
    /*tăng giá trị mảng lên 2 lần vì đã thêm ở trên*/
    count_arr += 2;
    return count_arr;
}

int16_t FrameMessage::DetectMessage(uint8_t *dataint, messageFrameMsg_t *dataout)
{
    uint8_t count_temp = 0;
    messageFrameMsg_t *frame_message_temp;
    frame_message_temp = (messageFrameMsg_t*)dataint;
    /*---------------------------------(Start (2byte))---------------------------------*/
    dataout->Start = Bytes_To_Uint16(dataint[count_temp], dataint[count_temp+1]);
    if(dataout->Start != START_BYTE)
    {
        return RETRUN_ERROR;
    }
    count_temp += 2;

    /*---------------------------------(Type Message (2byte))---------------------------------*/
    dataout->TypeMessage = Bytes_To_Uint16(dataint[count_temp], dataint[count_temp+1]);
    count_temp += 2;
    switch (dataout->TypeMessage)
    {
        case TYPE_MESSAGE_UPDATE_SENSOR:
        case TYPE_MESSAGE_UPDATE_DEVICE:
    /*---------------------------------(Length Udate (2byte))---------------------------------*/
            dataout->Length =  Bytes_To_Uint16(dataint[count_temp], dataint[count_temp+1]);
            count_temp += 2;

    /*---------------------------------(Data (40byte))---------------------------------*/
            for(int i = 0; i < (dataout->Length - 2); i++)
            {
                dataout->Data[i] = dataint[count_temp];
                count_temp ++;
            }
        break;

        case TYPE_MESSAGE_CONTROL_DEVICE:
    /*---------------------------------(Length Udate (2byte))---------------------------------*/
            dataout->Length =  Bytes_To_Uint16(dataint[count_temp], dataint[count_temp+1]);
            count_temp += 2;

    /*---------------------------------(Data (40byte))---------------------------------*/
            for(int i=0; i < (dataout->Length - 2); i++)
            {
                if(i <= 1)
                {
                    dataout->Data[i] = dataint[count_temp];
                }
                else
                {
                    dataout->Data[i] = 0x00;
                }
                count_temp ++;
            }
        break;
        default:
            return RETRUN_ERROR;
        break;
    }
    /*---------------------------------(Check Sum(2byte))---------------------------------*/
    uint16_t check_sum = CheckSum(dataint, (DEFAULT_BYTE + (dataout->Length - DEFAULT_BYTE_CHECKSUM)));
    dataout->Crc = Bytes_To_Uint16(dataint[count_temp], dataint[count_temp+1]);

    if(check_sum != dataout->Crc)
    {
        return RETRUN_ERROR;
    }
    count_temp += 2;
    return count_temp;
}


int16_t FrameMessage::DebugMessage(uint8_t *dataint)
{
    messageFrameMsg_t dataout;
    int16_t size_data = FrameMessage::DetectMessage(dataint, &dataout);
    printf("\n--------------------(Size: %d)--------------------\n", size_data);
    printf("Start       : %x\n", dataout.Start);
    printf("TypeMessage : %x\n", dataout.TypeMessage);
    if((dataout.TypeMessage == TYPE_MESSAGE_UPDATE_SENSOR) )
    {
        uint16_t count_arr = 0;
        for(int i = 0; i < ((size_data - 8)/4); i++)
        {
            
            printf("%f ", Bytes_To_Float(dataout.Data[count_arr], dataout.Data[count_arr+1], dataout.Data[count_arr+2], dataout.Data[count_arr+3]));
            count_arr += 4;
        }
        printf("\n");
    }
    else if (dataout.TypeMessage == TYPE_MESSAGE_UPDATE_DEVICE)
    {
        for(int i = 0; i < ((size_data - 8)); i++)
        {
            
            printf("%d ", (dataout.Data[i]));
        }
        printf("\n");
    }
    else
    {
        printf("Name DV     : %d\n", dataout.Data[0]);
        printf("Valuce      : %d\n", dataout.Data[0]);
    }
    printf("Check sum   : %x\n", dataout.Crc);
}

uint16_t FrameMessage::CheckSum(uint8_t *buf, uint8_t len)
{
	uint16_t crc = 0xFFFF, pos = 0, i = 0;
	for (pos = 0; pos < len; pos++)
	{
		crc ^= (uint16_t)buf[pos]; // XOR byte into least sig. byte of crc
		for (i = 8; i != 0; i--)   // Loop over each bit
		{
			if ((crc & 0x0001) != 0) // If the LSB is set
			{
				crc >>= 1; // Shift right and XOR 0xA001
				crc ^= 0xA001;
			}
			else // Else LSB is not set
			{
				crc >>= 1; // Just shift right
			}
		}
	}
	return crc;
}
