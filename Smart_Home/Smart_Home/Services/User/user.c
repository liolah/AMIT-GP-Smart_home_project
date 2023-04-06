/*
 * user.c
 *
 * Created: 4/4/2023 9:30:20 AM
 *  Author: hesha
 */

#include "user.h"

EN_UserStatusCode_t search_user(char* user_code_or_name, bool mode, ST_User_t* user) {
  // The mode is used to determine if the search is going to be done user name (remote mode) or user code (local mode). 
  if (REMOTE_MODE) {
    // search by user name
    // In each page 
    uint8_t page, userIndex, usersBlockStatus, usersAuthorityLevel;
    char tempUserName[13];
    char tempUserCode[7];
    char tempUserPassword[7];
    for (page = 0; page < 8; page++) {
      // Read the first two bytes to see which users are deleted and what blocks to search in. Also save the authority level in case the user was found.
      EEPROM_read_byte(page, 0, usersBlockStatus);
      EEPROM_read_byte(page, 1, usersAuthorityLevel);
      for (userIndex = 0; userIndex < 8;userIndex++) {
        if (read_bit(usersBlockStatus, userIndex)) {  // If the user isn't deleted
          EEPROM_read_block(page, 8 + 31 * userIndex, 13, tempUserName);
          if (strcmp(user_code_or_name, tempUserName) == 0) { // User has been found
            EEPROM_read_block(page, 21 + 31 * userIndex, 7, tempUserCode);
            EEPROM_read_block(page, 28 + 31 * userIndex, 7, tempUserPassword);
            user->isAdmin = read_bit(usersAuthorityLevel, userIndex);
            strcpy(user->user_name, tempUserName);
            strcpy(user->user_code, tempUserCode);
            strcpy(user->password, tempUserPassword);
            return USER_FOUND;
            }
          }
        }
      }
    user = NULL;
    return USER_NOT_FOUND;
    }
  else {
    // search by user code
    // In each page 
    uint8_t page, userIndex, usersBlockStatus, usersAuthorityLevel;
    char tempUserName[13];
    char tempUserCode[7];
    char tempUserPassword[7];
    for (page = 0; page < 8; page++) {
      // Read the first two bytes to see which users are deleted and what blocks to search in. Also save the authority level in case the user was found.
      EEPROM_read_byte(page, 0, usersBlockStatus);
      EEPROM_read_byte(page, 1, usersAuthorityLevel);
      for (userIndex = 0; userIndex < 8;userIndex++) {
        if (read_bit(usersBlockStatus, userIndex)) {  // If the user isn't deleted
          EEPROM_read_block(page, 21 + 31 * userIndex, 7, tempUserCode);
          if (strcmp(user_code_or_name, tempUserCode) == 0) { // User has been found
            EEPROM_read_block(page, 8 + 31 * userIndex, 13, tempUserName);
            EEPROM_read_block(page, 28 + 31 * userIndex, 7, tempUserPassword);
            user->isAdmin = read_bit(usersAuthorityLevel, userIndex);
            strcpy(user->user_name, tempUserName);
            strcpy(user->user_code, tempUserCode);
            strcpy(user->password, tempUserPassword);
            return USER_FOUND;
            }
          }
        }
      }
    user = NULL;
    return USER_NOT_FOUND;
    }
  }

bool validate_user_password(ST_User_t* user, char* password) {
  return (strcmp(user->password, password) == 0);
  }

void invalid_login_attempt(void) {
  invalid_trails++;
  if (invalid_trails < 3) {
    return;
    }
  set_alarm();
  }

void set_alarm(void) {
  Buzzer_on(BUZZER_PORT, BUZZER_PIN);
  }