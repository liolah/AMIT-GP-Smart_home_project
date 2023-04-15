/*
 * dio.h
 *
 * Created: 3/25/2023 3:20:38 PM
 *  Author: Hesham Hany
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
EN_dioError_t DIO_init(u8 pinNumber, u8 portNumber, u8 direction);

// Write a value to a pin
EN_dioError_t DIO_write(u8 pinNumber, u8 portNumber, u8 value);

// Read a value from a pin
EN_dioError_t DIO_Read(u8 pinNumber, u8 portNumber, u8* value);

// Toggle a pin
EN_dioError_t DIO_toggle(u8 pinNumber, u8 portNumber);

#endif /* DIO_H_ */