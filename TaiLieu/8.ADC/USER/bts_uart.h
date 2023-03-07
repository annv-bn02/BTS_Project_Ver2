#ifndef __UART__
#define __UART__
	
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include "gd32f30x.h"
#include "gd32f30x_usart.h"
	
extern uint8_t vru8_uart1_rxbuffer[];
extern __IO uint16_t vru16_uart1_rxcount; 
extern __IO uint8_t vru16_uart1_flag_rx;
	
void SmartBTS_USART1_Init(void);
void SmartBTS_USART1_SendChar(const uint8_t vr_datain);
void SmartBTS_USART1_SendString(const uint8_t *vr_datain);
void SmartBTS_USART1_SendOneByte(const uint8_t vr_datain);
void SmartBTS_USART1_SendArrayByte(const uint8_t *vr_datain, const uint16_t vr_arrsize );		
#ifdef __cplusplus
}
#endif

#endif
