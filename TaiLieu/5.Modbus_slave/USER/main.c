#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "ModbusRTU_Slave.h"

int main()
{
	char data[10] = "1234567890";
	systick_config();
	USART_Config(9600);
	ModbusRegister[0] = 10;
	ModbusRegister[1] = 15;
	ModbusRegister[2] = 20;
	ModbusRegister[3] = 4;
	ModbusRegister[4] = 5;
	ModbusRegister[5] = 6;

	ModbusCoil[0] = 1;
	ModbusCoil[1] = 1;
	ModbusCoil[2] = 1;
	ModbusCoil[3] = 1;
	ModbusCoil[4] = 1;
	ModbusCoil[5] = 1;
	ModbusCoil[6] = 1;
	ModbusCoil[7] = 1;
	ModbusCoil[8] = 1;
	ModbusCoil[9] = 1;
	ModbusCoil[10] = 1;
	ModbusCoil[11] = 0;
	while(1)
	{
		makePacket_03(data, 10);
		delay_1ms(1000);
	}
}



