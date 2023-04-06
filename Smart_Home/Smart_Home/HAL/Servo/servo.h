/*
 * servo.h
 *
 * Created: 3/26/2023 5:08:55 PM
 *  Author: hesha
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/Timer/timer.h"

#define SERVO_MAX_CONTROL_PULSE_WIDTH_uS 1000
#define SERVO_MIN_CONTROL_PULSE_WIDTH_uS 2000

#define SERVO_PORT PORT_D
#define SERVO_PIN  5

// Initialized the servo
void servo_init();

// Moves the servo to a specific angle (relative to the 0 angle position, not the previous one).
void servo_move_to_angle(uint8_t angle);

#endif /* SERVO_H_ */