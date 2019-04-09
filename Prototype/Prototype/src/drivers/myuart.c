/*
 * CFile1.c
 *
 * Created: 4/6/2019 7:51:49 PM
 *  Author: Nathan
 */ 

#include <asf.h>
#include "myuart.h"
#include "config/conf_clock.h"

void uart_init(uart_device* P_device)
{
	//sets output to high on Tx pin and sets the direction of rx and tx
	P_device->Port->DIRSET=P_device->Txpin;
	P_device->Port->DIRCLR=P_device->Rxpin;
	P_device->Port->OUTSET=P_device->Txpin;
	
	//enables peripheral clock
	sysclk_enable_peripheral_clock(P_device->Usart);
	sysclk_enable_module()
	
	uint32_t bpsbaud=P_device->Baud;
	//finds value of bsel bassed on 0 for bscale
	uint32_t bsel=CONFIG_SYSCLK_SOURCE/(16*bpsbaud)-1;
	uint8_t bscal=0;//sets the scaler to zero note that fbaud=fper/((bsel+1)16x2^bscale) when bsel is greater than or equal to zero and 
					//fbaud=fper/(16(bsel+2^bscale+1)) when bscale is less than zero
	//Bool bscalIsNegitive=0;
	
	//determines value of bascal by looping through values until valid value for bsel is attained
	//while (bsel>4095)
	//{
		//bscal++;
		//bsel=CONFIG_SYSCLK_SOURCE/((16*bpsbaud)<<bscal)-1;
		//if(bsel==7)
			//break;
	//}
	////does the same as above for negative values of bscal
	//while(bsel<20)
	//{
		//bscal++;
		//bscalIsNegitive=1;
		//bsel=(((uint32_t)CONFIG_SYSCLK_SOURCE)<<bscal)/((16*bpsbaud))-1<<bscal;
		//if(bscal==7)
			//break;
	//}
	////if bscal is negitive takes twos complement
	//if(bscalIsNegitive)
		//bscal=(~bscal)+1;
		
	P_device->Usart->BAUDCTRLB=bscal<<4+bsel>>8;
	P_device->Usart->BAUDCTRLA=(uint8_t)bsel;
	P_device->Usart->CTRLA=0b00111111;//allows any interupts neccisary
	P_device->Usart->CTRLB=0b00011000;//enables transmitter and reciever, turns off double clock speed, turns off multiprocessor communication mode, and sets Transmition bit 8 to 0
	P_device->Usart->CTRLC=0b00000011;//asynchronos mode, parity disabled, only 1 stop bit and char size is 7 bits
	
	
	
	
	
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