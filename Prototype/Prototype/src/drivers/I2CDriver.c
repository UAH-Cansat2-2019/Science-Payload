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
unsigned long bitrate=0;
void I2CInit(unsigned long baud)
{
	bitrate=baud;
	twi_master_options_t opt={.speed=baud,.chip=BUSAD};//creats options struct for initialazation
	twi_master_setup(&MYI2C,&opt);//sets up master
}
unsigned long readbitrate()
{
	return bitrate;
}
// writes to a device using two wire interface. the address is the seven bit identifier for the specific device
//data is an array of data that you wish to transfer. 
void twi_write(uint8_t * Data,uint8_t address)
{
	twi_package_t packet_write = {
		.addr=0,			//as far as I can tell this is something tacked on to the beginning for reading and writing to
		//memories such as roms it sends this with the data to tell it where to read from. Not entirely sure. I think if we need something
		//like this we will just code it ourselves for the individual device for debugging purposes.
		.addr_length=0,
		.chip         = address,      // TWI slave bus address
		.buffer       = (void *)Data, // transfer data source buffer
		.length       = sizeof(Data)  // transfer data size (bytes)
	};
	while (twi_master_write(&MYI2C, &packet_write) != TWI_SUCCESS);//transfers data and waits until transfer is finished to do anything else
}

//reads using two wire interface. address is the 7 bit identifier for each device. Data is the array the data will be stored in.
//returns the status of the transfer
status_code_t twi_read(uint8_t * Data,uint8_t address)
{
	twi_package_t packet_read = {
		.addr=0,
		.addr_length=0,
		.chip         = address,       // TWI slave bus address
		.buffer       = Data,          // transfer data destination buffer
		.length       = sizeof(Data)        // transfer data size (bytes)
	};
	return twi_master_read(&MYI2C, &packet_read); //preform read and return the status of the read
	
}
