
#include "bts_adc.h"

#define BOARD_ADC_CHANNEL   ADC_CHANNEL_10
#define ADC_GPIO_PORT_RCU   RCU_GPIOC
#define ADC_GPIO_PORT       GPIOC
#define ADC_GPIO_PIN        GPIO_PIN_0

_adc_kalman_filter_t_ Kalman_NTC;

void BTS_ADC_Init(void)
{
	/* enable GPIOA clock */
	rcu_periph_clock_enable(ADC_GPIO_PORT_RCU);
	/* enable ADC1 clock */
	rcu_periph_clock_enable(RCU_ADC1);
	/* config ADC clock */
	rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV4);
	/* config the GPIO as analog mode */
	gpio_init(ADC_GPIO_PORT, GPIO_MODE_AIN, GPIO_OSPEED_MAX, ADC_GPIO_PIN);
	
 /* ADC continuous function enable */
	adc_special_function_config(ADC1, ADC_SCAN_MODE, ENABLE);
	adc_special_function_config(ADC1, ADC_CONTINUOUS_MODE, DISABLE);    
	/* ADC trigger config */
	adc_external_trigger_source_config(ADC1, ADC_REGULAR_CHANNEL, ADC0_1_2_EXTTRIG_REGULAR_NONE); 
	/* ADC data alignment config */
	adc_data_alignment_config(ADC1, ADC_DATAALIGN_RIGHT);
	/* ADC mode config */
	adc_mode_config(ADC_MODE_FREE); 
	/* ADC channel length config */
	adc_channel_length_config(ADC1, ADC_REGULAR_CHANNEL, 1);

	/* ADC regular channel config */
	adc_regular_channel_config(ADC1, 0, BOARD_ADC_CHANNEL, ADC_SAMPLETIME_55POINT5);
	adc_external_trigger_config(ADC1, ADC_REGULAR_CHANNEL, ENABLE);

	/* ADC resolusion 6B */
	adc_resolution_config(ADC1, ADC_RESOLUTION_12B);  
	adc_software_trigger_enable(ADC1, ADC_REGULAR_CHANNEL);
	
	/* enable ADC interface */
	adc_enable(ADC1);
	/* ADC calibration and reset calibration */
	adc_calibration_enable(ADC1);
}

void BTS_ADC_NTC_Init(uint8_t gpio_element)
{
	/* enable ADC1 clock */
	rcu_periph_clock_enable(RCU_ADC1);
	/* config ADC clock */
	rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV4);	
 /* ADC continuous function enable */
	adc_special_function_config(ADC1, ADC_SCAN_MODE, ENABLE);
	adc_special_function_config(ADC1, ADC_CONTINUOUS_MODE, DISABLE);    
	/* ADC trigger config */
	adc_external_trigger_source_config(ADC1, ADC_REGULAR_CHANNEL, ADC0_1_2_EXTTRIG_REGULAR_NONE); 
	/* ADC data alignment config */
	adc_data_alignment_config(ADC1, ADC_DATAALIGN_RIGHT);
	/* ADC mode config */
	adc_mode_config(ADC_MODE_FREE); 
	/* ADC channel length config */
	adc_channel_length_config(ADC1, ADC_REGULAR_CHANNEL, 1);

	/* ADC regular channel config */
	adc_regular_channel_config(ADC1, gpio_element, gpio_pin_sensor[gpio_element].adc_channel, ADC_SAMPLETIME_55POINT5);
	adc_external_trigger_config(ADC1, ADC_REGULAR_CHANNEL, ENABLE);

	/* ADC resolusion 6B */
	adc_resolution_config(ADC1, ADC_RESOLUTION_12B);  
	adc_software_trigger_enable(ADC1, ADC_REGULAR_CHANNEL);
	
	/* enable ADC interface */
	adc_enable(ADC1);
	/* ADC calibration and reset calibration */
	adc_calibration_enable(ADC1);
}

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

uint16_t BTS_ADC_Read(void)
{
	uint16_t adc_value;
	adc_flag_clear(ADC1, ADC_FLAG_EOC);
	while(SET != adc_flag_get(ADC1, ADC_FLAG_EOC)){
	}
	adc_value = ADC_RDATA(ADC1);        
	BTS_Sys_Debug("6B: %d\r\n", adc_value);
	BTS_Sys_Debug("\r\n ***********************************\r\n");
	return 0;
}
