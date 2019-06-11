/*
 * definitions.h
 *
 * Created: 6/6/2019 4:49:54 PM
 *  Author: quaz9
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_


#define DEBUG 1
#define DEBUG_ADC 0
float temp;
float voltage;

uint32_t packetCount;
uint32_t missionTime;
int32_t pressure;
float altitude;
void write_telem_to_xbee(void);
double pitch;
double roll;
double heading;
uint8_t flightState;
#endif /* DEFINITIONS_H_ */