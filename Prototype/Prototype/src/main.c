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
/************** I2C buffer length******/
volatile extern uint8_t XbeeRx;

int main (void)
{
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
	
	I2CInit(115200,0x29);
	xbee_init();
	
	
	
	uint8_t data;
	int16_t acel[]={0,0,0};
	int16_t acelx;
		data=BNO055_OPERATION_MODE_CONFIG;
		BNO_Write (&data, BNO055_OPR_MODE_ADDR);
		delay_ms(22);
		
		data=BNO055_OPERATION_MODE_NDOF;
		BNO_Write (&data,BNO055_OPR_MODE_ADDR);
		delay_ms(8);
	while (1) 
	{
		
		BNO_Read(&data,BNO055_SELFTEST_RESULT_ADDR);
		
		printf("st_result = %i\n",data);
		
		BNO_Read(&data,BNO055_OPR_MODE_ADDR);
		
		printf("opr mode = %i\n",data);
		
		BNO_Read(&data,BNO055_CALIB_STAT_ADDR);
		printf("Calibstat %i\n",data);
		
		//get_acceleration(acel);
		//printf("acceleration is x = %i",acel[0]);
		//printf(", y=%i",acel[1]);
		//printf(", z=%i\n",acel[2]);
		
		
		printf("acelx %i\n",get_acceleration_x());
		delay_ms(500);
		

	}
}
