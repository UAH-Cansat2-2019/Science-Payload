/*
 * SPI.c
 *
 *
 * Created: 11/27/2018 1:49:24 PM
 *  Author: Nathan U.
 */ 

#include "SPI.h"
#include "Pins.h"
//Initializes the SPI on Port C
void SPI_init(void){
	SPIPORT.DIRSET = MISO|SPICLK;
	SPIPORT.DIRCLR = MOSI;
	//SPIPORT.OUTSET = 0b10110000;
	SPI1.CTRL =	   0b01010011;
}

void SPI_write(uint8_t data_byte){
	SPI1.DATA = data_byte;
	while(!(SPIC.STATUS>>7));
}
uint8_t SPI_read(void)
{
	SPI1.DATA = 0xFF; // make the DATA register something we know
	while(!(SPI1.STATUS>>7)); // wait for the SPI interrupt flag to let us know the transfer is complete
	return SPI1.DATA; // return the data from this function
}