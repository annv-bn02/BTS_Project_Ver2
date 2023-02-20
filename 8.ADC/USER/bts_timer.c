#include "bts_timer.h"

static uint8_t stt = 0;

void Timer_Init(void) {
 
  timer_parameter_struct timer_initpara;
	rcu_periph_clock_enable(RCU_TIMER2);
  timer_deinit(TIMER2);

  /* TIMER0 configuration */
  timer_initpara.prescaler = 6;
  timer_initpara.alignedmode = TIMER_COUNTER_DOWN;
  timer_initpara.counterdirection = TIMER_COUNTER_DOWN;
  timer_initpara.period = 15;
  timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
  timer_initpara.repetitioncounter = 0;
  timer_init(TIMER2, &timer_initpara);
	timer_repetition_value_config(TIMER2, 0);
	
	/* channel 0 interrupt enable */
	timer_interrupt_enable(TIMER2,TIMER_INT_UP);
	nvic_irq_enable(TIMER2_IRQn, 0, 0);
	timer_flag_clear(TIMER2, TIMER_INT_UP);
  timer_enable(TIMER2);
}

void TIMER2_IRQHandler(void)
{
	if(RESET != timer_interrupt_flag_get(TIMER2,TIMER_INT_UP))
	{
			timer_interrupt_flag_clear(TIMER2,TIMER_INT_UP);
			gpio_bit_write(GPIOA,GPIO_PIN_1, stt);
		  stt =! stt;
	}
}
