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

// Read the input on a channel and passes the value by reference
EN_ADCError_t ADC_read(uint8_t channel, uint16_t* result) {
  if (channel > 7) return WRONG_ADC_CHANNEL; 
  ADMUX &= (0xE0) | channel;  // Storing the channel in MUX4:0 bits
  // ADMUX &= (0b11100000) | channel;
  set_bit(ADCSRA, ADSC); // Start conversion
  while (read_bit(ADCSRA, ADIF) == 0) { ; } // Wait until the conversion is complete
  _delay_us(5); // An optional time out to make sure that the conversion result is stored in the ADC register
  // Since ADLAR is set to 0 by default, ADCH contains the two MSBs and ADCL contains the eight LSBs
  *result = ((uint16_t)ADCH << 8) + (uint16_t)ADCL;
  return ADC_OK;
  }

// TODO: implement this function
// Starts the conversion and waits for the user to use the adc interrupt to read the data and prepare for the next conversion. Doesn't wait until the conversion is complete like ADC_read()
EN_ADCError_t ADC_read_with_interrupt(uint8_t channel) {

  return ADC_OK;
  }
