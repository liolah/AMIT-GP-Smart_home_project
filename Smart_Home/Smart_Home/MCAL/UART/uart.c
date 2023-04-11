/*
 * uart.c
 *
 * Created: 3/25/2023 5:18:34 PM
 *  Author: hesha
 */

#include "uart.h"

 // Initialize the UART interface
EN_UARTError_t UART_init(unsigned long int baudRate) {
  //! Issue 1: The UBRR variable was being optimized, making the case statements empty, which goes under the fallthrough optimization and gets optimized
  //! until the default case is reached resulting in the function returning an error and the UART never gets initialized. (probably)
  //? So Just removed UBRR and used registers in the cases directly
  // Setting the baud rate
  // UBRR values are calculated based on 16MHz clock speed
  switch (baudRate) {
      case 2400U:
        // UBRR = 416;
        UBRRH = 1;
        UBRRL = 160;
        break;
      case 4800U:
        UBRRL = 207;
        break;
      case 9600U:
        UBRRL = 103;
        break;
      case 19200U:
        UBRRL = 51;
        break;
      case 115200U:
        UBRRL = 8;
        break;
      case 230400U:
        UBRRL = 3;
        break;
      case 500000U:
        UBRRL = 1;
        break;
      case 1000000U:
        UBRRL = 0;
        break;
      default:
        return WRONG_BAUDRATE;
        break;
    }

  // Enable the RX and TX pins
  set_bit(UCSRB, TXEN);
  set_bit(UCSRB, RXEN);
  // Setting the frame format (start bit - 8 data bits - no parity bits - one stop bit)
  set_bit(UCSRC, URSEL); // Setting this bit to one selects UCSRC reg to read and write. Since UBRR and UCSRC have the same memory address
  // Asynchronous by default 
  // Parity bit disabled by default
  // One stop bit by default
  // Set char size to 8 bits
  set_bit(UCSRC, UCSZ0);
  set_bit(UCSRC, UCSZ1);
  return UART_INIT_OK;
  }

// Send a char using UART
void UART_sendChar(char data) {
  while (!read_bit(UCSRA, UDRE)); // Wait for the register to be empty.
  UDR = data;
  while (!read_bit(UCSRA, TXC)); // Wait for the data in the register to be sent.
  }

// Receive a char using UART
void UART_receiveChar(char* x) {
  while (!read_bit(UCSRA, RXC)); // Wait for the data to be received.
  *x = UDR;
  }

void UART_sendString(char* str) {
  u32 i = 0;
  while (str[i] != 0) {
    UART_sendChar(str[i]);
    i++;
    }
  UART_sendChar(0); // Send null to terminate the string
  }

void UART_receiveString(char* str) {
  u32 i = 0;
  char c;
  UART_receiveChar(&c);
  while (c != 0) {
    str[i] = c;
    UART_receiveChar(&c);
    i++;
    }
  str[i] = 0; // Terminate the string with null
  }