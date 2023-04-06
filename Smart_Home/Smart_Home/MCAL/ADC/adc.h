/*
 * adc.h
 *
 * Created: 3/28/2023 1:01:44 PM
 *  Author: hesha
 */


#ifndef ADC_H_
#define ADC_H_

#define F_CPU 16000000

#include <util/delay.h>

#include <stdbool.h>
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"

#include "adc_config.h"

#define READ_WAIT_DURATION_uS 0
typedef enum EN_ADCError_t
  {
  ADC_OK, WRONG_ADC_CHANNEL
  } EN_ADCError_t;

// Initialize the ADC
EN_ADCError_t ADC_init();

// Initialize the ADC in auto triggering on the positive edge of timer0 compare match
// The conversion result is handled through the adc interrupt
EN_ADCError_t ADC_init_timer0_CTC_triggering_with_interrupt();

// Read the input on a channel and passes the value by reference
EN_ADCError_t ADC_read(uint8_t channel, uint16_t* result);

// Select an ADC channel to read from
EN_ADCError_t ADC_select_channel(uint8_t channel);

#endif /* ADC_H_ */