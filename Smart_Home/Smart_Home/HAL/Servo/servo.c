/*
 * servo.c
 *
 * Created: 3/26/2023 5:09:13 PM
 *  Author: hesha
 */ 

#include "servo.h"

 // Initialized the servo
void servo_init(){
  DIO_init(SERVO_PIN, SERVO_PORT, OUT);
  PWM_init(SERVO_PWM_PIN, 0, PWM_PHASE_CORRECT);
  }

// Moves the servo to a specific angle (relative to the 0 angle position, not the previous one).
void servo_move_to_angle(uint8_t angle){
  
}