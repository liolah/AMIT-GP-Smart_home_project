/*
 * dio.h
 *
 * Created: 3/25/2023 3:20:38 PM
 *  Author: hesha
 */


#ifndef DIO_H_
#define DIO_H_

#include <stdbool.h>
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"

#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'

#define IN 0
#define OUT 1

#define LOW 0
#define HIGH 1

typedef enum EN_dioError_t
	{
	DIO_OK, WRONG_PIN, WRONG_PORT, WRONG_DIRECTION, WRONG_STATE
	} EN_dioError_t;

// Initialize the pin direction
EN_dioError_t DIO_init(uint8_t pinNumber, uint8_t portNumber, uint8_t direction);

// Write a value to a pin
EN_dioError_t DIO_write(uint8_t pinNumber, uint8_t portNumber, uint8_t value);

// Read a value from a pin
EN_dioError_t DIO_Read(uint8_t pinNumber, uint8_t portNumber, uint8_t* value);

// Toggle a pin
EN_dioError_t DIO_toggle(uint8_t pinNumber, uint8_t portNumber);

#endif /* DIO_H_ */