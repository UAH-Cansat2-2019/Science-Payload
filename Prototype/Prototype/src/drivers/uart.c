/*
 * CFile1.c
 *
 * Created: 4/6/2019 7:51:49 PM
 *  Author: Nathan
 */ 

#include <asf.h>
#include "uart.h"
#include "config/conf_clock.h"

void uart_init(uart_device* P_device)

{
	//initializes struct containing all the options for uart communication
	static usart_serial_options_t usart_options = {
		.baudrate = 0,
		.charlength = USART_CHSIZE_8BIT_gc,
		.paritytype = USART_PMODE_DISABLED_gc,
		.stopbits = true
	};
	usart_options.baudrate=P_device->Baud;//sets the baud rate to baud rate passed in with the struct
	

	//sets the direction of Tx to out and sets it to high. sets the direction of Rx to input
	P_device->Port->DIR|=P_device->tx;
	P_device->Port->OUT|=P_device->tx;
	P_device->Port->DIR&=~P_device->rx;
	
	sysclk_enable_peripheral_clock(P_device->Usart);//enables peripheral clock for uart
	
	usart_serial_init(P_device->Usart, &usart_options);//asf function for initializing uart with the options from the struct we defined
	
	
	
}


uint8_t uart_read(uart_device * device)
{
	
	while(device->Usart->STATUS>>7);//wait for data to be read
	return device->Usart->DATA;
	
}
void uart_write(uart_device * device,uint8_t data)
{
	while(!(device->Usart->STATUS&0b00100000));//wait for transmition buffer to clear
	device->Usart->DATA=data;
	while((device->Usart->STATUS&0b01000000));//wait for data to be sent
}
