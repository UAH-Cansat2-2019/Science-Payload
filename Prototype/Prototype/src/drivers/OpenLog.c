/*
 * OpenLog.c
 *
 * Created: 5/7/2019 10:41:57 AM
 *  Author: natha
 */ 
#include <asf.h>
#include "uart.h"
#include "config/conf_clock.h"
#include "OpenLog.h"

static uart_device openLog;


void newOLogInit()//initializes the openLog uart communication interface
{
	//sets parameters of uart communication
	openLog.Baud=OPENLOG_BAUD;
    openLog.Port=P_OPENLOG_PORT;
	openLog.Usart=P_OPENLOG_UART;
	openLog.tx=OPENLOG_TX_PIN;
	openLog.rx=OPENLOG_RX_PIN;
	 uart_init(&openLog);//function that initializes uart
}
void openLogWrite(char * data)
{
	UARTWriteArray(openLog,data);
}
//maximum read length 99 chars
void openLogRead(char * data,char * fname)
{
	openLogWrite("262626");//switch to command mode
	char mode='\0';
	while(mode!='>')
		UARTReadArray(openLog,&mode);//wait for mode to switch
	
	
	char length[2];
	itoa(sizeof(data),length,10);//creates a string holding the length of the read
	
	openLogWrite("read ");//sends read command
	openLogWrite(fname);//sends the name of the file
	openLogWrite(" 0 ");//sends start point of read
	openLogWrite(length);//sends endpoint of read
	openLogWrite(" 1\r"); //sets output to ascii and carrage return to end command
	UARTReadArray(openLog,data);//reads data sent back
}