/*
 * buzzer.c
 *
 * Created: 3/26/2023 5:08:43 PM
 *  Author: Hesham Hany
 */

#include "buzzer.h"

 // Initialize the buzzer
EN_BuzzerError_t Buzzer_init(u8 buzzerPort, u8 buzzerPin) {
  // Check if the dio was initialized correctly
  if (DIO_init(buzzerPin, buzzerPort, OUT) == DIO_OK) {
    return BUZZER_OK;
    }
  // Return error code to indicate that the buzzer initialization failed
  return BUZZER_ERROR_INIT;
  }

// Turn on the buzzer
EN_BuzzerError_t Buzzer_on(u8 buzzerPort, u8 buzzerPin) {
  if (DIO_write(buzzerPin, buzzerPort, HIGH) == DIO_OK) {
    return BUZZER_OK;
    }
  // Return error code to indicate that attempting to turn on the buzzer has failed
  return BUZZER_ERROR_ON;
  }

// Turn off the buzzer
EN_BuzzerError_t Buzzer_off(u8 buzzerPort, u8 buzzerPin) {
  if (DIO_write(buzzerPin, buzzerPort, LOW) == DIO_OK) {
    return BUZZER_OK;
    }
  // Return error code to indicate that attempting to turn off the buzzer has failed
  return BUZZER_ERROR_OFF;
  }

// Toggle the buzzer
EN_BuzzerError_t Buzzer_toggle(u8 buzzerPort, u8 buzzerPin) {
  if (DIO_toggle(buzzerPin, buzzerPort) == DIO_OK) {
    return BUZZER_OK;
    }
  // Return error code to indicate that attempting to toggle the buzzer has failed
  return BUZZER_ERROR_TOGGLE;
  }