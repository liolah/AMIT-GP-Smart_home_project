/*
 * user.h
 *
 * Created: 4/4/2023 9:30:10 AM
 *  Author: hesha
 */ 


#ifndef USER_H_
#define USER_H_

#include <stdbool.h>
#include "../../HAL/EEPROM/eeprom.h"

typedef struct ST_User_t
{
  bool isAdmin;
  char user_code[7];
  char user_name[13];
  char password[11];
  } ST_User_t;

bool remote_user_loggedin = false;
bool local_user_loggedin = false;

uint8_t invalid_trails = 0;

void login_remote();

void login_normal();

void logout_remote();

void logout_normal();

// TODO: Add status code enum

void save_new_user(ST_User_t user);

void invalid_login_attempt();

void set_alarm();

#endif /* USER_H_ */