/*
 * adc.h
 *
 * Created: 3/28/2023 1:01:44 PM
 *  Author: hesha
 */


#ifndef ADC_H_
#define ADC_H_

#ifndef F_CPU
#define F_CPU 16000000ul
#endif

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

// Initialize the ADC in auto trigger mode
// The conversion result is handled through the adc interrupt
EN_ADCError_t ADC_init_auto_trigger(u8 trigger);

// Read the input on a channel and passes the value by reference
EN_ADCError_t ADC_read(u8 channel, u16* result);

// Select an ADC channel to read from
EN_ADCError_t ADC_select_channel(u8 channel);

#endif /* ADC_H_ */