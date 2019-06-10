/*
 * BNO055Driver.c
 *
 * Created: 5/30/2019 8:18:35 PM
 *  Author: natha
 */ 

//writes data to the to the imu
#include <ASF.h>
#include "drivers/I2CDriver.h"
#include "BNO055Driver.h"




void BNO_Write(uint8_t *data,uint8_t memAddress)
{
	twi_write(data,BN0_ADDR,memAddress);//writes data to the sensor
}


void BNO_Read(uint8_t * data,uint8_t memAddress)
{
	twi_read(data,BN0_ADDR,memAddress);
}
void BNO_init()
{
	//uint8_t data;
	//data=0;
	//twi_write(&data,BN0_ADDR,0X3D);
	//delay_ms(30);
	//
	//data=0X0C;
	//twi_write(&data,BN0_ADDR,0X3D);
	//delay_ms(10);
}
//uint16_t WhoAmIBNO()
//{
//
//uint8_t dataMSB = 0xFF;
//BNO_Read(&dataMSB,0x0C);
//uint8_t dataLSB = 0xFF;
//BNO_Read(&dataLSB, 0x0D);
//int16_t data = ((int16_t)dataMSB) << 8 + (uint16_t)dataLSB;
//return data;
//}

//store a three long array containing the x, y and z acceleration in that order units of cm/s^2
uint16_t get_acceleration_x()
{
	uint16_t acelx;
	uint8_t data = 0xff;
	delay_ms(10);
	BNO_Read(&data,BNO055_ACCEL_DATA_X_MSB_ADDR);
	delay_ms(10);
	
	acelx=(int16_t)data;
	
	acelx=acelx<<8;
	
	
	data = 0xff;
	delay_ms(10);
	BNO_Read(&data,BNO055_ACCEL_DATA_X_LSB_ADDR);
	delay_ms(10);

	acelx+=data;
	return acelx;
}

uint16_t get_acceleration_y()
{
	uint16_t acely;
	uint8_t data = 0xff;
	delay_ms(10);
	BNO_Read(&data,BNO055_ACCEL_DATA_Y_MSB_ADDR);
	delay_ms(10);
	
	acely=(int16_t)data;
	
	acely=acely<<8;
	
	
	data = 0xff;
	delay_ms(10);
	BNO_Read(&data,BNO055_ACCEL_DATA_Y_LSB_ADDR);
	delay_ms(10);

	acely+=data;
	return acely;
}

uint16_t get_acceleration_z()
{
	uint16_t acelz;
	uint8_t data = 0xff;
	delay_ms(10);
	BNO_Read(&data,BNO055_ACCEL_DATA_Z_MSB_ADDR);
	delay_ms(10);
	
	acelz=(int16_t)data;
	
	acelz=acelz<<8;
	
	
	data = 0xff;
	delay_ms(10);
	BNO_Read(&data,BNO055_ACCEL_DATA_Z_LSB_ADDR);
	delay_ms(10);

	acelz+=data;
	return acelz;
}

uint8_t is_BNO_calib()
{
	uint8_t data;
	BNO_Read(&data,BNO055_CALIB_STAT_ADDR);
	for(uint8_t i=0;i>6;i++)
	{
		if(!(data&1)) return 0;
		data=data>>1;
	}
	return 1;
}

//function to get heading, pitch, and roll in that order. degree measure
void get_Angle(double * quaternion)//takes a three element array
{
	uint16_t angle[4];
	
	uint8_t data;
	//gets heading
	data=0xff;
	
	delay_ms(15);
	BNO_Read(&data,BNO055_QUATERNION_DATA_W_MSB_ADDR);
	angle[0]=((uint16_t)data)<<8;
	data=0xFF;
	
	delay_ms(15);
	BNO_Read(&data,BNO055_QUATERNION_DATA_W_LSB_ADDR);
	angle[0]|=((uint16_t)data);
	
	
	//reads the pitch
	
	data=0xFF;
	
	delay_ms(15);
	BNO_Read(&data,BNO055_QUATERNION_DATA_X_MSB_ADDR);
	angle[1]=((uint16_t)data)<<8;
	data=0xFF;
	
	delay_ms(15);
	BNO_Read(&data,BNO055_QUATERNION_DATA_X_LSB_ADDR);
	angle[1]|=((uint16_t)data);
	
	
		data=0xff;
		
		delay_ms(15);
		BNO_Read(&data,BNO055_QUATERNION_DATA_Y_MSB_ADDR);
		angle[2]=((uint16_t)data)<<8;
		data=0xFF;
		
		delay_ms(15);
		BNO_Read(&data,BNO055_QUATERNION_DATA_Y_LSB_ADDR);
		angle[2]|=((uint16_t)data);
		
		
		//reads the pitch
		
		data=0xFF;
		
		delay_ms(15);
		BNO_Read(&data,BNO055_QUATERNION_DATA_Z_MSB_ADDR);
		angle[3]=((uint16_t)data)<<8;
		data=0xFF;
		
		delay_ms(15);
		BNO_Read(&data,BNO055_QUATERNION_DATA_Z_LSB_ADDR);
		angle[3]|=((uint16_t)data);
		
		
	
	
	const double scale = (1.0/(1<<14));
	
	quaternion[0] = 5;//*angle * scale;
	quaternion[1] =4;// angle[1] * scale;
	quaternion[2] = 3;//angle[2] * scale;//* scale;
	quaternion[3] = 2;//angle[3] * scale;//* scale;
	
	
	
}
//takes a pointer to store the x, y and z components of the magnetic field in microteslas
void get_mag(int16_t * mag)
{
	uint8_t data;
	//read x direction data
	data=0xff;
	
	BNO_Read(&data,BNO055_MAG_DATA_X_MSB_ADDR);
	mag[0]=((uint16_t)data)<<8;
	data=0xff;
	
	BNO_Read(&data,BNO055_MAG_DATA_X_LSB_ADDR);
	mag[0]+=data;
	mag[0]=mag[0]/16;//convert units
	
	//read y direction data
	data=0xff;
	
	BNO_Read(&data,BNO055_MAG_DATA_Y_MSB_ADDR);
	mag[2]=((uint16_t)data)<<8;
	data=0xff;
	
	BNO_Read(&data,BNO055_MAG_DATA_Y_LSB_ADDR);
	mag[1]+=data;
	mag[1]=mag[1]/16;//convert units
	
	//z magnetic info
	data=0xff;
	
	BNO_Read(&data,BNO055_MAG_DATA_Z_MSB_ADDR);
	mag[2]=((uint16_t)data)<<8;
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
	gyro[0]=((uint16_t)data)<<8;
	
	BNO_Read(&data,BNO055_GYRO_DATA_X_LSB_ADDR);
	gyro[0]+=data;
	gyro[0]=gyro[0]/16;
	
	
	BNO_Read(&data,BNO055_GYRO_DATA_Y_MSB_ADDR);
	gyro[1]=((uint16_t)data)<<8;
	
	BNO_Read(&data,BNO055_GYRO_DATA_Y_LSB_ADDR);
	gyro[1]+=data;
	gyro[1]=gyro[1]/16;
	
	BNO_Read(&data,BNO055_GYRO_DATA_Z_MSB_ADDR);
	gyro[2]=((uint16_t)data)<<8;
	
	BNO_Read(&data,BNO055_GYRO_DATA_Z_LSB_ADDR);
	gyro[2]+=data;
	gyro[2]=gyro[0]/16;
}
//populates array with offset array needs to be of length 18
void get_offsets(uint8_t * offsets)
{
	if(!is_BNO_calib()) return;
	uint8_t data=BNO055_OPERATION_MODE_CONFIG;
	BNO_Write(&data,BNO055_OPR_MODE_ADDR);//mode needs to be config to read offsets
	delay_ms(22);//by the data sheet it takes 19 ms to switch to config mode
	BNO_Read(offsets,BNO055_ACCEL_OFFSET_X_LSB_ADDR);//addresses the first element and the sensor automatically increments itself
	data=BNO055_OPERATION_MODE_NDOF;
	BNO_Write(&data,BNO055_OPR_MODE_ADDR);
}
//needs to be the exact same array as read gives you
void set_offsets(uint8_t * offsets)
{
	uint8_t data=BNO055_OPERATION_MODE_CONFIG;
	BNO_Write(&data,BNO055_OPR_MODE_ADDR);//mode needs to be config to Write offsets
	delay_ms(22);//by the data sheet it takes 19 ms to switch to config mode
	for(uint8_t i=0;i<18;i++)// It doesn't look like a multiple write is supported so I just loop through all possible values
	{
		BNO_Write(&data,i+BNO055_ACCEL_OFFSET_X_LSB_ADDR);
		offsets[i]=data;
	}
	data=BNO055_OPERATION_MODE_NDOF;
	BNO_Write(&data,BNO055_OPR_MODE_ADDR);
}




//void get_acceleration(int16_t acceleration[3])
//{
//uint8_t data=0xFF;
////read x data
//
//BNO_Read(&data,BNO055_ACCEL_DATA_X_MSB_ADDR);
//delay_ms(10);
//acceleration[0] = (((uint16_t) data)<<8);
//delay_ms(10);
//data=0xFF;
//delay_ms(10);
//BNO_Read(&data,BNO055_ACCEL_DATA_X_LSB_ADDR);
//delay_ms(10);
//acceleration[0]+=data;
//delay_ms(10);
////read y data
//data=0xFF;
//
//BNO_Read(&data,BNO055_ACCEL_DATA_Y_MSB_ADDR);
//
//delay_ms(10);
//
//acceleration[1]=(((uint16_t) data)<<8);
//
//delay_ms(10);
//
//data=0xFF;
//
//BNO_Read(&data,BNO055_ACCEL_DATA_Y_LSB_ADDR);
//acceleration[1]+=data;
//delay_ms(10);
////read z data
//data=0xff;
//
//BNO_Read(&data,BNO055_ACCEL_DATA_Z_MSB_ADDR);
//
//delay_ms(10);
//
//acceleration[2]= (((uint16_t) data)<<8);
//
//delay_ms(10);
//
//data=0xff;
//delay_ms(10);
//BNO_Read(&data,BNO055_ACCEL_DATA_Z_LSB_ADDR);
//
//delay_ms(10);
//
//acceleration[2]+=data;
//
//}