/*
 * lm35.c
 *
 * Created: 3/26/2023 5:09:33 PM
 *  Author: hesha
 */

#include "lm35.h"

 // Initialize LM35 in normal polling mode for general applications
void LM35_init_polling(u8 pinNumber) {
  DIO_init(pinNumber, PORT_A, IN);
  ADC_init();
  ADC_select_channel(pinNumber);
  }

// Initialize LM35 with the ADC in auto trigger mode
void LM35_init_INT(u8 pinNumber, u8 trigger) {
  DIO_init(pinNumber, PORT_A, IN);
  ADC_init_auto_trigger(trigger);
  ADC_select_channel(pinNumber);
  switch (trigger) {
      case TIMER_0_COMPARE_MATCH_TRIGGER:
        // Initialize timer 0 to run in CTC mode
        Timer_CTC_init(TIMER_0, 0);
        Timer_start(TIMER_0, 1024);
        break;
      case TIMER_1_COMPARE_MATCH_B_TRIGGER:
        // Since timer 1 is already running in pwm mode (in this specific system), no initializations will be made. Only OCR1B will be initialized.
        // OCR1B can be done using set_dutyCycle() since all it does is altering the values in the OCR registers. 
        // Setting the duty cycle to 1 here will initialize OCR1B with the same value in ICR1, which is 20000. 
        // With the timer 1 prescalar set to 8. Tis will cause a compare match to occur every 10 mS.
        PWM_set_DC(OC_1B, 1);
        break;
    }
  }