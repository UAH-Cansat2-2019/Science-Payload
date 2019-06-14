/*
 * spi_controller.c
 *
 * Created: 6/13/2019 11:15:32 PM
 *  Author: natha
 */ 
#include <asf.h>
#include "spi_controller.h"
#include <math.h>
int64_t c1;
int64_t c2;
int64_t c3;
int64_t c4;
int64_t c5;
int64_t c6;
int64_t temp;
float Pref;

void spi_init(void)
{
	sysclk_enable_peripheral_clock(&SPIC);
	//configures settings
	PORTC.DIR|=0b10110000;
	PORTC.DIR&=0b10111111;
	SPIC.CTRL=0b01010000;
	//reset sequence
	spi_deselect();
	spi_write(0x1E);
	delay_ms(3);
	spi_select();
	delay_ms(3);
	//PROM read gets calibration data
	c1=prom_read(0xA2);
	c2=prom_read(0xA4);
	c3=prom_read(0xA6);
	c4=prom_read(0xA8);
	c5=prom_read(0xAA);
	c6=prom_read(0xAC);
 	printf("\nc1=%u",(uint16_t)c1);
 	printf("\n%u",(uint16_t)c2);
 	printf("\n%u",(uint16_t)c3);
 	printf("\n%u",(uint16_t)c4);
 	printf("\n%u",(uint16_t)c5);
 	printf("\n%u",(uint16_t)c6);
	
}
int64_t prom_read(uint8_t com)
{
	int64_t responce;
	spi_deselect();
	spi_write(com);
	responce=((int64_t)spi_read())<<8;
	responce+=spi_read();
	spi_select();
	delay_ms(3);
	return responce;
}

void spi_select(void)
{
	PORTC.OUT|=0b00010000;
}

void spi_deselect(void)
{
	PORTC.OUT&=0b11101111;
}

uint8_t spi_read(void)
{
	SPIC.DATA = 0xFF; // make the DATA register something we know
	while(!(SPIC.STATUS>>7)); // wait for the SPI interrupt flag to let us know the transfer is complete
	
	return SPIC.DATA; // return the data from this function
}

void spi_write(uint8_t data)
{
	SPIC.DATA = data; // write the data we want to send to the data register
	while(!(SPIC.STATUS>>7)); // wait to ensure the data is sent before we do anything else
}
int64_t ms5607_read_adc(uint8_t com)
{
	uint64_t rx_data = 0; // temporary 16-bit value
	spi_deselect(); // select our spi device
	spi_write(com);
	spi_select();
	delay_ms(3);
	spi_deselect();
	spi_write(0x00); // write a specified command to ask for data
	
	/*typecast this expression from an 8-bit to a 16-bit and shift it 8 bits to the left
	  meaning the returned value is now in the upper 8 bits rx_data*/
    rx_data = ((int64_t)spi_read())<<16; 
	rx_data+=((int64_t)spi_read())<<8;
	rx_data += spi_read(); 
	
	spi_select(); // end spi exchange
	
	return rx_data; // return the 16-bit value
}
//calculates pressure from reads
int64_t get_pressure(void)
{
	//calculations using the formula from the data sheet
	int64_t d1=ms5607_read_adc(0x46);
	//printf("\n d1 = %lu",(uint32_t)d1);
	int64_t d2=ms5607_read_adc(0x56);
	//printf("\n d2 = %lu",(uint32_t)d2);
	int64_t dt=d2-c5*256;
	//printf("\n dt = %lu",(uint32_t)dt);
	temp=2000+(dt*c6)/8388608;
	//printf("\n temp = %lu",(uint32_t)temp);
	int64_t off=(c2<<17)+(c4*dt)/64;
	//printf("\n off = %lu",(uint32_t)off);
	int64_t sens =(c1<<16)+(c3*dt)/128;
	//printf("\n sens = %li",sens);
	int64_t P = (d1*sens/2097152-off)/32768;
	return P;
	
	
}
float calcAltitude()
{
	//printf("\nPref = %lu",(uint32_t)Pref);
	//printf("\n%lu",(uint32_t)temp);
	float p=(float)get_pressure();
	//printf("\n p= %lu",(uint32_t)p);
	float divPress = ((float)Pref)/p;
	
	float alt = ((pow(divPress,0.19022256 ) - 1) * (temp+273.15)) / 0.0065;
	alt=alt*0.328084;
	return alt;
}
void set_Pref(float pref)
{
	Pref=pref;
}