/*
 * definitions.h
 *
 * Created: 6/6/2019 4:49:54 PM
 *  Author: quaz9
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <string.h>
#include <util/atomic.h>
#include <math.h>
#include <wdt.h>

//#include "uart.h" 

/**
	DEBUG OPTIONS
**/
#define DEBUG true
#define DEBUG_ADC false
#define DEBUG_IMU false
#define DEBUG_TELEM true
#define DEBUG_GPS true

#define FAILSAFE_LAUNCH_MODE false // backup for flight states if we don't actually test them


/************************************************************************/
/* FS0 Launch Detect Params                                                                     */
/************************************************************************/
#define FS0_MIN_VEL			 2	// m/s
#define FS0_MIN_ACCEL		 5  // m/s^2
#define FS0_MAX_HEIGHT_DRIFT 15 // m
#define FS0_MIN_ALTITUDE     40 // m


/************************************************************************/
/* FS1 Apogee Detect Params                                             */
/************************************************************************/
#define FS1_MAX_VEL			 -2	// m/s
#define FS1_MAX_ACCEL		 2  // m/s^2
#define FS1_MAX_HEIGHT_DRIFT 50 // m
#define FS1_MIN_ALTITUDE     10 // m


/************************************************************************/
/* FS2 Apogee Detect Params                                             */
/************************************************************************/
#define FS2_MIN_VEL			 2	 // m/s
#define FS2_MAX_ACCEL		 -5  // m/s^2
#define FS2_MAX_HEIGHT_DRIFT 50  // m
#define FS2_MAX_ALTITUDE     460 // m



/************************************************************************/
/* FS3 Apogee Detect Params                                             */
/************************************************************************/
#define FS3_MAX_VEL			 3	 // m/s
#define FS3_MAX_ACCEL		 10  // m/s^2
#define FS3_MAX_HEIGHT_DRIFT 50  // m
#define FS3_MAX_ALTITUDE     80  // m



bool blockTransmission;

float temp;
float voltage;

float accZ;

uint32_t packetCount;
uint32_t missionTime;
int32_t pressure;
float altitude;

double pitch;
double roll;
double heading;
double velocity;
double accelHeight;
uint8_t flightState;



#endif /* DEFINITIONS_H_ */