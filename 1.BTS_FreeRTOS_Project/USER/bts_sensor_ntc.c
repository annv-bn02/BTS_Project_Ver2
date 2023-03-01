#include "bts_sensor_ntc.h"

static float convert_NTC_Analog_to_Temperature(uint16_t adc_value);

/**
 * @brief Config for the sensor NTC.
 * 
 */
void Sensor_NTC_Init(void)
{
	BTS_Config_GPIO_Sensor(SENSOR_NTC1);
	BTS_Config_GPIO_Sensor(SENSOR_NTC2);
	BTS_ADC_NTC_Init(SENSOR_NTC1);
}

/**
 * @brief Get temperature value of the sensor NTC.
 * 
 * @return 1
 */
uint8_t Sensor_NTC_Get(void)
{	
	
	uint16_t adc_value, adc_kalman;
	adc_software_trigger_enable(ADC1, ADC_REGULAR_CHANNEL);
	adc_flag_clear(ADC1, ADC_FLAG_EOC);
	while(SET != adc_flag_get(ADC1, ADC_FLAG_EOC))
	{
	}
	adc_value = adc_regular_data_read(ADC1) ;
	adc_kalman = ADC_Kalman_Filter(adc_value, &Kalman_NTC);
#if DEBUG_ALL
	BTS_Sys_Debug("12B: %d\r\n",adc_value); 
	BTS_Sys_Debug("T: %fC\r\n", convert_NTC_Analog_to_Temperature(adc_kalman));
	BTS_Sys_Debug("\r\n ***********************************\r\n");
#endif
	return 1;
}

/**
 * @brief convert analog value of NTC to temerature value.
 * 
 * @param adc_value : analog value of NTC.
 * @return float : temperature value of NTC.
 */
static float convert_NTC_Analog_to_Temperature(uint16_t adc_value)
{
	float B = 3950, t0 = 298.15, r25 = 10000, v_out, r_ntc, v_supply = 3.3;
	float t;
	v_out =	adc_value * v_supply / 4095;
	r_ntc = (v_out * r25) /(v_supply - v_out);
	t = (t0*B)/(t0*log(r_ntc/r25)+B) - 273.15;    
	return t; 	
}
