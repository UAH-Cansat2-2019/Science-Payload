/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>



#include "drivers/uart.h"
#include "BNO055Driver.h"

#include "RingBuff.h"

#include <string.h>
#include <util/atomic.h>
#include <math.h>

//#include "drivers/I2CDriver.h"
#include "drivers/gps.h"
#include "drivers/Xbee.h"
#include "drivers/definitions.h"
#include "drivers/OpenLog.h"
#include "drivers/bno055.h"
#include "drivers/IMU.h"
#include "drivers/adc_sensors.h"
#include "driver/mechanism.h"
/************** I2C buffer length******/
volatile extern uint8_t XbeeRx;



void print_calibration_data(void);

int main (void)
{
	
	
	
	
	uint16_t packetCount = 0;
	
	board_init();
	sysclk_init();
	
	
	//sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_HIRES);
	//sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_HIRES);
	//sysclk_enable_module(SYSCLK_PORT_D, SYSCLK_HIRES);
	sysclk_enable_module(SYSCLK_PORT_F, PR_TWI_bm);
	//sysclk_enable_module(SYSCLK_PORT_F, PR_TWI_bm);

	//sysclk_enable_peripheral_clock(&USARTE0);

	
	
	uart_terminal_init();
	newOLogInit();
	printf("uart is working\n");
	
	char* telemetryString = (char*)malloc(255 * sizeof(char)) ;
	*telemetryString = "\0";
	char* s_teamID = "2118";//what a hardcoded char pointer?
	char* s_missionTime = (char*)malloc(10 * sizeof(char));
	char* s_packetCount =(char*)malloc(10 * sizeof(char));
	char* s_altitude= (char*)malloc(10 * sizeof(char));
	char* s_pressure= (char*)malloc(10 * sizeof(char));
	char* s_temp= (char*)malloc(10 * sizeof(char));
	char* s_voltage= (char*)malloc(10 * sizeof(char));
	char* s_gpsTime= (char*)malloc(10 * sizeof(char));
	char* s_gpsLat= (char*)malloc(10 * sizeof(char));
	char* s_gpsLong= (char*)malloc(10 * sizeof(char));
	char* s_gpsAlt= (char*)malloc(10 * sizeof(char));
	char* s_gpsSats= (char*)malloc(10 * sizeof(char));
	char* s_pitch= (char*)malloc(10 * sizeof(char));
	char* s_roll= (char*)malloc(10 * sizeof(char));
	char* s_spinRate= (char*)malloc(10 * sizeof(char));
	char* s_flightState= (char*)malloc(10 * sizeof(char));
	char* s_cardinalDir= (char*)malloc(10 * sizeof(char));
	
	pmic_init();
	delay_ms(1000);
	pmic_set_scheduling(PMIC_SCH_ROUND_ROBIN);
	cpu_irq_enable();
	
	printf("\tpmic Init\n");
	
	//I2CInit(115200,0x28);
	//delay_ms(1000);
	sysclk_enable_peripheral_clock(&TWIF);
	
	imu_init();
	xbee_init();
	
	thermistor_init();
	volt_init();
	printf("\tXbee Init\n");
	
	
	
	uint8_t data;
	float temp;
	float voltage;
			

		
	while (1) 
	{
	
		buzz_on();
		imu_update();
		
		printf("Pitch: %i\nRoll: %i\nYaw: %i\n",(int)imu_pitch(), (int)imu_roll(), (int)imu_heading());
		printf("CALBRATION STATUSES:  Accel: %u, Gyro: %u, Mag: %u, Sys: %u\n", imu_accel_cal(), imu_gyro_cal(), imu_mag_cal(), imu_sys_cal());
		
		
		
		temp = getTemperature();
		printf("temp: %f\n", temp);
		
		voltage = getVoltage();
		printf("volt: %f\n",voltage);
			
		//print_calibration_data();
		
		
	
		sprintf(s_missionTime, " ");
		sprintf(s_packetCount, " ");
		sprintf(s_altitude, " ");
		sprintf(s_pressure, " ");
		sprintf(s_temp, " ");
		sprintf(s_voltage, " ");
		sprintf(s_gpsTime, " ");
		sprintf(s_gpsLat, " ");
		sprintf(s_gpsLong, " ");
		sprintf(s_gpsAlt, " ");
		sprintf(s_gpsSats, " ");
		sprintf(s_pitch, " ");
		sprintf(s_roll, " ");
		sprintf(s_spinRate, " ");
		sprintf(s_flightState, " ");
		sprintf(s_cardinalDir, " ");
		
		
		sprintf(telemetryString,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",
			s_teamID,
			s_missionTime,
			s_packetCount,
			s_altitude,
			s_pressure,
			s_temp,
			s_voltage,
			s_gpsTime,
			s_gpsLat,
			s_gpsLong,
			s_gpsAlt,
			s_gpsSats,
			s_pitch,
			s_roll,
			s_spinRate,
			s_flightState,
			s_cardinalDir);
		
		xbeeWrite(telemetryString);
		delay_ms(25):
		buzz_off();
		delay_ms(25);

		
	
							
	}
}


void get_offset(int MSB_reg, uint16_t * returnData)
{
	
}

void print_calibration_data()
{
	
}

