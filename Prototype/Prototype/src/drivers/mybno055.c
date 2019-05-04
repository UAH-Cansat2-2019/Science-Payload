/*
 * mybno055.c
 *
 * Created: 4/15/2019 1:35:15 PM
 *  Author: Nathan
 */ 
#include <ASF.h>
#include "mybno055.h"
#include "I2CDriver.h"


//writes data to the to the imu 
void BNO_Write(uint8_t *data,uint8_t memAddress)
{
	if(readBusad()!=BN0_ADDR)//checks if I2C to the right bitrate has been initialized
	{
		I2CInit(BN0_BAUD_HZ,BN0_ADDR);
	}
	twi_write(data,BN0_ADDR,memAddress);//writes data to the sensor
}


void BNO_Read(uint8_t * data,uint8_t memAddress)
{
	twi_read(data,BN0_ADDR,memAddress);
}

//who am I register
uint16_t WhoAmIBNO()
{
	
	uint8_t dataMSB = 0xFF;
	BNO_Read(&dataMSB,0x0C);
	uint8_t dataLSB = 0xFF;
	BNO_Read(&dataLSB, 0x0D);
	int16_t data = ((int16_t)dataMSB) << 8 + (uint16_t)dataLSB; 
	return data;
}

void BNO055_Config()
{
	//sets mode to config mode
	uint8_t data=BNO055_OPERATION_MODE_REG;
	BNO_Write (&data, BNO055_OPERATION_MODE_CONFIG);
	
	//select units
	 data=BNO055_UNIT_SEL_ADDR;
	 
	BNO_Write(BNO055_UNIT_SEL_ADDR,UNIT_SEL);
	
	
	//sets mode to fusion bno
	data=BNO055_OPERATION_MODE_REG;

	BNO_Write (&data,BNO055_OPERATION_MODE_NDOF);
	
}
//store a three long array containing the x, y and z acceleration in that order units of cm/s^2
void get_acceleration(int16_t * acceleration)
{
	uint8_t data=0xFF;
	//read x data
	
	 BNO_Read(&data,BNO055_ACCEL_DATA_X_MSB_ADDR);
	 acceleration[0]= ((uint16_t) data)<<8;
	 data=0xFF;
	
	 BNO_Read(&data,BNO055_ACCEL_DATA_X_LSB_ADDR);
	 acceleration[0]+=data;
	 
	 //read y data
	 data=0xFF;
	 
	 BNO_Read(&data,BNO055_ACCEL_DATA_Y_MSB_ADDR);
	 acceleration[1]=((uint16_t) data)<<8;
	 
	 data=0xFF;
	 
	 BNO_Read(&data,BNO055_ACCEL_DATA_Y_LSB_ADDR);
	 acceleration[1]+=data;
	 
	 //read z data
	 data=0xff;
	 
	 BNO_Read(&data,BNO055_ACCEL_DATA_Z_MSB_ADDR);
	 acceleration[2]= ((uint16_t) data)<<8;
	 data=0xff;
	
	 BNO_Read(&data,BNO055_ACCEL_DATA_Z_LSB_ADDR);
	 acceleration[2]+=data;
	 
}

//function to get heading, pitch, and roll in that order. degree measure
void get_Angle(int16_t * angle)//takes a three element array
{
	uint8_t data;
	//gets heading
	data=BNO055_EULER_H_MSB_ADDR;
	
	BNO_Read(&data,BNO055_EULER_H_MSB_ADDR);
	angle[0]=((uint16_t)data)<<8;
	data=0xFF;
	
	BNO_Read(&data,BNO055_EULER_H_LSB_ADDR);
	angle[0]+=data;
	angle[0]=angle[0]/16;//convert to degrees
	
	//reads the pitch
	data=BNO055_EULER_P_MSB_ADDR;

	data=0xFF;
	BNO_Read(&data,BNO055_EULER_P_MSB_ADDR);
	angle[1]=((uint16_t)data)<<8;
	data=0xff;
	
	BNO_Read(&data,BNO055_EULER_P_LSB_ADDR);
	angle[1]+=data;
	angle[1]=angle[1]/16;
	
	//reads the roll
	data=0xff;
	
	BNO_Read(&data,BNO055_EULER_R_MSB_ADDR);
	angle[2]=((uint16_t)data)<<8;
	data=0xff;
	
	BNO_Read(&data,BNO055_EULER_R_LSB_ADDR);
	angle[2]+=data;
	angle[2]=angle[2]/16;
}
//takes a pointer to store the x, y and z components of the magnetic field in microteslas
void get_mag(int16_t * mag)
{
	uint8_t data;
	//read x direction data
	data=0xff;
	
	BNO_Read(&data,BNO055_MAG_DATA_X_MSB_ADDR);
	mag[0]=(uint16_t)data<<8;
	data=0xff;
	
	BNO_Read(&data,BNO055_MAG_DATA_X_LSB_ADDR);
	mag[0]+=data;
	mag[0]=mag[0]/16;//convert units
	
	//read y direction data
	data=0xff;
	
	BNO_Read(&data,BNO055_MAG_DATA_Y_MSB_ADDR);
	mag[2]=(uint16_t)data<<8;
	data=0xff;
	
	BNO_Read(&data,BNO055_MAG_DATA_Y_LSB_ADDR);
	mag[1]+=data;
	mag[1]=mag[1]/16;//convert units
	
	//z magnetic info
	data=0xff;
	
	BNO_Read(&data,BNO055_MAG_DATA_Z_MSB_ADDR);
	mag[2]=(uint16_t)data<<8;
	data=0xff;
	
	BNO_Read(&data,BNO055_MAG_DATA_Z_LSB_ADDR);
	mag[2]+=data;
	mag[2]=mag[2]/16;
	
}

//gets gyroscopic acceleration in dps
void get_gyro(int16_t*gyro)
{
	uint8_t data;
	
	BNO_Read(&data,BNO055_GYRO_DATA_X_MSB_ADDR);
	gyro[0]=data<<8;
	
	BNO_Read(&data,BNO055_GYRO_DATA_X_LSB_ADDR);
	gyro[0]+=data;
	gyro[0]=gyro[0]/16;
	
	
	BNO_Read(&data,BNO055_GYRO_DATA_Y_MSB_ADDR);
	gyro[1]=data<<8;
	
	BNO_Read(&data,BNO055_GYRO_DATA_Y_LSB_ADDR);
	gyro[1]+=data;
	gyro[1]=gyro[1]/16;
	
	BNO_Read(&data,BNO055_GYRO_DATA_Z_MSB_ADDR);
	gyro[2]=data<<8;
	
	BNO_Read(&data,BNO055_GYRO_DATA_Z_LSB_ADDR);
	gyro[2]+=data;
	gyro[2]=gyro[0]/16;
}

