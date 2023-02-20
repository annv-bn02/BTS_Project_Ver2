#include "gd32f30x_gpio.h"
#include "gd32f30x_eval.h"
#include "gd32f30x.h"
#include "systick.h"
#include <stdio.h>
#include "bts_uart.h"
#include "bts_timer.h"
#include "bts_adc.h"
int main()
{
	systick_config();
	SmartBTS_USART1_Init();
	BTS_ADC_Init();

	while(1)
	{
		adc_software_trigger_enable(ADC1, ADC_REGULAR_CHANNEL);
		BTS_ADC_Read();
		delay_1ms(500);
	}
}





