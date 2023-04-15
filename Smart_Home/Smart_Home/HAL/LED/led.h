/*
 * led.h
 *
 * Created: 3/26/2023 5:05:10 PM
 *  Author: Hesham Hany
 */


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO/dio.h"

typedef enum EN_ledError_t
  {
  LED_OK, LED_ERROR_INIT, LED_ERROR_ON, LED_ERROR_OFF, LED_ERROR_TOGGLE
  } EN_ledError_t;

// Initialize the LED
EN_ledError_t LED_init(u8 ledPort, u8 ledPin);

// Turn on the LED
EN_ledError_t LED_on(u8 ledPort, u8 ledPin);

// Turn off the LED
EN_ledError_t LED_off(u8 ledPort, u8 ledPin);

// Toggle the LED
EN_ledError_t LED_toggle(u8 ledPort, u8 ledPin);

#endif /* LED_H_ */