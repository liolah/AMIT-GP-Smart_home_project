/*
 * remote.c
 *
 * Created: 4/9/2023 4:21:11 PM
 *  Author: hesha
 */

#include "remote.h"

uint8_t msg_buffer[15];
uint8_t msg_length;
uint8_t msg_buffer_pointer;
uint8_t requesting_function;
bool invalid_user_input;
bool dump_invalid_data;


void remote_init(uint32_t baudRate) {
  BT_init(baudRate);
  }


void test() {
  BT_sendString("Hello!\n");
  }

void callFunWhenBufferReady(uint8_t functionNumber) {
  switch (functionNumber) {
      case 0:
        break;
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
    }
  }

ISR(USART_RXC_vect) {
  // If the buffer is full or the msg length is reached without the input being terminated by null, then it's wrong input
  // If the input is invalid, reset the buffer pointer, set the invalid input flag and call the function responsible for handling the input
  if (dump_invalid_data) {
    if (UDR == 0) {
      dump_invalid_data = false;
      invalid_user_input = false;
      }
      return;
    }
  msg_buffer[msg_buffer_pointer] = UDR;
  msg_buffer_pointer++;

  // Msg is empty
  // Ignore null msgs
  if (msg_buffer[msg_buffer_pointer - 1] == 0 && msg_buffer_pointer == 1) {
    msg_buffer_pointer = 0;
    }

  // Msg is longer than required
  if (msg_buffer_pointer == msg_length && msg_buffer[msg_buffer_pointer - 1] != 0) {
    invalid_user_input = true;
    dump_invalid_data = true;
    msg_buffer_pointer = 0;
    callFunWhenBufferReady(requesting_function);
    }

  // Msg has ended and is within the required length
  if (msg_buffer[msg_buffer_pointer - 1] == 0 && msg_buffer_pointer <= msg_length) {
    callFunWhenBufferReady(requesting_function);
    msg_buffer_pointer = 0;
    }
  }