/*
 * adc_sensors.c
 *
 * Created: 6/9/2019 2:21:12 PM
 *  Author: quaz9
 */ 

#include "adc_sensors.h"

void adc_init(ADC_t* adc, uint8_t ch_mask)
{
	struct adc_config adc_conf;
	struct adc_channel_config adcch_conf;
	adc_read_configuration(adc, &adc_conf);
	adcch_read_configuration(adc, ch_mask, &adcch_conf);
	adc_set_conversion_parameters(&adc_conf, ADC_SIGN_OFF, ADC_RES_12,
	ADC_REF_VCC);
	adc_set_conversion_trigger(&adc_conf, ADC_TRIG_MANUAL, 1, 0);
	adc_set_clock_rate(&adc_conf, 200000UL);
	adcch_set_input(&adcch_conf, ADCCH_POS_PIN0, ADCCH_NEG_NONE, 0);
	adc_write_configuration(adc, &adc_conf);
	adcch_write_configuration(adc, ch_mask, &adcch_conf);
	
	
}
void thermistor_init(void)
{
	adc_init(&THERM_ADC,THERM_ADC_CH);
	
	if(DEBUG) printf("Thermistor Initialized.\n");
}
void volt_init(void)
{
	adc_init(&VOLT_ADC,VOLT_ADC_CH);
	
	if(DEBUG) printf("Voltage Initialized.\n");
}


float getADCRead(ADC_t* adc, uint8_t ch_mask)
{
		adc_enable(adc);
		
		
		adc_start_conversion(adc, ch_mask);
		adc_wait_for_interrupt_flag(adc, ch_mask);
		uint16_t adcReading = adc_get_result(adc, ch_mask);
		//printf("ADC reading = %u\n", adcReading);
		//float voltage = adcReading/4096.0*2;	//We have to find these numbers by applying differing voltage, printing ADC readings, and solve equation
		//printf("voltage: %f \n", voltage);
		
		adc_disable(adc);
		return adcReading;
	
}
float getVoltage(void)
{
	float adc_val = getADCRead(&VOLT_ADC,VOLT_ADC_CH)/4096.0*2;
	if(DEBUG && DEBUG_ADC) printf("volt: %f\n",adc_val);
	return adc_val;
}
float getTemperature(void)
{
	float adc_val = getADCRead(&THERM_ADC,THERM_ADC_CH)*.636;
	//float resistance = (8300.0)*((adc_val/3.3)-1);
	//printf("\n%f\n",resistance);
	uint32_t temperature = 1.0/(1.0/298.15 + 1.0/3977.0*log(4096.0/(float)adc_val-1.0));
	if(DEBUG && DEBUG_ADC) printf("temp: %f\n", temperature-273.15);
	return (temperature - 273.15);
	
	
}