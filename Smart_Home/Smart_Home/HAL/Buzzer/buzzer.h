/*
 * buzzer.h
 *
 * Created: 3/26/2023 5:08:11 PM
 *  Author: Hesham Hany
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
EN_BuzzerError_t Buzzer_init(u8 buzzerPort, u8 buzzerPin);

// Turn on the buzzer
EN_BuzzerError_t Buzzer_on(u8 buzzerPort, u8 buzzerPin);

// Turn off the buzzer
EN_BuzzerError_t Buzzer_off(u8 buzzerPort, u8 buzzerPin);

// Toggle the buzzer
EN_BuzzerError_t Buzzer_toggle(u8 buzzerPort, u8 buzzerPin);

#endif /* BUZZER_H_ */