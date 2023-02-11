#ifndef __UART3__
#define __UART3__
	
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include "gd32f30x.h"
#include "gd32f30x_usart.h"
	
#include "bts_sys.h"

/*
    -Enum ch?a thông tin các tr?ng thái c?a máy tr?ng thái nh?n USART.
*/
#define FSM_STATE 5 /* Ð? dài ph?n t? có trong fsm_state_e */
typedef enum
{
	FSM_STATE_START_FRAME = 0,
	FSM_STATE_TYPE_MESSAGE = 1,
	FSM_STATE_TYPE_DEVICE = 2,
	FSM_STATE_LENGHT_DATA = 3,
	FSM_STATE_END = 4,
} fsm_state_e;

/*
-Enum ch?a các giá tr? t?i dó thay d?i tr?ng thái c?a máy tr?ng thái nh?n USART.
*/
typedef enum
{
	FSM_STATE_CHANGE_VALUE_START_FRAME = 0,
	FSM_STATE_CHANGE_VALUE_TYPE_MESSAGE = 2,
	FSM_STATE_CHANGE_VALUE_TYPE_DEVICE = 4,
	FSM_STATE_CHANGE_VALUE_LENGHT_DATA = 6,
	FSM_STATE_CHANGE_VALUE_END = 8,
} fsm_state_change_value_e;

#define  Array_Out_Size 50

extern uint8_t vru8_bts_uart_fsm_array_out[Array_Out_Size];	
	
extern uint8_t vru8_uart3_rxbuffer[];
extern __IO uint16_t vru16_uart3_rxcount; 
extern __IO uint8_t vru16_uart3_flag_rx;
	
extern int8_t TimeOut_Wait;
extern uint8_t TimeOut_Count;

void SmartBTS_USART3_Init(void);
void SmartBTS_USART3_SendChar(const uint8_t vr_datain);
void SmartBTS_USART3_SendString(const char *vr_datain);
void SmartBTS_USART3_SendOneByte(const uint8_t vr_datain);
void SmartBTS_USART3_SendArrayByte(const uint8_t *vr_datain, const uint16_t vr_arrsize );	

void SmartBTS_USART3_FSM_TimeOut(void);

#ifdef __cplusplus
}
#endif

#endif
