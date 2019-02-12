/*
 * SPI.h
 *
 * Created: 11/27/2018 1:41:31 PM
 *  Author: Nathan U
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <asf.h>

void SPI_init(void);
void SPI_write(uint8_t data);
uint8_t SPI_read(void);



#endif /* SPI_H_ */