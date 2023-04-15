/*
 * lights.h
 *
 * Created: 4/14/2023 6:25:27 AM
 *  Author: hesha
 */


#ifndef LIGHTS_H_
#define LIGHTS_H_

#include "../../HAL/LED/led.h"
#include "../../MCAL/Timer/timer.h"

#define LAMP_1 1
#define LAMP_2 2
#define LAMP_3 3
#define LAMP_4 4
#define LAMP_5 5
#define LAMP_6 6

#define LAMP_1_PIN   2
#define LAMP_1_PORT  PORT_C 

#define LAMP_2_PIN   3
#define LAMP_2_PORT  PORT_C 

#define LAMP_3_PIN   4
#define LAMP_3_PORT  PORT_C 

#define LAMP_4_PIN   5
#define LAMP_4_PORT  PORT_C 

#define LAMP_5_PIN   6
#define LAMP_5_PORT  PORT_C 

#define LAMP_6_DIMMABLE_PIN      7
#define LAMP_6_DIMMABLE_PWM_PIN  OC_2
#define LAMP_6_DIMMABLE_PORT     PORT_D

 // Initializes all six lamps
void Lamps_init(void);

// Turn on a lamp
void Lamp_on(u8 lampNumber);

// Turn off a lamp
void Lamp_off(u8 lampNumber);

// Toggle a lamp
void Lamp_toggle(u8 lampNumber);

// Adjust the brightness of the dimmable lamp
void Lamp_dimmable_set_brightness(double brightness);

#endif /* LIGHTS_H_ */