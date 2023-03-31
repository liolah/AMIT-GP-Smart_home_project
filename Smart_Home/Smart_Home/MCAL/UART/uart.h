/*
 * uart.h
 *
 * Created: 3/25/2023 5:18:08 PM
 *  Author: hesha
 */


#ifndef UART_H_
#define UART_H_

#include <stdbool.h>
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"

typedef enum EN_UARTError_t
  {
  UART_INIT_OK, WRONG_BAUDRATE
  } EN_UARTError_t;

#define F_CPU 16000000

// Initialize the UART interface
EN_UARTError_t UART_init(uint32_t baudRate);

// Send a char using UART
void UART_sendChar(uint8_t data);

// Receive a char using UART
void UART_receiveChar(uint8_t* x);

void UART_sendString(uint8_t* str);

void UART_receiveString(uint8_t* str);

#endif /* UART_H_ */