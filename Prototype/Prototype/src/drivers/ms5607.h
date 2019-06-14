/*
 * ms5607.h
 *
 * Created: 6/9/2019 4:12:11 PM
 *  Author: quaz9
 */ 


#ifndef MS5607_H_
#define MS5607_H_

#include <asf.h>
#include <spi.h>
//#include "definitions.h"

#define MS5607_PORT &PORTC
#define MS5607_SPI_PORT SPIC

uint16_t C1, C2, C3, C4, C5, C6;
uint32_t D1, D2;



void spi_init_pins(void);

void prom_read(void);

void spi_init_module(void);

int32_t getPressure(void);



#endif /* MS5607_H_ */