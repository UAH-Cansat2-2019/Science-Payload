/*
 * Xbee.h
 *
 * Created: 5/29/2019 5:29:13 PM
 *  Author: natha
 */ 


#ifndef XBEE_H_
#define XBEE_H_

#include "definitions.h"

#define P_XBEEUART (&USARTD0)
#define P_XBEEPORT (&PORTD)
#define XBEETXPIN 0b00001000
#define XBEERXPIN 0b00000100
#define XBEEBAUD 115200

#define XBEE_UART USARTD0
#define READ_INTURUPT USARTD1_RXC_vect
#include <string.h>
volatile uint8_t XbeeRx;

void xbee_init(void);
void xbeeWrite(uint8_t* data);

#endif /* XBEE_H_ */