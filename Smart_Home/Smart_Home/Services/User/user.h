/*
 * user.h
 *
 * Created: 4/4/2023 9:30:10 AM
 *  Author: Hesham Hany
 */


#ifndef USER_H_
#define USER_H_

#include <stdbool.h>
#include <string.h>
#include "../../HAL/EEPROM/eeprom.h"
#include "../../HAL/Buzzer/buzzer.h"

#define REMOTE_MODE 0
#define LOCAL_MODE  1

bool remote_user_loggedin;

bool local_user_loggedin;

// When both an admin remote user and a local user are connected to the system, the local user has to get a permission from the admin to be able to control the system at the same time.
bool local_control_permission_granted;

bool run_system;

u8 invalid_trails;

typedef struct ST_User_t
  {
  bool isAdmin;
  s8 name[13];
  s8 code[7];
  s8 password[11];
  } ST_User_t;

typedef enum EN_UserStatusCode_t
  {
  LOGIN_SUCCESSFUL, LOGIN_FAILED, USER_FOUND, USER_NOT_FOUND, WRONG_USERNAME, WRONG_PASSWORD, WRONG_USERCODE, LOGOUT_SUCCESSFUL, DB_INIT_SUCCESSFUL, USERS_DB_FORMATTED_SUCCESSFULLY, USER_ADDED_SUCCESSFULLY, USER_DELETED_SUCCESSFULLY, ERROR_FULL_DB
  } EN_UserStatusCode_t;

EN_UserStatusCode_t User_DB_init(void);

EN_UserStatusCode_t getUserByName(s8* userName, ST_User_t* user);

EN_UserStatusCode_t getUserByCode(s8* userCode, ST_User_t* user);

EN_UserStatusCode_t add_user(ST_User_t* user);

EN_UserStatusCode_t delete_user(ST_User_t* user);

// Searches for the user by the username. user is null if the user isn't found 
EN_UserStatusCode_t user_search(s8* user_code_or_name, bool mode, ST_User_t* user);

void invalid_remote_login_attempt(void);

//*******************************************************
//! One time run functions 
//*******************************************************
// This functions clears all data on the EEPROM
// The users are saved on the EEPROM as follows:
// Each page can store up to 8 users (each user requires 32 bytes and the page size is 256 bytes).
// The first eight bytes of each page are reserved.
// The first bytes is used to save the status of each user location (exists or available to overwrite(deleted)) using bit masking. Each bit is used to save a user location state. 0 = deleted, 1 = exists
// The second bytes is used to save the authority of each user (admin or not) using bit masking.0 = normal user, 1 = admin
// The other six bytes are reserved unused. 
// Excluding the isAdmin flag, each user needs 31 bytes to be stored. Starting from bytes 9. The users are stored one after each other.
//? It also creates the first admin user. username: admin, userCode: 000000, password: 1234
EN_UserStatusCode_t User_DB_format(void);

#endif /* USER_H_ */