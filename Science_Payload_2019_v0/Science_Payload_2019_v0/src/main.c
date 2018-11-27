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
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
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

/* Include all that stuff */
#include <asf.h>
#include <time.h>

// Systems Data
public uint8_t flight_state;
pulbic uint16_t packet_count;
public long mission_time;


// GPS Data
public long gps_time;
public long gps_lat;
public long gps_long;
public long gps_alt;
public uint8_t gps_sats;

// Sensor Data
public float pressure;
public float board_temp;
public float external_temp;
public float voltage;

public float roll;
public float pitch;
public float bonus_direction;
public float spin_rate;



int main (void)
{
	sysclk_init(); //initialize system clock
				//TODO: make sure the system clock is set to the correct frequency
				//TODO: make sure libraries are properly configured
				
	//INIT Timer Counter Bois		
	sysclk_enable_peripheral_clock(&TCC0); //TODO: CHECK REGISTER
	sysclk_enable_peripheral_clock(&TCD0); //TODO: CHECK REGISTER
	
	
	sysclk_enable_module(SYSCLK_PORT_F, SYSCLK_HIRES); //TODO: CHECK PORT
	sysclk_enable_module(SYSCLK_PORT_D, SYSCLK_HIRES); //TODO: CHECK PORT
	sysclk_enable_module(SYSCLK_PORT_C, PR_SPI_bm);	 //TODO: CHECK PORT
	
	//TODO: Initialize External RTC (in case of failure)
	
	//Init USART ports
	
	sysclk_enable_peripheral_clock(&USARTC0);  //EG port - MIGHT NEED TO CHANGE
		//Initialize USART Devices
		
		
	//Init SPI ports
	sysclk_enable_peripheral_clock(&SPIC); //EG Port - MIGHT NEED TO CHANGE
		//Initialize SPI Devices
	
	//Init ADC Ports
	sysclk_enable_peripheral_clock(%ADCA); //EG Port - MIGHT NEED TO CHANGE
		//Initialize ADC Devices
		
	
	/* Reset Protocols */
	
		// Read MCU status Register to determine reason for reset
		
		// If reset was unintentional

			// read time from external RTC
			
			// Load previous data packet from Open Log
			
			
			// Recalibrate Pressure From EEProm
			// Recalibrate Temperature from EEProm
			// Recalibrate Altitude from EEProm and Previous packet
				//Use the disconnect time and previous velocit(ies?) to find altitude
				//smoothing?
			// Recalibrate Roll from EEprom
			// Recalibrate Pitch from EEProm
			// Recalibrate Bonus Direction from EEProm
			// Recalibrate Spin-Rate from EEprom?
			
			
			
			// Recallibrate GPS from EEprom? (or just pretend to.. we need to test
				//and figure out if the GPS will lose its sync easily. If it does, we
				//should figure out how to spoof the data if it's lost)
			
			
		
		// Else
			// Clear EEProm (or just ignore it)
			
			// Initialize all variables not initialized
			
			
	while(1)		// Main Program Loop
	{
		/*Flight State 0 - Ground and Ascent*/
			// Measure and Record All Telemetry
			// Transmit Limited Telemetry until Ascent?
			
			// If velocity < 0 for long time
				// Increment flight state
			
		/*Flight State 1 - Contained Descent*/
			// Meaure, Transmit, and record all telemetry
			
			// If Altitude <= 450 m, and (smoothed) Velocity < 0
				// Increment flight state
			
		/*Flight State 2 - Free Descent*/
			// Measure, Transmit, and Record All Telemetry, Maintain Orientation
			
			
			// If velocity < 5 m/s for long time
				// Increment Flight State
			
		/*Flight State 3 - Landing*/
			// Activate Buzzer, and Stop Transmitting
		
			// Buzz Forever my sweetie
		
	}		
	
	
	
}
