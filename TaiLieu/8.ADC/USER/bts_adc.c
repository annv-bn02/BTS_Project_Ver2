
#include "bts_adc.h"
#include "math.h"
#define BOARD_ADC_CHANNEL   ADC_CHANNEL_10
#define ADC_GPIO_PORT_RCU   RCU_GPIOC
#define ADC_GPIO_PORT       GPIOC
#define ADC_GPIO_PIN        GPIO_PIN_0

uint32_t adc_value[2];

/*!
    \brief      configure the DMA peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dma_config(void)
{
    /* ADC_DMA_channel configuration */
    dma_parameter_struct dma_data_parameter;
    
    /* ADC DMA_channel configuration */
    dma_deinit(DMA0, DMA_CH0);
    
    /* initialize DMA data mode */
    dma_data_parameter.periph_addr = (uint32_t)(&ADC_RDATA(ADC1));
    dma_data_parameter.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_data_parameter.memory_addr = (uint32_t)(&adc_value);
    dma_data_parameter.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_32BIT;
    dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_32BIT;  
    dma_data_parameter.direction = DMA_PERIPHERAL_TO_MEMORY;
    dma_data_parameter.number = 2;
    dma_data_parameter.priority = DMA_PRIORITY_HIGH;
    dma_init(DMA0, DMA_CH0, dma_data_parameter);

    dma_circulation_enable(DMA0, DMA_CH0);
  
    /* enable DMA channel */
    dma_channel_enable(DMA0, DMA_CH0);
}

void BTS_ADC_Init(void)
{

	/* enable GPIOA clock */
	rcu_periph_clock_enable(ADC_GPIO_PORT_RCU);
	/* enable ADC1 clock */
	rcu_periph_clock_enable(RCU_ADC1);
	/* config ADC clock */
	rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV4);
	/* config the GPIO as analog mode */
	gpio_init(GPIOC, GPIO_MODE_AIN, GPIO_OSPEED_MAX, GPIO_PIN_1|GPIO_PIN_2); 
	
	/* ADC continous function enable */
    adc_special_function_config(ADC1, ADC_SCAN_MODE, ENABLE);  
    /* ADC trigger config */
    adc_external_trigger_source_config(ADC1, ADC_REGULAR_CHANNEL, ADC0_1_2_EXTTRIG_REGULAR_NONE);  
    /* ADC data alignment config */
    adc_data_alignment_config(ADC1, ADC_DATAALIGN_RIGHT);  
    /* ADC mode config */
    adc_mode_config(ADC_DAUL_REGULAL_PARALLEL); 
    /* ADC channel length config */
    adc_channel_length_config(ADC1, ADC_REGULAR_CHANNEL, 2);
  
    /* ADC regular channel config */
    adc_regular_channel_config(ADC1, 0, ADC_CHANNEL_11, ADC_SAMPLETIME_55POINT5);
    adc_regular_channel_config(ADC1, 1, ADC_CHANNEL_12, ADC_SAMPLETIME_55POINT5);

    /* ADC external trigger enable */
    adc_external_trigger_config(ADC1, ADC_REGULAR_CHANNEL, ENABLE);    
    /* enable ADC interface */    
    adc_enable(ADC1);    
    /* ADC calibration and reset calibration */    
    adc_calibration_enable(ADC1);    

    /* ADC DMA function enable */
    adc_dma_mode_enable(ADC1);
}

uint16_t BTS_ADC_Read(void)
{
	float B = 3950, T0 = 298.15, R25 = 10000;
	float T;
	uint16_t adc_value;
	adc_software_trigger_enable(ADC1, ADC_REGULAR_CHANNEL);
	adc_flag_clear(ADC1, ADC_FLAG_EOC);
	while(SET != adc_flag_get(ADC1, ADC_FLAG_EOC))
	{
	}
	adc_value = ADC_RDATA(ADC1) ;  
	printf("6B: %d\r\n",adc_value);
	T = (1 / ((log((adc_value*3.3) / R25)/B) + (1 / T0))) - 273.15;            
	printf("6B: %d\r\n",(int )T);
	printf("\r\n ***********************************\r\n");
}
