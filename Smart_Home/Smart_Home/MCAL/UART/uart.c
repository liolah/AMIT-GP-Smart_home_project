/*
 * uart.c
 *
 * Created: 3/25/2023 5:18:34 PM
 *  Author: hesha
 */

#include "uart.h"

 // Initialize the UART interface
EN_UARTError_t UART_init(uint32_t baudRate) {
  uint16_t UBRR;
  switch (baudRate) {
      case 2400:
        UBRR = 416;
        break;
      case 4800:
        UBRR = 207;
        break;
      case 9600:
        UBRR = 103;
        break;
      case 19200:
        UBRR = 51;
        break;
      case 115200:
        UBRR = 8;
        break;
      default:
        return WRONG_BAUDRATE;
        break;
    }
  
  // Setting the baud rate
  UBRRH = (uint8_t)UBRR >> 8;
  UBRRL = (uint8_t)UBRR;
  // Enable the RX and TX pins
  set_bit(UCSRB, TXEN);
  set_bit(UCSRB, RXEN);
  // Setting the frame format (start bit - 8 data bits - no parity bits - one stop bit)
  set_bit(UCSRC, URSEL); // Setting this bit to one selects UCSRC reg to read and write. Since UBRR and UCSRC have the same memory address
  // Asynchronous by default 
  // Parity bit diabled by default
  // One stop bit by default
  // Set char size to 8 bits
  set_bit(UCSRC, UCSZ0);
  set_bit(UCSRC, UCSZ1);
  return UART_INIT_OK;
  }

// Send a char using UART
void UART_sendChar(uint8_t data) {
  while (!read_bit(UCSRA, UDRE)); // Wait for the register to be empty.
  UDR = data;
  while (!read_bit(UCSRA, TXC)); // Wait for the data in the register to be sent.
  }

// Receive a char using UART
void UART_receiveChar(uint8_t* x) {
  while (!read_bit(UCSRA, RXC)); // Wait for the data to be received.
  *x = UDR;
  }

void UART_sendString(uint8_t* str) {
  uint32_t i = 0;
  while (str[i] != 0) {
    UART_sendChar(str[i]);
    i++;
    }
  UART_sendChar(0); // Send null to terminate the string
  }

void UART_receiveString(uint8_t* str) {
  uint32_t i = 0;
  uint8_t c;
  UART_receiveChar(&c);
  while (c != 0) {
    str[i] = c;
    UART_receiveChar(&c);
    i++;
    }
    str[i] = 0; // Terminate the string with null
  }