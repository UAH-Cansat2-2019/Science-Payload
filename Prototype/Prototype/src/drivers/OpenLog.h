/*
 * OpenLog.h
 *
 * Created: 5/7/2019 10:42:45 AM
 *  Author: natha
 */ 


#ifndef OPENLOG_H_
#define OPENLOG_H_

#define OPENLOG_BAUD 115200
#define P_OPENLOG_PORT (&PORTC)
#define P_OPENLOG_UART (&USARTC0)
#define OPENLOG_TX_PIN (0b00001000)
#define  OPENLOG_RX_PIN (0b00000100)


void openLogWrite(char * data);
void newOLogInit(void);
void openLogRead(char * data,char * fname);
#endif /* OPENLOG_H_ */