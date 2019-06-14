///*
 //* gps.c
 //*
 //* Created: 5/25/2019 4:49:36 PM
 //*  Author: quaz9
 //*/ 
//
#include <asf.h>
#include "drivers/gps.h"
#include "drivers/uart.h"
#include <string.h>
static uart_device gps_uart;
uint8_t is_gps_rx_triggered;
uint8_t rxdata;
char rxDataBuff[80];
uint8_t sentencePosition=0;

#define LONGITUDE_SIZE 22
char longitude[LONGITUDE_SIZE];

#define LATITUDE_SIZE 22
char latitude[LATITUDE_SIZE];

#define TIMESTR_SIZE 12
char time[TIMESTR_SIZE];

#define NUMSAT_SIZE 3
char num_sat[NUMSAT_SIZE];

#define ALTATUDE_SIZE 10
char altatude[ALTATUDE_SIZE];
//
//#include <string.h>
//#include "drivers/GPS.h"
////#include "config/ports.h"
//#include <string.h>
//#include "drivers/GPS.h"
//
////#include "config/ports.h"
////#include "drivers/uart_tools.h"
//#include "RingBuffer.h"
////#include "CommandParse.h"
////#include "tools/satellite_vectors.h"
//
//
//void init_GPS_pins_and_usart(void)
//{
	//GPS_PORT.DIR |= 0b10000000;
	//GPS_PORT.DIR &= 0b10111111;
	//ioport_set_pin_high(GPS_SEND_PIN);
	//
	////Config pins
	////PORTA.DIR |= 0b00001100;
	//// 	if (mode == GPS_MODE_NMEA)
	//// 	{
	//// 		ioport_set_pin_high(GPS_CONFIG_PIN_8);
	//// 		ioport_set_pin_high(GPS_CONFIG_PIN_16);
	//// 	}
	//// 	else //Assume UBX
	//// 	{
	//// 		ioport_set_pin_low(GPS_CONFIG_PIN_8);
	//// 		ioport_set_pin_low(GPS_CONFIG_PIN_16);
	//// 	}
	//
	//
	////Configure USART
	//sysclk_enable_peripheral_clock(&GPS_USART);
	//
	//static usart_serial_options_t options = {
		//.baudrate = 4800,
		//.charlength = USART_CHSIZE_8BIT_gc,
		//.paritytype = USART_PMODE_DISABLED_gc,
		//.stopbits = 1
	//};
	//
	//usart_serial_init(&GPS_USART, &options);
//}
//
//uint8_t startswith(uint8_t* data, const char* beginning)
//{
	//uint8_t i = 0;
	//while (1)
	//{
		//if (beginning[i] == '\0')
		//return 1;
		//if (beginning[i] != data[i])
		//return 0;
		//i++;
	//}
	//return 1;
//}
//
//uint8_t find_the_beginning (uint8_t* some_array, uint8_t length)
//{
	//uint8_t i;
	//for ( i=0; i< (length); i++ )
	//{
		//if(some_array[i]=='$')
		//{
			//return i;
		//}
	//}
	//return i+1;
//}
//uint8_t find_the_end(uint8_t* some_array, uint8_t length)
//{
	//uint8_t b=1;
	//uint8_t i;
	//for ( i=0; i< (length); i++ )
	//{
		//if(some_array[i]=='\r' && some_array[i+1]=='\n')
		//{
			//return i;
		//}
	//}
	//return i+1;
//}
//
//GPS_data_t getGPSDatafromNMEA(uint8_t* NMEA_sentence, uint8_t sentencelength)
//{
	//int8_t countcommas=0;
	//GPS_data_t GPSData;
	//uint8_t first_comma_position=0;
	//uint8_t second_comma_position=0;
	//uint8_t third_comma_position=0;
	//uint8_t fourth_comma_position=0;
	//uint8_t fifth_comma_position=0;
	//uint8_t comma7=0;
	//uint8_t comma8=0;
	//uint8_t comma9=0;
	//uint8_t comma10=0;
	//uint8_t commab=0;
	//uint8_t commac=0;
	//uint8_t speedwritten=0;
	//uint8_t heightwritten=0;
	//uint8_t no_of_sateliiteswritten=0;
	//uint8_t comma_position=0;
	//int a=0;
	//if (startswith(NMEA_sentence, "$GPGGA"))
	//{
		////printf("Parsing GPGGA with len %u\n", sentencelength);
		//for (a=0;a<sentencelength; a++)
		//{
			////printf("hate6");
			//if (NMEA_sentence[a]==',')
			//{
				////printf("gfhghhf");
				//countcommas++;
				//if (countcommas == 1)
				//{
					////printf("Begin %u, end %u\n", NMEA_sentence[a + 1] - '0', NMEA_sentence[a + 2] - '0');
					//GPSData.hour = 10 * (NMEA_sentence[a + 1] - (uint8_t)'0') + (NMEA_sentence[a + 2] - (uint8_t)'0');
					//GPSData.minutes = 10 * (NMEA_sentence[a + 3] - '0') + NMEA_sentence[a + 4] - '0';
					//GPSData.seconds = 10 * (NMEA_sentence[a + 5] - '0') + NMEA_sentence[a + 6] - '0';
				//}
				//else if (countcommas == 2 && NMEA_sentence[a+1] != ',')
				//{
					//GPSData.latdegrees = 10*(NMEA_sentence[a+1] - '0') + (NMEA_sentence[a+2] - '0');
					////printf("%u\n",GPSData.latdegrees);
					//GPSData.latminutes = 100000l*(NMEA_sentence[a+3] - '0') + 10000l*(NMEA_sentence[a+4] - '0') + 1000l*(NMEA_sentence[a+6] - '0') + 100l*(NMEA_sentence[a+7] - '0') + 10l*(NMEA_sentence[a+8] - '0') + (NMEA_sentence[a+9] - '0');
					////printf("%lu\n",GPSData.latminutes);
//
					//GPSData.latdecimal = (NMEA_sentence[a+11] == 'N' ? 1.0 : -1.0) * ((double)GPSData.latdegrees + ((double)GPSData.latminutes/(60.0*10000.0)));
//
					////printf("%f\n",GPSData.latdecimal);
				//}
				//else if (countcommas == 2)
				//{
					//GPSData.latdecimal = 0.0;
				//}
				//else if (countcommas == 4 && NMEA_sentence[a+1] != ',')
				//{
					//GPSData.londegrees = 100*(NMEA_sentence[a+1] - '0') +10*(NMEA_sentence[a+2] - '0') + (NMEA_sentence[a+3] - '0');
					////printf("%u\n",GPSData.londegrees);
					//GPSData.lonminutes = 100000l*(NMEA_sentence[a+4] - '0')
					//+ 10000l*(NMEA_sentence[a+5] - '0')
					//+ 1000l*(NMEA_sentence[a+7] - '0')
					//+ 100l*(NMEA_sentence[a+8] - '0')
					//+ 10l*(NMEA_sentence[a+9] - '0')
					//+ (NMEA_sentence[a+10] - '0');
					////printf("%lu\n",GPSData.lonminutes);
					//GPSData.londecimal = (NMEA_sentence[a+12] == 'E' ? 1.0 : -1.0) * ((double)GPSData.londegrees + ((double)GPSData.lonminutes/(60.0*10000.0)));
					////printf("%f\n",GPSData.londecimal);
				//}
				//else if(countcommas == 4)
				//{
					//GPSData.londecimal = 0.0;
				//}
				//else if (countcommas == 6)
				//{
					//GPSData.fix_status = NMEA_sentence[a + 1] - '0';
				//}
				//else if (countcommas == 9)
				//{
					//uint8_t period_reached = 0;
					//uint8_t period_counter;
					//float altitude = 0;
					//uint8_t inc = 0;
					//while (NMEA_sentence[a + inc + 1] != ',')
					//{
						//if (NMEA_sentence[a + inc + 1] == '.')
						//{
							//period_reached = 1;
							//period_counter = 1;
						//}
						//else if (!period_reached)
						//{
							//altitude *= 10;
							//altitude += (float)(NMEA_sentence[a + inc + 1] - '0');
						//}
						//else if (period_reached && period_counter == 1)
						//{
							//altitude += ((float)(NMEA_sentence[a + inc + 1] - '0')) / 10.0;
							//break;
						//}
						//
						//inc++;
					//}
					//GPSData.altitude = altitude;
					////printf("Altitudes!\n");
				//}
			//}
			//
		//}
	//}
	//else
	//{
		////printf("hate2");
		////GPSData.latdegrees[0]='\0';
		////GPSData.latminutes[0]='\0';
		////GPSData.latdirection=' ';
		////GPSData.longdegrees[0]='\0';
		////GPSData.longminutes[0]='\0';
		////GPSData.longdirection=' ';
		////GPSData.noofsatellites[0]='\0';
		////GPSData.noofsatellites[0]='\0';
		////GPSData.speed[0]='\0';
	//}
	//
	////printf("NMEA sentence %s\n", NMEA_sentence);
	//
//
	////printf("hate6");
	//
	////printf("GPS lat degrees %s\n", GPSData.latdegrees);
	////printf("GPS lat minutes %s\n",GPSData.latminutes);
	////printf("GPS lat direction %c\n", GPSData.latdirection);
	///*printf("GPS long degrees %s\n", GPSData.longdegrees);
	//printf("GPS long minutes %s\n",GPSData.longminutes);
	//printf("GPS long direction %c \n", GPSData.longdirection);*/
	//
	//
	//
	//
	//
	//
	////printf("GPSDATA altitude test %s \n ", GPSData.altitude);
	////printf("GPS no of satellites test= %s \n", GPSData.noofsatellites);
	//return GPSData;
//
//
//}
//
//
//uint8_t findnext(uint8_t* searchstr, uint8_t target, uint8_t length)
//{
	//uint8_t i;
	//for (i = 0; i < length; i++)
	//{
		//if (searchstr[i] == target)
		//{
			//return i;
		//}
	//}
//}
//
//
//void init_gps_interrupts(void)
//{
	///*	This function will be called once to set up the XBee port for sending/receiving interrupts
		//It should not enable interrupts globally, just for receiving and sending on this one port
	//*/
////	printf("y u no work");
	//GPS_USART.CTRLA = 0b00010100; //RXint low-level, TXint low-level, DREint off;
	//gpgga_index = 0;
	//uint8_t dollar_counter = 0;
	//uint8_t current_sentence = SENTENCE_NONE;
	//last_finished = SENTENCE_NONE;
	//
//}
//
//void init_gps_buffers(void)
///* Don't use the buffers before calling this. Please. It's kind of important. */
//{
	//rbu8_init(&gps_receive_buffer, RAW_gps_receive_buffer, GPS_RECEIVE_BUFFER_SIZE);
	//rbu8_init(&gps_send_buffer, RAW_gps_send_buffer, GPS_TRANSMIT_BUFFER_SIZE);
//}
//
//ISR (GPS_RECEIVE_INTERRUPT_VECTOR)
//{
	///*	This code will run whenever a character comes in on GPS_PORT (PORTC)
	//
		//It can access global variables, but only if they're declared with the "volatile" keyword
		//It should not have any code that waits for anything. Examples include
			//*
			
			
			
			//* while (!(SPIC.STATUS >> 7));
		//Essentially, it needs to run fast. This can be called as many as 25,000 times per second, and the cansat has other stuff to do
	//*/
	//uint8_t c = GPS_USART.DATA;
	//
	//if (current_sentence == SENTENCE_GPGGA)
	//{
		//gpgga_buff[gpgga_index] = c;
		//gpgga_index++;
		////printf("GPGGA %i = %i\n", gpgga_index, gpgga_buff[gpgga_index]);
	//}	
	//
	//if (c == '\n')
	//{
		//last_finished = current_sentence;
		//current_sentence = SENTENCE_NONE;
		//dollar_counter = 0;
	//}
	//else if (c == '$' && current_sentence == SENTENCE_NONE)
	//{
		//dollar_counter = 1;
	//}
	//
	//if (dollar_counter > 0)
	//{
		//if (dollar_counter == 5 && c == 'G' )
		//{
			//current_sentence= SENTENCE_GPGGA;
			//memcpy(gpgga_buff, "$GPGG", 5);
			//gpgga_index = 5;
			//dollar_counter++;
		//}
		//else
		//{
			//dollar_counter++;
		//}
	//}
	////printf("Interrupt Executed.\n");
	////rbu8_write(&gps_receive_buffer, &(GPS_USART.DATA), 1);
//}
//
//ISR (GPS_SEND_INTERRUPT_VECTOR)
//{
	///*	This code will run whenever XBEE_PORT (PORTC) is ready to send more data
		//This interrupt should also check the status of the CTS (Clear-To-Send) line on the XBee, because otherwise it might overload the XBee with data.
		//
		//It can access global variables, but only if they're declared with the "volatile" keyword
		//It should not have any code that waits for anything. Examples include
			//* printf
			//* while (!(SPIC.STATUS >> 7));
		//Essentially, it needs to run fast. This can be called as many as 25,000 times per second, and the cansat has other stuff to do
	//*/
	//
  //rbu8_read(&gps_send_buffer, &(GPS_USART.DATA), 1);
  //rbu8_delete_oldest(&gps_send_buffer, 1);
//}
void gps_init()
{
		gps_uart.Baud=GPS_BAUD;
		gps_uart.Port=P_GPS_PORT;
		gps_uart.Usart=P_GPS_UART;
		gps_uart.tx=GPS_TX_PIN;
		gps_uart.rx=GPS_RX_PIN;
		uart_init(&gps_uart);//function that initializes uart
		GPS_UART.CTRLA=0x14;
		usart_set_rx_interrupt_level(P_GPS_UART,USART_INT_LVL_HI);
		is_gps_rx_triggered=0;
		printf("GPS Initialized");
}
void gps_write(char * data,size_t length)
{
	usart_serial_write_packet(gps_uart.Usart,data,length);
}
ISR(GPS_RX_INTERUPT)
{
	rxdata=GPS_UART.DATA;

	is_gps_rx_triggered=1;
}

void gps_update()
{
	sentencePosition++;
	rxDataBuff[sentencePosition%80]=rxdata;
	is_gps_rx_triggered=0;
	uint8_t pos;
	if(rxdata=='$')
	{
		sentencePosition=0;
	}
	else if(is_gpgga())
	{
		uint8_t commaCount=0;
		for(uint8_t i=5;i<=sentencePosition;i++)
		{
			if(rxdata==',')
			{
				commaCount++;
				if(commaCount==2){
					pos=sentencePosition-1;
					for(uint8_t i=0; i<TIMESTR_SIZE;i++)
					{
						time[i]='\0';
					}
					while(rxDataBuff[pos]!=',')
					{
						time[(sentencePosition-pos)%TIMESTR_SIZE]=rxDataBuff[pos];
						pos--;
					}
				}
				
				else if(commaCount==4)
				{
					
					for(uint8_t i=0; i<LONGITUDE_SIZE;i++)
					{
						longitude[i]='\0';
					}
					pos=sentencePosition-3;
					while(rxDataBuff[pos]!=',')
					{
						longitude[(sentencePosition-pos)%LONGITUDE_SIZE]=rxDataBuff[pos];
						pos--;
					}
					longitude[(sentencePosition-pos)%LONGITUDE_SIZE]=rxDataBuff[sentencePosition-1];
					
				}
				else if (commaCount==6)
				{
					for(uint8_t i=0; i<LATITUDE_SIZE;i++)
					{
						latitude[i]='\0';
					}
					pos=sentencePosition-3;
					while(rxDataBuff[pos]!=',')
					{
						latitude[(sentencePosition-pos)%LATITUDE_SIZE]=rxDataBuff[pos];
						pos--;
					}
					latitude[(sentencePosition-pos)%LATITUDE_SIZE]=rxDataBuff[sentencePosition-1];
				}
				else if(commaCount==8)
				{
					pos=sentencePosition-1;
					for(uint8_t i=0; i<NUMSAT_SIZE;i++)
					{
						num_sat[i]='\0';
					}
					while(rxDataBuff[pos]!=',')
					{
						num_sat[(sentencePosition-pos)%NUMSAT_SIZE]=rxDataBuff[pos];
						pos--;
					}
				}
				else if(commaCount==10)
				{
						pos=sentencePosition-1;
						for(uint8_t i=0; i<ALTATUDE_SIZE;i++)
						{
							altatude[i]='\0';
						}
						while(rxDataBuff[pos]!=',')
						{
							altatude[(sentencePosition-pos)%ALTATUDE_SIZE]=rxDataBuff[pos];
							pos--;
						}
				
				}
			
		}
	}
	}
}
uint8_t is_gpgga()
{
	if(sentencePosition<5) return 0;
	uint8_t output= (rxDataBuff[0]=='G')&&(rxDataBuff[1]=='P')&&(rxDataBuff[2]=='G')&&(rxDataBuff[3]=='G')&&(rxDataBuff[4]=='A');
	return output;
}
uint8_t is_rx_triggered()
{
	return is_gps_rx_triggered;
}



void init_gps_interrupts(void)
{
	GPS_USART.CTRLA = 0b00010100;
	gpgga_index = 0;
	uint8_t dollar
	
}
void init_gps_buffers(void);


volatile uint8_t RAW_gps_recieve_buffer[GPS_RECEIVE_BUFFER_SIZE];
volatile uint8_t RAW_gps_send_buffer[GPS_TRANSMIT_BUFFER_SIZE];

volatile RingBufferu8_t gps_receive_buffer;

volatile RingBufferu8_t gps_send_buffer;
