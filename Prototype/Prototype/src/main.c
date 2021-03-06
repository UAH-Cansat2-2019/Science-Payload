/**
 * \file
 *
 * \brief Empty user application template
 *
 */


#include <asf.h>
#include "drivers/definitions.h"

#include "drivers/gps.h"
#include "drivers/gps_interrupts.h"
#include "drivers/adc_sensors.h"

#include "drivers/IMU.h"
#include "drivers/mechanisms.h"
#include "drivers/ms5607.h"
#include "drivers/OpenLog.h"
#include "drivers/uart.h"
#include "drivers/Xbee.h"
#include "drivers/Hall_sensor.h"
/*#include "flight_states.h"*/
/************** I2C buffer length******/
volatile extern uint8_t XbeeRx;

uint16_t packetlen(const uint8_t* buff);
uint16_t packetlen(const uint8_t* buff)
{
	uint16_t i = 0;
	for (i = 0; i < 1024; i++)
	{
		if (buff[i] == '\n')
		return i;
	}
	return 1024;
}

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
			servo_init();
			//set_servo(100);
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
	
	

	
	
	if(DEBUG && 0)
	{
		wdt_set_timeout_period(WDT_TIMEOUT_PERIOD_2KCLK);
		wdt_enable();
	}
	

	
	uart_terminal_init();
	newOLogInit();

	if(DEBUG) printf("uart is working\n");
	
	
	spi_init_module();
	
	

	
	pmic_init();
	pmic_set_scheduling(PMIC_SCH_ROUND_ROBIN);
	irq_initialize_vectors();
	cpu_irq_enable();
	
	init_GPS_pins_and_usart();
	init_gps_interrupts();
	init_gps_buffers();	
	//imu_init();
	//delay_s(1);
	xbee_init();
	

	thermistor_init();
	volt_init();

	uint8_t servoPos = 0;
	//set_servo(0);
	
	buzz_on();
	delay_ms(1000);
	buzz_off();
	//delay_ms(5);
	//buzz_on();
	//delay_ms(5);
	//asm("nop");
	//buzz_off();
	
	/**
		MAIN PROGRAM LOOP	
	**/
	//xbeeWrite("hello There!");
	hall_init();
	while (true)
	{
		
		
		printf("\ngood morning realterm");
		while(1)
		{
			printf("hall reading %u \n",hallVoltRead());
			delay_ms(500);
		}
		//xbeeWrite("hello There! xbee");
		imu_update();
		
		
		/***
		Get Telemetry - Part of every flight state
		***/
		missionTime = ((float)rtc_get_time())/10.0;
		pressure = getPressure();
		printf("%f\n", pressure);
		//printf("is it me?");
		char alt[10];
		char lat[10];
		char longi[10];
		char numSat[10];
		char gpstime[10];
		
		if (last_finished != SENTENCE_NONE)
		{
			rbu8_read(&gps_receive_buffer,gpstmp,85);
			altitude_from_gpgga(gps_receive_buffer.buffer,alt);
			latitude_from_gpgga(gps_receive_buffer.buffer,lat);
			longitude_from_gpgga(gps_receive_buffer.buffer,longi);
			num_sat_from_gpgga(gps_receive_buffer.buffer,numSat);
			time_from_gpgga(gps_receive_buffer.buffer,gpstime);
			current_sentence=SENTENCE_NONE;
				printf("%s\n",gps_receive_buffer.buffer);
				delay_s(1);
				printf("alt=%s, lat=%s longi=%s, numsat=%s, gpstime=%s \n",alt,lat,longi,numSat,gpstime);
				
			
		}
	
		
		//printf("Sats: %u\n",GPSSats);
		////printf("Lat: %u\n",GPSLat);
		////printf("Long: %u\n",GPSLong);
		temp = getTemperature();
		printf("%f\n", temp);
		altitude = pressure ; // TODO: finish function
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
			
		};
		
			
		delay_ms(50);		
	}
}


