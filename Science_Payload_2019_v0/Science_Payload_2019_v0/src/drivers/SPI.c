/*
 * SPI.c
 *
 *
 * Created: 11/27/2018 1:49:24 PM
 *  Author: Nathan U.
 */ 

#include "SPI.h"
//Initializes the SPI on Port C
void SPI_init(char Port){
	PORTC.DIRSET = 0b10110000;
	PORTC.DIRCLR = 0b01000000;
	PORTC.OUTSET = 0b10110000;
	SPIC.CTRL =	   0b01010011;
}

void SPI_write(char Port,uint8_t data_byte){
	/*switch (Port){
		case 'A'
	};*/
	SPIC.DATA = data_byte;
	while(!(SPIC.STATUS>>7));
}