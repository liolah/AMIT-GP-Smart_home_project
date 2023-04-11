/*
 * hc_05.h
 *
 * Created: 3/26/2023 5:07:59 PM
 *  Author: hesha
 */


#ifndef HC_05_H_
#define HC_05_H_

#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/UART/uart.h"

#define HC_05_STATUS_PORT PORT_D
#define HC_05_STATUS_PIN 2

void BT_init(u32 buadRate);

void BT_sendChar(char data);

void BT_sendString(char* str);

#endif /* HC_05_H_ */