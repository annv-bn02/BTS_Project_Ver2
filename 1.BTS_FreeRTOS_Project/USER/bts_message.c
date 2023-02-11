#include "bts_message.h"

/*mảng này dùng để kiểm tra xem sensor chọn là loại nào*/
static type_sensor_e type_sensor_arr[TYPE_SENSOR_SIZE] = {TYPE_SENSOR_NTC, TYPE_SENSOR_DOOR, TYPE_SENSOR_SMOKE, TYPE_SENSOR_WATER, TYPE_SENSOR_CONDITIONER_STATUS};

/*mảng này để biết data chiếm bao nhiêu byte để thực hiện cộng với length*/
static uint8_t length_sensor_arr[TYPE_SENSOR_SIZE] = {4, 1, 1, 1, 1};

uint16_t CheckSum(uint8_t *buf, uint8_t len);

/*
    @brief: Tạo mảng data chuẩn frame bản tin Sensor.
    @node: Chức năng hàm được sử dụng để tạo một mảng chứa thông tin bản tin
           yêu cầu/phản hồi các thông tin của sensor(loại bản tin, loại cảm biến...)
    @param datain: Là một struct chưa các thông tin được người dùng chỉ định để tạo bản tin.
    @param dataout: Là con trỏ dùng để lấy mảng sao khi tạo thành công.
    @retval: Độ dài của mảng dataout.
*/
uint8_t BTS_Message_Create_Frame_Sensor(sensorFrameMsg_t Sensor_DataIn, uint8_t *Sensor_DataOut)
{
    uint8_t *data_sensor_temp;
    uint16_t count_arr_data = 0;
    uint16_t count_arr_sensor = 0;
    sensorFrameMsg_t *frame_sensor_temp;
    /*dùng con trỏ frame_sensor_temp trỏ đến Sensor_DataIn*/
    frame_sensor_temp = &Sensor_DataIn;
    /*ép kiểu frame_sensor_temp về kiểu uint8_t, mục đích để chuyển từ struct -> arr*/
    data_sensor_temp = (uint8_t *)frame_sensor_temp;

    switch (Sensor_DataIn.TypeMessage)
    {
    case TYPE_MESSAGE_SENSOR_REQUEST:
        Sensor_DataIn.LengthData = LENGTH_SENSOR_REQUEST;
        break;

    default:
        for (count_arr_sensor = 0; count_arr_sensor < TYPE_SENSOR_SIZE; count_arr_sensor++)
        {
            if (Sensor_DataIn.TypeDevice == type_sensor_arr[count_arr_sensor])
            {
                Sensor_DataIn.LengthData = LENGTH_SENSOR_REQUEST + length_sensor_arr[count_arr_sensor];
            }
        }
        break;
    }
    /*tính toán checksum, length = LENGTH_DEFAULT(6byte) + Sensor_DataIn.length(tính theo bên trên)*/
    Sensor_DataIn.CheckFrame = CheckSum(data_sensor_temp, (LENGTH_DEFAULT + Sensor_DataIn.LengthData));
    /*Copy từ mảng data_sensor_temp ra mảng Sensor_DataOut*/
    for (count_arr_data = 0; count_arr_data < (LENGTH_DEFAULT + Sensor_DataIn.LengthData); count_arr_data++)
    {
        Sensor_DataOut[count_arr_data] = data_sensor_temp[count_arr_data];
    }
    /*Ghi giá trị checksum tính được vào cuối mảng*/
    Sensor_DataOut[count_arr_data] = (Sensor_DataIn.CheckFrame & 0xff);
    Sensor_DataOut[count_arr_data + 1] = ((Sensor_DataIn.CheckFrame >> 8) & 0xff);
    /*tăng giá trị mảng lên 2 lần vì đã thêm ở trên*/
    count_arr_data += 2;
    return count_arr_data;
}

/*
    @brief: Giải mã bản tin Sensor từ mảng sang dạng struct.
    @node: Chức năng hàm được sử dụng để giải mã ra một struct các thông tin
            của Sensor(loại bản tin, loại cảm biến...) từ mảng thông tin.
    @param datain: Là một mảng data của bản tin cần được giải mã sang dạng bản tin struct của Sensor.
    @param dataout: Là con trỏ dùng để lấy bản tin struct Sensor sau khi giải mã thành công.
    @retval: 0.
*/
uint8_t BTS_Message_Detect_Frame_Sensor(uint8_t *Sensor_DataIn, sensorFrameMsg_t *Sensor_DataOut)
{
    uint8_t temp = 0;

    Sensor_DataOut->StartFrame = Bts_Convert_From_Bytes_To_Uint16(Sensor_DataIn[temp], Sensor_DataIn[temp + 1]);
    temp += 2;
    Sensor_DataOut->TypeMessage = Bts_Convert_From_Bytes_To_Uint16(Sensor_DataIn[temp], Sensor_DataIn[temp + 1]);
    temp += 2;
    Sensor_DataOut->TypeDevice = Bts_Convert_From_Bytes_To_Uint16(Sensor_DataIn[temp], Sensor_DataIn[temp + 1]);
    temp += 2;
    Sensor_DataOut->LengthData = Bts_Convert_From_Bytes_To_Uint16(Sensor_DataIn[temp], Sensor_DataIn[temp + 1]);
    temp += 2;
    switch (Sensor_DataOut->TypeMessage)
    {
    case TYPE_MESSAGE_SENSOR_REQUEST:
        Sensor_DataOut->SensorName = Bts_Convert_From_Bytes_To_Uint16(Sensor_DataIn[temp], Sensor_DataIn[temp + 1]); /* code */
        temp += 2;
        break;
    default:
        temp += 2;
        if (Sensor_DataOut->TypeDevice == TYPE_SENSOR_NTC)
        {
            Sensor_DataOut->Data[0] = Sensor_DataIn[temp++];
            Sensor_DataOut->Data[1] = Sensor_DataIn[temp++];
            Sensor_DataOut->Data[2] = Sensor_DataIn[temp++];
            Sensor_DataOut->Data[3] = Sensor_DataIn[temp++];
        }
        else
        {
            Sensor_DataOut->Data[0] = Sensor_DataIn[temp++];
        }
        break;
    }
    Sensor_DataOut->CheckFrame = Bts_Convert_From_Bytes_To_Uint16(Sensor_DataIn[temp], Sensor_DataIn[temp + 1]);
    return 0;
}

/*
    @brief: Tạo mảng data chuẩn frame bản tin Device.
    @node: Chức năng hàm được sử dụng để tạo một mảng chứa thông tin bản tin
           yêu cầu/phản hồi các thông tin của Device(loại bản tin, loại cảm biến...)
    @param datain: Là một struct chưa các thông tin được người dùng chỉ định để tạo bản tin.
    @param dataout: Là con trỏ dùng để lấy mảng sao khi tạo thành công.
    @retval: Độ dài của mảng dataout.
*/
uint8_t BTS_Message_Create_Frame_Device(deviceFrameMsg_t Device_DataIn, uint8_t *Device_DataOut)
{
    uint8_t *data_device_temp;
    uint16_t count_arr_data = 0;
    deviceFrameMsg_t *frame_device_temp;
    /*dùng con trỏ frame_device_temp trỏ đến Device_DataIn*/
    frame_device_temp = &Device_DataIn;
    /*ép kiểu frame_device_temp về kiểu uint8_t, mục đích để chuyển từ struct -> arr*/
    data_device_temp = (uint8_t *)frame_device_temp;
    switch (Device_DataIn.TypeMessage)
    {
    case TYPE_MESSAGE_DEVICE_REQUEST:
        Device_DataIn.LengthData = LENGTH_DEVICE_REQUEST;
        break;

    case TYPE_MESSAGE_DEVICE_RESPONSE:
        Device_DataIn.LengthData = LENGTH_DEVICE_RESPONSE;
        break;
    }
    /*tính toán checksum, length = LENGTH_DEFAULT(6byte) + Sensor_DataIn.length(tính theo bên trên)*/
    Device_DataIn.CheckFrame = CheckSum(data_device_temp, (LENGTH_DEFAULT + Device_DataIn.LengthData));
    /*Copy từ mảng data_sensor_temp ra mảng Sensor_DataOut*/
    for (count_arr_data = 0; count_arr_data < (LENGTH_DEFAULT + Device_DataIn.LengthData); count_arr_data++)
    {
        Device_DataOut[count_arr_data] = data_device_temp[count_arr_data];
    }
    /*Ghi giá trị checksum tính được vào cuối mảng*/
    Device_DataOut[count_arr_data] = (Device_DataIn.CheckFrame & 0xff);
    Device_DataOut[count_arr_data + 1] = ((Device_DataIn.CheckFrame >> 8) & 0xff);
    /*tăng giá trị mảng lên 2 lần vì đã thêm ở trên*/
    count_arr_data += 2;
    return count_arr_data;
}

/*
    @brief: Giải mã bản tin Device từ mảng sang dạng struct.
    @node: Chức năng hàm được sử dụng để giải mã ra một struct các thông tin
            của Device(loại bản tin, loại cảm biến...) từ mảng thông tin.
    @param datain: Là một mảng data của bản tin cần được giải mã sang dạng bản tin struct của Device.
    @param dataout: Là con trỏ dùng để lấy bản tin struct Device sau khi giải mã thành công.
    @retval: 0.
*/
uint8_t BTS_Message_Detect_Frame_Device(uint8_t *Device_DataIn, deviceFrameMsg_t *Device_DataOut)
{
    uint8_t temp = 0;
    Device_DataOut->StartFrame = Bts_Convert_From_Bytes_To_Uint16(Device_DataIn[temp], Device_DataIn[temp + 1]);
    temp += 2;
    Device_DataOut->TypeMessage = Bts_Convert_From_Bytes_To_Uint16(Device_DataIn[temp], Device_DataIn[temp + 1]);
    temp += 2;
    Device_DataOut->TypeDevice = Bts_Convert_From_Bytes_To_Uint16(Device_DataIn[temp], Device_DataIn[temp + 1]);
    temp += 2;
    Device_DataOut->LengthData = Bts_Convert_From_Bytes_To_Uint16(Device_DataIn[temp], Device_DataIn[temp + 1]);
    temp += 2;
    Device_DataOut->DeviceName = Bts_Convert_From_Bytes_To_Uint16(Device_DataIn[temp], Device_DataIn[temp + 1]);
    temp += 2;
    Device_DataOut->CommandType = Device_DataIn[temp++];
    if (Device_DataOut->TypeMessage == TYPE_MESSAGE_DEVICE_RESPONSE)
    {
        Device_DataOut->StatusDevice = Device_DataIn[temp++];
    }
    Device_DataOut->CheckFrame = Bts_Convert_From_Bytes_To_Uint16(Device_DataIn[temp], Device_DataIn[temp + 1]);
    return 0;
}

/*
    @brief: Tạo mã checksum riêng cho bản tin.
    @node: Hàm được dùng để tạo mã Checksum của bản tin từ các thông tin trong bản tin.
    @param buf: Là một mảng data của bản tin để tạo checksum.
    @param len: Là chiều dài mảng data để tạo checksum.
    @retval: 0.
*/
uint16_t CheckSum(uint8_t *buf, uint8_t len)
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
