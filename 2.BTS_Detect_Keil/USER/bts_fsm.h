
#ifndef __BTS_FSM__
#define __BTS_FSM__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
/*
    -Enum chứa thông tin các trạng thái của máy trạng thái nhận USART.
*/
#define FSM_STATE 5 /* Độ dài phần tử có trong fsm_state_e */
    typedef enum
    {
        FSM_STATE_START_FRAME = 0,
        FSM_STATE_TYPE_MESSAGE = 1,
        FSM_STATE_TYPE_DEVICE = 2,
        FSM_STATE_LENGHT_DATA = 3,
        FSM_STATE_END = 4,
    } fsm_state_e;

/*
    -Enum chứa các giá trị tại đó thay đổi trạng thái của máy trạng thái nhận USART.
*/
    typedef enum
    {
        FSM_STATE_CHANGE_VALUE_START_FRAME = 0,
        FSM_STATE_CHANGE_VALUE_TYPE_MESSAGE = 2,
        FSM_STATE_CHANGE_VALUE_TYPE_DEVICE = 4,
        FSM_STATE_CHANGE_VALUE_LENGHT_DATA = 6,
        FSM_STATE_CHANGE_VALUE_END = 8,
    } fsm_state_change_value_e;

    uint8_t Bts_Fsm_Usart(uint8_t DataIn, uint8_t *ArrayOut);
#ifdef __cplusplus
}
#endif

#endif