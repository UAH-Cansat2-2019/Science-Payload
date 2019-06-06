/*
 * I2CDriver.c
 *Interface for communicating with all of our I2C devices
 * 
 *  Author: Nathan
 */ 
#include "compiler.h"
#include <asf.h>
#include "I2CDriver.h"
//needed to use I2C. two devices use different baud rates call this function again.
//there is some example code at http://asf.atmel.com/docs/latest/xmegaa/html/twi_quickstart.html
uint8_t busAddress;

void I2CInit(uint32_t baud,uint8_t busad)
{
	busAddress=busad;
	twi_master_options_t opt={.speed=baud,.chip=busad};//creats options struct for initialazation
	twi_master_setup(&MYI2C,&opt);//sets up master
}
uint8_t readBusad()
{
	return busAddress;
}
// writes to a device using two wire interface. the address is the seven bit identifier for the specific device
//data is an array of data that you wish to transfer. 
void twi_write(uint8_t * Data,uint8_t address,uint8_t memAddress)
{
	twi_package_t packet_write = 
	{
		.addr=memAddress,	
		.addr_length=sizeof(uint8_t),
		.chip         = address,      // TWI slave bus address
		.buffer       = Data, // transfer data source buffer
		.length       = sizeof(Data)  // transfer data size (bytes)
	};
	while (twi_master_write(&MYI2C, &packet_write) != TWI_SUCCESS) printf("fail");//transfers data and waits until transfer is finished to do anything else
}

//reads using two wire interface. address is the 7 bit identifier for each device. Data is the array the data will be stored in.
//returns the status of the transfer
void twi_read(uint8_t * Data,uint8_t address,uint8_t memAddress)
{
	twi_package_t packet_read = 
	{
		.addr=memAddress,
		.addr_length=sizeof(uint8_t),
		.chip         = address,       // TWI slave bus address
		.buffer       = Data,          // transfer data destination buffer
		.length       = sizeof(Data)        // transfer data size (bytes)
	};
	twi_master_read(&MYI2C, &packet_read); //preform read and return the status of the read
	//Data = packet_read.buffer;
	
	
}
