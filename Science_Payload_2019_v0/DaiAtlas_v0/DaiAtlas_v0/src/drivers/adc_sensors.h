/*
 * adc_sensors.h
 *
 * Created: 6/9/2019 2:20:54 PM
 *  Author: quaz9
 */ 


#ifndef ADC_SENSORS_H_
#define ADC_SENSORS_H_

#include <asf.h>
#include <adc.h>
#include <math.h>
#include "definitions.h"

#define THERM_ADC ADCA
#define THERM_ADC_CH ADC_CH0
#define THERM_POS ADCCH_POS_PIN6

#define VOLT_ADC ADCA
#define VOLT_ADC_CH ADC_CH1
#define VOLT_POS ADCCH_POS_PIN5



void adc_init(ADC_t* adc, uint8_t ch_mask, uint8_t pos);
void thermistor_init(void);
void volt_init(void);
float getADCRead(ADC_t* adc, uint8_t ch_mask);
float getVoltage(void);
float getTemperature(void);



#endif /* ADC_SENSORS_H_ */