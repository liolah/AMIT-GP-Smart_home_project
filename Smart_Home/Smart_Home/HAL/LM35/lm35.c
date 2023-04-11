/*
 * lm35.c
 *
 * Created: 3/26/2023 5:09:33 PM
 *  Author: hesha
 */ 

#include "lm35.h"

// The lm35 will be used with the ADC in auto triggering mode
void lm35_init(uint8_t pinNumber) {
  ADC_init_auto_trigger(TIMER_0_COMPARE_MATCH_TRIGGER);
  ADC_select_channel(pinNumber);
  DIO_init(pinNumber, PORT_A, IN);
  Timer_CTC_init(TIMER_0, 0);
  Timer_start(TIMER_0, 1024);
  }