/*
 * hc_05.c
 *
 * Created: 3/26/2023 5:07:52 PM
 *  Author: hesha
 */

#include "hc_05.h"

void BT_init(u32 baudRate) {
  DIO_init(HC_05_STATUS_PIN, HC_05_STATUS_PORT, IN);
  UART_init(baudRate);
  }

void BT_sends8(s8 data) {
  UART_sends8(data);
  }

void BT_sendString(s8* str) {
  UART_sendString(str);
  }