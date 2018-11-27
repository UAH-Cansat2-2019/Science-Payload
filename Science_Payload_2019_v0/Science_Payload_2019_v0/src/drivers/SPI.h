/*
 * SPI.h
 *
 * Created: 11/27/2018 1:41:31 PM
 *  Author: Nathan U
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <asf.h>

void SPI_init(char Port);
void SPI_write(char Port,uint8_t data);
uint8_t SPI_read (char Port);




#endif /* SPI_H_ */