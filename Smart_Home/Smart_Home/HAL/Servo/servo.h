/*
 * servo.h
 *
 * Created: 3/26/2023 5:08:55 PM
 *  Author: hesha
 */


 //? This a driver fro SG90 9g Micro Servo
//^ The servo takes a PWM signal with 50Hz frequency as input (Pulse width, aka periodic time, is 20mS).
//^ The servo angle is determined by the duration of the high pulse (duty cycle). 
//^ A PWM signal with high pulse duration of * 1mS * will make the servo move to * 0 * angle position
//^ A PWM signal with high pulse duration of * 1.5mS * will make the servo move to * 90 * angle position
//^ A PWM signal with high pulse duration of * 2mS * will make the servo move to * 180 * angle position

#ifndef SERVO_H_
#define SERVO_H_

#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/Timer/timer.h"

#define SERVO_MAX_CONTROL_HIGH_PULSE_WIDTH_uS 1000
#define SERVO_MIN_CONTROL_HIGH_PULSE_WIDTH_uS 2000

#define SERVO_PORT PORT_D
#define SERVO_PWM_PIN  OC_1A
#define SERVO_PIN  5

#define SERVO_MIN_ANGLE  0
#define SERVO_MAX_ANGLE  180

// Initialized the servo
void servo_init();

// Moves the servo to a specific angle (relative to the 0 angle position, not the previous one).
void servo_move_to_angle(uint8_t angle);

#endif /* SERVO_H_ */