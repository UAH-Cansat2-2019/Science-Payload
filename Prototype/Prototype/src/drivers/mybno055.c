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
void BNO055_Write(uint8_t *data)
{
	if(readbitrate()!=(BN0_BAUD_KHZ)*1000)//checks if I2C to the right bitrate has been initialized
	{
		I2CInit(BN0_BAUD_KHZ*1000);
	}
	twi_write(data,BN0_ADDR);//writes data to the sensor
}
void BNO_Read(uint8_t * data)
{
	twi_read(data,BN0_ADDR);
}
void BNO055_Config()
{
	//sets mode to config mode
	uint8_t data[]={BNO055_OPERATION_MODE_REG,BNO055_OPERATION_MODE_CONFIG};
	BNO055_Write (data);
	
	//select units
	 data[0]=BNO055_UNIT_SEL_ADDR;
	 data[1]=UNIT_SEL;
	BNO055_Write(data);
	
	
	//sets mode to fusion bno
	data[0]=BNO055_OPERATION_MODE_REG;
	data[1]=BNO055_OPERATION_MODE_NDOF;
	BNO055_Write (data);
	
}
//store a three long array containing the x, y and z acceleration in that order units of cm/s^2
void get_acceleration(uint16_t * acceleration)
{
	uint8_t data;
	//read x data
	data=BNO055_ACCEL_DATA_X_MSB_ADDR;
	 BNO055_Write(&data);
	 BNO_Read(&data);
	 acceleration[0]= ((uint16_t) data)<<8;
	 data=BNO055_ACCEL_DATA_X_LSB_ADDR;
	 BNO055_Write(&data);
	 BNO_Read(&data);
	 acceleration[0]+=data;
	 
	 //read y data
	 data=BNO055_ACCEL_DATA_Y_MSB_ADDR;
	 BNO055_Write(&data);
	 BNO_Read(&data);
	 acceleration[1]=((uint16_t) data)<<8;
	 
	 data=BNO055_ACCEL_DATA_Y_LSB_ADDR;
	 BNO055_Write(&data);
	 BNO_Read(&data);
	 acceleration[1]+=data;
	 
	 //read z data
	 data=BNO055_ACCEL_DATA_Z_MSB_ADDR;
	 BNO055_Write(&data);
	 BNO_Read(&data);
	 acceleration[2]= ((uint16_t) data)<<8;
	 data=BNO055_ACCEL_DATA_Z_LSB_ADDR;
	 BNO055_Write(&data);
	 BNO_Read(&data);
	 acceleration[2]+=data;
	 
}

//function to get heading, pitch, and roll in that order. degree measure
void get_Angle(uint16_t * angle)//takes a three element array
{
	uint8_t data;
	//gets heading
	data=BNO055_EULER_H_MSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	angle[0]=((uint16_t)data)<<8;
	data=BNO055_EULER_H_LSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	angle[0]+=data;
	angle[0]=angle[0]/16;//convert to degrees
	
	//reads the pitch
	data=BNO055_EULER_P_MSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	angle[1]=((uint16_t)data)<<8;
	data=BNO055_EULER_P_LSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	angle[1]+=data;
	angle[1]=angle[1]/16;
	
	//reads the roll
	data=BNO055_EULER_R_MSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	angle[2]=((uint16_t)data)<<8;
	data=BNO055_EULER_R_LSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	angle[2]+=data;
	angle[2]=angle[2]/16;
}
//takes a pointer to store the x, y and z components of the magnetic field in microteslas
void get_mag(uint16_t * mag)
{
	uint8_t data;
	//read x direction data
	data=BNO055_MAG_DATA_X_MSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	mag[0]=(uint16_t)data<<8;
	data=BNO055_MAG_DATA_X_LSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	mag[0]+=data;
	mag[0]=mag[0]/16;//convert units
	
	//read y direction data
	data=BNO055_MAG_DATA_Y_MSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	mag[2]=(uint16_t)data<<8;
	data=BNO055_MAG_DATA_Y_LSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	mag[1]+=data;
	mag[1]=mag[1]/16;//convert units
	
	//z magnetic info
	data=BNO055_MAG_DATA_Z_MSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	mag[2]=(uint16_t)data<<8;
	data=BNO055_MAG_DATA_Z_LSB_ADDR;
	BNO055_Write(&data);
	BNO_Read(&data);
	mag[2]+=data;
	mag[2]=mag[2]/16;
	
}

//gets gyroscopic acceleration in dps
void get_gyro(uint16_t*gyro)
{
	uint8_t data;
	BNO055_Write(BNO055_GYRO_DATA_X_MSB_ADDR);
	BNO_Read(&data);
	gyro[0]=data<<8;
	BNO055_Write(BNO055_GYRO_DATA_X_LSB_ADDR);
	BNO_Read(&data);
	gyro[0]+=data;
	gyro[0]=gyro[0]/16;
	
	BNO055_Write(BNO055_GYRO_DATA_Y_MSB_ADDR);
	BNO_Read(&data);
	gyro[1]=data<<8;
	BNO055_Write(BNO055_GYRO_DATA_Y_LSB_ADDR);
	BNO_Read(&data);
	gyro[1]+=data;
	gyro[1]=gyro[1]/16;
	
	BNO055_Write(BNO055_GYRO_DATA_Z_MSB_ADDR);
	BNO_Read(&data);
	gyro[2]=data<<8;
	BNO055_Write(BNO055_GYRO_DATA_Z_LSB_ADDR);
	BNO_Read(&data);
	gyro[2]+=data;
	gyro[2]=gyro[0]/16;
}

//modes to save power when not in use
void BNO055_Sleep()
{
	uint8_t data[]={BNO055_PWR_MODE_ADDR,SUSP_PWR_MODE};
	BNO055_Write (data);
}
void BNO055_Wake()
{
	uint8_t data[]={BNO055_PWR_MODE_ADDR,NORM_PWR_MODE};
	BNO055_Write (data);
	
}
