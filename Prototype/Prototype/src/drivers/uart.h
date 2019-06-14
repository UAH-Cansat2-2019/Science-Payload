/*
 * myuart.h
 *I didn't understand the uart api you got so i'm going to try to make my own.
 *My plan is to make a struct to hold all of the ports, pins and baudrate for each device and 
 *make an init function that assigns this information to the struct and all the read and write functions will take this struct as an input
 * Created: 4/6/2019 7:52:34 PM
 *  Author: Nathan
 */ 


#ifndef UART_H_


#include "definitions.h"


//defines a struct to hold all the information about each uart device
typedef struct uart_device{
	PORT_t * Port;
	USART_t * Usart;
	uint8_t rx;
	uint8_t tx;
	uint32_t Baud;
	} uart_device;
	
void openlog_init(uart_device * openLog);
void uart_init(uart_device* P_device);
uint8_t uart_read(uart_device * device);
void uart_write(uart_device * device,uint8_t data);
void UARTWriteArray(uart_device device, char * data);
void UARTReadArray(uart_device device,char * data);

#define UART_TERMINAL_SERIAL			&USARTE0
#define UART_TERMINAL_SERIAL_BAUDRATE	115200
#define UART_TERMINAL_SERIAL_CHAR_LEN	USART_CHSIZE_8BIT_gc
#define UART_TERMINAL_SERIAL_PARITY		USART_PMODE_DISABLED_gc
#define UART_TERMINAL_SERIAL_STOP_BIT	true



#define UART_TERMINAL_TX_PIN			PIN3_bm
#define UART_TERMINAL_PORT				PORTE

void uart_terminal_init(void);
#define UART_H_





#endif /* MYUART_H_ */