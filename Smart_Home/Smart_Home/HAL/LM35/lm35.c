/*
 * lm35.c
 *
 * Created: 3/26/2023 5:09:33 PM
 *  Author: Hesham Hany
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
  }