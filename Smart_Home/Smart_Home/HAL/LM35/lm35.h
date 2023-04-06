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

void lm35_init(uint8_t pinNumber);

#endif /* LM35_H_ */