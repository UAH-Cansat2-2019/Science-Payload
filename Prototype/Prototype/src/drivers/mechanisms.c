/*
 * mechanisms.c
 *
 * Created: 6/9/2019 5:18:52 PM
 *  Author: quaz9
 */ 

#include "drivers/mechanisms.h"
#include "pwm.h"

void servo_init(void)
{
	
	
	pwm_init(&pwm_cfg, SERVO_TC, SERVO_PWM, 500);
	
	if(DEBUG) printf("Servos Initialized.\n");
}

void set_servo(uint16_t dutyCycle)
{
	pwm_start(&pwm_cfg,dutyCycle);
	if(DEBUG) printf("Set Servo to duty cycle of %u\n", dutyCycle);
}



void buzz_on(void)
{
	PORTC.DIRSET |= 0b00000001;
	PORTC.OUTSET |= 0b00000001;
	
	if(DEBUG) printf("Buzzer ON\n");
	
}
void buzz_off(void)
{
	PORTC.DIRSET |= 0b00000001;
	PORTC.OUTSET &= 0b11111110;
	
	if(DEBUG) printf("Buzzer OFF\n");
}