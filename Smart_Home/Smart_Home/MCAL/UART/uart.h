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

#ifndef F_CPU
#define F_CPU 16000000ul
#endif

typedef enum EN_UARTError_t
  {
  UART_INIT_OK, WRONG_BAUDRATE
  } EN_UARTError_t;

// Initialize the UART interface
EN_UARTError_t UART_init(unsigned long int baudRate);

// Send a char using UART
void UART_sendChar(char data);

// Receive a char using UART
void UART_receiveChar(char* x);

void UART_sendString(char* str);

void UART_receiveString(char* str);

#endif /* UART_H_ */