
#include "bts_utilities.h"
#include <ctime>
using namespace std;

SerialPort serialtest("/dev/ttyUSB0", B9600, 1);
GetMessage getmessage;
FrameMessage framemessage;

uint8_t CreateFrame_Test(uint8_t *arr);
uint8_t Detectrame_Test(void);

int main()
{
   uint8_t array[100];
    if(CreateFrame_Test(array))
    {
        framemessage.DebugMessage(array);
    }
    /*
    uint16_t sizeof_message;
    uint8_t arr[100];

    clock_t start = clock();
  
    clock_t end = clock();
    double elapsed_time = double(20000) / CLOCKS_PER_SEC * 1000;
    std::cout << "Elapsed time: " << elapsed_time << " ms\n";

    for(int i=0; i<10; i++)
    {
        if(arr[i]<= 0x0f)
        {
            printf("0%x ", arr[i]);
        }
        else
        {
            printf("%x ", arr[i]);
        }
      
    }
    printf("\n");

    serialtest.writebyte(arr, 10);

    while(1)
    {
        int32_t checkdata = serialtest.Available();

        if(checkdata > 0)
        {
			getmessage.GetMessages(serialtest.readbyte(), arr);
			if(getmessage.IsMessage(sizeof_message) == 1)
			{
				printf("\n-------------------------- (%d) -------------------------- \n", sizeof_message);
				//framemessage.Debug_Data(arr);
				cout << "-------------------------- (END) -------------------------- \n";
			}
        }
        getmessage.TimeOut();
        
    }
    */
    return 0;
}


uint8_t CreateFrame_Test(uint8_t *arr)
{
    messageFrameMsg_t datain;
    int16_t size_data;

    printf("\n--------------------(Start Create)--------------------\n");
    /*---------------------------------(Start)---------------------------------*/
    datain.Start = START_BYTE;
    /*---------------------------------(TypeMessage)---------------------------------*/
    datain.TypeMessage = TYPE_MESSAGE_UPDATE_SENSOR;
    /*---------------------------------(Data)---------------------------------*/
    if(datain.TypeMessage == TYPE_MESSAGE_UPDATE_SENSOR)
    {
        uint16_t count_arr = 0;
        for(int i = 0; i < 10; i++)
        {
            data_format_float_bytes input_convert;
            input_convert.data_float = 20.5 + i;
            datain.Data[count_arr] = input_convert.bytes[3];
            datain.Data[count_arr+1] = input_convert.bytes[2];
            datain.Data[count_arr+2] = input_convert.bytes[1];
            datain.Data[count_arr+3] = input_convert.bytes[0];
            count_arr += 4;
        }
    }
    else  if(datain.TypeMessage == TYPE_MESSAGE_UPDATE_DEVICE)
    {
        for(int i = 0; i < 40; i++)
        {
            datain.Data[i] = i;
        }
    }
    else if(datain.TypeMessage == TYPE_MESSAGE_CONTROL_DEVICE)
    {
        datain.Data[0] = 0x30;
        datain.Data[1] = 0x50;
    }
    /*---------------------------------(Data)---------------------------------*/
    size_data = framemessage.CreateMessage(datain, arr);
    cout << "size: " << size_data << endl;
    if(size_data > 0)
    {
        for(int i = 0; i < size_data; i++)
        {
            if(arr[i]<= 0x0f)
            {
                printf("0%x ", arr[i]);
            }
            else
            {
                printf("%x ", arr[i]);
            }
        }
        printf("\n--------------------(Create Done)--------------------\n");
        return 1;
    }
   
    return 0;
}
