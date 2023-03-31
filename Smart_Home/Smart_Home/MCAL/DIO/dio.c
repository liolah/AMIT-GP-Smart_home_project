/*
 * dio.c
 *
 * Created: 3/25/2023 3:21:14 PM
 *  Author: hesha
 */

#include "dio.h"

bool isValidPinNumber(uint8_t pinNumber) {
	if (pinNumber < 8) {
		return true;
		}
	return false;
	}

bool isValidPortNumber(uint8_t portNumber) {
	if (portNumber == PORT_A || portNumber == PORT_B || portNumber == PORT_C || portNumber == PORT_D) {
		return true;
		}
	return false;
	}

bool isValidDirection(uint8_t direction) {
	if (direction == IN || direction == OUT) {
		return true;
		}
	return false;
	}

bool isValidState(uint8_t state) {
	if (state == HIGH || state == LOW) {
		return true;
		}
	return false;
	}

// Initialize the pin direction
EN_dioError_t DIO_init(uint8_t pinNumber, uint8_t portNumber, uint8_t direction) {
	// Validate the pin number
	if (!isValidPinNumber(pinNumber)) {
		return WRONG_PIN;
		}
	// Validate the port number
	if (!isValidPortNumber(portNumber)) {
		return WRONG_PORT;
		}
	// Validate the direction
	if (!isValidDirection(direction)) {
		return WRONG_DIRECTION;
		}
	switch (portNumber) {
			case PORT_A:
				if (direction == OUT) {
					set_bit(DDRA, pinNumber);
					}
				else {
					clear_bit(DDRA, pinNumber);
					}
				break;
			case PORT_B:
				if (direction == OUT) {
					set_bit(DDRB, pinNumber);
					}
				else {
					clear_bit(DDRB, pinNumber);
					}
				break;
			case PORT_C:
				if (direction == OUT) {
					set_bit(DDRC, pinNumber);
					}
				else {
					clear_bit(DDRC, pinNumber);
					}
				break;
			case PORT_D:
				if (direction == OUT) {
					set_bit(DDRD, pinNumber);
					}
				else {
					clear_bit(DDRD, pinNumber);
					}
				break;
		}
	return DIO_OK;
	}

// Write a value to a pin
EN_dioError_t DIO_write(uint8_t pinNumber, uint8_t portNumber, uint8_t state) {
	// Validate the pin number
	if (!isValidPinNumber(pinNumber)) {
		return WRONG_PIN;
		}
	// Validate the port number
	if (!isValidPortNumber(portNumber)) {
		return WRONG_PORT;
		}
	// Validate the pin state
	if (!isValidState(state)) {
		return WRONG_STATE;
		}
	switch (portNumber) {
			case PORT_A:
				if (state == HIGH) {
					set_bit(PORTA, pinNumber);
					}
				else {
					clear_bit(PORTA, pinNumber);
					}
				break;
			case PORT_B:
				if (state == HIGH) {
					set_bit(PORTB, pinNumber);
					}
				else {
					clear_bit(PORTB, pinNumber);
					}
				break;
			case PORT_C:
				if (state == HIGH) {
					set_bit(PORTC, pinNumber);
					}
				else {
					clear_bit(PORTC, pinNumber);
					}
				break;
			case PORT_D:
				if (state == HIGH) {
					set_bit(PORTD, pinNumber);
					}
				else {
					clear_bit(PORTD, pinNumber);
					}
				break;
		}
	return DIO_OK;
	}

// Read a value from a pin
EN_dioError_t DIO_Read(uint8_t pinNumber, uint8_t portNumber, uint8_t* value) {
	// Validate the pin number
	if (!isValidPinNumber(pinNumber)) {
		return WRONG_PIN;
		}
	// Validate the port number
	if (!isValidPortNumber(portNumber)) {
		return WRONG_PORT;
		}
	switch (portNumber) {
			case PORT_A:
				*value = read_bit(PINA, pinNumber);
				break;
			case PORT_B:
				*value = read_bit(PINB, pinNumber);
				break;
			case PORT_C:
				*value = read_bit(PINC, pinNumber);
				break;
			case PORT_D:
				*value = read_bit(PIND, pinNumber);
				break;
		}
	return DIO_OK;
	}

// Toggle a pin
EN_dioError_t DIO_toggle(uint8_t pinNumber, uint8_t portNumber) {
	// Validate the pin number
	if (!isValidPinNumber(pinNumber)) {
		return WRONG_PIN;
		}
	// Validate the port number
	if (!isValidPortNumber(portNumber)) {
		return WRONG_PORT;
		}
	switch (portNumber) {
			case PORT_A:
				toggle_bit(PORTA, pinNumber);
				break;
			case PORT_B:
				toggle_bit(PORTB, pinNumber);
				break;
			case PORT_C:
				toggle_bit(PORTC, pinNumber);
				break;
			case PORT_D:
				toggle_bit(PORTD, pinNumber);
				break;
		}
	return DIO_OK;
	}