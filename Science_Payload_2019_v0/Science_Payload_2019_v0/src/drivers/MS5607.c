/*
 * MS5607.c
 *
 * Pressure Sensor
 *
 * Created: 11/27/2018 1:35:43 PM
 *  Author: quaz9
 */ 
#include <asf.h>
#include "drivers/SPI.h"
#include "Pins.h"
#include "MS5607.h"
	int64_t Cvalue[6];//stores the calibration values returned by the prom sequence
	void pressure_init(void)
	{
		uint8_t SS=PRESS_SS;
		const int8_t prom[6] = {0xA2,0xA4,0xA6,0xA8,0xAA,0xAC};//prom read commands
		
		PRESS_PORT.DIR |=SS;//setting the direction of the slave select
		
		//Reset sequence ensures calibration values are loaded into the memory
		SPIPORT.OUT&=~SS;//pulls slave select low
		SPI_write(0xE1);//reset command
		delay_ms(3);
		SPIPORT.OUT|=SS;//pulls slave high
		
		for(uint8_t i=0; i<6;i++)//loops through the prom read sequence
		{
			Cvalue[i]=(int64_t)promread(prom[i]);
			delay_ms(3);
		}
	}
	
	uint16_t promread(uint8_t prompt)
	{
		uint8_t SS=PRESS_SS;
		SPIPORT.OUT&=~SS;//pulls slave select low
		SPI_write(prompt);//sends the pressure sensor a prompt
		uint16_t responce=(uint16_t)SPI_read();// reads the first returned bit
		responce=responce<<8;//most significant bit is sent first so shift it over
		responce+=(uint16_t)SPI_read();//reads second bit
		SPIPORT.OUT|=SS;//pulls slave high
		return responce;
	}
	int64_t ms5607_read_adc(uint8_t com)
{
	uint64_t rx_data = 0; // temporary 16-bit value
	PRESS_PORT.DIR &=~PRESS_SS; // select our spi device
	SPI_write(com);
	PRESS_PORT.DIR |=PRESS_SS;
	delay_ms(3);
	PRESS_PORT.DIR &=~PRESS_SS;;
	SPI_write(0x00); // write a specified command to ask for data
	
	/*typecast this expression from an 8-bit to a 16-bit and shift it 8 bits to the left
	  meaning the returned value is now in the upper 8 bits rx_data*/
    rx_data = ((int64_t)SPI_read())<<16; 
	rx_data+=((int64_t)SPI_read())<<8;
	rx_data += SPI_read(); 
	
	PRESS_PORT.DIR |=PRESS_SS; // end spi exchange
	
	return rx_data; // return the 16-bit value
}
	int64_t get_pressure(void)
	{
		//int64_t temp;
		//calculations using the formula from the data sheet
		int64_t d1=ms5607_read_adc(0x46);
		//printf("\n d1 = %lu",(uint32_t)d1);
		int64_t d2=ms5607_read_adc(0x56);
		//printf("\n d2 = %lu",(uint32_t)d2);
		int64_t dt=d2-(Cvalue[4]<<8);
		//printf("\n dt = %lu",(uint32_t)dt);
		//temp=2000+dt*(Cvalue[5]>>23);
		//printf("\n temp = %lu",(uint32_t)temp);
		int64_t off=(Cvalue[1]<<17)+((Cvalue[3]*dt)>>6);
		//printf("\n off = %lu",(uint32_t)off);
		int64_t sens =(Cvalue[0]<<16)+((Cvalue[2]*dt)>>7);
		//printf("\n sens = %li",sens);
		int64_t P = (((d1*sens)>>21)-off)>>15;
		return P;
	}