/*
 * MS5607.h
 *
 * Pressure Sensor
 * 
 * Created: 11/27/2018 1:39:48 PM
 *  Author: Nathan U
 */ 


#ifndef MS5607_H_
#define MS5607_H_

#include <asf.h>
#include "drivers/SPI.h"
void pressure_init(void);
uint16_t promread(uint8_t prompt);


#endif /* MS5607_H_ */