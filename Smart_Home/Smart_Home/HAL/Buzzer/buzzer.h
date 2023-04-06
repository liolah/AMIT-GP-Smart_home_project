/*
 * buzzer.h
 *
 * Created: 3/26/2023 5:08:11 PM
 *  Author: hesha
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../MCAL/DIO/dio.h"

#define BUZZER_PORT PORT_D
#define BUZZER_PIN  6
typedef enum EN_BuzzerError_t
  {
  BUZZER_OK, BUZZER_ERROR_INIT, BUZZER_ERROR_ON, BUZZER_ERROR_OFF, BUZZER_ERROR_TOGGLE
  } EN_BuzzerError_t;

// Initialize the buzzer
EN_BuzzerError_t Buzzer_init(uint8_t buzzerPort, uint8_t buzzerPin);

// Turn on the buzzer
EN_BuzzerError_t Buzzer_on(uint8_t buzzerPort, uint8_t buzzerPin);

// Turn off the buzzer
EN_BuzzerError_t Buzzer_off(uint8_t buzzerPort, uint8_t buzzerPin);

// Toggle the buzzer
EN_BuzzerError_t Buzzer_toggle(uint8_t buzzerPort, uint8_t buzzerPin);

#endif /* BUZZER_H_ */