/*
 * relay.h
 *
 * Created: 3/26/2023 5:12:34 PM
 *  Author: Hesham Hany
 */


#ifndef RELAY_H_
#define RELAY_H_

#include "../../MCAL/DIO/dio.h"

typedef enum EN_relayError_t
  {
  RELAY_OK, RELAY_ERROR_INIT, RELAY_ERROR_ON, RELAY_ERROR_OFF, RELAY_ERROR_TOGGLE
  } EN_relayError_t;

// Initialize the relay
EN_relayError_t relay_init(u8 relayPort, u8 relayPin);

// Turn on the relay
EN_relayError_t relay_on(u8 relayPort, u8 relayPin);

// Turn off the relay
EN_relayError_t relay_off(u8 relayPort, u8 relayPin);

// Toggle the relay
EN_relayError_t relay_toggle(u8 relayPort, u8 relayPin);

#endif /* RELAY_H_ */