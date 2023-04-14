/*
 * lm35.h
 *
 * Created: 3/26/2023 5:09:27 PM
 *  Author: hesha
 */


#ifndef LM35_H_
#define LM35_H_

#include "../../MCAL/ADC/adc.h"
#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/Timer/timer.h"

 // Initialize LM35 in normal polling mode for general applications
void LM35_init_polling(u8 pinNumber);

// Initialize LM35 with the ADC in auto trigger mode
void LM35_init_INT(u8 pinNumber, u8 trigger);

#endif /* LM35_H_ */