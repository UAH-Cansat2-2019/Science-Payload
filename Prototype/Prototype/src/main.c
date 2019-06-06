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
#include "drivers/I2CDriver.h"
#include "RingBuff.h"
#include <string.h>
#include "drivers/gps.h"
#include <util/atomic.h>
#include "drivers/Xbee.h"
#include <math.h>
#include <string.h>
#include "drivers/definitions.h"
/************** I2C buffer length******/
volatile extern uint8_t XbeeRx;





int main (void)
{
	
	
	char* telemetryString = (char*)malloc(255 * sizeof(char)) ;
	char* s_teamID = "2118";
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
	
	uint16_t packetCount = 0;
	
	//board_init();

	/* Insert application code here, after the board has been initialized. */

	/* This skeleton code simply sets the LED to the state of the button. */
	
	
	sysclk_init();
	board_init();
	uart_terminal_init();
	printf("uart is working\n");
	
	pmic_init();
	pmic_set_scheduling(PMIC_SCH_ROUND_ROBIN);
	cpu_irq_enable();
	
	//printf("\tpmic Init\n");
	
	I2CInit(115200,0x29);
	
	//printf("\tI2CInit\n");
	
	xbee_init();
	
	//printf("\tXbee Init\n");
	
	
	
	uint8_t data;
	int16_t acel[]={0,0,0};
	int16_t acelx;
		data=BNO055_OPERATION_MODE_CONFIG;
	//printf("\tPre-read1\n");
		BNO_Write (&data, BNO055_OPR_MODE_ADDR);
	//printf("\tPre-read2\n");
		delay_ms(22);
		
		data=BNO055_OPERATION_MODE_NDOF;
		BNO_Write (&data,BNO055_OPR_MODE_ADDR);
		delay_ms(8);
		
		const char* accXStr = (char*)malloc(83 * sizeof(char)) ;
		const char* accYStr = (char*)malloc(83 * sizeof(char)) ;
		const char* accZStr = (char*)malloc(83 * sizeof(char)) ;
		
	while (1) 
	{
		//printf("\tPre-read\n");
		//BNO_Read(&data,BNO055_SELFTEST_RESULT_ADDR);
		
		//printf("st_result = %i\n",data);
		
		//BNO_Read(&data,BNO055_OPR_MODE_ADDR);
		
		//printf("opr mode = %i\n",data);
		
		//BNO_Read(&data,BNO055_CALIB_STAT_ADDR);
		//printf("Calibstat %i\n",data);
		
		//get_acceleration(acel);
		//printf("acceleration is x = %i",acel[0]);
		//printf(", y=%i",acel[1]);
		//printf(", z=%i\n",acel[2]);
		
		int accX = get_acceleration_x();
		int accY = get_acceleration_y();
		int accZ = get_acceleration_z();
		
		
		
		
		delay_ms(5);
		if(accX>=0) sprintf(accXStr,"acelx %i.%i\n",abs(accX/100), abs(accX%100));
		else sprintf(accXStr,"acelx -%i.%i\n",abs(accX/100), abs(accX%100));
		delay_ms(5);
		if(accY>=0)sprintf(accYStr,"acely %i.%i\n",abs(accY/100), abs(accY%100) );
		else sprintf(accYStr,"acely -%i.%i\n",abs(accY/100), abs(accY%100) );
		delay_ms(5);
		if(accZ>=0)sprintf(accZStr,"acelz %i.%i\n",abs(accZ/100), abs(accZ%100));
		else sprintf(accZStr,"acelz %i.%i\n",abs(accZ/100), abs(accZ%100));
		
		
		
		printf(accXStr);
		printf(accYStr);
		printf(accZStr);
	
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
		
		
		sprintf(telemetryString,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",s_teamID,
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
	
		
		delay_ms(500);
		//printf("HELEHLALH\n");
		
		
							
	}
}

void tprintf()
{

}
