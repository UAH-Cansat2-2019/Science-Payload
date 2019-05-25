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
#include "drivers/mybno055.h"
#include "drivers/I2CDriver.h"
#include "RingBuff.h"
#include <string.h>
#include "drivers/gps.h"
#include <util/atomic.h>
/************** I2C buffer length******/

#define	I2C_BUFFER_LEN 8
#define I2C0 5

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

int main (void)
{
	//board_init();

	/* Insert application code here, after the board has been initialized. */

	/* This skeleton code simply sets the LED to the state of the button. */
	
	//struct bno055_t myBNO;
	
	sysclk_init();
	board_init();
	uart_device openLog;
	uart_device xbee;
	uart_device gps;
	openlog_init(&openLog);
	xbee_init(&xbee);
	gps_init(&gps);
	uart_init(&openLog);
	uart_init(&xbee);
	uart_init(&gps);
	uart_terminal_init();
	printf("uart is working\n");
	I2CInit(115200,BN0_ADDR);
	BNO055_Config();
	p_bstru nums;
	u16BuffInit(&nums);
	uint8_t i=0;
	//uint8_t cal = isBnoCalib();
	GPS_data_t gps_data;
	uint8_t got_good_time = 0;
	int32_t gps_local_delta;
	
	uint8_t gpstmp[85];
	
	uint32_t GPSTime;
	uint32_t GPSLat;
	uint32_t GPSLong;
	uint32_t GPSAlt;
	uint32_t GPSSats;
	uint32_t time_ms;
	init_GPS_pins_and_usart();
	init_gps_interrupts();
	init_gps_buffers();
	
	pmic_init();
	pmic_set_scheduling(PMIC_SCH_FIXED_PRIORITY);
	cpu_irq_enable();
	
	while (1) {
		usart_serial_write_packet(&USARTF0,"hello",strlen("hello"));
		i++;
		putu16(nums,i);
		printf(&USARTC1,"\n\nThe array is: ",strlen("\n\nThe array is: "));
		for(uint8_t j=0;j<10;j++)
		{
			printf(" %i", getu16(nums,j));
		}
		printf("\n");
		printf("Who am I: %d", WhoAmIBNO());
		
		
		if (last_finished != SENTENCE_NONE)
		{
			if (last_finished == SENTENCE_GPGGA)
			{
				ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
				{
					memcpy(gpstmp, gpgga_buff, 85);
				}
				gpstmp[packetlen(gpstmp)] = '\0';

				GPS_data_t gps_data = getGPSDatafromNMEA(gpstmp, strlen(gpstmp));
				GPSAlt =	gps_data.altitude;
				GPSLat =	gps_data.latdecimal;
				GPSLong=	gps_data.londecimal;
				
				last_finished = SENTENCE_NONE;
				
				if (gps_data.fix_status)
				{
					uint32_t GPS_secs = 3600 * (uint32_t)gps_data.hour + 60 * (uint32_t)gps_data.minutes + (uint32_t)gps_data.seconds;
					uint32_t safetime;
					ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
					{
						safetime = time_ms;
					}
					gps_local_delta = GPS_secs - safetime;
					got_good_time = 1;
				}
				
			}
		}
		
		
		
		int16_t acceleration [3];
		int16_t mag [3];
		int16_t gyro [3];
		
		//if(isBnoCalib() > 33){
		//get_acceleration(acceleration);
		//get_mag(mag);
		//get_gyro(gyro);
		//}
		printf("Altitude: %d", GPSAlt);
		printf("\nAccelerometer is %i, \t %i, \t %i \n",acceleration[0], acceleration[1], acceleration[2]);
		printf("Magnetometer is %i, \t %i, \t %i \n",mag[0],mag[1],mag[2] );
		printf("Gyroscope is %i, \t %i, \t %i \n\n",gyro[0],gyro[1],gyro[2] );
		delay_ms(500);

	}
}
