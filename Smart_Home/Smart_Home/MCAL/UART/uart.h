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

// Send a s8 using UART
void UART_sends8(s8 data);

// Receive a s8 using UART
void UART_receives8(s8* x);

void UART_sendString(s8* str);

void UART_receiveString(s8* str);

#endif /* UART_H_ */