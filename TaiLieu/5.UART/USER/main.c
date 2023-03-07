#include "gd32f30x_gpio.h"
#include "gd32f30x_eval.h"
#include "gd32f30x.h"
#include "systick.h"
#include <stdio.h>
#include "bts_uart.h"
#include "mosbus.h"

int main()
{
	systick_config();
    SmartBTS_USART0_Init();
    while(1)
	{
		
		if(uart0_flag_rx == 1)
		{
			uart0_flag_rx = 0;
			SmartBTS_USART0_SendString("okkkkkk");
		}
    }
	return 0;
}