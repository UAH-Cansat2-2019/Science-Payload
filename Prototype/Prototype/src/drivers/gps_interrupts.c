/*
 * gps_interrupts.c
 *
 * Created: 6/14/2019 1:51:12 AM
 *  Author: quaz9
 */ 
#include <string.h>
#include "gps.h"
#include "gps_interrupts.h"

void init_gps_interrupts(void)
{
	/*	This function will be called once to set up the XBee port for sending/receiving interrupts
		It should not enable interrupts globally, just for receiving and sending on this one port
	*/
//	printf("y u no work");
	GPS_USART.CTRLA = 0b00010100; //RXint low-level, TXint low-level, DREint off;
	gpgga_index = 0;
	uint8_t dollar_counter = 0;
	uint8_t current_sentence = SENTENCE_NONE;
	last_finished = SENTENCE_NONE;
	
}

void init_gps_buffers(void)
/* Don't use the buffers before calling this. Please. It's kind of important. */
{
	rbu8_init(&gps_receive_buffer, RAW_gps_receive_buffer, GPS_RECEIVE_BUFFER_SIZE);
	rbu8_init(&gps_send_buffer, RAW_gps_send_buffer, GPS_TRANSMIT_BUFFER_SIZE);
}

ISR (GPS_RECEIVE_INTERRUPT_VECTOR)
{
	/*	This code will run whenever a character comes in on GPS_PORT (PORTC)
	
		It can access global variables, but only if they're declared with the "volatile" keyword
		It should not have any code that waits for anything. Examples include
			* printf
			* while (!(SPIC.STATUS >> 7));
		Essentially, it needs to run fast. This can be called as many as 25,000 times per second, and the cansat has other stuff to do
	*/
	uint8_t ch = GPS_USART.DATA;
	
	//printf("%c\n",ch);
	//printf("%c""\0", (char)ch);
	//putchar(c);
	//putchar(c);
	if (current_sentence == SENTENCE_GPGGA)
	{
		if (ch == '\n')
		{
			
			rbu8_write(gpgga_buff, &gps_receive_buffer, gpgga_index);
			last_finished = current_sentence;
			gpgga_index=0;
			current_sentence = SENTENCE_WAIT;
			dollar_counter = 0;
		}
		
		gpgga_buff[gpgga_index] = ch;
		gpgga_index++;
		//printf("GPGGA %i = %i\n", gpgga_index, gpgga_buff[gpgga_index]);
		
	

	}
	else if (ch == '$' && current_sentence == SENTENCE_NONE)
	{
		dollar_counter = 1;
	}
	
	if (dollar_counter > 0 && current_sentence == SENTENCE_NONE)
	{
		if (dollar_counter == 5 && ch == 'G' )
		{
			current_sentence= SENTENCE_GPGGA;
			memcpy(gpgga_buff, "$GPGG", 5);
			gpgga_index = 5;
			dollar_counter++;
		}
		else
		{
			dollar_counter++;
		}
	}
	//printf("Interrupt Executed.\n");
	//rbu8_write(&gps_receive_buffer, &(GPS_USART.DATA), 1);
}

ISR (GPS_SEND_INTERRUPT_VECTOR)
{
	/*	This code will run whenever XBEE_PORT (PORTC) is ready to send more data
		This interrupt should also check the status of the CTS (Clear-To-Send) line on the XBee, because otherwise it might overload the XBee with data.
		
		It can access global variables, but only if they're declared with the "volatile" keyword
		It should not have any code that waits for anything. Examples include
			* printf
			* while (!(SPIC.STATUS >> 7));
		Essentially, it needs to run fast. This can be called as many as 25,000 times per second, and the cansat has other stuff to do
	*/
	
  rbu8_read(&gps_send_buffer, &(GPS_USART.DATA), 1);
  rbu8_delete_oldest(&gps_send_buffer, 1);
}