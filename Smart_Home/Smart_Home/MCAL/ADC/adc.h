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

typedef enum EN_ADCError_t
  {
  ADC_OK, WRONG_ADC_CHANNEL
  } EN_ADCError_t;

// Initialize the ADC
EN_ADCError_t ADC_init();

// Read the input on a channel and passes the value by reference
EN_ADCError_t ADC_read(uint8_t channel, uint16_t* result);

// Starts the conversion and waits for the user to use the adc interrupt to read the data and prepare for the next conversion. Doesn't wait until the conversion is complete like ADC_read()
EN_ADCError_t ADC_read_with_interrupt(uint8_t channel);

#endif /* ADC_H_ */