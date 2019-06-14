/*
 * Xbee.c
 *
 * Created: 5/29/2019 5:28:29 PM
 *  Author: natha
 */ 

#include <asf.h>
#include "Xbee.h"

static uart_device xbee_uart;
volatile extern uint8_t XbeeRx;

static void xbee_callback(void)
{
	write_telem_to_xbee();
	tc_clear_overflow(&XBEE_TC);
	
}

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
	
	tc_enable(&XBEE_TC);
	tc_set_overflow_interrupt_callback(&XBEE_TC, xbee_callback);
	tc_set_wgm(&XBEE_TC, TC_WG_NORMAL);
	tc_write_period(&XBEE_TC, XBEE_WRITE_INTERVAL);
	tc_set_overflow_interrupt_level(&XBEE_TC, TC_INT_LVL_LO);
	cpu_irq_enable();
	tc_write_clock_source(&XBEE_TC, TC_CLKSEL_DIV1_gc);
}

void xbeeWrite(uint8_t* data)
{	
	if(blockTransmission) return NULL;
	usart_serial_write_packet(P_XBEEUART, data, strlen(data));
	packetCount++;
	if(DEBUG) printf("%s \n",(const)data);
}

void write_telem_to_xbee()
{
	char* telemetryString [255];
	*telemetryString = "\0";
	char* s_teamID = "2118";
	char* s_missionTime  [10];
	char* s_packetCount [10];
	char* s_altitude [10];
	char* s_pressure [10];
	char* s_temp [10];
	char* s_voltage [10];
	char* s_gpsTime [10];
	char* s_gpsLat [10];
	char* s_gpsLong [10];
	char* s_gpsAlt [10];
	char* s_gpsSats [10];
	char* s_pitch [10];
	char* s_roll [10];
	char* s_spinRate [10];
	char* s_flightState [10];
	char* s_cardinalDir [10];
	
	sprintf(s_missionTime, "%i", missionTime);
	sprintf(s_packetCount, "%i", packetCount);
	sprintf(s_altitude, "%f", altitude);
	sprintf(s_pressure, "%i",pressure);
	sprintf(s_temp, "%f", temp);
	sprintf(s_voltage, "%f", voltage);
	sprintf(s_gpsTime, " ");
	sprintf(s_gpsLat, " ");
	sprintf(s_gpsLong, " ");
	sprintf(s_gpsAlt, " ");
	sprintf(s_gpsSats, " ");
	sprintf(s_pitch, "%f", pitch);
	sprintf(s_roll, "%f", roll);
	sprintf(s_spinRate, " ");
	sprintf(s_flightState, "%i", flightState);
	sprintf(s_cardinalDir, "%f", heading);
	
	
	sprintf(telemetryString,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",
	s_teamID,
	s_missionTime,
	s_packetCount,
	s_altitude,
	s_pressure,
	s_temp,
	s_voltage,
	s_gpsTime,
	s_gpsLat,
	s_gpsLong,
	s_gpsAlt,
	s_gpsSats,
	s_pitch,
	s_roll,
	s_spinRate,
	s_flightState,
	s_cardinalDir);
	
	xbeeWrite(telemetryString);
}


ISR(READ_INTURUPT)
{
	XbeeRx=XBEE_UART.DATA;
}