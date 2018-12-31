/*
 * MS5607.c
 *
 * Pressure Sensor
 *
 * Created: 11/27/2018 1:35:43 PM
 *  Author: quaz9
 */ 
#include "drivers/MS5607.h"
#include <asf.h>
#include "drivers/SPI.h"
	
	
	#define SS 0b00010000;// I don't know if we're using a different pin for slave select for the pressure sensor 
								// but this one was on the data sheet for pin desc
	int64_t Cvalue[6];//stores the calibration values returned by the prom sequence
	void pressure_init(void)
	{
		const int8_t prom[6] = {0xA2,0xA4,0xA6,0xA8,0xAA,0xAC};//prom read commands
		
		PORTC.DIR |=SS;//setting the direction of the slave select
		
		//Reset sequence ensures calibration values are loaded into the memory
		PORTC.OUT&=~SS;//pulls slave select low
		SPI_write("C",0xE1);//reset command
		delay_ms(3);
		PORTC.OUT|=SS;//pulls slave high
		
		for(uint8_t i=0; i<5;i++)//loops through the prom read sequence
		{
			Cvalue[i]=(int64_t)promread(prom[i]);
		}
	}
	
	uint16_t promread(uint8_t prompt)
	{
		PORTC.OUT&=~SS;//pulls slave select low
		SPI_write("C",prompt);//sends the pressure sensor a prompt
		uint16_t responce=(uint16_t)SPI_read("C");// reads the first returned bit
		responce=responce<<8;//most significant bit is sent first so shift it over
		responce+=(uint16_t)SPI_read("C");//reads second bit
		PORTC.OUT|=SS;//pulls slave high
		return responce;
	}