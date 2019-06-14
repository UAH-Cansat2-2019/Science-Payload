/*
 * IMU.h
 *
 * Created: 6/7/2019 11:23:19 AM
 *  Author: trbinsc
 */ 



#ifndef IMU_H_
#define IMU_H_

#include <asf.h>
#include <string.h>
#include "bno055.h"
#include "definitions.h"

#define FIXMATH_NO_CACHE 1

#define	I2C_BUFFER_LEN 64
#define I2C0 5
#define	BNO055_I2C_BUS_WRITE_ARRAY_INDEX	((u8)1)

#define IMU_TWI TWIF

void imu_init();

void imu_update();

double currentAccZ;
double currentVelZ;
double currentPosZ;
double prevAccZ;
double prevVelZ;
double prevPosZ ;
double prevTime;
double prevPrevTime;

double imu_accel_x();
double imu_accel_y();
double imu_accel_z();
double imu_accel_dist();

double imu_vel_z();
double imu_pos_z();

double imu_roll();
double imu_pitch();
double imu_heading();

uint8_t imu_accel_cal();
uint8_t imu_gyro_cal();
uint8_t imu_mag_cal();
uint8_t imu_sys_cal();



#endif /* IMU_H_ */