/*
 * hc_05.c
 *
 * Created: 3/26/2023 5:07:52 PM
 *  Author: hesha
 */ 

#include "hc_05.h"

void BT_init(uint32_t buadRate) {
  DIO_init(HC_05_STATUS_PIN, HC_05_STATUS_PORT, IN);
  UART_init(buadRate);
  }