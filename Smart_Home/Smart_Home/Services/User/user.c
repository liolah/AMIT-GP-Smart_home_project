/*
 * user.c
 *
 * Created: 4/4/2023 9:30:20 AM
 *  Author: hesha
 */

#include "user.h"

bool remote_user_loggedin = false;
bool local_user_loggedin = false;

uint8_t invalid_trails = 0;

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
      EEPROM_read_byte(page, 0, &usersBlockStatus);
      EEPROM_read_byte(page, 1, &usersAuthorityLevel);
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
      EEPROM_read_byte(page, 0, &usersBlockStatus);
      EEPROM_read_byte(page, 1, &usersAuthorityLevel);
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

void eeprom_fill_zeroes(void) {
  uint8_t page;
  uint16_t byte;
  char zeroes[16] = { 0 };
  for (page = 0; page < 8;page++) {
    for (byte = 0; byte < 256; byte += 16) {
      EEPROM_write_block(page, byte, 16, zeroes);
      }
    }
  }

void write_first_user(void) {
  // Write that the first user block is in use
  EEPROM_write_byte(0, 0, 1);
  // Wite that the first user's an admin
  EEPROM_write_byte(0, 1, 1);
  char name[13] = "admin";
  char code[7] = "000000";
  char password[11] = "123456";
  EEPROM_write_block(0, 2, 13, name);
  EEPROM_write_block(0, 15, 7, code);
  EEPROM_write_block(0, 22, 11, password);
  }

EN_UserStatusCode_t format_users_db(void) {
  eeprom_fill_zeroes();
  write_first_user();
  return USERS_DB_FORMATTED_SUCCESSFULLY;
  }
