/*
 * timer_config.h
 *
 * Created: 3/27/2023 4:56:45 PM
 *  Author: hesha
 */


#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

#define PWM_NON_INVERTED_MODE

#define PWM_PRESCALAR 8

#define TIMER_1_FAST_PWM_8_BIT       0
#define TIMER_1_FAST_PWM_9_BIT       1
#define TIMER_1_FAST_PWM_10_BIT      2
#define TIMER_1_FAST_PWM_TOP_ICR1    3
#define TIMER_1_FAST_PWM_TOP_OCR1A   4

#define TIMER_1_PHASE_CORRECT_PWM_8_BIT       5
#define TIMER_1_PHASE_CORRECT_PWM_9_BIT       6
#define TIMER_1_PHASE_CORRECT_PWM_10_BIT      7
#define TIMER_1_PHASE_CORRECT_PWM_TOP_ICR1    8
#define TIMER_1_PHASE_CORRECT_PWM_TOP_OCR1A   9

#define TIMER_1_FAST_PWM_MODE TIMER_1_FAST_PWM_TOP_ICR1

#define TIMER_1_PHASE_CORRECT_PWM_MODE TIMER_1_PHASE_CORRECT_PWM_TOP_ICR1

 // Determines the frequency
#define TIMER_1_FAST_PWM_TOP_ICR1_VALUE           0xFFFF
 // ICR1 is set to generate 50Hz PWM signal fro the servo
#define TIMER_1_PHASE_CORRECT_PWM_TOP_ICR1_VALUE  20000

#endif /* TIMER_CONFIG_H_ */