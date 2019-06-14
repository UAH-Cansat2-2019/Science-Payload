/*
 * Xbee.h
 *
 * Created: 5/29/2019 5:29:13 PM
 *  Author: natha
 */ 


#ifndef XBEE_H_
#define XBEE_H_

#include "definitions.h"
#include <string.h>
#include "uart.h"
#define P_XBEEUART (&USARTC0)
#define P_XBEEPORT (&PORTC)
#define XBEETXPIN 0b00001000
#define XBEERXPIN 0b00000100
#define XBEEBAUD 115200

#define XBEE_UART USARTC0
#define READ_INTURUPT USARTC0_RXC_vect


#define XBEE_TC TCC0
#define XBEE_WRITE_INTERVAL 31249

volatile uint8_t XbeeRx;

void xbee_init(void);
void xbeeWrite(uint8_t* data);
void write_telem_to_xbee();

#endif /* XBEE_H_ */