/*
 * I2CDriver.h
 *
 * Created: 4/9/2019 1:45:21 AM
 *  Author: natha
 */ 


#ifndef I2CDRIVER_H_

#define MYI2C TWIC
#define BUSAD (uint16_t)(&TWIC)

void I2CInit(uint32_t baud,uint8_t busad);

void twi_write(uint8_t * Data,uint8_t address,uint8_t memAddress);

void twi_read(uint8_t * Data,uint8_t address,uint8_t memAddress);

uint8_t readBusad(void);
#define I2CDRIVER_H_





#endif /* I2CDRIVER_H_ */