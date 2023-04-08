/*
 * servo.c
 *
 * Created: 3/26/2023 5:09:13 PM
 *  Author: hesha
 */

#include "servo.h"

 // Initialized the servo
void servo_init() {
  DIO_init(SERVO_PIN, SERVO_PORT, OUT);
  PWM_init(SERVO_PWM_PIN, (SERVO_MIN_HIGH_PULSE_DURATION_mS / SERVO_PULSE_PERIODIC_TIME_mS), PWM_PHASE_CORRECT);
  Timer_start(TIMER_1, 8);
  }

// Moves the servo to a specific angle (relative to the 0 angle position, not the previous one).
void servo_move_to_angle(uint8_t angle) {
  PWM_set_DC(SERVO_PWM_PIN, ((double)angle / ((SERVO_MAX_ANGLE - SERVO_MIN_ANGLE) * (SERVO_PULSE_PERIODIC_TIME_mS / (SERVO_MAX_HIGH_PULSE_DURATION_mS - SERVO_MIN_HIGH_PULSE_DURATION_mS)))) + (SERVO_MIN_HIGH_PULSE_DURATION_mS / SERVO_PULSE_PERIODIC_TIME_mS));
  }