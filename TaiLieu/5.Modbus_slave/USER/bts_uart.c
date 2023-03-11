#include "bts_uart.h"
#include "bts_uart3.h"
#include "bts_modbus.h"
#define UART_FSM 0

uint8_t vru8_uart1_rxbuffer[100];
__IO uint16_t vru16_uart1_rxcount; 
__IO uint8_t vru16_uart1_flag_rx = 0;
/* You need this if you want use printf */
/* Struct FILE is implemented in stdio.h */
struct __FILE {
    int dummy;
};
FILE __stdout;

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
	SmartBTS_USART1_SendChar(ch);
	return ch;
}

void SmartBTS_USART1_Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_USART0);
	rcu_periph_clock_enable(RCU_AF);
	/* configure USART Tx as alternate function push-pull */
	gpio_init(GPIOA,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9);
	gpio_init(GPIOA,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO_PIN_10);

	usart_baudrate_set(USART0, 115200);
	/* configure USART transmitter */
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
	/* configure USART receiver */
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);
	/* enable USART */
	usart_interrupt_enable(USART0, USART_INT_RBNE);
	nvic_irq_enable(USART0_IRQn, 0, 0);
	usart_enable(USART0);
}

void SmartBTS_USART1_SendChar(const uint8_t vr_datain)
{
	usart_data_transmit(USART0, vr_datain);
	while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
}

void SmartBTS_USART1_SendString(const uint8_t *vr_datain)
{
	while(*vr_datain)
	{
		SmartBTS_USART1_SendChar(*vr_datain);
		vr_datain++;
	}
}

void SmartBTS_USART1_SendOneByte(const uint8_t vr_datain)
{
	usart_data_transmit(USART0, (uint8_t)vr_datain);
	while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
}

void SmartBTS_USART1_SendArrayByte(const uint8_t *vr_datain, const uint16_t vr_arrsize)
{
	uint8_t vr_countlength;
	for(vr_countlength = 0; vr_countlength < vr_arrsize; vr_countlength++)
	{
		SmartBTS_USART1_SendOneByte(vr_datain[vr_countlength]);
	}
}

void USART0_IRQHandler(void)
{
	uint8_t vr_tempchar;
	if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))
	{
		//vr_tempchar = usart_data_receive(USART0);
		//MBRTUMasterRecvByteISRCallback(&MBRTUHandle, vr_tempchar);
	}
}

//void USART0_IRQHandler(void)
//{
//	uint8_t vr_tempchar;
//	if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))
//	{
//		vr_tempchar = usart_data_receive(USART0);
//		if(vr_tempchar != '\n')
//		{	
//			vru8_uart1_rxbuffer[vru16_uart1_rxcount] = vr_tempchar;
//			vru16_uart1_rxcount++;
//		}
//		else
//		{
//			vru8_uart1_rxbuffer[vru16_uart1_rxcount] = 0x00;
//			vru16_uart1_flag_rx = 1;
//			vru16_uart1_rxcount = 0;
//		}
//	}
//}



uint8_t array_out[50];

uint8_t uart3_rxbuffer[100];
__IO uint16_t uart3_rxcount; 
__IO uint8_t uart3_flag_rx = 0;

/**
 * @brief Configure the UART3 for 9600 baud rate, 8 data bits, 1 stop bit, no parity
 * 
 */
void SmartBTS_USART3_Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_UART3);
	rcu_periph_clock_enable(RCU_AF);
	/* configure USART Tx as alternate function push-pull */
	gpio_init(GPIOC,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_10);
	gpio_init(GPIOC,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO_PIN_11);

	usart_baudrate_set(UART3, 9600);
	/* configure USART transmitter */
	usart_transmit_config(UART3, USART_TRANSMIT_ENABLE);
	/* configure USART receiver */
	usart_receive_config(UART3, USART_RECEIVE_ENABLE);
	/* enable USART */
	usart_interrupt_enable(UART3, USART_INT_RBNE);
	
	/*Chon muc uu tien*/
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
	nvic_irq_enable(UART3_IRQn, 0, 0);
	usart_enable(UART3);
}

/**
 * @brief Send a character
 * 
 * @param datain 
 */
void SmartBTS_USART3_SendChar(const uint8_t datain)
{
	usart_data_transmit(UART3, datain);
	while(RESET == usart_flag_get(UART3, USART_FLAG_TBE));
}

/**
 * @brief send a string
 * 
 * @param datain 
 */
void SmartBTS_USART3_SendString(const char *datain)
{
	while(*datain)
	{
		SmartBTS_USART3_SendChar((uint8_t)*datain);
		datain++;
	}
}

/**
 * @brief Send a byte data
 * 
 * @param datain 
 */
void SmartBTS_USART3_SendOneByte(const uint8_t datain)
{
	usart_data_transmit(UART3, (uint8_t)datain);
	while(RESET == usart_flag_get(UART3, USART_FLAG_TBE));
}

/**
 * @brief Send array bytes data
 * 
 * @param datain 
 */
void SmartBTS_USART3_SendArrayByte(const uint8_t *datain, const uint16_t arrsize)
{
	uint8_t countlength;
	for(countlength = 0; countlength < arrsize; countlength++)
	{
		SmartBTS_USART3_SendOneByte(datain[countlength]);
	}
}

#if (UART_FSM == 1)
/**
 * @brief Received array data of message
 * 
 * @return uint8_t* : array data of message
 */
uint8_t* SmartBTS_USART3_Get_Array_Data(void)
{
	return array_out;
}

void UART3_IRQHandler(void) 
{
	uint8_t temp_data;
	
	if (RESET != usart_interrupt_flag_get(UART3, USART_INT_FLAG_RBNE)) 
	{
		temp_data = usart_data_receive(UART3);
		BTS_Get_Message(temp_data, array_out);
	}
}

#else
void UART3_IRQHandler(void)
{
	uint8_t vr_tempchar;
	if(RESET != usart_interrupt_flag_get(UART3, USART_INT_FLAG_RBNE))
	{
		vr_tempchar = usart_data_receive(UART3);
		MBRTUMasterRecvByteISRCallback(&MBRTUHandle, vr_tempchar);
	}
}

//void UART3_IRQHandler(void)
//{
//	uint8_t tempchar;
//	if(RESET != usart_interrupt_flag_get(UART3, USART_INT_FLAG_RBNE))
//	{
//		tempchar = usart_data_receive(UART3);
//		if(tempchar != '\n')
//		{	
//			uart3_rxbuffer[uart3_rxcount] = tempchar;
//			uart3_rxcount++;
//		}
//		else
//		{
//			uart3_rxbuffer[uart3_rxcount] = 0x00;
//			uart3_flag_rx = 1;
//			uart3_rxcount = 0;
//		}
//	}
//}
#endif

