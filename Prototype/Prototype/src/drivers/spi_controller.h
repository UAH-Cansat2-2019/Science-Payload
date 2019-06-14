/*
 * spi_controller.h
 *
 * Created: 6/13/2019 11:15:50 PM
 *  Author: natha
 */ 

#ifndef SPI_CONTROLLER_H_
#define SPI_CONTROLLER_H_


void spi_init(void);

int64_t prom_read(uint8_t);

void spi_write(uint8_t data);

uint8_t spi_read(void);

void spi_deselect(void);

int64_t get_pressure(void);

void spi_select(void);

int64_t ms5607_read_adc(uint8_t com);

float calcAltitude(void);

void set_Pref(float pref);


#endif /* SPI_CONTROLLER_H_ */