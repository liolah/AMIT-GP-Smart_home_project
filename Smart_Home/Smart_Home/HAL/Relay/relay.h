/*
 * relay.h
 *
 * Created: 3/26/2023 5:12:34 PM
 *  Author: hesha
 */ 


#ifndef RELAY_H_
#define RELAY_H_

#include "../../MCAL/DIO/dio.h"

typedef enum EN_relayError_t
  {
  RELAY_OK, RELAY_ERROR_INIT, RELAY_ERROR_ON, RELAY_ERROR_OFF, RELAY_ERROR_TOGGLE
  } EN_relayError_t;

// Initialize the relay
EN_relayError_t relay_init(uint8_t relayPort, uint8_t relayPin);

// Turn on the relay
EN_relayError_t relay_on(uint8_t relayPort, uint8_t relayPin);

// Turn off the relay
EN_relayError_t relay_off(uint8_t relayPort, uint8_t relayPin);

// Toggle the relay
EN_relayError_t relay_toggle(uint8_t relayPort, uint8_t relayPin);

#endif /* RELAY_H_ */