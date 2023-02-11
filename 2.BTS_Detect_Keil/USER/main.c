#include "stm32f10x.h"                  // Device header
#include "uart.h"
#include "bts_convert.h"
#include "bts_message.h"
#include "bts_debug_detect.h"
uint8_t Recei[1000];
int main()
{
	INIT_UART_1(UART1_BAUDRATE);
	INIT_UART_2(UART2_BAUDRATE);
	while(1)
	{
		BTS_Debug_Detect_Frame();
	}
}


