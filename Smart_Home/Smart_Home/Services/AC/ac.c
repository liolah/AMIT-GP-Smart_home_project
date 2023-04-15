/*
 * ac.c
 *
 * Created: 4/14/2023 6:24:50 AM
 *  Author: hesha
 */

#include "ac.h"

void AC_auto_control_service_start(void) {
  LM35_init_INT(TEMPERATURE_SENSOR_PIN, AC_ADC_TRIGGER);
  DIO_init(AC_PIN, AC_PORT, OUT);
  ADC_INT_init();

#if TIMER_0_TOV_RESET_METHOD == TIMER_0_TOV_RESET_BY_ACTIVATING_TIMER0_OVF_INT
  set_bit(TIMSK, TOIE0);
#endif 

#if AC_ADC_TRIGGER == TIMER_0_COMPARE_MATCH_TRIGGER
  // The timer is initialized to take the longest possible duration between each ADC trigger(~16mS at 16MHz clock). Change according to application.
  //! For some reason compare match triggers doesn't work on Proteus. I tried numerous times but it still doesn't work.
  //? However, it works perfectly as intended when debugging on atmel studio.
  //* The timer overflow triggers works fine. 
  Timer_CTC_init(TIMER_0, 255);
  Timer_start(TIMER_0, 1024);
#elif AC_ADC_TRIGGER == TIMER_0_OVF_TRIGGER
  Timer_normal_init(TIMER_0, 0);
  Timer_start(TIMER_0, 1024);
#elif AC_ADC_TRIGGER == TIMER_1_COMPARE_MATCH_B_TRIGGER
  // Since timer 1 is already running in pwm mode (in this specific system), no initializations will be made. Only OCR1B will be initialized.
  // OCR1B can be done using set_dutyCycle() since all it does is altering the values in the OCR registers. 
  // Setting the duty cycle to 1 here will initialize OCR1B with the same value in ICR1, which is 20000. 
  // With the timer 1 prescalar set to 8. This will cause a compare match to occur every 20 mS.
  PWM_set_DC(OC_1B, 1);
#elif AC_ADC_TRIGGER == TIMER_1_OVF_TRIGGER
  Timer_normal_init(TIMER_1, 0);
  Timer_start(TIMER_1, 256);
#endif
  }

#if TIMER_0_TOV_RESET_METHOD == TIMER_0_TOV_RESET_BY_ACTIVATING_TIMER0_OVF_INT
// To reset the TOV0 flag. Alternatively, it can be reset in the ADC complete interrupt.
ISR(TIMER0_OVF_vect) {}
#endif

ISR(ADC_vect) {
  u16 temperature;
  temperature = ADCL + (ADCH << 8);
  // Since the ADC is set to use the internal VREF of 2.56 V, the resolution of the ADC is 2.5 mV. This resolution allows to measure the temperature
  // out of the LM35 with a resolution of 0.25 degree celsius, since each 10mV  increment on the LM35 output is 1 degree C.
  // If the temperature is higher than the maximum specified temperature, turn on the AC.
  if (temperature > AMBIENT_HIGH_TEMP_ADC_VAL) DIO_write(AC_PIN, AC_PORT, HIGH);
  // If the temperature became below the minimum specified temperature turn off the AC.
  if (temperature < AMBIENT_LOW_TEMP_ADC_VAL) DIO_write(AC_PIN, AC_PORT, LOW);

#if TIMER_0_TOV_RESET_METHOD == TIMER_0_TOV_RESET_VIA_ADC_COMPLETE_INTERRUPT
  // Since the ADC is configured in auto trigger mode with timer 0 overflow as the trigger, 
  // The overflow interrupt flag bit must be cleared by software if timer 0 overflow interrupt isn't used. 
  // Otherwise the triggering won't work and the ADC will halt.
  set_bit(TIFR, TOV0);
#endif
  }