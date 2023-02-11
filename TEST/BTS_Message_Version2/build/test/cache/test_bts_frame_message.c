#include "src/bts_frame_message.h"
#include "src/bts_utilities.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
uint8_t CreateFrame_Test(uint8_t *arr);

uint8_t Detectrame_Test(void);



void setUp(void)

{

}



void tearDown(void)

{

}



void test_BTS_Frame_Message_Updata_Sensor(void)

{

    messageFrameMsg_t datain;

    int16_t size_data;

    uint8_t array_out[100];

    int8_t array_test[100] = {0x55, 0xaa, 0x01, 0x00, 0x2a, 0x00, 0x41, 0xa4, 0x00, 0x00, 0x41, 0xac, 0x00, 0x00, 0x41, 0xb4,

     0x00, 0x00, 0x41, 0xbc, 0x00, 0x00, 0x41, 0xc4, 0x00, 0x00, 0x41, 0xcc, 0x00, 0x00, 0x41, 0xd4, 0x00, 0x00, 0x41, 0xdc,

     0x00, 0x00, 0x41, 0xe4, 0x00, 0x00, 0x41, 0xec, 0x00, 0x00};

    printf("\n--------------------(Start Create)--------------------\n");



    datain.Start = 0xAA55;



    datain.TypeMessage = TYPE_MESSAGE_UPDATE_SENSOR;



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



    size_data = CreateMessage(datain, array_out);



    for(int i = 0; i < 46;i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((array_test[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_UINT8);

    }



    printf("size: %d\n",size_data);

    if(size_data > 0)

    {

        for(int i = 0; i < size_data; i++)

        {

            if(array_out[i]<= 0x0f)

            {

                printf("0%x ", array_out[i]);

            }

            else

            {

                printf("%x ", array_out[i]);

            }

        }

        printf("\n--------------------(Create Done)--------------------\n");

    }

}



void test_BTS_Frame_Message_Updata_Device(void)

{

    messageFrameMsg_t datain;

    int16_t size_data;

    uint8_t array_out[100];

    int8_t array_test[100] = {0x55, 0xaa, 0x02, 0x00, 0x2a, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,

     0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,

     0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27};

    printf("\n--------------------(Start Create)--------------------\n");



    datain.Start = 0xAA55;



    datain.TypeMessage = TYPE_MESSAGE_UPDATE_DEVICE;



    for(int i = 0; i < 40; i++)

    {

        datain.Data[i] = i;

    }



    size_data = CreateMessage(datain, array_out);



    for(int i = 0; i < 46;i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((array_test[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_UINT8);

    }



    printf("size: %d\n",size_data);

    if(size_data > 0)

    {

        for(int i = 0; i < size_data; i++)

        {

            if(array_out[i]<= 0x0f)

            {

                printf("0%x ", array_out[i]);

            }

            else

            {

                printf("%x ", array_out[i]);

            }

        }

        printf("\n--------------------(Create Done)--------------------\n");

    }

}
