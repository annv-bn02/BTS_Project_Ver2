#include "bts_uart3.h"

#define UART_FSM 1

fsm_state_e bts_uart_fsm_state = FSM_STATE_START_FRAME;
uint16_t vru16_bts_uart_fsm_count = 0;
uint16_t vru16_bts_uart_fsm_data_lenght;
uint8_t vru8_bts_uart_fsm_flag = 0;
uint8_t vru8_bts_uart_fsm_array_out[Array_Out_Size];

uint8_t vru8_uart3_rxbuffer[100];
__IO uint16_t vru16_uart3_rxcount; 
__IO uint8_t vru16_uart3_flag_rx = 0;

int8_t TimeOut_Wait ;
uint8_t TimeOut_Count ;

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
	SmartBTS_USART3_SendChar(ch);
	return ch;
}

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

void SmartBTS_USART3_SendChar(const uint8_t vr_datain)
{
	usart_data_transmit(UART3, vr_datain);
	while(RESET == usart_flag_get(UART3, USART_FLAG_TBE));
}

void SmartBTS_USART3_SendString(const char *vr_datain)
{
	while(*vr_datain)
	{
		SmartBTS_USART3_SendChar((uint8_t)*vr_datain);
		vr_datain++;
	}
}

void SmartBTS_USART3_SendOneByte(const uint8_t vr_datain)
{
	usart_data_transmit(UART3, (uint8_t)vr_datain);
	while(RESET == usart_flag_get(UART3, USART_FLAG_TBE));
}

void SmartBTS_USART3_SendArrayByte(const uint8_t *vr_datain, const uint16_t vr_arrsize)
{
	uint8_t vr_countlength;
	for(vr_countlength = 0; vr_countlength < vr_arrsize; vr_countlength++)
	{
		SmartBTS_USART3_SendOneByte(vr_datain[vr_countlength]);
	}
}

void SmartBTS_USART3_FSM_TimeOut(void)
{
	if(TimeOut_Wait == 0)
	{
		vru16_bts_uart_fsm_count = 0;
		bts_uart_fsm_state = FSM_STATE_START_FRAME;
	}
}

#if (UART_FSM == 1)
void UART3_IRQHandler(void) 
{
	uint8_t vr_temp_data;
	
	if (RESET != usart_interrupt_flag_get(UART3, USART_INT_FLAG_RBNE)) 
	{
		TimeOut_Count = 0;
		TimeOut_Wait = 1;
		vr_temp_data = usart_data_receive(UART3);
		switch (bts_uart_fsm_state)
		{
		case FSM_STATE_START_FRAME:
			vru8_bts_uart_fsm_array_out[vru16_bts_uart_fsm_count] = vr_temp_data;
			vru16_bts_uart_fsm_count++;
			if (vru16_bts_uart_fsm_count == FSM_STATE_CHANGE_VALUE_TYPE_MESSAGE)
			{
				bts_uart_fsm_state = FSM_STATE_TYPE_MESSAGE;
			}
			break;
		case FSM_STATE_TYPE_MESSAGE:
			vru8_bts_uart_fsm_array_out[vru16_bts_uart_fsm_count] = vr_temp_data;
			vru16_bts_uart_fsm_count++;
			if (vru16_bts_uart_fsm_count == FSM_STATE_CHANGE_VALUE_TYPE_DEVICE)
			{
				bts_uart_fsm_state = FSM_STATE_TYPE_DEVICE;
			}
			break;
		case FSM_STATE_TYPE_DEVICE:
			vru8_bts_uart_fsm_array_out[vru16_bts_uart_fsm_count] = vr_temp_data;
			vru16_bts_uart_fsm_count++;
			if (vru16_bts_uart_fsm_count == FSM_STATE_CHANGE_VALUE_LENGHT_DATA)
			{
				bts_uart_fsm_state = FSM_STATE_LENGHT_DATA;
			}
			break;
		case FSM_STATE_LENGHT_DATA:
			vru8_bts_uart_fsm_array_out[vru16_bts_uart_fsm_count] = vr_temp_data;
			vru16_bts_uart_fsm_count++;
			if (vru16_bts_uart_fsm_count == FSM_STATE_CHANGE_VALUE_END)
			{
				// Do c?c frame data c? chi?u d?i kh?c nhau n?n c?n d?c data lenght luu v?o bi?n lenght m?c d?ch d? nh?n c?c data k? ti?p ch?nh x?c
				// lenght = data lenght + 8byte chua thong tin phia truoc.
				vru16_bts_uart_fsm_data_lenght = Bts_Convert_From_Bytes_To_Uint16(vru8_bts_uart_fsm_array_out[6], vru8_bts_uart_fsm_array_out[7]) + 8;
				if (vru16_bts_uart_fsm_data_lenght < 24)
				{
					bts_uart_fsm_state = FSM_STATE_END;
				}
				else if (vru16_bts_uart_fsm_data_lenght > 24)
				{
					vru16_bts_uart_fsm_count = 0;
					bts_uart_fsm_state = FSM_STATE_START_FRAME;
				}
			}
			break;
		case FSM_STATE_END:
			vru8_bts_uart_fsm_array_out[vru16_bts_uart_fsm_count] = vr_temp_data;
			vru16_bts_uart_fsm_count++;
			if (vru16_bts_uart_fsm_count == vru16_bts_uart_fsm_data_lenght)
			{
				vru16_bts_uart_fsm_count = 0;
				bts_uart_fsm_state = FSM_STATE_START_FRAME;
				vru8_bts_uart_fsm_flag = 1;
				vru16_uart3_flag_rx = 1;
			}
			break;
		}
	}
}
#else
void UART3_IRQHandler(void)
{
	uint8_t vr_tempchar;
	if(RESET != usart_interrupt_flag_get(UART3, USART_INT_FLAG_RBNE))
	{
		vr_tempchar = usart_data_receive(UART3);
		if(vr_tempchar != '\n')
		{	
			vru8_uart3_rxbuffer[vru16_uart3_rxcount] = vr_tempchar;
			vru16_uart3_rxcount++;
		}
		else
		{
			vru8_uart3_rxbuffer[vru16_uart3_rxcount] = 0x00;
			vru16_uart3_flag_rx = 1;
			vru16_uart3_rxcount = 0;
		}
	}
}
#endif
