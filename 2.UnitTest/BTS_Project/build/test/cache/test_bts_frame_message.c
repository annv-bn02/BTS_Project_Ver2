#include "src/bts_convert.h"
#include "src/bts_frame_message.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
void setUp(void)

{

}



void tearDown(void)

{

}



void test_BTS_Frame_Message_Update_Sensor(void)

{

    messageFrameMsg_t dataout;

    float data_test[10];

    int16_t size_data;

    uint8_t array_out[100];

    int8_t array_test[100] = {0x55, 0xaa, 0x01, 0x00, 0x2a, 0x00, 0x41, 0xa4, 0x00, 0x00, 0x41, 0xac, 0x00, 0x00, 0x41, 0xb4,

     0x00, 0x00, 0x41, 0xbc, 0x00, 0x00, 0x41, 0xc4, 0x00, 0x00, 0x41, 0xcc, 0x00, 0x00, 0x41, 0xd4, 0x00, 0x00, 0x41, 0xdc,

     0x00, 0x00, 0x41, 0xe4, 0x00, 0x00, 0x41, 0xec, 0x00, 0x00};

    printf("\n--------------------(Start Create)--------------------\n");



    uint16_t count_arr = 0;

    for(int i = 0; i < 10; i++)

    {

        data_test[i] = 20.5 + i;

    }



    size_data = BTS_Frame_Creat_Sensor(data_test, array_out);



    for(int i = 0; i < ((10 * 4) + 6);i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((array_test[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT8);

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



        printf("\n--------------------(Start Detect)--------------------\n");

    size_data = DetectMessage(array_out, &dataout);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.Start)), (UNITY_INT)(UNITY_UINT16)((0xAA55)), (

   ((void *)0)

   ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.TypeMessage)), (UNITY_INT)(UNITY_UINT16)((TYPE_MESSAGE_UPDATE_SENSOR)), (

   ((void *)0)

   ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.Length)), (UNITY_INT)(UNITY_UINT16)(((10 * 4) + 2)), (

   ((void *)0)

   ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_UINT16);

    for(int i = 0; i < (10 * 4);i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((dataout.Data[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[6 + i])), (

       ((void *)0)

       ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_UINT8);

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.Crc)), (UNITY_INT)(UNITY_UINT16)((Bts_Convert_From_Bytes_To_Uint16(array_out[size_data - 2], array_out[size_data - 1]))), (

   ((void *)0)

   ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_UINT16);

    printf("StartFrame:  %x\n", dataout.Start);

    printf("TypeMessage: %x\n", dataout.TypeMessage);

    printf("Length:      %x\n", dataout.Length);

    printf("Data:        %x\n", dataout.Length);

    for(int i = 0; i < (10 * 4);i += 4)

    {



        printf("%f ", Bts_Convert_From_Bytes_To_Float(dataout.Data[i], dataout.Data[i+1], dataout.Data[i+2], dataout.Data[i+3]));

    }

    printf("\nChecksum:    %x\n", dataout.Crc);

    printf("\n--------------------(Detect Done)--------------------\n");

}



void test_BTS_Frame_Message_Update_Device(void)

{

    messageFrameMsg_t dataout;

    uint8_t data_test[(10*4)];

    int16_t size_data;

    uint8_t array_out[100];

    int8_t array_test[100] = {0x55, 0xaa, 0x02, 0x00, 0x2a, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,

     0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,

     0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27};

    printf("\n--------------------(Start Create)--------------------\n");



    for(int i = 0; i < (10*4); i++)

    {

        data_test[i] = i;

    }



    size_data = BTS_Frame_Creat_Device(data_test, array_out);



    for(int i = 0; i < ((10*4) + 6);i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((array_test[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(96), UNITY_DISPLAY_STYLE_UINT8);

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



    printf("\n--------------------(Start Detect)--------------------\n");

    size_data = DetectMessage(array_out, &dataout);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.Start)), (UNITY_INT)(UNITY_UINT16)((0xAA55)), (

   ((void *)0)

   ), (UNITY_UINT)(118), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.TypeMessage)), (UNITY_INT)(UNITY_UINT16)((TYPE_MESSAGE_UPDATE_DEVICE)), (

   ((void *)0)

   ), (UNITY_UINT)(119), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.Length)), (UNITY_INT)(UNITY_UINT16)(((10*4) + 2)), (

   ((void *)0)

   ), (UNITY_UINT)(120), UNITY_DISPLAY_STYLE_UINT16);

    for(int i = 0; i < (10*4);i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((dataout.Data[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[6 + i])), (

       ((void *)0)

       ), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_UINT8);

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.Crc)), (UNITY_INT)(UNITY_UINT16)((Bts_Convert_From_Bytes_To_Uint16(array_out[size_data - 2], array_out[size_data - 1]))), (

   ((void *)0)

   ), (UNITY_UINT)(125), UNITY_DISPLAY_STYLE_UINT16);

    printf("StartFrame:  %x\n", dataout.Start);

    printf("TypeMessage: %x\n", dataout.TypeMessage);

    printf("Length:      %x\n", dataout.Length);

    printf("Data:        %x\n", dataout.Length);

    for(int i = 0; i < (10*4);i++)

    {

        printf("%d ", dataout.Data[i]);

    }

    printf("\nChecksum:    %x\n", dataout.Crc);

    printf("\n--------------------(Detect Done)--------------------\n");

}





void test_BTS_Frame_Message_Control_Device(void)

{

    messageFrameMsg_t dataout;

    uint8_t name, value;

    int16_t size_data;

    uint8_t array_out[100];

    int8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x02, 0xff};

    printf("\n--------------------(Start Create)--------------------\n");



    name = DEVICE_LAMP;

    value = 255;



    size_data = BTS_Frame_Control_Device(name, value, array_out);



    for(int i = 0; i < (2 + 6);i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((array_test[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(155), UNITY_DISPLAY_STYLE_UINT8);

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



    printf("\n--------------------(Start Detect)--------------------\n");

    size_data = DetectMessage(array_out, &dataout);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.Start)), (UNITY_INT)(UNITY_UINT16)((0xAA55)), (

   ((void *)0)

   ), (UNITY_UINT)(176), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.TypeMessage)), (UNITY_INT)(UNITY_UINT16)((TYPE_MESSAGE_CONTROL_DEVICE)), (

   ((void *)0)

   ), (UNITY_UINT)(177), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.Length)), (UNITY_INT)(UNITY_UINT16)((2 + 2)), (

   ((void *)0)

   ), (UNITY_UINT)(178), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((dataout.Data[0])), (UNITY_INT)(UNITY_UINT8 )((name)), (

   ((void *)0)

   ), (UNITY_UINT)(179), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((dataout.Data[1])), (UNITY_INT)(UNITY_UINT8 )((value)), (

   ((void *)0)

   ), (UNITY_UINT)(180), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((dataout.Crc)), (UNITY_INT)(UNITY_UINT16)((Bts_Convert_From_Bytes_To_Uint16(array_out[size_data - 2], array_out[size_data - 1]))), (

   ((void *)0)

   ), (UNITY_UINT)(181), UNITY_DISPLAY_STYLE_UINT16);

    printf("StartFrame:  %x\n", dataout.Start);

    printf("TypeMessage: %x\n", dataout.TypeMessage);

    printf("Length:      %x\n", dataout.Length);

    printf("Name:        %x\n", dataout.Data[0]);

    printf("Value:       %x\n", dataout.Data[1]);

    printf("Checksum:    %x\n", dataout.Crc);

    printf("\n--------------------(Detect Done)--------------------\n");



}
