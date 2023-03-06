/*!
    \file  main.c
    \brief ADC channel of temperature and Vref 

    \version 2017-02-10, V1.0.0, firmware for GD32F30x
    \version 2018-10-10, V1.1.0, firmware for GD32F30x
    \version 2018-12-25, V2.0.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32f30x.h"
#include "systick.h"
#include <stdio.h>
#include "bts_uart.h"
#include "stdlib.h"
#include "math.h"

float temperature;
float vref_value;


typedef struct
{
	float ADC_OLD_Value;
	float P_k1_k1;

	float Q;
	float R; 
	float Kg;
	float P_k_k1;
	float kalman_adc_old;
	
	uint8_t init_data;
}_adc_kalman_filter_t_;
_adc_kalman_filter_t_ Kalman_NTC1, Kalman_NTC2;

void rcu_config(void);
void adc_config(void);
static float convert_NTC_Analog_to_Temperature(uint16_t adc_value);
uint16_t ADC_Kalman_Filter(unsigned long ADC_Value, _adc_kalman_filter_t_ *_adc_kalman_);
/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/

int main(void)
{
	uint16_t adc_kalman;
    /* configure systick */
    systick_config();  
    /* system clocks configuration */
    rcu_config();
    /* ADC configuration */
    adc_config();
    /* USART configuration */
	SmartBTS_USART1_Init();

    while(1){
        /* ADC software trigger enable */
        adc_software_trigger_enable(ADC1, ADC_INSERTED_CHANNEL);
        /* delay a time in milliseconds */
        delay_1ms(2000);
      
        /* value convert */
		adc_kalman = ADC_Kalman_Filter(ADC_IDATA0(ADC1), &Kalman_NTC1);
		printf(" the temperature NTC 1 %f degrees Celsius\r\n", convert_NTC_Analog_to_Temperature(adc_kalman));
		adc_kalman = ADC_Kalman_Filter(ADC_IDATA1(ADC1), &Kalman_NTC2);
		printf(" the temperature NTC 2 %f degrees Celsius\r\n", convert_NTC_Analog_to_Temperature(adc_kalman));
    }

}

/*!
    \brief      configure the different system clocks
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_config(void)
{
    /* enable ADC clock */
    rcu_periph_clock_enable(RCU_ADC1);
    /* config ADC clock */
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV4);
}


/*!
    \brief      configure the ADC peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_config(void)
{
    /* ADC SCAN function enable */
    adc_special_function_config(ADC1, ADC_SCAN_MODE, ENABLE);
    adc_special_function_config(ADC1, ADC_CONTINUOUS_MODE, DISABLE); 
    /* ADC trigger config */
    adc_external_trigger_source_config(ADC1, ADC_INSERTED_CHANNEL, ADC0_1_2_EXTTRIG_INSERTED_NONE);
    /* ADC mode config */
    adc_mode_config(ADC_MODE_FREE);
    /* ADC data alignment config */
    adc_data_alignment_config(ADC1, ADC_DATAALIGN_RIGHT);  
    /* ADC channel length config */
    adc_channel_length_config(ADC1, ADC_INSERTED_CHANNEL, 2);

  
    /* ADC temperature sensor channel config */
    adc_inserted_channel_config(ADC1, 0, ADC_CHANNEL_0, ADC_SAMPLETIME_239POINT5);
    /* ADC internal reference voltage channel config */
    adc_inserted_channel_config(ADC1, 1, ADC_CHANNEL_1, ADC_SAMPLETIME_239POINT5);

    adc_external_trigger_config(ADC1, ADC_INSERTED_CHANNEL, ENABLE);
  
    /* ADC temperature and Vrefint enable */
    adc_tempsensor_vrefint_enable();
 
    
    /* enable ADC interface */
    adc_enable(ADC1);
    delay_1ms(1);
    /* ADC calibration and reset calibration */
    adc_calibration_enable(ADC1);
}
/*
 * @brief Anti-interference for the analog voltage 
 * 
 * @param ADC_Value : analog voltage value
 * @param _adc_kalman_ : structure for the kalman filter
 * @return uint16_t : analog voltage after filtering
 */
uint16_t ADC_Kalman_Filter(unsigned long ADC_Value, _adc_kalman_filter_t_ *_adc_kalman_)
{
		float x_k1_k1,x_k_k1;
		uint16_t kalman_adc;
	  float Z_k;
		if(_adc_kalman_->init_data == 0)
		{
			_adc_kalman_->ADC_OLD_Value = 0.0;
			_adc_kalman_->P_k1_k1 = 0.0;
			_adc_kalman_->kalman_adc_old=0;
			_adc_kalman_->Q = 0.0001; //Q: Regulation noise, Q increases, dynamic response becomes faster, and convergence stability becomes worse
			_adc_kalman_->R = 0.0005;    //R: Test noise, R increases, dynamic response becomes slower, convergence stability becomes better
			_adc_kalman_->Kg = 0;
			_adc_kalman_->P_k_k1 = 1;
			_adc_kalman_->init_data = 1;
		}
		
    Z_k = ADC_Value;
    x_k1_k1 = _adc_kalman_->kalman_adc_old;

    x_k_k1 = x_k1_k1;
    _adc_kalman_->P_k_k1 = _adc_kalman_->P_k1_k1 + _adc_kalman_->Q;

    _adc_kalman_->Kg = _adc_kalman_->P_k_k1/(_adc_kalman_->P_k_k1 + _adc_kalman_->R);

    kalman_adc = x_k_k1 + _adc_kalman_->Kg * (Z_k - _adc_kalman_->kalman_adc_old);
    _adc_kalman_->P_k1_k1 = (1 - _adc_kalman_->Kg)*_adc_kalman_->P_k_k1;
    _adc_kalman_->P_k_k1 = _adc_kalman_->P_k1_k1;

    _adc_kalman_->ADC_OLD_Value = ADC_Value;
    _adc_kalman_->kalman_adc_old = kalman_adc;
	return kalman_adc;
}

static float convert_NTC_Analog_to_Temperature(uint16_t adc_value)
{	
	float B = 3950, t0 = 298.15, r25 = 10000, v_out, r_ntc, v_supply = 3.3;
	float t;
	v_out =	adc_value * v_supply / 4095;
	r_ntc = (v_out * r25) /(v_supply - v_out);
	t = (t0*B)/(t0*log(r_ntc/r25)+B) - 273.15;    
	return t; 	
}
