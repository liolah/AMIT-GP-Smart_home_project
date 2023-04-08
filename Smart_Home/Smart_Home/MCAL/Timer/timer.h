/*
 * timer.h
 *
 * Created: 3/25/2023 4:37:37 PM
 *  Author: hesha
 */


#ifndef TIMER_H_
#define TIMER_H_

#include <stdbool.h>
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"

#include "timer_config.h"

#define TIMER_0 0
#define TIMER_1 1
#define TIMER_2 2

#define OC_0  0
#define OC_1A 1
#define OC_1B 2
#define OC_2  3

#define PWM_FAST 1
#define PWM_PHASE_CORRECT 2
#define PWM_PHASE_AND_FREQUENCY_CORRECT 3

typedef enum EN_timerError_t
  {
  TIMER_OK, WRONG_TIMER, WRONG_PRESCALAR, WRONG_TIMER_TCNT_VALUE, WRONG_TIMER_OCR_VALUE, WRONG_PWM_MODE, WRONG_PWM_PIN
  } EN_timerError_t;

// TODO: A function that takes the timer number and the duration then adjusts the prescalar settings optimally to get the exact required time after a number of cycles. returns the minimum number of cycles

// Initialize the timers to start in normal mode
EN_timerError_t Timer_normal_init(uint8_t timerNumber, uint16_t initialVal);

// Initialize the timers to start in CTC mode
EN_timerError_t Timer_CTC_init(uint8_t timerNumber, uint16_t compareValue);

// Initialize the timers to start in pwm mode
// The PWM pin must be set as output 
EN_timerError_t PWM_init(uint8_t pwmPin, double dutyCycle, uint8_t mode);

// Change the duty cycle of a timer
EN_timerError_t set_DC(uint8_t pwmPin, double dutyCycle);

// disconnects the OC pins and sets the prescalar to 0.
EN_timerError_t PWM_stop(uint8_t pwmPin);

// Start the timer
EN_timerError_t Timer_start(uint8_t timerNumber, uint16_t prescalar);

// Stop the timer
EN_timerError_t Timer_stop(uint8_t timerNumber);

// Reset the timer
EN_timerError_t Timer_reset(uint8_t timerNumber);

// Check if the timer's OCF is set and reset the flag if set
EN_timerError_t Timer_read_and_reset_OCF(uint8_t timerNumber, bool* flag);

#endif /* TIMER_H_ */