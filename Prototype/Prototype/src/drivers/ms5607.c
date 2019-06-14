/*
 * ms5607.c
 *
 * Created: 6/9/2019 4:11:57 PM
 *  Author: quaz9
 */ 

#include "ms5607.h"


uint8_t commands [2] = {0x48, 0x58};
uint8_t read_buffer [2*3];
	
void spi_init_pins(void)
{
	ioport_configure_port_pin(&PORTC, PIN1_bm, IOPORT_INIT_HIGH|IOPORT_DIR_OUTPUT);
	
	ioport_configure_port_pin(&PORTC, PIN4_bm, IOPORT_PULL_UP|IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTC, PIN5_bm, IOPORT_INIT_HIGH|IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&PORTC, PIN6_bm, IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTC, PIN7_bm, IOPORT_INIT_HIGH|IOPORT_DIR_OUTPUT);
	
}

void spi_init_module(void)
{
	spi_init_pins();
	struct spi_device  spi_device_cong = {
		.id = IOPORT_CREATE_PIN(PORTC,1)
	};
		
	spi_master_init(&MS5607_SPI_PORT);
	spi_master_setup_device(&MS5607_SPI_PORT, &spi_device_cong, SPI_MODE_0, 1000000,0);
	spi_enable(&MS5607_SPI_PORT);
	spi_write_packet(&MS5607_SPI_PORT, "0x1e", 1); //reset
	prom_read();
	
	printf("spi init");
}

void prom_read(void)
{
	struct spi_device  spi_device_cong = {
		.id = IOPORT_CREATE_PIN(PORTC,1)
	};
	
	spi_select_device(&MS5607_SPI_PORT, &spi_device_cong);
	
	uint8_t prom_commands_c [6] = {0xA2, 0xA4, 0xA6, 0xA8, 0xAA, 0xAC};
	uint8_t prom_c_read_buffer [12];

	
	for(uint8_t i = 0; i <= sizeof(prom_commands_c); i++)
	{
		
		spi_write_packet(&MS5607_SPI_PORT, prom_commands_c[i], 1);
		delay_ms(25);
		spi_read_packet(&MS5607_SPI_PORT, prom_c_read_buffer[i], 2);
		delay_ms(25);
		
	}

	
	
	C1 = prom_c_read_buffer[0]<<8 |prom_c_read_buffer[1];
	C2 = prom_c_read_buffer[2]<<8 |prom_c_read_buffer[3];
	C3 = prom_c_read_buffer[4]<<8 |prom_c_read_buffer[5];
	C4 = prom_c_read_buffer[6]<<8 |prom_c_read_buffer[7];
	C5 = prom_c_read_buffer[8]<<8 |prom_c_read_buffer[9];
	C6 = prom_c_read_buffer[10]<<8 |prom_c_read_buffer[11];
	
	spi_deselect_device(&MS5607_SPI_PORT, &spi_device_cong);
	

	
}

int32_t getPressure(void)
{

struct spi_device  spi_device_cong = {
	.id = IOPORT_CREATE_PIN(PORTC,1)
};
	
	spi_select_device(&MS5607_SPI_PORT, &spi_device_cong);

	for(uint8_t i = 0; i < sizeof(commands); i++)
	{
		spi_write_packet(&MS5607_SPI_PORT, commands[i], 1);
		spi_read_packet(&MS5607_SPI_PORT, read_buffer[i], 3);
		
	}
	
	

	spi_deselect_device(&MS5607_SPI_PORT, &spi_device_cong);
	uint32_t pressure_val = (uint32_t) read_buffer[0]<<16| read_buffer[1]<<8 |read_buffer[2];
	printf("%u\n",pressure_val);
	
	D1 = (uint32_t) read_buffer[0]<<16| read_buffer[1]<<8 |read_buffer[2];
	D2 = (uint32_t)  read_buffer[3]<<16| read_buffer[4]<<8 |read_buffer[5];
	
	int32_t dT = (int64_t)D2 - (int64_t)C5 * 256; // Runs calculations to get dT
	int32_t TEMP = 2000 + (int64_t)dT * (int64_t)C6 / 8388608; // Finds actual temp

	
	int64_t OFF =	(int64_t)C2 * 131072 + ((int64_t)C4 * (int64_t)dT) / 64;
	int64_t SENS = (int64_t)C1 * 65536 + ((int64_t)C3 * (int64_t)dT) / 128;
	int32_t P = ((int64_t)D1 * (int64_t)SENS / 2097152 - (int64_t)OFF) / 32768; // Gets the actual temperature and type casts it.

	fprintf("%f\n", P);
	return P;
}