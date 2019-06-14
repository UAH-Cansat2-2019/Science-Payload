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
#include <wdt.h>
//#include "drivers/I2CDriver.h"
#include "drivers/gps.h"
#include "drivers/Xbee.h"
#include "drivers/definitions.h"
#include "drivers/OpenLog.h"
#include "drivers/bno055.h"
#include "drivers/IMU.h"
#include "drivers/adc_sensors.h"
#include "drivers/mechanisms.h"
#include "drivers/gps.h"
#include "drivers/ms5607.h"
#include "drivers/spi_controller.h"

/************** I2C buffer length******/
volatile extern uint8_t XbeeRx;



void print_calibration_data(void);

int main (void)
{
	board_init();
	sysclk_init();
	//rtc_init();
	
	//packetCount = 0;
	//missionTime = rtc_get_time();
	//printf("%u", missionTime >> 16);
	
	if(DEBUG && 0)
	{
		wdt_set_timeout_period(WDT_TIMEOUT_PERIOD_2KCLK);
		wdt_enable();
	}
	

	
	uart_terminal_init();
	//newOLogInit();
	
	printf("uart is working\n");
	//spi_init();

	
	pmic_init();
	pmic_set_scheduling(PMIC_SCH_ROUND_ROBIN);
	irq_initialize_vectors();
	cpu_irq_enable();
	gps_init();
	//gps_init();
	
	//imu_init();
	//delay_s(1);
	//xbee_init();
	//servo_init();
	//thermistor_init();
	//volt_init();
	//spi_init_module();
	
	
	
	
	//uint8_t data;

	//uint8_t servoPos = 0;
	//set_servo(0);
	//buzz_on();
	//buzz_off();
	while (1) 
	{
		//imu_update();
		
		//printf("Pitch: %i\nRoll: %i\nYaw: %i\n",(int)imu_pitch(), (int)imu_roll(), (int)imu_heading());
		//printf("CALBRATION STATUSES:  Accel: %u, Gyro: %u, Mag: %u, Sys: %u\n", imu_accel_cal(), imu_gyro_cal(), imu_mag_cal(), imu_sys_cal());

		//Get Telemetry
		//missionTime = rtc_get_time();
		//packetCount++;
		//pressure = getPressure();
		//altitude = pressure / 9000; // TODO: finish function
		//temp = getTemperature();	
		//voltage = getVoltage();

		//set_servo(servoPos);
		//servoPos +=100;
		//pitch = imu_pitch();
		//roll = imu_roll();
		//heading = imu_heading();
		
		
		//write_telem_to_xbee();
		
		
		delay_ms(1000);


		
	
							
	}
}

void write_telem_to_xbee()
{
	char* telemetryString [255];
	*telemetryString = "\0";
	char* s_teamID = "2118";
	char* s_missionTime  [10];
	char* s_packetCount [10];
	char* s_altitude [10];
	char* s_pressure [10];
	char* s_temp [10];
	char* s_voltage [10];
	char* s_gpsTime [10];
	char* s_gpsLat [10];
	char* s_gpsLong [10];
	char* s_gpsAlt [10];
	char* s_gpsSats [10];
	char* s_pitch [10];
	char* s_roll [10];
	char* s_spinRate [10];
	char* s_flightState [10];
	char* s_cardinalDir [10];
	
	sprintf(s_missionTime, "%i", missionTime);
	sprintf(s_packetCount, "%i", packetCount);
	sprintf(s_altitude, "%f", altitude);
	sprintf(s_pressure, "%i",pressure);
	sprintf(s_temp, "%f", temp);
	sprintf(s_voltage, "%f", voltage);
	sprintf(s_gpsTime, " ");
	sprintf(s_gpsLat, " ");
	sprintf(s_gpsLong, " ");
	sprintf(s_gpsAlt, " ");
	sprintf(s_gpsSats, " ");
	sprintf(s_pitch, "%f", pitch);
	sprintf(s_roll, "%f", roll);
	sprintf(s_spinRate, " ");
	sprintf(s_flightState, "%i", flightState);
	sprintf(s_cardinalDir, "%f", heading);
	
	
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
}

void get_offset(int MSB_reg, uint16_t * returnData)
{
	
}

void print_calibration_data()
{
	
}

