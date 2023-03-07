#include "usart.h"
#include "string.h"
#include "delay.h"
char vr_Numberal[100][100];
char vr_Recei[1000];
char vr_GetChar;
int vr_locate = 0;
unsigned int count=0;
unsigned int Stt=0;


int USART_FlagDB(void)
{
	if(Stt==1)
	{
		Stt=0;
		return 1;
	}
	else 
		return 0;
}

unsigned int Numberal(int vr_Num, int vr_locate)
{
	unsigned int vr_number_of_digits=1;
	while(vr_Num>0)
	{
		vr_Numberal[vr_locate][vr_number_of_digits++] = vr_Num%10;
//		003 012 031
		vr_Num /= 10;
	}
	return vr_number_of_digits;
}
//123
void USART_SendNum(int vr_Num) 
{
	int vr_number_of_digits;
	
	vr_number_of_digits = Numberal(vr_Num,vr_locate)-1;
	while(vr_number_of_digits>0)
	{
		USART_SendChar(vr_Numberal[vr_locate][vr_number_of_digits]+'0');
		vr_number_of_digits--;
	}
	
}

void USART_Config(unsigned int Baurates)
{
    GPIO_InitTypeDef GPIO_Struct;
	USART_InitTypeDef USART_Struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_Struct.GPIO_Mode	 = GPIO_Mode_AF_PP;
	GPIO_Struct.GPIO_Pin     = GPIO_Pin_9;
	GPIO_Struct.GPIO_Speed	 = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
	GPIO_Struct.GPIO_Mode	 = GPIO_Mode_IN_FLOATING;
	GPIO_Struct.GPIO_Pin     = GPIO_Pin_10;
	GPIO_Struct.GPIO_Speed	 = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
	USART_Struct.USART_BaudRate 			= Baurates;
	USART_Struct.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
	USART_Struct.USART_Mode 				= USART_Mode_Rx|USART_Mode_Tx;
	USART_Struct.USART_Parity      			= USART_Parity_No;
	USART_Struct.USART_StopBits 			= USART_StopBits_1;
	USART_Struct.USART_WordLength 			= USART_WordLength_8b;
	USART_Init(USART1,&USART_Struct);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
	USART_Cmd(USART1,ENABLE);
}

void USART_SendChar(char vr_Char)
{
	USART_SendData(USART1,vr_Char);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}

void USART_SendString(char *vr_Str)
{
	while(*vr_Str != 0)
	{
		USART_SendChar(*vr_Str++);
	}
}


void USART_SendArrayData(void)
{
	uint16_t i;
	int8_t array_test_sensor[50] = {0x55, 0xaa, 0x01, 0x00, 0x2a, 0x00, 0x41, 0xa4, 0x00, 0x00, 0x41, 0xac, 0x00, 0x00, 0x41, 0xb4,
	0x00, 0x00, 0x41, 0xbc, 0x00, 0x00, 0x41, 0xc4, 0x00, 0x00, 0x41, 0xcc, 0x00, 0x00, 0x41, 0xd4, 0x00, 0x00, 0x41, 0xdc, 
	0x00, 0x00, 0x41, 0xe4, 0x00, 0x00, 0x41, 0xec, 0x00, 0x00, 0xb0, 0x9c};
	int8_t array_test_device[50] = {0x55, 0xaa, 0x02, 0x00, 0x2a, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
     0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 
     0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0xbl, 0xf3};
	for(i = 0;i < 48;i++)
	{
		USART_SendChar((uint8_t) array_test_sensor[i]);
	}
	Delay(100);
	for(i = 0;i < 48;i++)
	{
		USART_SendChar((uint8_t) array_test_device[i]);
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		vr_GetChar = USART_ReceiveData(USART1);
		if(vr_GetChar != '\n')
		{
			vr_Recei[count] = vr_GetChar;
			count++;
		}
		else
		{
			Stt=1;
			vr_Recei[count-1] = 0;
			count = 0;
		}
	}
}

int USART_Compare(char* vr_String)
{
	unsigned char status=1;
	if(strcmp(vr_String,vr_Recei)!=0)
	{
		status=0;
	}
	return status;
}
