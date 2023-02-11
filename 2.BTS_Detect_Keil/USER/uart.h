 
/*
  ******************************************************************************
  * @file		Uart.h                                                              *
  * @author	Nguyen Quang Bien                                                  *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef __UART__
#define __UART__
#include "stm32f10x.h"
#include "stdio.h"
#ifdef __cplusplus
 extern "C" {
#endif
	 
#define  UART1_BAUDRATE (9600)
#define  UART2_BAUDRATE (9600)
#define  UART3_BAUDRATE (9600)
	 
#define string_size 20
	
#include "stdio.h"
#include <stdarg.h>
#include "bts_convert.h"
#include <stdint.h>

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

extern uint8_t array_out[50];	
	
extern char Flag1_Receive;
extern char Array1_Receive[];
extern char Count1_Data;
	 
extern char Flag2_Receive;
extern char Array2_Receive[];
extern char Count2_Data;

extern char Flag3_Receive;
extern char Array3_Receive[];
extern char Count3_Data;	 
	 
void INIT_UART(void);
int UART1_Flag(void);
int UART1_Flag_Fsm(void);
void INIT_UART_1(unsigned int BaudRates);
void UART1_SendChar(char data);
void UART1_SendString(char *data);
void UART1_SendByte(uint8_t *data, uint8_t sizes); 

void INIT_UART_2(unsigned int BaudRates);
void UART2_SendChar(char data);
void UART2_SendString(char *data);
void UART2_SendByte(uint8_t *data, uint8_t sizes); 

void INIT_UART_3(unsigned int BaudRates);
void UART3_SendChar(char data);		 
void UART3_SendString(char *data);



#ifdef __cplusplus
}
#endif

#endif

