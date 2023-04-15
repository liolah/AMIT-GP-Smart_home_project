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
EN_ADCError_t ADC_select_channel(u8 channel) {
  if (channel > 7) return WRONG_ADC_CHANNEL;
  ADMUX = (ADMUX & 0xE0) | channel;  // Storing the channel in MUX4:0 bits
  // ADMUX = (ADMUX & 0b11100000) | channel;
  return ADC_OK;
  }

// Read the input on a channel and passes the value by reference
EN_ADCError_t ADC_read(u8 channel, u16* result) {
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
  * result = (u16)ADCL + ((u16)ADCH << 8); //? This will work
  //! *result = ((u16)ADCH << 8) + (u16)ADCL; // This won't work
  return ADC_OK;
  }

// Initialize the ADC in auto trigger mode
EN_ADCError_t ADC_init_auto_trigger(u8 trigger) {
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
  // Select the auto trigger source
  //! Cause of a bug: setting ADTS bits one by one. when setting them one by one, only the last bit is set and the rest are cleared. 
  //! The bits must be set in one write operation.
  //^ Generally, in this project, setting bits in a register one by one has caused multiple issues, also sometimes the order matters. other times a register must be read before another.
  //? Setting one bit is okay. But multiple bits need to be set in one write operation.
  switch (trigger) {
      case FREE_RUNNING_MODE_TRIGGER:
        // All bits are clear by default
        // Start free running mode first conversion
        set_bit(ADCSRA, ADSC);
        break;
      case ANALOG_COMPARATOR_TRIGGER:
        set_bit(SFIOR, ADTS0);
        break;
      case INT0_TRIGGER:
        set_bit(SFIOR, ADTS1);
        break;
      case TIMER_0_COMPARE_MATCH_TRIGGER:
        SFIOR |= (1 << ADTS0) | (1 << ADTS1);
        break;
      case TIMER_0_OVF_TRIGGER:
        set_bit(SFIOR, ADTS2);
        break;
      case TIMER_1_COMPARE_MATCH_B_TRIGGER:
        SFIOR |= (1 << ADTS0) | (1 << ADTS2);
        break;
      case TIMER_1_OVF_TRIGGER:
        SFIOR |= (1 << ADTS1) | (1 << ADTS2);
        break;
    }
  // Enable the ADC
  set_bit(ADCSRA, ADEN);
  return ADC_OK;
  }