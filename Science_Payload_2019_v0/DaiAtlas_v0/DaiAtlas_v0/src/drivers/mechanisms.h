/*
 * mechanisms.h
 *
 * Created: 6/9/2019 5:19:04 PM
 *  Author: quaz9
 */ 


#ifndef MECHANISMS_H_
#define MECHANISMS_H_

#include <asf.h>
#include <pwm.h>

#include "definitions.h"



#define SERVO_PWM   PWM_CH_A
#define BUZZ_PORT   PORTB
#define SERVO_TC PWM_TCE0

struct pwm_config pwm_cfg;
void servo_init(void);
void set_servo(uint16_t dutyCycle);

void buzz_on(void);
void buzz_off(void);


#endif /* MECHANISMS_H_ */