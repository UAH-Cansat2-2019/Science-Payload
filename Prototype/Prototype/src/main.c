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
/************** I2C buffer length******/

#define	I2C_BUFFER_LEN 8
#define I2C0 5



int main (void)
{
	//board_init();

	/* Insert application code here, after the board has been initialized. */

	/* This skeleton code simply sets the LED to the state of the button. */
	
	//struct bno055_t myBNO;
	
	sysclk_init();
	board_init();
	uart_device openLog;
	openlog_init(&openLog);
	uart_init(&openLog);
	uart_terminal_init();
	printf("uart is working\n");
	//I2CInit(BN0_BAUD_HZ,BN0_ADDR);
	//BNO055_Config();
	p_bstru nums;
	u16BuffInit(&nums);
	uint8_t i=0;
	while (1) {
		
		i++;
		putu16(nums,i);
		printf("\n\nThe array is: ");
		for(uint8_t j=0;j<10;j++)
		{
			printf(" %i", getu16(nums,j));
		}
		delay_s(2);
		//int16_t acceleration [3];
		//int16_t mag [3];
		//int16_t gyro [3];
		
		//get_acceleration(acceleration);
		//get_mag(mag);
		//get_gyro(gyro);
		//printf("\nAccelerometer is %i, \t %i, \t %i \n",acceleration[0], acceleration[1], acceleration[2]);
		//printf("Magnetometer is %i, \t %i, \t %i \n",mag[0],mag[1],mag[2] );
		//printf("Gyroscope is %i, \t %i, \t %i \n\n",gyro[0],gyro[1],gyro[2] );

	}
}
