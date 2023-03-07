#include "gd32f30x_gpio.h"
#include "gd32f30x_eval.h"
#include "gd32f30x.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

int i = 0, j = 0, k = 0;
void Fn_RTOS_TaskLed1(void *p);
void Fn_RTOS_TaskLed2(void *p);
void Fn_RTOS_TaskLed3(void *p);

int main()
{
	rcu_periph_clock_enable(RCU_GPIOC);
	gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_8|GPIO_PIN_9);
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_8);
	gpio_bit_write(GPIOC,GPIO_PIN_9, 1);
	gpio_bit_write(GPIOA,GPIO_PIN_8, 1);
	xTaskCreate(Fn_RTOS_TaskLed1, (const char*) "Red LED Blink", 128, NULL, 1, NULL);
	xTaskCreate(Fn_RTOS_TaskLed2, (const char*) "Red LED Blink", 128, NULL, 1, NULL);
	xTaskCreate(Fn_RTOS_TaskLed3, (const char*) "Red LED Blink", 128, NULL, 1, NULL);
	vTaskStartScheduler();
//    while(1)
//		{
//			gpio_bit_write(GPIOC,GPIO_PIN_8, 0);
//			gpio_bit_write(GPIOC,GPIO_PIN_8, 1);
//	
//			
//			gpio_bit_write(GPIOC,GPIO_PIN_9, 0);
//			gpio_bit_write(GPIOC,GPIO_PIN_9, 1);

//			
//			gpio_bit_write(GPIOA,GPIO_PIN_8, 0);
//			gpio_bit_write(GPIOA,GPIO_PIN_8, 1);

//    }
	return 0;
}

void Fn_RTOS_TaskLed1(void *p){
	while(1)
	{
		gpio_bit_write(GPIOC,GPIO_PIN_8, i);
		i =! i;
		vTaskDelay(100/portTICK_RATE_MS);
	}
}

void Fn_RTOS_TaskLed2(void *p){
	while(1){
		gpio_bit_write(GPIOC, GPIO_PIN_9, j);
		j =! j;
		vTaskDelay(1000/portTICK_RATE_MS);
	}
}

void Fn_RTOS_TaskLed3(void *p){
	while(1){
		gpio_bit_write(GPIOA, GPIO_PIN_8, k);
		k =! k;
		vTaskDelay(500/portTICK_RATE_MS);
	}
}
