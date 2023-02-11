#ifndef __UART__
#define __UART__
	
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include "gd32f30x.h"
#include "gd32f30x_usart.h"
	
#include "bts_sys.h"



extern uint8_t vru8_uart0_rxbuffer[];
extern __IO uint16_t vru16_uart0_rxcount; 
extern __IO uint8_t vru16_uart0_flag_rx;	
	
void SmartBTS_USART0_Init(void);
void SmartBTS_USART0_SendChar(const uint8_t vr_datain);
void SmartBTS_USART0_SendString(const char *vr_datain);
void SmartBTS_USART0_SendOneByte(const uint8_t vr_datain);
void SmartBTS_USART0_SendArrayByte(const uint8_t *vr_datain, const uint16_t vr_arrsize );		
#ifdef __cplusplus
}
#endif

#endif
