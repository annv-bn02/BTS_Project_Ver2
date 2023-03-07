#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "delay.h"                  // Device header

unsigned int tim_prescaler=7200;
unsigned int tim_period=10;
void Timer_Config(void)
{
	TIM_TimeBaseInitTypeDef Timer_struct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	Timer_struct.TIM_CounterMode = TIM_CounterMode_Up;
	Timer_struct.TIM_Prescaler = tim_prescaler - 1;
	Timer_struct.TIM_Period = 65535;
	TIM_TimeBaseInit(TIM2, &Timer_struct);

}

void Delay_ms(void)
{
	Timer_Config();
	TIM_Cmd(TIM2,ENABLE);
	TIM_SetCounter(TIM2,0);
	while(TIM_GetCounter(TIM2)<tim_period);
	TIM_Cmd(TIM2,DISABLE);
}

void Delay(unsigned int vr_Time)
{
	while(vr_Time--)
	{
		Delay_ms();
	}
}

	