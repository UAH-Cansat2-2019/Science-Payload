/*
 * ms5607.c
 *
 * Created: 6/9/2019 4:11:57 PM
 *  Author: quaz9
 */ 

#include "ms5607.h"
#include <spi.h>


void spi_init_pins(void)
{
	ioport_configure_port_pin(&MS5607_PORT, PIN1_bm, IOPORT_INIT_HIGH|IOPORT_DIR_OUTPUT);
	
	ioport_configure_port_pin(&MS5607_PORT, PIN4_bm, IOPORT_PULL_UP|IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&MS5607_PORT, PIN5_bm, IOPORT_INIT_HIGH|IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&MS5607_PORT, PIN6_bm, IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&MS5607_PORT, PIN7_bm, IOPORT_INIT_HIGH|IOPORT_DIR_OUTPUT);
	
}

void spi_init_module(void)
{
	struct spi_device spi_device_conf = {
		.id = IOPORT_CREATE_PIN(MS5607_PORT,1)
		};
		
	spi_master_init(&MS5607_SPI_PORT);
	spi_master_setup_device(&MS5607_SPI_PORT, &spi_device_conf, SPI_MODE_0, 1000000,0);
	spi_enable(&MS5607_SPI_PORT);
	
}

float read_pressure(void)
{
	
		
	struct spi_device  spi_device_conf = {
		.id = IOPORT_CREATE_PIN(MS5607_PORT,1)
	};
	
	spi_select_device(&MS5607_SPI_PORT, &spi_device_conf);
	
	uint8_t command[1] = {0x48}; //pressure read thingy
	uint8_t read_buffer[4];
	spi_write_packet(&MS5607_SPI_PORT, command,1);
	spi_read_packet(&MS5607_SPI_PORT, read_buffer,4);
	
	spi_deselect_device(&MS5607_SPI_PORT, &spi_device_conf);
	uint32_t pressure_val = (uint32_t)*read_buffer;
	fprintf("%f\n", pressure_val);
}