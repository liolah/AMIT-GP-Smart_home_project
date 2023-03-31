/*
 * led.c
 *
 * Created: 3/26/2023 5:05:03 PM
 *  Author: hesha
 */ 

#include "led.h"

 // Initialize the LED
EN_ledError_t LED_init(uint8_t ledPort, uint8_t ledPin) {
  // Check if the dio was initialized correctly
  if (DIO_init(ledPin, ledPort, OUT) == DIO_OK) {
    return LED_OK;
    }
  // Return error code to indicate that the led initialization failed
  return LED_ERROR_INIT;
  }

// Turn on the LED
EN_ledError_t LED_on(uint8_t ledPort, uint8_t ledPin) {
  if (DIO_write(ledPin, ledPort, HIGH) == DIO_OK) {
    return LED_OK;
    }
  // Return error code to indicate that attempting to turn on the led has failed
  return LED_ERROR_ON;
  }

// Turn off the LED
EN_ledError_t LED_off(uint8_t ledPort, uint8_t ledPin) {
  if (DIO_write(ledPin, ledPort, LOW) == DIO_OK) {
    return LED_OK;
    }
  // Return error code to indicate that attempting to turn off the led has failed
  return LED_ERROR_OFF;
  }

// Toggle the LED
EN_ledError_t LED_toggle(uint8_t ledPort, uint8_t ledPin) {
  if (DIO_toggle(ledPin, ledPort) == DIO_OK) {
    return LED_OK;
    }
  // Return error code to indicate that attempting to toggle the led has failed
  return LED_ERROR_TOGGLE;
  }