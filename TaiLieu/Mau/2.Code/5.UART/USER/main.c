#include "gd32f30x_gpio.h"
#include "gd32f30x_eval.h"
#include "gd32f30x.h"
#include "systick.h"
#include <stdio.h>
#include "bts_uart.h"

int main()
{
		systick_config();
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_8|GPIO_PIN_9);
		rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_8);
    while(1)
		{
			gpio_bit_write(GPIOC,GPIO_PIN_8, 0);
			delay_1ms(500);
			gpio_bit_write(GPIOC,GPIO_PIN_8, 1);
			delay_1ms(500);
			
			gpio_bit_write(GPIOC,GPIO_PIN_9, 0);
			delay_1ms(500);
			gpio_bit_write(GPIOC,GPIO_PIN_9, 1);
			delay_1ms(500);
			
			gpio_bit_write(GPIOA,GPIO_PIN_8, 0);
			delay_1ms(500);
			gpio_bit_write(GPIOA,GPIO_PIN_8, 1);
			delay_1ms(500);
    }
	return 0;
}