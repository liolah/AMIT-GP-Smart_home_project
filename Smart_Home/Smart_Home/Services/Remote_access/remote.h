/*
 * remote.h
 *
 * Created: 4/9/2023 4:21:03 PM
 *  Author: hesha
 */ 


#ifndef REMOTE_H_
#define REMOTE_H_

#include <stdbool.h>
#include "../../HAL/HC-05/hc_05.h"
#include "../../MCAL/Interrupts/interrupts.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"

uint8_t msg_buffer[15];
uint8_t msg_length;
uint8_t msg_buffer_pointer;
bool invalid_user_input;

typedef enum EN_remoteConnStat_t
  {
  REMOTE_INIT_SUCCESSFUL
  }
EN_remoteConnStat_t;

void remote_init(uint32_t baudRate);

void test();

#endif /* REMOTE_H_ */