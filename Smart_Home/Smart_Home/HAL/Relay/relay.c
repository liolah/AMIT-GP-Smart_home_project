/*
 * relay.c
 *
 * Created: 3/26/2023 5:12:40 PM
 *  Author: hesha
 */ 

#include "relay.h"

 // Initialize the relay
EN_relayError_t relay_init(uint8_t relayPort, uint8_t relayPin) {
  // Check if the dio was initialized correctly
  if (DIO_init(relayPin, relayPort, OUT) == DIO_OK) {
    return RELAY_OK;
    }
  // Return error code to indicate that the relay initialization failed
  return RELAY_ERROR_INIT;
  }

// Turn on the relay
EN_relayError_t relay_on(uint8_t relayPort, uint8_t relayPin) {
  if (DIO_write(relayPin, relayPort, HIGH) == DIO_OK) {
    return RELAY_OK;
    }
  // Return error code to indicate that attempting to turn on the relay has failed
  return RELAY_ERROR_ON;
  }

// Turn off the relay
EN_relayError_t relay_off(uint8_t relayPort, uint8_t relayPin) {
  if (DIO_write(relayPin, relayPort, LOW) == DIO_OK) {
    return RELAY_OK;
    }
  // Return error code to indicate that attempting to turn off the relay has failed
  return RELAY_ERROR_OFF;
  }

// Toggle the relay
EN_relayError_t relay_toggle(uint8_t relayPort, uint8_t relayPin) {
  if (DIO_toggle(relayPin, relayPort) == DIO_OK) {
    return RELAY_OK;
    }
  // Return error code to indicate that attempting to toggle the relay has failed
  return RELAY_ERROR_TOGGLE;
  }