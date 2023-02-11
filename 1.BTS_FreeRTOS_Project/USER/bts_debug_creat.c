#include "bts_debug_creat.h"

/* M?ng ch?a tên các di?u hoà */
static list_conditioner_e list_conditioner_arr[LIST_CONDITIONER_SIZE] = {DEVICE_CONDITIONER_1, DEVICE_CONDITIONER_2, DEVICE_CONDITIONER_3, DEVICE_CONDITIONER_4};

/* M?ng ch?a tên các qu?t */
static list_fan_e list_fan_arr[LIST_FAN_SIZE] = {DEVICE_FAN_1, DEVICE_FAN_2, DEVICE_FAN_3, DEVICE_FAN_4};

/* M?ng ch?a tên các dèn */
static list_lamp_e list_lamp_arr[LIST_LAMP_SIZE] = {DEVICE_LAMP_1, DEVICE_LAMP_2, DEVICE_LAMP_3, DEVICE_LAMP_4};

void test_BTS_Message_Create_Frame_Sensor_Request_NTC_Indoor(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/

//    uint8_t arr_data_sensor_request_NTC_Indoor_test[LENGTH_DEFAULT + LENGTH_SENSOR_REQUEST] = {
//        0x55, 0xAA, 0x01, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00};

    sensorFrameMsg_t frame_sensor_test;
    uint8_t arr_data_sensor_request_NTC_Indoor_out[50], length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_REQUEST;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_NTC;
    frame_sensor_test.SensorName = SENSOR_NAME_NTC_INDOOR;
    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_request_NTC_Indoor_out);
	SmartBTS_USART3_SendArrayByte(arr_data_sensor_request_NTC_Indoor_out,length_arr);	
//    BTS_Sys_Debug("/*-----------------------------------------*/");
//    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Sensor_Request_Smoke\n");
//    BTS_Sys_Debug("length: %d\n", length_arr);
//    // t?o b?n tin d?ng frame t? arr

//    Print_Data_Message(arr_data_sensor_request_NTC_Indoor_out, length_arr);
//    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/


//    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
//    // test b?n tin frame du?c detect
//    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_request_NTC_Indoor_out, &frame_sensor_detect);
//    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_NTC_Indoor_out[LENGTH_DEFAULT],
//                                                                    arr_data_sensor_request_NTC_Indoor_out[LENGTH_DEFAULT + 1]);
//    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_NTC_Indoor_out[length_arr - 2],
//                                                                    arr_data_sensor_request_NTC_Indoor_out[length_arr - 1]);
//	Print_Data_Detect_Sensor(frame_sensor_detect);
//    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Request_Smoke\n");
//    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
   
}

/*Hàm test SC20 yêu c?u c?p nh?t c?m bi?n nhi?t d?(ngoài tr?i) */
void test_BTS_Message_Create_Frame_Sensor_Request_NTC_Outdoor(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
//    uint8_t arr_data_sensor_request_NTC_Outdoor_test[LENGTH_DEFAULT + LENGTH_SENSOR_REQUEST] = {
//        0x55, 0xAA, 0x01, 0x00, 0x01, 0x00, 0x04, 0x00, 0x02, 0x00};

    sensorFrameMsg_t frame_sensor_test;
    uint8_t arr_data_sensor_request_NTC_Outdoor_out[50], length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_REQUEST;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_NTC;
    frame_sensor_test.SensorName = SENSOR_NAME_NTC_OUTDOOR;

    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_request_NTC_Outdoor_out);
	SmartBTS_USART3_SendArrayByte(arr_data_sensor_request_NTC_Outdoor_out,length_arr);
//    BTS_Sys_Debug("/*-----------------------------------------*/");
//    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Sensor_Request_NTC_Outdoor\n");
//    BTS_Sys_Debug("length: %d\n", length_arr);
//    // t?o b?n tin d?ng frame t? arr
//    Print_Data_Message(arr_data_sensor_request_NTC_Outdoor_out, length_arr);
//    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/

//    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
//    // test b?n tin frame du?c detect
//    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_request_NTC_Outdoor_out, &frame_sensor_detect);
//    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_NTC_Outdoor_out[LENGTH_DEFAULT],
//                                                                    arr_data_sensor_request_NTC_Outdoor_out[LENGTH_DEFAULT + 1]);
//    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_NTC_Outdoor_out[length_arr - 2],
//                                                                    arr_data_sensor_request_NTC_Outdoor_out[length_arr - 1]);
//    Print_Data_Detect_Sensor(frame_sensor_detect);
//    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Request_NTC_Outdoor\n");
//    BTS_Sys_Debug("/*-----------------------------------------*/");
//    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*Hàm test SC20 yêu c?u c?p nh?t c?m bi?n m? c?a */
void test_BTS_message_Create_Frame_Sensor_Request_Door(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
//    uint8_t arr_data_sensor_request_Door_test[LENGTH_DEFAULT + LENGTH_SENSOR_REQUEST] = {
//        0x55, 0xAA, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x01, 0x00};

    sensorFrameMsg_t frame_sensor_test;
    uint8_t arr_data_sensor_request_Door_out[50], length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_REQUEST;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_DOOR;
    frame_sensor_test.SensorName = SENSOR_NAME_DOOR_1;

    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_request_Door_out);
	SmartBTS_USART3_SendArrayByte(arr_data_sensor_request_Door_out,length_arr);
//    BTS_Sys_Debug("/*-----------------------------------------*/");
//    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Sensor_Request_Door\n");
//    BTS_Sys_Debug("length: %d\n", length_arr);
//    Print_Data_Message(arr_data_sensor_request_Door_out, length_arr);
//    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
//    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
//    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_request_Door_out, &frame_sensor_detect);
//    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_Door_out[LENGTH_DEFAULT],
//                                                                    arr_data_sensor_request_Door_out[LENGTH_DEFAULT + 1]);
//    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_Door_out[length_arr - 2],
//                                                                    arr_data_sensor_request_Door_out[length_arr - 1]);
//    Print_Data_Detect_Sensor(frame_sensor_detect);
//    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Request_Door\n");
//    BTS_Sys_Debug("/*-----------------------------------------*/");
//    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*Hàm test SC20 yêu c?u c?p nh?t c?m bi?n khói */
void test_BTS_Message_Create_Frame_Sensor_Request_Smoke(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
//    uint8_t arr_data_sensor_request_Smoke_test[LENGTH_DEFAULT + LENGTH_SENSOR_REQUEST] = {
//        0x55, 0xAA, 0x01, 0x00, 0x03, 0x00, 0x04, 0x00, 0x01, 0x00};

    sensorFrameMsg_t frame_sensor_test;
    uint8_t arr_data_sensor_request_Smoke_out[50],length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_REQUEST;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_SMOKE;
    frame_sensor_test.SensorName = SENSOR_NAME_SMOKE_1;

    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_request_Smoke_out);
	SmartBTS_USART3_SendArrayByte(arr_data_sensor_request_Smoke_out,length_arr);
//    BTS_Sys_Debug("/*-----------------------------------------*/");
//    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Sensor_Request_Smoke\n");
//    BTS_Sys_Debug("length: %d\n", length_arr);
//    // t?o b?n tin d?ng frame t? arr

//    Print_Data_Message(arr_data_sensor_request_Smoke_out, length_arr);
//    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
//    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
//    // test b?n tin frame du?c detect
//    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_request_Smoke_out, &frame_sensor_detect);
//    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_Smoke_out[LENGTH_DEFAULT],
//                                                                    arr_data_sensor_request_Smoke_out[LENGTH_DEFAULT + 1]);
//    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_Smoke_out[length_arr - 2],
//                                                                    arr_data_sensor_request_Smoke_out[length_arr - 1]);
//    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Request_Smoke\n");
//    BTS_Sys_Debug("/*-----------------------------------------*/");
//    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*Hàm test SC20 yêu c?u c?p nh?t c?m bi?n nu?c */
void test_BTS_Message_Create_Frame_Sensor_Request_Water(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
//    uint8_t arr_data_sensor_request_Water_test[LENGTH_DEFAULT + LENGTH_SENSOR_REQUEST] = {
//        0x55, 0xAA, 0x01, 0x00, 0x04, 0x00, 0x04, 0x00, 0x01, 0x00};

    sensorFrameMsg_t frame_sensor_test;
    uint8_t arr_data_sensor_request_Water_out[50], length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_REQUEST;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_WATER;
    frame_sensor_test.SensorName = SENSOR_NAME_WATER_1;

    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_request_Water_out);
	SmartBTS_USART3_SendArrayByte(arr_data_sensor_request_Water_out,length_arr);
//    BTS_Sys_Debug("/*-----------------------------------------*/");
//    BTS_Sys_Debug("\nStart test_BTS_message_Create_Frame_Sensor_Request_Water\n");
//    BTS_Sys_Debug("length: %d\n", length_arr);
//    // t?o b?n tin d?ng frame t? arr

//    Print_Data_Message(arr_data_sensor_request_Water_out, length_arr);
//    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
//	/*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
//    // test b?n tin frame du?c detect
//    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_request_Water_out, &frame_sensor_detect);
//    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_Water_out[LENGTH_DEFAULT],
//                                                                    arr_data_sensor_request_Water_out[LENGTH_DEFAULT + 1]);
//    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_Water_out[length_arr - 2],
//                                                                    arr_data_sensor_request_Water_out[length_arr - 1]);
//    Print_Data_Detect_Sensor(frame_sensor_detect);
//    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Request_Water\n");
//    BTS_Sys_Debug("/*-----------------------------------------*/");
//    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*Hàm test SC20 yêu c?u c?p nh?t di?u khi?n di?u hòa */
void test_BTS_Message_Create_Frame_Sensor_Request_Conditioner_Status(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
//    uint8_t arr_data_sensor_request_Conditioner_Status_test[LENGTH_DEFAULT + LENGTH_SENSOR_REQUEST] = {
//        0x55, 0xAA, 0x01, 0x00, 0x05, 0x00, 0x04, 0x00, 0x01, 0x00};

    sensorFrameMsg_t frame_sensor_test, frame_sensor_detect;
    uint8_t arr_data_sensor_request_Conditioner_Status_out[50], length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_REQUEST;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_CONDITIONER_STATUS;
    frame_sensor_test.SensorName = SENSOR_NAME_CONDITIONER_STATUS_1;

    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_request_Conditioner_Status_out);

    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Sensor_Request_Conditioner_Status\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // t?o b?n tin d?ng frame t? arr
    Print_Data_Message(arr_data_sensor_request_Conditioner_Status_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
	/*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // test b?n tin frame du?c detect
    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_request_Conditioner_Status_out, &frame_sensor_detect);
    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_Conditioner_Status_out[LENGTH_DEFAULT],
                                                                    arr_data_sensor_request_Conditioner_Status_out[LENGTH_DEFAULT + 1]);
    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_request_Conditioner_Status_out[length_arr - 2],
                                                                    arr_data_sensor_request_Conditioner_Status_out[length_arr - 1]);
    Print_Data_Detect_Sensor(frame_sensor_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Request_Conditioner_Status\n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*Hàm test GD32 ph?n h?i yêu c?u c?p nh?t giá tr? c?m bi?n nhi?t d?(trong nhà)*/
void test_BTS_Message_Create_Frame_Sensor_Response_NTC_Indoor(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
    float test_bts_message_data = 22.5;
    uint8_t *data_float_to_byte = Bts_Convert_From_Float_To_Bytes(test_bts_message_data);
//   uint8_t arr_data_sensor_response_NTC_Indoor_test[LENGTH_DEFAULT + LENGTH_SENSOR_RESPONSE_NTC] = {
//       0x55, 0xAA, 0x02, 0x00, 0x01, 0x00, 0x08, 0x00, 0x01, 0x00, data_float_to_byte[3], data_float_to_byte[2], data_float_to_byte[1], data_float_to_byte[0]};

    sensorFrameMsg_t frame_sensor_test, frame_sensor_detect;
    uint8_t arr_data_sensor_response_NTC_Indoor_out[50], length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_RESPONSE;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_NTC;
    frame_sensor_test.SensorName = SENSOR_NAME_NTC_INDOOR;
    frame_sensor_test.Data[0] = data_float_to_byte[3];
    frame_sensor_test.Data[1] = data_float_to_byte[2];
    frame_sensor_test.Data[2] = data_float_to_byte[1];
    frame_sensor_test.Data[3] = data_float_to_byte[0];

    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_response_NTC_Indoor_out);

    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_message_Create_Frame_Sensor_Response_NTC_Indoor\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // t?o b?n tin d?ng frame t? arr

    Print_Data_Message(arr_data_sensor_response_NTC_Indoor_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
	/*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // test b?n tin frame du?c detect
    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_response_NTC_Indoor_out, &frame_sensor_detect);
    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_NTC_Indoor_out[LENGTH_DEFAULT],
                                                                    arr_data_sensor_response_NTC_Indoor_out[LENGTH_DEFAULT + 1]);
    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_NTC_Indoor_out[length_arr - 2],
                                                                    arr_data_sensor_response_NTC_Indoor_out[length_arr - 1]);
    Print_Data_Detect_Sensor(frame_sensor_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Response_NTC_Indoor\n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*Hàm test GD32 ph?n h?i yêu c?u c?p nh?t giá tr? c?m bi?n nhi?t d?(ngoài tr?i)*/
void test_BTS_Message_Create_Frame_Sensor_Response_NTC_Outdoor(void)
{ /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/

    float test_bts_message_data = 29.5;
	uint8_t *data_float_to_byte = Bts_Convert_From_Float_To_Bytes(test_bts_message_data);
//    uint8_t arr_data_sensor_response_NTC_Outdoor_test[LENGTH_DEFAULT + LENGTH_SENSOR_RESPONSE_NTC] = {
//        0x55, 0xAA, 0x02, 0x00, 0x01, 0x00, 0x08, 0x00, 0x02, 0x00, data_float_to_byte[3], data_float_to_byte[2], data_float_to_byte[1], data_float_to_byte[0]};

    sensorFrameMsg_t frame_sensor_test, frame_sensor_detect;
    uint8_t arr_data_sensor_response_NTC_Outdoor_out[50], length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_RESPONSE;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_NTC;
    frame_sensor_test.SensorName = SENSOR_NAME_NTC_OUTDOOR;
    frame_sensor_test.Data[0] = data_float_to_byte[3];
    frame_sensor_test.Data[1] = data_float_to_byte[2];
    frame_sensor_test.Data[2] = data_float_to_byte[1];
    frame_sensor_test.Data[3] = data_float_to_byte[0];
    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_response_NTC_Outdoor_out);
    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Sensor_Response_NTC_Outdoor\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // t?o b?n tin d?ng frame t? arr

    Print_Data_Message(arr_data_sensor_response_NTC_Outdoor_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
	/*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // test b?n tin frame du?c detect
    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_response_NTC_Outdoor_out, &frame_sensor_detect);
    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_NTC_Outdoor_out[LENGTH_DEFAULT],
                                                                    arr_data_sensor_response_NTC_Outdoor_out[LENGTH_DEFAULT + 1]);
    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_NTC_Outdoor_out[length_arr - 2],
                                                                    arr_data_sensor_response_NTC_Outdoor_out[length_arr - 1]);
    Print_Data_Detect_Sensor(frame_sensor_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Response_NTC_Outdoor\n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*Hàm test GD32 ph?n h?i yêu c?u c?p nh?t tr?ng thái c?m bi?n m? c?a*/
void test_BTS_message_Create_Frame_Sensor_Response_Door(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
    uint8_t data_door = 0;
//    uint8_t arr_data_sensor_response_Door_test[LENGTH_DEFAULT + LENGTH_SENSOR_RESPONSE_DOOR] = {
//       0x55, 0xAA, 0x02, 0x00, 0x02, 0x00, 0x05, 0x00, 0x01, 0x00, data_door};

    sensorFrameMsg_t frame_sensor_test, frame_sensor_detect;
    uint8_t arr_data_sensor_response_Door_out[50], length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_RESPONSE;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_DOOR;
    frame_sensor_test.SensorName = SENSOR_NAME_DOOR_1;
    frame_sensor_test.Data[0] = data_door;

    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_response_Door_out);

    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Sensor_Response_Door\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // t?o b?n tin d?ng frame t? arr

    Print_Data_Message(arr_data_sensor_response_Door_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
	/*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // test b?n tin frame du?c detect
    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_response_Door_out, &frame_sensor_detect);
    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_Door_out[LENGTH_DEFAULT],
                                                                    arr_data_sensor_response_Door_out[LENGTH_DEFAULT + 1]);
    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_Door_out[length_arr - 2],
                                                                    arr_data_sensor_response_Door_out[length_arr - 1]);
    Print_Data_Detect_Sensor(frame_sensor_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Response_Door\n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*Hàm test GD32 ph?n h?i yêu c?u c?p nh?t tr?ng thái c?m bi?n khói*/
void test_BTS_Message_Create_Frame_Sensor_Response_Smoke(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/

    uint8_t data_smoke = 0;
//    uint8_t arr_data_sensor_response_Smoke_test[LENGTH_DEFAULT + LENGTH_SENSOR_RESPONSE_SMOKE] = {
//        0x55, 0xAA, 0x02, 0x00, 0x03, 0x00, 0x05, 0x00, 0x01, 0x00, data_smoke};

    sensorFrameMsg_t frame_sensor_test, frame_sensor_detect;
    uint8_t arr_data_sensor_response_Smoke_out[50], length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_RESPONSE;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_SMOKE;
    frame_sensor_test.SensorName = SENSOR_NAME_SMOKE_1;
    frame_sensor_test.Data[0] = data_smoke;

    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_response_Smoke_out);

    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Sensor_Response_Smoke\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    Print_Data_Message(arr_data_sensor_response_Smoke_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
	/*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // test b?n tin frame du?c detect
    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_response_Smoke_out, &frame_sensor_detect);
    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_Smoke_out[LENGTH_DEFAULT],
                                                                    arr_data_sensor_response_Smoke_out[LENGTH_DEFAULT + 1]);
    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_Smoke_out[length_arr - 2],
                                                                    arr_data_sensor_response_Smoke_out[length_arr - 1]);
    Print_Data_Detect_Sensor(frame_sensor_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Response_Smoke\n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*Hàm test GD32 ph?n h?i yêu c?u c?p nh?t tr?ng thái c?m bi?n nu?c*/
void test_BTS_Message_Create_Frame_Sensor_Response_Water(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/

    uint8_t data_water = 0;
    
//    uint8_t arr_data_sensor_response_Water_test[LENGTH_DEFAULT + LENGTH_SENSOR_RESPONSE_WATER] = {
//        0x55, 0xAA, 0x02, 0x00, 0x04, 0x00, 0x05, 0x00, 0x01, 0x00, data_water};
    sensorFrameMsg_t frame_sensor_test, frame_sensor_detect;
    uint8_t arr_data_sensor_response_Water_out[50], length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_RESPONSE;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_WATER;
    frame_sensor_test.SensorName = SENSOR_NAME_WATER_1;
    frame_sensor_test.Data[0] = data_water;

    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_response_Water_out);
    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Sensor_Response_Water\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
	Print_Data_Message(arr_data_sensor_response_Water_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // test b?n tin frame du?c detect
    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_response_Water_out, &frame_sensor_detect);
    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_Water_out[LENGTH_DEFAULT],
                                                                    arr_data_sensor_response_Water_out[LENGTH_DEFAULT + 1]);
    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_Water_out[length_arr - 2],
                                                                    arr_data_sensor_response_Water_out[length_arr - 1]);
    Print_Data_Detect_Sensor(frame_sensor_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Response_Water\n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*Hàm test GD32 ph?n h?i yêu c?u c?p nh?t tr?ng thái di?u khi?n di?u hòa*/
void test_BTS_Message_Create_Frame_Sensor_Response_Conditioner_Status(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/

    uint8_t data_conditioner = 0;
//    uint8_t arr_data_sensor_response_Conditioner_Status_test[LENGTH_DEFAULT + LENGTH_SENSOR_RESPONSE_CONDITIONER_STATUS] = {
//        0x55, 0xAA, 0x02, 0x00, 0x05, 0x00, 0x05, 0x00, 0x01, 0x00, data_conditioner};

    sensorFrameMsg_t frame_sensor_test, frame_sensor_detect;
    uint8_t arr_data_sensor_response_Conditioner_Status_out[50], length_arr = 0;

    frame_sensor_test.StartFrame = START_BYTE;
    frame_sensor_test.TypeMessage = TYPE_MESSAGE_SENSOR_RESPONSE;
    frame_sensor_test.TypeDevice = TYPE_SENSOR_CONDITIONER_STATUS;
    frame_sensor_test.SensorName = SENSOR_NAME_CONDITIONER_STATUS_1;
    frame_sensor_test.Data[0] = data_conditioner;

    length_arr = BTS_Message_Create_Frame_Sensor(frame_sensor_test, arr_data_sensor_response_Conditioner_Status_out);

    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Sensor_Response_Conditioner_Status\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // t?o b?n tin d?ng frame t? arr


    Print_Data_Message(arr_data_sensor_response_Conditioner_Status_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
	/*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // test b?n tin frame du?c detect
    BTS_Message_Detect_Frame_Sensor(arr_data_sensor_response_Conditioner_Status_out, &frame_sensor_detect);
    frame_sensor_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_Conditioner_Status_out[LENGTH_DEFAULT],
                                                                    arr_data_sensor_response_Conditioner_Status_out[LENGTH_DEFAULT + 1]);
    frame_sensor_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_sensor_response_Conditioner_Status_out[length_arr - 2],
                                                                    arr_data_sensor_response_Conditioner_Status_out[length_arr - 1]);
    Print_Data_Detect_Sensor(frame_sensor_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Sensor_Response_Conditioner_Status\n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

void test_BTS_Message_Create_Frame_Device_Request_Conditioner(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
    deviceFrameMsg_t frame_device_test, frame_device_detect;
    uint8_t device_name = list_conditioner_arr[2];
//   uint8_t arr_data_device_request_conditioner_test[LENGTH_DEVICE_REQUEST + LENGTH_DEFAULT] = {
//        0x55, 0xAA, 0x03, 0x00, 0x01, 0x00, 0x05, 0x00, device_name, 0x00, 0x01};
    uint8_t arr_data_device_request_conditioner_out[50], length_arr = 0;
    // truy?n các giá tr? vào m?ng d? test theo b?n tin request c?a di?u hoà
    frame_device_test.StartFrame = START_BYTE;
    frame_device_test.TypeMessage = TYPE_MESSAGE_DEVICE_REQUEST;
    frame_device_test.TypeDevice = TYPE_DEVICE_CONDITIONER;
    frame_device_test.DeviceName = device_name;
    frame_device_test.CommandType = COMMAND_TYPE_SET;
    // t?o b?n tin d?ng arr t? frame
    length_arr = BTS_Message_Create_Frame_Device(frame_device_test, arr_data_device_request_conditioner_out);
    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Device_Request_Conditioner\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // test b?n tin arr du?c creat
    Print_Data_Message(arr_data_device_request_conditioner_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // t?o b?n tin d?ng frame t? arr
    BTS_Message_Detect_Frame_Device(arr_data_device_request_conditioner_out, &frame_device_detect);
    frame_device_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_request_conditioner_out[LENGTH_DEFAULT],
                                                                    arr_data_device_request_conditioner_out[LENGTH_DEFAULT + 1]);
    frame_device_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_request_conditioner_out[length_arr - 2],
                                                                    arr_data_device_request_conditioner_out[length_arr - 1]);
    // test b?n tin frame du?c detect
    Print_Data_Detect_Device(frame_device_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Device_Request_Conditioner \n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*
    Hàm dùng d? test b?n tin request c?a qu?t
*/
void test_BTS_Message_Create_Frame_Device_Request_Fan(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
    uint8_t device_name = list_fan_arr[2];

    deviceFrameMsg_t frame_device_test, frame_device_detect;
    // M?ng test theo d?ng b?n tin resquest c?a qu?t
//    uint8_t arr_data_device_request_fan_test[LENGTH_DEVICE_REQUEST + LENGTH_DEFAULT] = {
//        0x55, 0xAA, 0x03, 0x00, 0x02, 0x00, 0x05, 0x00, device_name, 0x00, 0x01};

    uint8_t arr_data_device_request_fan_out[50], length_arr = 0;
    // truy?n các giá tr? vào m?ng d? test theo b?n tin request c?a qu?t
    frame_device_test.StartFrame = START_BYTE;
    frame_device_test.TypeMessage = TYPE_MESSAGE_DEVICE_REQUEST;
    frame_device_test.TypeDevice = TYPE_DEVICE_FAN;
    frame_device_test.DeviceName = device_name;
    frame_device_test.CommandType = COMMAND_TYPE_SET;
    // t?o b?n tin d?ng arr t? frame
    length_arr = BTS_Message_Create_Frame_Device(frame_device_test, arr_data_device_request_fan_out);
    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Device_Request_Fan\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // test b?n tin arr du?c creat
    Print_Data_Message(arr_data_device_request_fan_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // t?o b?n tin d?ng frame t? arr
    BTS_Message_Detect_Frame_Device(arr_data_device_request_fan_out, &frame_device_detect);
    frame_device_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_request_fan_out[LENGTH_DEFAULT],
                                                                    arr_data_device_request_fan_out[LENGTH_DEFAULT + 1]);
    frame_device_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_request_fan_out[length_arr - 2],
                                                                    arr_data_device_request_fan_out[length_arr - 1]);

    // test b?n tin frame du?c detect
    Print_Data_Detect_Device(frame_device_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Device_Request_Fan \n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*
    Hàm dùng d? test b?n tin request c?a dèn
*/
void test_BTS_Message_Create_Frame_Device_Request_Lamp(void)
{
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
    uint8_t device_name = list_lamp_arr[2];

    deviceFrameMsg_t frame_device_test, frame_device_detect;
    // M?ng test theo d?ng b?n tin resquest c?a dèn
//    uint8_t arr_data_device_request_lamp_test[LENGTH_DEVICE_REQUEST + LENGTH_DEFAULT] = {
//       0x55, 0xAA, 0x03, 0x00, 0x03, 0x00, 0x05, 0x00, device_name, 0x00, 0x01};

    uint8_t arr_data_device_request_lamp_out[50], length_arr = 0;
    // truy?n các giá tr? vào m?ng d? test theo b?n tin request c?a dèn
    frame_device_test.StartFrame = START_BYTE;
    frame_device_test.TypeMessage = TYPE_MESSAGE_DEVICE_REQUEST;
    frame_device_test.TypeDevice = TYPE_DEVICE_LAMP;
    frame_device_test.DeviceName = device_name;
    frame_device_test.CommandType = COMMAND_TYPE_SET;
    // t?o b?n tin d?ng arr t? frame
    length_arr = BTS_Message_Create_Frame_Device(frame_device_test, arr_data_device_request_lamp_out);
    // khung test
    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Device_Request_Lamp\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // test b?n tin arr du?c creat
    Print_Data_Message(arr_data_device_request_lamp_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // t?o b?n tin d?ng frame t? arr
    BTS_Message_Detect_Frame_Device(arr_data_device_request_lamp_out, &frame_device_detect);
    frame_device_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_request_lamp_out[LENGTH_DEFAULT],
                                                                    arr_data_device_request_lamp_out[LENGTH_DEFAULT + 1]);
    frame_device_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_request_lamp_out[length_arr - 2],
                                                                    arr_data_device_request_lamp_out[length_arr - 1]);

    // test b?n tin frame du?c detect
    Print_Data_Detect_Device(frame_device_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Device_Request_Lamp \n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
}

/*
    Hàm dùng d? test b?n tin response success c?a di?u hoà
*/
void test_BTS_Message_Create_Frame_Device_Response_Success_Conditioner(void)
{
    
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
    uint8_t device_name = list_conditioner_arr[2];
    deviceFrameMsg_t frame_device_test, frame_device_detect;
    // M?ng test theo d?ng b?n tin response success c?a di?u hoà
//    uint8_t arr_data_device_response_success_conditioner_test[LENGTH_DEVICE_RESPONSE + LENGTH_DEFAULT] = {
//       0x55, 0xAA, 0x04, 0x00, 0x01, 0x00, 0x06, 0x00, device_name, 0x00, 0x01, 0x01};

    uint8_t arr_data_device_response_success_conditioner_out[50],length_arr = 0;
    // truy?n các giá tr? vào m?ng d? test theo b?n tin response success c?a di?u hoà
    frame_device_test.StartFrame = START_BYTE;
    frame_device_test.TypeMessage = TYPE_MESSAGE_DEVICE_RESPONSE;
    frame_device_test.TypeDevice = TYPE_DEVICE_CONDITIONER;
    frame_device_test.DeviceName = device_name;
    frame_device_test.CommandType = COMMAND_TYPE_SET;
    frame_device_test.StatusDevice = STATUS_DEVICE_ON;
    // t?o b?n tin d?ng arr t? frame
    length_arr = BTS_Message_Create_Frame_Device(frame_device_test, arr_data_device_response_success_conditioner_out);
    // khung test
    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Device_Response_Success_Conditioner\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // test b?n tin arr du?c creat
    Print_Data_Message(arr_data_device_response_success_conditioner_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // t?o b?n tin d?ng frame t? arr
    BTS_Message_Detect_Frame_Device(arr_data_device_response_success_conditioner_out, &frame_device_detect);
    frame_device_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_success_conditioner_out[LENGTH_DEFAULT],
                                                                    arr_data_device_response_success_conditioner_out[LENGTH_DEFAULT + 1]);
    frame_device_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_success_conditioner_out[length_arr - 2],
                                                                    arr_data_device_response_success_conditioner_out[length_arr - 1]);

    // test b?n tin frame du?c detect
    Print_Data_Detect_Device(frame_device_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Device_Response_Success_Conditioner \n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*
    Hàm dùng d? test b?n tin response success c?a qu?t
*/
void test_BTS_Message_Create_Frame_Device_Response_Success_Fan(void)
{
    
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
    uint8_t device_name = list_fan_arr[2];

    deviceFrameMsg_t frame_device_test, frame_device_detect;
    // M?ng test theo d?ng b?n tin response success c?a qu?t
//    uint8_t arr_data_device_response_success_fan_test[LENGTH_DEVICE_RESPONSE + LENGTH_DEFAULT] = {
//        0x55, 0xAA, 0x04, 0x00, 0x02, 0x00, 0x06, 0x00, device_name, 0x00, 0x01, 0x00};

    uint8_t arr_data_device_response_success_fan_out[50], length_arr = 0;
    // truy?n các giá tr? vào m?ng d? test theo b?n tin response success c?a qu?t
    frame_device_test.StartFrame = START_BYTE;
    frame_device_test.TypeMessage = TYPE_MESSAGE_DEVICE_RESPONSE;
    frame_device_test.TypeDevice = TYPE_DEVICE_FAN;
    frame_device_test.DeviceName = device_name;
    frame_device_test.CommandType = COMMAND_TYPE_SET;
    frame_device_test.StatusDevice = STATUS_DEVICE_FAN_ON;
    // t?o b?n tin d?ng arr t? frame
    length_arr = BTS_Message_Create_Frame_Device(frame_device_test, arr_data_device_response_success_fan_out);
    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Device_Response_Success_Fan\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // test b?n tin arr du?c creat
    Print_Data_Message(arr_data_device_response_success_fan_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // t?o b?n tin d?ng frame t? arr
    BTS_Message_Detect_Frame_Device(arr_data_device_response_success_fan_out, &frame_device_detect);
    frame_device_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_success_fan_out[LENGTH_DEFAULT],
                                                                    arr_data_device_response_success_fan_out[LENGTH_DEFAULT + 1]);
    frame_device_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_success_fan_out[length_arr - 2],
                                                                    arr_data_device_response_success_fan_out[length_arr - 1]);

    // test b?n tin frame du?c detect
    Print_Data_Detect_Device(frame_device_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Device_Response_Success_Fan \n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*
    Hàm dùng d? test b?n tin response success c?a dèn
*/
void test_BTS_Message_Create_Frame_Device_Response_Success_Lamp(void)
{
    
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
    uint8_t device_name = list_lamp_arr[2];

    deviceFrameMsg_t frame_device_test, frame_device_detect;
    // M?ng test theo d?ng b?n tin response success c?a dèn
//    uint8_t arr_data_device_response_success_lamp_test[LENGTH_DEVICE_RESPONSE + LENGTH_DEFAULT] = {
//       0x55, 0xAA, 0x04, 0x00, 0x03, 0x00, 0x06, 0x00, device_name, 0x00, 0x01, 0x01};
    uint8_t arr_data_device_response_success_lamp_out[50], length_arr = 0;
    // truy?n các giá tr? vào m?ng d? test theo b?n tin response success c?a dèn
    frame_device_test.StartFrame = START_BYTE;
    frame_device_test.TypeMessage = TYPE_MESSAGE_DEVICE_RESPONSE;
    frame_device_test.TypeDevice = TYPE_DEVICE_LAMP;
    frame_device_test.DeviceName = device_name;
    frame_device_test.CommandType = COMMAND_TYPE_SET;
    frame_device_test.StatusDevice = STATUS_DEVICE_ON;
    // t?o b?n tin d?ng arr t? frame
    length_arr = BTS_Message_Create_Frame_Device(frame_device_test, arr_data_device_response_success_lamp_out);
    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Device_Response_Success_Lamp\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // test b?n tin arr du?c creat
    Print_Data_Message(arr_data_device_response_success_lamp_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // t?o b?n tin d?ng frame t? arr
    BTS_Message_Detect_Frame_Device(arr_data_device_response_success_lamp_out, &frame_device_detect);
    frame_device_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_success_lamp_out[LENGTH_DEFAULT],
                                                                    arr_data_device_response_success_lamp_out[LENGTH_DEFAULT + 1]);
    frame_device_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_success_lamp_out[length_arr - 2],
                                                                    arr_data_device_response_success_lamp_out[length_arr - 1]);

    // test b?n tin frame du?c detect
    Print_Data_Detect_Device(frame_device_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Device_Response_Success_Lamp \n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*
    Hàm dùng d? test b?n tin response error c?a di?u hoà
*/
void test_BTS_Message_Create_Frame_Device_Response_Error_Conditioner(void)
{
    
    // M?ng test theo d?ng b?n tin response error c?a di?u hoà
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
    deviceFrameMsg_t frame_device_test, frame_device_detect;
//    uint8_t arr_data_device_response_error_conditioner_test[LENGTH_DEVICE_RESPONSE + LENGTH_DEFAULT] = {
//        0x55, 0xAA, 0x04, 0x00, 0x01, 0x00, 0x06, 0x00, 0x90, 0x00, 0x90, 0x90};
    uint8_t arr_data_device_response_error_conditioner_out[50], length_arr = 0;
    // truy?n các giá tr? vào m?ng d? test theo b?n tin response error c?a di?u hoà
    frame_device_test.StartFrame = START_BYTE;
    frame_device_test.TypeMessage = TYPE_MESSAGE_DEVICE_RESPONSE;
    frame_device_test.TypeDevice = TYPE_DEVICE_CONDITIONER;
    frame_device_test.DeviceName = DEVICE_CONDITIONER_ERROR;
    frame_device_test.CommandType = COMMAND_TYPE_ERROR;
    frame_device_test.StatusDevice = STATUS_DEVICE_ERROR;
    // t?o b?n tin d?ng arr t? frame
    length_arr = BTS_Message_Create_Frame_Device(frame_device_test, arr_data_device_response_error_conditioner_out);
    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Device_Response_Error_Conditioner\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // test b?n tin arr du?c creat
    Print_Data_Message(arr_data_device_response_error_conditioner_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // t?o b?n tin d?ng frame t? arr
    BTS_Message_Detect_Frame_Device(arr_data_device_response_error_conditioner_out, &frame_device_detect);
    frame_device_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_error_conditioner_out[LENGTH_DEFAULT],
                                                                    arr_data_device_response_error_conditioner_out[LENGTH_DEFAULT + 1]);
    frame_device_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_error_conditioner_out[length_arr - 2],
                                                                    arr_data_device_response_error_conditioner_out[length_arr - 1]);

    // test b?n tin frame du?c detect
    Print_Data_Detect_Device(frame_device_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Device_Response_Error_Conditioner \n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}

/*
    Hàm dùng d? test b?n tin response error c?a qu?t
*/
void test_BTS_Message_Create_Frame_Device_Response_Error_Fan(void)
{
    
    // M?ng test theo d?ng b?n tin response error c?a qu?t
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
    deviceFrameMsg_t frame_device_test, frame_device_detect;
//    uint8_t arr_data_device_response_error_fan_test[LENGTH_DEVICE_RESPONSE + LENGTH_DEFAULT] = {
//        0x55, 0xAA, 0x04, 0x00, 0x02, 0x00, 0x06, 0x00, 0x90, 0x00, 0x90, 0x90};
    uint8_t arr_data_device_response_error_fan_out[50], length_arr = 0;
    // truy?n các giá tr? vào m?ng d? test theo b?n tin response error c?a qu?t
    frame_device_test.StartFrame = START_BYTE;
    frame_device_test.TypeMessage = TYPE_MESSAGE_DEVICE_RESPONSE;
    frame_device_test.TypeDevice = TYPE_DEVICE_FAN;
    frame_device_test.DeviceName = STATUS_DEVICE_FAN_ERROR;
    frame_device_test.CommandType = COMMAND_TYPE_ERROR;
    frame_device_test.StatusDevice = STATUS_DEVICE_ERROR;
    // t?o b?n tin d?ng arr t? frame
    length_arr = BTS_Message_Create_Frame_Device(frame_device_test, arr_data_device_response_error_fan_out);
    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Device_Response_Error_Fan\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // test b?n tin arr du?c creat
    Print_Data_Message(arr_data_device_response_error_fan_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // t?o b?n tin d?ng frame t? arr
    BTS_Message_Detect_Frame_Device(arr_data_device_response_error_fan_out, &frame_device_detect);
    frame_device_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_error_fan_out[LENGTH_DEFAULT],
                                                                    arr_data_device_response_error_fan_out[LENGTH_DEFAULT + 1]);
    frame_device_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_error_fan_out[length_arr - 2],
                                                                    arr_data_device_response_error_fan_out[length_arr - 1]);

    // test b?n tin frame du?c detect
    Print_Data_Detect_Device(frame_device_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Device_Response_Error_Fan \n");
    BTS_Sys_Debug("/*-----------------------------------------*/");
} /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/

/*
    Hàm dùng d? test b?n tin response error c?a dèn
*/
void test_BTS_Message_Create_Frame_Device_Response_Error_Lamp(void)
{
    
    // M?ng test theo d?ng b?n tin response error c?a dèn
    /*--------------------------------------------------------------(START_CREAT_FRAME)--------------------------------------------------------------*/
    deviceFrameMsg_t frame_device_test, frame_device_detect;
//    uint8_t arr_data_device_response_error_lamp_test[LENGTH_DEVICE_RESPONSE + LENGTH_DEFAULT] = {
//        0x55, 0xAA, 0x04, 0x00, 0x03, 0x00, 0x06, 0x00, 0x90, 0x00, 0x90, 0x90};
    uint8_t arr_data_device_response_error_lamp_out[50], length_arr = 0;
    // truy?n các giá tr? vào m?ng d? test theo b?n tin response error c?a dèn
    frame_device_test.StartFrame = START_BYTE;
    frame_device_test.TypeMessage = TYPE_MESSAGE_DEVICE_RESPONSE;
    frame_device_test.TypeDevice = TYPE_DEVICE_LAMP;
    frame_device_test.DeviceName = DEVICE_LAMP_ERROR;
    frame_device_test.CommandType = COMMAND_TYPE_ERROR;
    frame_device_test.StatusDevice = STATUS_DEVICE_ERROR;
    // t?o b?n tin d?ng arr t? frame
    length_arr = BTS_Message_Create_Frame_Device(frame_device_test, arr_data_device_response_error_lamp_out);
    BTS_Sys_Debug("/*-----------------------------------------*/");
    BTS_Sys_Debug("\nStart test_BTS_Message_Create_Frame_Device_Response_Error_Lamp\n");
    BTS_Sys_Debug("length: %d\n", length_arr);
    // test b?n tin arr du?c creat
    Print_Data_Message(arr_data_device_response_error_lamp_out, length_arr);
    /*--------------------------------------------------------------(END_CREAT_FRAME)--------------------------------------------------------------*/
    /*--------------------------------------------------------------(START_DETECT_FRAME)--------------------------------------------------------------*/
    // t?o b?n tin d?ng frame t? arr
    BTS_Message_Detect_Frame_Device(arr_data_device_response_error_lamp_out, &frame_device_detect);
    frame_device_test.LengthData = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_error_lamp_out[LENGTH_DEFAULT],
                                                                    arr_data_device_response_error_lamp_out[LENGTH_DEFAULT + 1]);
    frame_device_test.CheckFrame = Bts_Convert_From_Bytes_To_Uint16(arr_data_device_response_error_lamp_out[length_arr - 2],
                                                                    arr_data_device_response_error_lamp_out[length_arr - 1]);

    // test b?n tin frame du?c detect
    Print_Data_Detect_Device(frame_device_detect);
    BTS_Sys_Debug("\nEnd test_BTS_Message_Create_Frame_Device_Response_Error_Lamp \n");
    BTS_Sys_Debug("/*-----------------------------------------*/");

    /*--------------------------------------------------------------(END_DETECT_FRAME)--------------------------------------------------------------*/
}


/*
    @brief: Hàm in m?ng data du?c creat.
    @node: In l?n lu?t t?ng ph?n t? trong m?ng data du?c creat .
    @param arr: Là m?ng data du?c creat.
    @param length: Là chi?u dài m?ng.
    @retval: 0.
*/
void Print_Data_Message(uint8_t *arr, uint8_t length)
{
	uint8_t i;
    BTS_Sys_Debug("Array creat: ");
    for (i = 0; i < length; i++)
    {
        if (arr[i] <= 0x0F)
        {
            BTS_Sys_Debug("0%x ", arr[i]);
        }
        else
        {
            BTS_Sys_Debug("%x ", arr[i]);
        }
    }
}

/*
    @brief: Hàm in m?ng data du?c detect.
    @node: In l?n lu?t t?ng giá tr? trong struct data du?c detect c?a device .
    @param frame: Là struct data du?c detect.
    @retval: 0.
*/
void Print_Data_Detect_Device(deviceFrameMsg_t frame)
{
    BTS_Sys_Debug("\n-----------------------------------------------------\n");
	BTS_Sys_Debug("\t\t\tFrame Device Detect \n");
	BTS_Sys_Debug("StartFrame   :%x\n", frame.StartFrame);
	BTS_Sys_Debug("TypeMessage  :%x\n", frame.TypeMessage);
	BTS_Sys_Debug("TypeDevice   :%x\n", frame.TypeDevice);
	BTS_Sys_Debug("LengthData   :%d\n", frame.LengthData);
	BTS_Sys_Debug("DeviceName   :%x\n", frame.DeviceName);
	BTS_Sys_Debug("CommandType  :%x\n", frame.CommandType);
	if (frame.TypeMessage == TYPE_MESSAGE_DEVICE_RESPONSE)
	{
		BTS_Sys_Debug("StatusDevice :%x\n", frame.StatusDevice);
	}
	BTS_Sys_Debug("CheckFrame   :%x\n", frame.CheckFrame);
	BTS_Sys_Debug("-----------------------------------------------------\n");
}

/*
    @brief: Hàm in m?ng data du?c detect.
    @node: In l?n lu?t t?ng giá tr? trong struct data du?c detect c?a sensor .
    @param frame: Là struct data du?c detect.
    @retval: 0.
*/
void Print_Data_Detect_Sensor(sensorFrameMsg_t frame)
{
    float data_float;
	BTS_Sys_Debug("\n-----------------------------------------------------\n");
	BTS_Sys_Debug("\t\t\tFrame Sensor Detect \n");
	BTS_Sys_Debug("StartFrame  : %x\n", frame.StartFrame);
	BTS_Sys_Debug("TypeMessage : %x\n", frame.TypeMessage);
	BTS_Sys_Debug("TypeDevice  : %x\n", frame.TypeDevice);
	BTS_Sys_Debug("LengthData  : %d\n", frame.LengthData);
	switch (frame.TypeMessage)
	{
	case TYPE_MESSAGE_SENSOR_REQUEST:
		BTS_Sys_Debug("SensorName  : %x\n", frame.SensorName);
		break;
	case TYPE_MESSAGE_SENSOR_RESPONSE:
		if (frame.TypeDevice == TYPE_SENSOR_NTC)
		{
			data_float = Bts_Convert_From_Bytes_To_Float(frame.Data[0], frame.Data[1],
			frame.Data[2], frame.Data[3]);
			BTS_Sys_Debug("Data        : %f \n", data_float);
		}
		else     
		{
			BTS_Sys_Debug("Data        : %d\n", frame.Data[0]);
		}
		break;
	}
	BTS_Sys_Debug("CheckFrame  : %x\n", frame.CheckFrame);
	BTS_Sys_Debug("-----------------------------------------------------\n");
}

