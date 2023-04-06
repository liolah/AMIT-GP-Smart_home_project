/*
 * adc.c
 *
 * Created: 3/28/2023 1:01:51 PM
 *  Author: hesha
 */

#include "adc.h"

 // Initialize the ADC
EN_ADCError_t ADC_init() {
#if (ADC_VREF == AREF)
  // since the defualt for pins is to be low (0) we don't need to change anything here(since it's 0).
  // I don't need to write anything too. Because the VREF won't be changed during the run time. The only case I will need to clear a bit is if it was set by the MCU or me.
#elif (ADC_VREF == AVCC)
  set_bit(ADMUX, REFS0);
#elif (ADC_VREF == INTERNAL_VREF)
  set_bit(ADMUX, REFS0);
  set_bit(ADMUX, REFS1);
#endif
  // Setting the prescalar to 128 so the operation frequency of the adc be within
  // the applicable range (50KHz-200KHz). The oscillator frequency is 16000000, Therefore the only applicable prescalar is 128.
  set_bit(ADCSRA, ADPS0);
  set_bit(ADCSRA, ADPS1);
  set_bit(ADCSRA, ADPS2);
  set_bit(ADCSRA, ADEN); // Enable the ADC
  return ADC_OK;
  }


// Select an ADC channel to read from
EN_ADCError_t ADC_select_channel(uint8_t channel) {
  if (channel > 7) return WRONG_ADC_CHANNEL;
  ADMUX = (ADMUX & 0xE0) | channel;  // Storing the channel in MUX4:0 bits
  // ADMUX = (ADMUX & 0b11100000) | channel;
  return ADC_OK;
  }

// Read the input on a channel and passes the value by reference
EN_ADCError_t ADC_read(uint8_t channel, uint16_t* result) {
  ADC_select_channel(channel);
  set_bit(ADCSRA, ADSC); // Start conversion
  while (read_bit(ADCSRA, ADIF) == 0); // Wait until the conversion is complete
#if READ_WAIT_DURATION_uS
  _delay_us(READ_WAIT_DURATION_uS); // An optional time out to make sure that the conversion result is stored in the ADC register
#endif
  // Since ADLAR is set to 0 by default, ADCH contains the two MSBs and ADCL contains the eight LSBs
  // ADCL must be read first then ADCH.
  // When ADCL is read, the ADC Data Register is not updated until ADCH is read.Consequently, if the result is left
  //   adjusted and no more than 8 - bit precision is required, it is sufficient to read ADCH.Otherwise, ADCL must be read
  //   first, then ADCH.
  * result = (uint16_t)ADCL + ((uint16_t)ADCH << 8); //? This will work
  //! *result = ((uint16_t)ADCH << 8) + (uint16_t)ADCL; // This won't work
  return ADC_OK;
  }

// Initialize the ADC in auto triggering on the positive edge of timer0 compare match
EN_ADCError_t ADC_init_timer0_CTC_triggering_with_interrupt() {
#if (ADC_VREF == AREF)
  // since the defualt for pins is to be low (0) we don't need to change anything here(since it's 0).
  // I don't need to write anything too. Because the VREF won't be changed during the run time. The only case I will need to clear a bit is if it was set by the MCU or me.
#elif (ADC_VREF == AVCC)
  set_bit(ADMUX, REFS0);
#elif (ADC_VREF == INTERNAL_VREF)
  set_bit(ADMUX, REFS0);
  set_bit(ADMUX, REFS1);
#endif
  // Setting the prescalar to 128 so the operation frequency of the adc be within
  // the applicable range (50KHz-200KHz). The oscillator frequency is 16000000, Therefore the only applicable prescalar is 128.
  set_bit(ADCSRA, ADPS0);
  set_bit(ADCSRA, ADPS1);
  set_bit(ADCSRA, ADPS2);
  // Enable the auto trigger mode
  set_bit(ADCSRA, ADATE);
  // Set the auto trigger mode to timer0 compare match
  set_bit(SFIOR, ADTS0);
  set_bit(SFIOR, ADTS1);
  // Enable the ADC
  set_bit(ADCSRA, ADEN);
  // Enable the ADC conversion complete interrupt
  set_bit(ADCSRA, ADIE);
  return ADC_OK;
  }