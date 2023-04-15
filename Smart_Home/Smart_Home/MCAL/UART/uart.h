/*
 * uart.h
 *
 * Created: 3/25/2023 5:18:08 PM
 *  Author: Hesham Hany
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
EN_UARTError_t UART_init(u32 baudRate);

// Send a Char using UART
void UART_sendChar(s8 data);

// Receive a Char using UART
void UART_receiveChar(s8* x);

void UART_sendString(s8* str);

void UART_receiveString(s8* str);

#endif /* UART_H_ */