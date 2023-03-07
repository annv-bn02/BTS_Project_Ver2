#include "stm32f10x.h"
#include "stdio.h"
#include "usart.h"
#include "delay.h"
int main()
{
	USART_Config(9600);
	while(1)
	{
		USART_SendArrayData();
		Delay(3000);
	}
}
