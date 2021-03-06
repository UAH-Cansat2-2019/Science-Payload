/*
 * Xbee.c
 *
 * Created: 5/29/2019 5:28:29 PM
 *  Author: natha
 */ 

#include <asf.h>
#include "uart.h"
#include "Xbee.h"
static uart_device xbee_uart;
volatile extern uint8_t XbeeRx;

void xbee_init()
{
	xbee_uart.Baud=XBEEBAUD;
	xbee_uart.Port=P_XBEEPORT;
	xbee_uart.Usart=P_XBEEUART;
	xbee_uart.tx=XBEETXPIN;
	xbee_uart.rx=XBEERXPIN;
	uart_init(&xbee_uart);
	XBEE_UART.CTRLA=0x14;
	if(DEBUG) printf("Xbee Initialized.\n");
}

void xbeeWrite(uint8_t* data)
{	
	usart_serial_write_packet(P_XBEEUART, data, strlen(data));
	if(DEBUG) printf("%s \n",(const)data);
}

ISR(READ_INTURUPT)
{
	XbeeRx=XBEE_UART.DATA;
}