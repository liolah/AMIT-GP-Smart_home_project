/*
 * remote.h
 *
 * Created: 4/9/2023 4:21:03 PM
 *  Author: hesha
 */


#ifndef REMOTE_H_
#define REMOTE_H_

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "../User/user.h"
#include "../../HAL/HC-05/hc_05.h"
#include "../../MCAL/Interrupts/interrupts.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"

s8 msg_buffer[15];
u8 msg_length;
u8 msg_buffer_pointer;
bool invalid_user_input;

typedef enum EN_remoteConnStat_t
  {
  REMOTE_INIT_SUCCESSFUL
  }
EN_remoteConnStat_t;

void remote_init(u32 baudRate);


#endif /* REMOTE_H_ */