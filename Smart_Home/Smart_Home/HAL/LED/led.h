/*
 * led.h
 *
 * Created: 3/26/2023 5:05:10 PM
 *  Author: hesha
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO/dio.h"

typedef enum EN_ledError_t
  {
  LED_OK, LED_ERROR_INIT, LED_ERROR_ON, LED_ERROR_OFF, LED_ERROR_TOGGLE
  } EN_ledError_t;

// Initialize the LED
EN_ledError_t LED_init(uint8_t ledPort, uint8_t ledPin);

// Turn on the LED
EN_ledError_t LED_on(uint8_t ledPort, uint8_t ledPin);

// Turn off the LED
EN_ledError_t LED_off(uint8_t ledPort, uint8_t ledPin);

// Toggle the LED
EN_ledError_t LED_toggle(uint8_t ledPort, uint8_t ledPin);

#endif /* LED_H_ */