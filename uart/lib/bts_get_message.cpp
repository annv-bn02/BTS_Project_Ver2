
#include "bts_get_message.h"

int16_t length_message = 0;

static void ClearState(void);

static uint16_t Bytes_To_Uint16(uint8_t data1, uint8_t data2)
{
    data_format_uint8_16_t input_convert;
    input_convert.bytes[0] = data1;
    input_convert.bytes[1] = data2;
    return input_convert.data_uint16;
}
/**
 * @brief Get the Message:: Get Message objectL: parameters initialization 
 * 
 */
GetMessage::GetMessage(void)
{
	count_element_arr = 0;
	flag_new_message = false;
	fsm_state = FSM_STATE_START;

	timeout_start = 0;
	timeout_end = 0;
	timeout_wait = false;
}

/**
 * @brief Get the Message:: Is Message object 
 * Get new Message, notification for user has new message
 * @param length 
 * @return true - new message
 * @return false - not new message 
 */
bool GetMessage::IsMessage(uint16_t &length)
{
	if(flag_new_message == true)
	{
		flag_new_message = false;
		length = length_message;
		return 1;
	}
	return 0;
}
/**
 * @brief Get the Message:: Time Out object
 * time to receive the new message 
 * used to avoid the case where the message is long or the message is shorter than the message length
 */
void GetMessage::TimeOut(void)
{
	if(timeout_wait == true)
	{  
		timeout_end = clock();
		if((timeout_end - timeout_start) >= 20000)
		{		
			length_message = 0;
			flag_new_message = false;
			count_element_arr = 0;
			timeout_wait = false;
			fsm_state = FSM_STATE_START;
		}
	}
	else
	{
		timeout_start = 0;
		timeout_end = 0;
	}
}

/**
 * @brief Get the Message:: Get Messages object
 * used to get standard message from the message buffer to receive
 * @param datain - one byte data receive
 * @param arr_message - array data out of message
 */
void GetMessage::GetMessages(uint8_t datain, uint8_t arr_message[])
{
	timeout_start = clock();
	timeout_wait = true;
	switch (fsm_state)
	{
		case FSM_STATE_START:
			arr_message[count_element_arr] = datain;
			count_element_arr++;
			if (count_element_arr == FSM_STATE_CHANGE_VALUE_WAIT)
			{
				if(Bytes_To_Uint16(arr_message[0], arr_message[1]) != 0xAA55)
				{
					GetMessage::ClearState();
				}
				else
				{
					fsm_state = FSM_STATE_WAIT;
				}
			}
		break;
		
		case FSM_STATE_WAIT:
			
		break;
		
		case FSM_STATE_END:
			
		break;
	}
}

void GetMessage::ClearState(void)
{
	count_element_arr = 0;
	data_after_length = 0;
    timeout_start = 0;
    timeout_end = 0;
    timeout_wait = false;
    fsm_state = FSM_STATE_START;
}
