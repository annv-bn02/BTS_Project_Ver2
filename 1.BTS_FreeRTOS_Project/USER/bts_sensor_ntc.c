#include "bts_sensor_ntc.h"

static int32_t convert_NTC_Analog_to_Temperature(uint16_t adc_value);

void Sensor_NTC_Init(void)
{
	BTS_Config_GPIO_Sensor(SENSOR_NTC1);
	BTS_Config_GPIO_Sensor(SENSOR_NTC2);
	BTS_ADC_Init();
}

uint8_t Sensor_NTC_Get(void)
{	
	
	uint16_t adc_value;
	adc_software_trigger_enable(ADC1, ADC_REGULAR_CHANNEL);
	adc_flag_clear(ADC1, ADC_FLAG_EOC);
	while(SET != adc_flag_get(ADC1, ADC_FLAG_EOC))
	{
	}
	adc_value = ADC_RDATA(ADC1) ;
	BTS_Sys_Debug("6B: %d\r\n",adc_value); 
	BTS_Sys_Debug("T: %dC\r\n", convert_NTC_Analog_to_Temperature(adc_value));
	BTS_Sys_Debug("\r\n ***********************************\r\n");
	return 1;
}

static int32_t convert_NTC_Analog_to_Temperature(uint16_t adc_value)
{
	float B = 3100, T0 = 298.15, R25 = 10000, vout, R_NTC;
	float T;
	vout =	adc_value * 3.3 / 4095;
	R_NTC = (vout * R25) /(3.3 - vout);
	T = (T0 * B)  * 100 / ((T0 * log(R_NTC / R25)) + B) - 27315;    
	return (int)T; 	
}
