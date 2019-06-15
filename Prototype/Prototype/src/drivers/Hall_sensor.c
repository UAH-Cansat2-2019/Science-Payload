/*
 * Hall_sensor.c
 *
 * Created: 6/14/2019 11:38:25 PM
 *  Author: natha
 */ 
#include <asf.h>
#include "drivers/Hall_sensor.h"


void hall_init(void)
{
	sysclk_enable_peripheral_clock(&ADCA);
	//sets up adc
	PORTA.DIR|=0b00010000;
	ADCA.CTRLA = 0x01;
	ADCA.CTRLB = 0x00;//12 bit mode
	ADCA.PRESCALER = 0x05;//prescalar 128
	ADCA.REFCTRL=0x10;
	ADCA.CAL = adc_get_calibration_data(ADC_CAL_ADCA);
	ADCA.CH0.CTRL = 0x01; // single ended input
	ADCA.CH0.MUXCTRL = 0x04; // seading ADA pin 4
}

uint16_t hallVoltRead(void)
{
	
	ADCA.CH0.CTRL |= 0x80; // start the conversion
	while(!(ADCA.CH0.INTFLAGS)); // wait until the conversion is done
	uint16_t in= ADCA.CH0.RES; // return the 12-bit result as a uint16_t
	return in;
	//printf("\n%u",in);
	//calculates voltage using measured data
	//gives zero if the measurement is so close it yeilds negative
}