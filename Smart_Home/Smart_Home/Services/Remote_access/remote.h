/*
 * remote.h
 *
 * Created: 4/9/2023 4:21:03 PM
 *  Author: Hesham Hany
 */


#ifndef REMOTE_H_
#define REMOTE_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "remote_config.h"
#include "../User/user.h"
#include "../Local_access/local.h"
#include "../Door/door.h"
#include "../Lights/lights.h"
#include "../../HAL/HC-05/hc_05.h"
#include "../../MCAL/Interrupts/interrupts.h"

s8 msg_buffer[15];
s8 msg_length;
s8 msg_buffer_pointer;
bool remote_user_loggedin;

typedef enum EN_remoteConnStat_t
  {
  REMOTE_INIT_SUCCESSFUL
  }
EN_remoteConnStat_t;

void Remote_init(u32 baudRate);

void println_msg(s8* msg);

void print_msg(s8* msg);

void remote_login_prompt(void);

void invalid_remote_login_attempt(void);

void logout(void);

void grant_local_control_permission(void);

void initial_options_menu(void);

void remote_control(void);

void control_device(void);

void add_user_prompt(void);

void delete_user_prompt(void);
#endif /* REMOTE_H_ */