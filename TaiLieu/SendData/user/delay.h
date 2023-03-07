/*
  ******************************************************************************
  * @file		delay.h                                                              *
  * @author	    Nguyen Van An                                               *
  * @date		23/04/2022                                                      *
  ******************************************************************************
*/
	
#ifndef __GPIO_LED__
#define __GPIO_LED__

#ifdef __cplusplus
 extern "C" {
#endif

void Timer_Config(void);
void Delay(unsigned int vr_Time);
void Delay_ms(void);
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/

