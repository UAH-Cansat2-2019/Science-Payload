/*
 * myuart.h
 *I didn't understand the uart api you got so i'm going to try to make my own.
 *My plan is to make a struct to hold all of the ports, pins and baudrate for each device and 
 *make an init function that assigns this information to the struct and all the read and write functions will take this struct as an input
 * Created: 4/6/2019 7:52:34 PM
 *  Author: Nathan
 */ 


#ifndef UART_H_



//defines a struct to hold all the information about each uart device
typedef struct uart_device{
	PORT_t * Port;
	USART_t * Usart;
	uint8_t rx;
	uint8_t tx;
	uint32_t Baud;
	
	} uart_device;
void uart_init(uart_device* P_device);
uint8_t uart_read(uart_device * device);
void uart_write(uart_device * device,uint8_t data);
#define UART_H_





#endif /* MYUART_H_ */