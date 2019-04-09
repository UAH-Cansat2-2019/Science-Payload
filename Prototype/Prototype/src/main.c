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
#include "drivers/bno055.h"
#include "drivers/myuart.h"


/************** I2C buffer length******/

#define	I2C_BUFFER_LEN 8
#define I2C0 5

#define	BNO055_I2C_BUS_WRITE_ARRAY_INDEX	((u8)1)


s8 BNO055_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 BNO055_iERROR = BNO055_INIT_VALUE;
	u8 array[I2C_BUFFER_LEN];
	u8 stringpos = BNO055_INIT_VALUE;

	array[BNO055_INIT_VALUE] = reg_addr;
	for (stringpos = BNO055_INIT_VALUE; stringpos < cnt; stringpos++){
		array[stringpos + BNO055_I2C_BUS_WRITE_ARRAY_INDEX] =
			*(reg_data + stringpos);
	}

	return (s8)BNO055_iERROR;
}


s8 BNO055_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 BNO055_iERROR = BNO055_INIT_VALUE;
	u8 array[I2C_BUFFER_LEN] = {BNO055_INIT_VALUE};
	u8 stringpos = BNO055_INIT_VALUE;

	array[BNO055_INIT_VALUE] = reg_addr;

	
	for (stringpos = BNO055_INIT_VALUE; stringpos < cnt; stringpos++)
		*(reg_data + stringpos) = array[stringpos];
	return (s8)BNO055_iERROR;
}
/*	Brief : The delay routine
 *	\param : delay in ms
*/
void BNO055_delay_msek(u32 msek)
{
	/*Here you can write your own delay routine*/
}


int main (void)
{
	//board_init();

	/* Insert application code here, after the board has been initialized. */

	/* This skeleton code simply sets the LED to the state of the button. */
	
	//struct bno055_t myBNO;
	
	//myBNO.bus_read = BNO055_I2C_bus_read;
	//myBNO.bus_write = BNO055_I2C_bus_write;
	//myBNO.delay_msec = BNO055_delay_msek;
	//myBNO.dev_addr = BNO055_I2C_ADDR1;	
	//bno055_init(&myBNO);
	//bno055_set_operation_mode(BNO055_OPERATION_MODE_NDOF);//NDOF
	//
	//struct bno055_euler_float_t eulerData;
	//bno055_convert_float_euler_hpr_deg(&eulerData);
	
	sysclk_init();
	uart_device openLog;
	openLog.Baud=9600;
	openLog.Port=&PORTC;
	openLog.Usart=&USARTC0;
	openLog.tx=0b00001000;
	openLog.rx=0b00000100;
	
	uart_init(&openLog);
	while (1) {
		const uint8_t* str = "It's treason, then.\n";
		usart_serial_write_packet(openLog->Usart, str,sizeof(str));
		delay_s(5);
		/* Is button pressed? */
		//if (ioport_get_pin_level(BUTTON_0_PIN) != BUTTON_0_ACTIVE) {
			///* Yes, so turn LED on. */
			//ioport_set_pin_level(LED_0_PIN, LED_0_ACTIVE);
		//} else {
			///* No, so turn LED off. */
			//ioport_set_pin_level(LED_0_PIN, !LED_0_ACTIVE);
		//}
	}
}
