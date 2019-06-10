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

#define MS5607_PORT PORTD
#define MS5607_SPI_PORT SPID

void spi_init_pins(void);

void spi_init_module(void);

float read_pressure(void);



#endif /* MS5607_H_ */