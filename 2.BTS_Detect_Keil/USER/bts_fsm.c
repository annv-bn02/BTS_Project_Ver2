#include "bts_fsm.h"
#include "bts_convert.h"
fsm_state_e fsm_state = FSM_STATE_START_FRAME;
uint16_t bts_fsm_count = 0;
uint16_t bts_fsm_data_lenght;
/*
    @brief: Máy trạng thái nhận data USART và ghép vào mảng data.
    @node: Hàm nhận data qua USART rồi truyền vào mảng data theo đúng thứ tự, chức năng .
    @param DataIn: Là một data 1byte được nhận qua USART rồi truyền sang ArrayOut.
    @param ArrayOut: Là một mảng data thông tin được nhận.
    @retval: 0.
*/
uint8_t Bts_Fsm_Usart(uint8_t DataIn, uint8_t *ArrayOut)
{
    switch (fsm_state)
    {
    case FSM_STATE_START_FRAME:

        ArrayOut[bts_fsm_count] = DataIn;
        bts_fsm_count++;
        if (bts_fsm_count == FSM_STATE_CHANGE_VALUE_TYPE_MESSAGE)
        {
            fsm_state = FSM_STATE_TYPE_MESSAGE;
        }
        break;
    case FSM_STATE_TYPE_MESSAGE:
        ArrayOut[bts_fsm_count] = DataIn;
        bts_fsm_count++;
        if (bts_fsm_count == FSM_STATE_CHANGE_VALUE_TYPE_DEVICE)
        {
            fsm_state = FSM_STATE_TYPE_DEVICE;
        }
        break;
    case FSM_STATE_TYPE_DEVICE:
        ArrayOut[bts_fsm_count] = DataIn;
        bts_fsm_count++;
        if (bts_fsm_count == FSM_STATE_CHANGE_VALUE_LENGHT_DATA)
        {
            fsm_state = FSM_STATE_LENGHT_DATA;
        }
        break;
    case FSM_STATE_LENGHT_DATA:
        ArrayOut[bts_fsm_count] = DataIn;
        bts_fsm_count++;
        if (bts_fsm_count == FSM_STATE_CHANGE_VALUE_END)
        {
            // Do các frame data có chiều dài khác nhau nên cần đọc data lenght lưu vào biến lenght mục đích để nhận các data kế tiếp chính xác
            // lenght = data lenght + 8byte chua thong tin phia truoc.
            bts_fsm_data_lenght = Bts_Convert_From_Bytes_To_Uint16(ArrayOut[6], ArrayOut[7]) + 8;
            if (bts_fsm_count == FSM_STATE_CHANGE_VALUE_END && bts_fsm_data_lenght < 24)
            {
                fsm_state = FSM_STATE_END;
            }
            else if (bts_fsm_count == FSM_STATE_CHANGE_VALUE_END && bts_fsm_data_lenght > 24)
            {
                bts_fsm_count = 0;
                fsm_state = FSM_STATE_START_FRAME;
                return 1;
            }
        }
        break;
    case FSM_STATE_END:
        ArrayOut[bts_fsm_count] = DataIn;
        bts_fsm_count++;
        if (bts_fsm_count == bts_fsm_data_lenght)
        {
            bts_fsm_count = 0;
            fsm_state = FSM_STATE_START_FRAME;
            return 1;
        }
        break;
    }
    return 0;
}