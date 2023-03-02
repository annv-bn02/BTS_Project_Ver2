#include "src/bts_convert.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



void test_BTS_Convert_Float_To_Bytes(void)

{

    float data_in = 1.67;

    uint8_t data_test[4] = {0x8f, 0xc2, 0xd5, 0x3f};

    printf("\n-----------Convert Float To Bytes--------\n");

    uint8_t *data_out = Bts_Convert_From_Float_To_Bytes(data_in);

    for(int i = 0; i < 4; i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((data_test[i])), (UNITY_INT)(UNITY_UINT8 )((data_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT8);

    }

    printf("Data convert: ");

    for(int i = 0; i < 4; i++)

    {

        printf("%x ", data_out[i]);

    }

    printf("\n----------------Convert Done--------------\n");

}



void test_BTS_Convert_Int_To_Bytes(void)

{

    int data_in = 30202023;

    uint8_t data_test[4] = {0xa7, 0xd8, 0xcc, 0x01};

    printf("\n-----------Convert Int To Bytes--------\n");

    uint8_t *data_out = Bts_Convert_From_Int_To_Bytes(data_in);

    for(int i = 0; i < 4; i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((data_test[i])), (UNITY_INT)(UNITY_UINT8 )((data_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_UINT8);

    }

    printf("Data convert: ");

    for(int i = 0; i < 4; i++)

    {

        printf("%x ", data_out[i]);

    }

    printf("\n----------------Convert Done--------------\n");

}



void test_BTS_Convert_Uint16_To_Bytes(void)

{

    uint16_t data_in = 578;

    uint8_t data_test[2] = {0x42, 0x02};

    printf("\n-----------Convert Float To Bytes--------\n");

    uint8_t *data_out = Bts_Convert_From_Uint16_To_Bytes(data_in);

    for(int i = 0; i < 2; i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((data_test[i])), (UNITY_INT)(UNITY_UINT8 )((data_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_UINT8);

    }

    printf("Data convert: ");

    for(int i = 0; i < 2; i++)

    {

        printf("%x ", data_out[i]);

    }

    printf("\n----------------Convert Done--------------\n");

}



void test_BTS_Convert_Bytes_To_Float(void)

{

    float data_test = 713.23;

    uint8_t data_in[4] = {0x44, 0x32, 0x4e, 0xb8};

    printf("\n-----------Convert Bytes To Float--------\n");

    float data_out = Bts_Convert_From_Bytes_To_Float(data_in[0], data_in[1], data_in[2], data_in[3]);

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((data_test)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((data_test))), (UNITY_FLOAT)((UNITY_FLOAT)((data_out))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(73)));

    printf("Data convert: %f ", data_out);

    printf("\n----------------Convert Done--------------\n");

}



void test_BTS_Convert_Bytes_To_Int(void)

{

    int data_test = 20232030;

    uint8_t data_in[4] = {0x5e, 0xb7, 0x34, 0x01};

    printf("\n-----------Convert Bytes To Int--------\n");

    int data_out = Bts_Convert_From_Bytes_To_Int(data_in[0], data_in[1], data_in[2], data_in[3]);

    UnityAssertEqualNumber((UNITY_INT)((data_test)), (UNITY_INT)((data_out)), (

   ((void *)0)

   ), (UNITY_UINT)(84), UNITY_DISPLAY_STYLE_INT);

    printf("Data convert: %d ", data_out);

    printf("\n----------------Convert Done--------------\n");

}



void test_BTS_Convert_Bytes_To_Uint16(void)

{

    uint16_t data_test = 685;

    uint8_t data_in[2] = {0xad, 0x02};

    printf("\n-----------Convert Bytes To Uint16--------\n");

    uint16_t data_out = Bts_Convert_From_Bytes_To_Uint16(data_in[0], data_in[1]);

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((data_test)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((data_test))), (UNITY_FLOAT)((UNITY_FLOAT)((data_out))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(95)));

    printf("Data convert: %d ", data_out);

    printf("\n----------------Convert Done--------------\n");

}
