/*
 * servo.h
 *
 * Created: 3/26/2023 5:08:55 PM
 *  Author: Hesham Hany
 */


 //? This a driver fro SG90 9g Micro Servo
//^ The servo takes a PWM signal with 50Hz frequency as input (Pulse width, aka periodic time, is 20mS).
//^ The servo angle is determined by the duration of the high pulse (duty cycle). 
//^ A PWM signal with high pulse duration of * 1mS * will make the servo move to * 0 * angle position
//^ A PWM signal with high pulse duration of * 1.5mS * will make the servo move to * 90 * angle position
//^ A PWM signal with high pulse duration of * 2mS * will make the servo move to * 180 * angle position
//! However, when I tried it practically, it worked from 0.5mS to 2.5mS, so I will adjust the simulation accordingly

#ifndef SERVO_H_
#define SERVO_H_


#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/Timer/timer.h"

#define SERVO_PORT PORT_D
#define SERVO_PWM_PIN  OC_1A
#define SERVO_PIN  5

#define SERVO_PULSE_PERIODIC_TIME_mS 20.0 

#define SERVO_MIN_HIGH_PULSE_DURATION_mS  0.5
#define SERVO_MAX_HIGH_PULSE_DURATION_mS  2.5

#define SERVO_MIN_ANGLE  0.0
#define SERVO_MAX_ANGLE  180.0

// Initialized the servo
void Servo_init();

// Moves the servo to a specific angle (relative to the 0 angle position, not the previous one).
void Servo_move_to_angle(u8 angle);

#endif /* SERVO_H_ */