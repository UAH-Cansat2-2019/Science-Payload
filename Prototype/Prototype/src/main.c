/**
 * \file
 *
 * \brief Empty user application template
 *
 */


#include <asf.h>
#include "drivers/definitions.h"


#include "drivers/adc_sensors.h"
#include "drivers/gps.h"
#include "drivers/IMU.h"
#include "drivers/mechanisms.h"
#include "drivers/ms5607.h"
#include "drivers/OpenLog.h"
#include "drivers/uart.h"
#include "drivers/Xbee.h"

/*#include "flight_states.h"*/
/************** I2C buffer length******/
volatile extern uint8_t XbeeRx;



//#include "asf.h"
void fs_0()
{
	// detect launch??????
	if(velocity > FS0_MIN_VEL 
		&& accZ > FS0_MIN_ACCEL
		&& abs(accelHeight - altitude) < FS0_MAX_HEIGHT_DRIFT
		&& altitude > FS0_MIN_ALTITUDE)
	{
			flightState ++;
	}
}

void fs_1()
{
	// get vertical velocity
	// see if we've found a peak vertical velocity
	// we auto-deploy
	// move to next flight state
	if(velocity < FS1_MAX_VEL 
		&& abs(accZ - 9.8) < FS1_MAX_ACCEL  
		&& abs(accelHeight - altitude) < FS1_MAX_HEIGHT_DRIFT
		&& altitude > FS1_MIN_ALTITUDE)
	{
			flightState ++;
	}
}
void fs_2()
{
	// get altitude and vertical velocity
	// make sure our velocity is nominal
	// if altitude is just above 450m, trigger servo for deployment (time servo and deployment to see how long it takes for umbilical to disconnect?)
	//  Is there a way to verify that our umbilical is disconnected??
	
	// BONUS: turn on camera
	if(velocity > FS2_MIN_VEL 
		&& accZ > FS2_MAX_ACCEL 
		&& abs(accelHeight - altitude) < FS2_MAX_HEIGHT_DRIFT 
		&& altitude < FS2_MAX_ALTITUDE)
	{
			set_servo(100);
			flightState ++;
	}
}
void fs_3()
{
	// freely descend
	// get altitude and vertical velocity
	// check nominal velocity
	// if altitude is < 40m and velocity < 1 m/s -->> landed
	//   Turn buzzer on
	//   stop transmitting
	if(abs(velocity) < FS3_MAX_VEL 
		&& abs(accZ) < FS3_MAX_ACCEL
		&& abs(accelHeight - altitude) < FS3_MAX_HEIGHT_DRIFT
		&& altitude > FS3_MAX_ALTITUDE)
	{
			buzz_on();
			blockTransmission = true;
	}
}







int main (void)
{
	blockTransmission = false;
	board_init();
	
	/**
	
	
	//TODO: HANDLE RESETS
	
	
	**/
	
	sysclk_init();
	rtc_init();
	
	
	//missionTime = rtc_get_time();
	
	if(DEBUG && DEBUG_TELEM) printf("%u", missionTime >> 16);
	
	if(DEBUG && 0)
	{
		wdt_set_timeout_period(WDT_TIMEOUT_PERIOD_2KCLK);
		wdt_enable();
	}
	

	
	uart_terminal_init();
	//newOLogInit();

	if(DEBUG) printf("uart is working\n");
	

	
	//pmic_init();
	//pmic_set_scheduling(PMIC_SCH_ROUND_ROBIN);
	//cpu_irq_enable();
	
	//gps_init();	
	//imu_init();
	//delay_s(1);
	//xbee_init();
	//servo_init();
	//thermistor_init();
	//volt_init();
	spi_init_module();

	//uint8_t servoPos = 0;
	//set_servo(0);
	
	//buzz_on();
	//delay_ms(5);
	//buzz_off();
	//delay_ms(5);
	//buzz_on();
	//delay_ms(5);
	//buzz_off();
	
	/**
		MAIN PROGRAM LOOP	
	**/
	while (true)
	{
		
		//imu_update();
		
		
		/***
		Get Telemetry - Part of every flight state
		***/
		//missionTime = rtc_get_time();
		pressure = getPressure();
		printf("%f\n", pressure);
		/*temp = getTemperature();
		altitude = pressure / 9000; // TODO: finish function
		voltage = getVoltage();
		velocity = imu_vel_z();
		accelHeight = imu_pos_z();
		accZ = imu_accel_z();
		pitch = imu_pitch();
		roll = imu_roll();
		heading = imu_heading();
		
		switch(flightState)
		{
			case 0:
				fs_0();
				break;
			case 1:
				fs_1();
				break;
			case 2:
				fs_2();
				break;
		    case 3:
				fs_3();
				break;
			default: 
				break;
			
		};*/
		
			
		delay_ms(50);		
	}
}


