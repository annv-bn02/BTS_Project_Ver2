#include "usart.h"
#include "string.h"
#include "ModbusRTU_Slave.h"
GPIO_TypeDef* GPIOx;
USART_TypeDef* USARTx = USART1;
char vr_Recei[1000];
char vr_Numberal[100][100];
char vr_GetChar;
int vr_locate = 0;
unsigned int count=0;
unsigned int stt_flag=0;
uint16_t Tx_pin,Rx_pin;
struct __FILE 
{
	int dummy;
};
FILE __stdout;
int fputc(int ch, FILE *f) 
{
	USART_SendChar(ch);
	return ch;
}

int USART_FlagDB(void)
{
	if(stt_flag==1)
	{
		stt_flag=0;
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
	if(USARTx == USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
		Tx_pin = GPIO_Pin_9;
		Rx_pin = GPIO_Pin_10;
		GPIOx = GPIOA;
	}
	else if(USARTx == USART2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		Tx_pin = GPIO_Pin_2;
		Rx_pin = GPIO_Pin_3;
		GPIOx = GPIOA;
	}
	else if(USARTx == USART3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		Tx_pin = GPIO_Pin_10;
		Rx_pin = GPIO_Pin_11;
		GPIOx = GPIOB;
	}
	
	GPIO_Struct.GPIO_Mode	 = GPIO_Mode_AF_PP;
	GPIO_Struct.GPIO_Pin     = Tx_pin;
	GPIO_Struct.GPIO_Speed	 = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&GPIO_Struct);
	
	GPIO_Struct.GPIO_Mode	 = GPIO_Mode_IN_FLOATING;
	GPIO_Struct.GPIO_Pin     = Rx_pin;
	GPIO_Struct.GPIO_Speed	 = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&GPIO_Struct);
	
	USART_Struct.USART_BaudRate 			= Baurates;
	USART_Struct.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
	USART_Struct.USART_Mode 				= USART_Mode_Rx|USART_Mode_Tx;
	USART_Struct.USART_Parity      			= USART_Parity_No;
	USART_Struct.USART_StopBits 			= USART_StopBits_1;
	USART_Struct.USART_WordLength 			= USART_WordLength_8b;
	USART_Init(USARTx,&USART_Struct);
	
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_EnableIRQ(USART2_IRQn);
	NVIC_EnableIRQ(USART3_IRQn);
	USART_Cmd(USARTx,ENABLE);
}


void Delay_ms(unsigned int vr_Time)
{
	unsigned int i,j;
	for(i=0;i<vr_Time;i++)
	{
		for(j=0;j<0x2aff;j++)
		{
		
		}
	}
}

void USART_SendChar(char vr_Char)
{
	USART_SendData(USARTx,vr_Char);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
}

void USART_SendString(char *vr_Str)
{
	while(*vr_Str != 0)
	{
		USART_SendChar(*vr_Str++);
	}
}

void USART_SendOneByte(const uint8_t data)
{
	USART_SendData(USARTx,(uint8_t)data);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
}

void USART_SendArrayBytes(const uint8_t *vr_datain, const uint16_t vr_arrsize)
{
	uint8_t vr_countlength;
	for(vr_countlength = 0; vr_countlength < vr_arrsize; vr_countlength++)
	{
		USART_SendOneByte(vr_datain[vr_countlength]);
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
			stt_flag=1;
			vr_Recei[count-1] = 0;
			count = 0;
		}
	}
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		vr_GetChar = USART_ReceiveData(USART2);
		if(vr_GetChar != '\n')
		{
			vr_Recei[count] = vr_GetChar;
			count++;
		}
		else
		{
			stt_flag=1;
			vr_Recei[count-1] = 0;
			count = 0;
		}
	}
}

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		vr_GetChar = USART_ReceiveData(USART3);
		if(vr_GetChar != '\n')
		{
			vr_Recei[count] = vr_GetChar;
			count++;
		}
		else
		{
			stt_flag=1;
			vr_Recei[count-1] = 0;
			count = 0;
		}
	}
}

int USART_Compare(char* vr_String)
{
	unsigned char stt_compare=1;
	if(strcmp(vr_String,vr_Recei)!=0)
	{
		stt_compare=0;
	}
	return stt_compare;
}
