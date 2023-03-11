#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "bts_modbus.h"



 void mutex_lock(void)
{

}

 void mutex_unlock(void)
{

}

 void timerStop(void)
{
    count_modbus = 0;
}

 void timerStart(void)
{
    count_modbus = 1;
}

 void delayms(uint32_t nms)
{
    delay_1ms(nms);
}

 uint32_t sendData(const void* buf, uint32_t len)
{
	//SmartBTS_USART1_SendArrayByte(buf, len);
	USART_SendArrayBytes(buf, len);
    return len;
}

int main()
{
	int ret = 0;
	uint8_t count = 0;
	uint16_t ucBuf[50];
	char arr[50];
	systick_config();
	USART_Config(9600);
	MBRTUHandle.delayms = delayms;
	MBRTUHandle.timerStart = timerStart;
	MBRTUHandle.timerStop = timerStop;
	MBRTUHandle.sendData = sendData;
	while(1)
	{
		ret = MBRTUMasterReadHoldingRegisters(&MBRTUHandle, 1, 0, 0x25, 500, ucBuf);
		for(count=0; count<0x25; count++)
		{
			sprintf(arr, "%d = %d \n",count, ucBuf[count]);
			printf("%s", arr);
			delay_1ms(10);
		}
		delay_1ms(1000);
	}
}



