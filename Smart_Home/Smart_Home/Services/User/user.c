/*
 * user.c
 *
 * Created: 4/4/2023 9:30:20 AM
 *  Author: Hesham Hany
 */

#include "user.h"

EN_UserStatusCode_t User_DB_init(void) {
  EEPROM_init();
  return DB_INIT_SUCCESSFUL;
  }

EN_UserStatusCode_t getUserByName(s8* userName, ST_User_t* user) {
  // search by user name
    // In each page 
  u8 page, userIndex, usersBlockStatus, usersAuthorityLevel;
  s8 tempUserName[13];
  s8 tempUserCode[7];
  s8 tempUserPassword[7];
  for (page = 0; page < 8; page++) {
    // Read the first two bytes to see which users are deleted and what blocks to search in. Also save the authority level in case the user was found.
    EEPROM_read_byte(page, 0, &usersBlockStatus);
    EEPROM_read_byte(page, 1, &usersAuthorityLevel);
    for (userIndex = 0; userIndex < 8;userIndex++) {
      if (read_bit(usersBlockStatus, userIndex)) {  // If the user isn't deleted
        EEPROM_read_block(page, 8 + 31 * userIndex, 13, tempUserName);
        if (strcmp(userName, tempUserName) == 0) { // User has been found
          EEPROM_read_block(page, 21 + 31 * userIndex, 7, tempUserCode);
          EEPROM_read_block(page, 28 + 31 * userIndex, 7, tempUserPassword);
          user->isAdmin = read_bit(usersAuthorityLevel, userIndex);
          strcpy(user->name, tempUserName);
          strcpy(user->code, tempUserCode);
          strcpy(user->password, tempUserPassword);
          return USER_FOUND;
          }
        }
      }
    }
  user = NULL;
  return USER_NOT_FOUND;
  }

EN_UserStatusCode_t getUserByCode(s8* userCode, ST_User_t* user) {
  // search by user code
   // In each page 
  u8 page, userIndex, usersBlockStatus, usersAuthorityLevel;
  s8 tempUserName[13];
  s8 tempUserCode[7];
  s8 tempUserPassword[7];
  for (page = 0; page < 8; page++) {
    // Read the first two bytes to see which users are deleted and what blocks to search in. Also save the authority level in case the user was found.
    EEPROM_read_byte(page, 0, &usersBlockStatus);
    EEPROM_read_byte(page, 1, &usersAuthorityLevel);
    for (userIndex = 0; userIndex < 8;userIndex++) {
      if (read_bit(usersBlockStatus, userIndex)) {  // If the user isn't deleted
        EEPROM_read_block(page, 21 + 31 * userIndex, 7, tempUserCode);
        if (strcmp(userCode, tempUserCode) == 0) { // User has been found
          EEPROM_read_block(page, 8 + 31 * userIndex, 13, tempUserName);
          EEPROM_read_block(page, 28 + 31 * userIndex, 7, tempUserPassword);
          user->isAdmin = read_bit(usersAuthorityLevel, userIndex);
          strcpy(user->name, tempUserName);
          strcpy(user->code, tempUserCode);
          strcpy(user->password, tempUserPassword);
          return USER_FOUND;
          }
        }
      }
    }
  user = NULL;
  return USER_NOT_FOUND;
  }

EN_UserStatusCode_t user_search(s8* user_code_or_name, bool mode, ST_User_t* user) {
  // The mode is used to determine if the search is going to be done user name (remote mode) or user code (local mode). 
  if (REMOTE_MODE) {
    return getUserByName(user_code_or_name, user);
    }
  else {
    return getUserByCode(user_code_or_name, user);
    }
  }

void Alarm_set(void) {
  Buzzer_init(BUZZER_PORT, BUZZER_PIN);
  Buzzer_on(BUZZER_PORT, BUZZER_PIN);
  }

void write_user(u8 userBlockIndex, ST_User_t* user) {
  // Get the user block location (page - index)
  u8 page = userBlockIndex / 8;
  u8 blockNumber = userBlockIndex % 8;
  // Read and update the block status (reserve the block). And update the user authority level flag if the user is admin
  u8 usersBlockStatus, usersAuthorityLevel;
  EEPROM_read_byte(page, 0, &usersBlockStatus);
  EEPROM_read_byte(page, 1, &usersAuthorityLevel);
  set_bit(usersBlockStatus, blockNumber);
  if (user->isAdmin) set_bit(usersAuthorityLevel, blockNumber);
  EEPROM_write_byte(page, 0, usersBlockStatus);
  EEPROM_write_byte(page, 1, usersAuthorityLevel);
  // Write the user data
  EEPROM_write_block(page, 8 + 31 * blockNumber, 13, user->name);
  EEPROM_write_block(page, 21 + 31 * blockNumber, 7, user->code);
  EEPROM_write_block(page, 28 + 31 * blockNumber, 11, user->password);
  }

EN_UserStatusCode_t add_user(ST_User_t* user) {
  // Find an empty location to write the user data
  u8 page, usersBlockStatus, availableUserBlockIndex = 0;
  for (page = 0; page < 8; page++) {
    EEPROM_read_byte(page, 0, &usersBlockStatus);
    if (usersBlockStatus != 0xFF) {
      // Find the block number in the page
      while (read_bit(usersBlockStatus, availableUserBlockIndex) != 0) availableUserBlockIndex++;
      break;
      }
    }
  // If no location is found return error
  if (page == 8) return ERROR_FULL_DB;
  // Save the user to the EEPROM
  availableUserBlockIndex += (page * 8);
  write_user(availableUserBlockIndex, user);
  return USER_ADDED_SUCCESSFULLY;
  }

EN_UserStatusCode_t delete_user(ST_User_t* user) {
  // Find the user block index
  u8 page, userIndex, usersBlockStatus, usersAuthorityLevel;
  // Comparing the user code is slightly more efficient because it's shorter
  s8 tempUserCode[7];
  for (page = 0; page < 8; page++) {
    // Read the first two bytes to see which users are deleted and what blocks to search in. Also save the authority level in case the user was found.
    EEPROM_read_byte(page, 0, &usersBlockStatus);
    EEPROM_read_byte(page, 1, &usersAuthorityLevel);
    for (userIndex = 0; userIndex < 8;userIndex++) {
      if (read_bit(usersBlockStatus, userIndex)) {  // If the user isn't deleted
        EEPROM_read_block(page, 21 + 31 * userIndex, 7, tempUserCode);
        if (strcmp(user->code, tempUserCode) == 0) { // User has been found
          // Mark it as deleted
          clear_bit(usersBlockStatus, userIndex);
          clear_bit(usersAuthorityLevel, userIndex);
          EEPROM_write_byte(page, 0, usersBlockStatus);
          EEPROM_write_byte(page, 1, usersAuthorityLevel);
          return USER_DELETED_SUCCESSFULLY;
          }
        }
      }
    }
  return USER_NOT_FOUND;
  }

// *****************************************************
// DB initialization functions
// *****************************************************
void EEPROM_fill_zeroes(void) {
  u8 page;
  u16 byte;
  s8 zeroes[16] = { 0 };
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
  s8 name[13] = "admin";
  s8 code[7] = "000000";
  s8 password[11] = "123456";
  EEPROM_write_block(0, 8, 13, name);
  EEPROM_write_block(0, 21, 7, code);
  EEPROM_write_block(0, 28, 11, password);
  }

EN_UserStatusCode_t User_DB_format(void) {
  EEPROM_fill_zeroes();
  write_first_user();
  return USERS_DB_FORMATTED_SUCCESSFULLY;
  }
