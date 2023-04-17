/*
 * keypad.c
 *
 * Created: 3/26/2023 5:06:37 PM
 *  Author: Hesham Hany
 */

#include "keypad.h"

EN_KeypadStatusCode_t Keypad_init(void) {
  // Set rows as outputs
  DIO_init(KEYPAD_R0_PIN, KEYPAD_PORT, OUT);
  DIO_init(KEYPAD_R1_PIN, KEYPAD_PORT, OUT);
  DIO_init(KEYPAD_R2_PIN, KEYPAD_PORT, OUT);
  DIO_init(KEYPAD_R3_PIN, KEYPAD_PORT, OUT);
  // Set all high
  DIO_write(KEYPAD_R0_PIN, KEYPAD_PORT, HIGH);
  DIO_write(KEYPAD_R1_PIN, KEYPAD_PORT, HIGH);
  DIO_write(KEYPAD_R2_PIN, KEYPAD_PORT, HIGH);
  DIO_write(KEYPAD_R3_PIN, KEYPAD_PORT, HIGH);
  // Set columns as inputs
  DIO_init(KEYPAD_C0_PIN, KEYPAD_PORT, IN);
  DIO_init(KEYPAD_C1_PIN, KEYPAD_PORT, IN);
  DIO_init(KEYPAD_C2_PIN, KEYPAD_PORT, IN);
  DIO_init(KEYPAD_C3_PIN, KEYPAD_PORT, IN);
  // Activate the pull up resistors
  DIO_write(KEYPAD_C0_PIN, KEYPAD_PORT, HIGH);
  DIO_write(KEYPAD_C1_PIN, KEYPAD_PORT, HIGH);
  DIO_write(KEYPAD_C2_PIN, KEYPAD_PORT, HIGH);
  DIO_write(KEYPAD_C3_PIN, KEYPAD_PORT, HIGH);

  return KEYPAD_INIT_OK;
  }

void toggle_row(u8 row) {
  switch (row) {
      case 0:
        DIO_toggle(KEYPAD_R0_PIN, KEYPAD_PORT);
        break;
      case 1:
        DIO_toggle(KEYPAD_R1_PIN, KEYPAD_PORT);
        break;
      case 2:
        DIO_toggle(KEYPAD_R2_PIN, KEYPAD_PORT);
        break;
      case 3:
        DIO_toggle(KEYPAD_R3_PIN, KEYPAD_PORT);
        break;
    }
  }

void check_col(u8 col, u8* res) {
  switch (col) {
      case 0:
        DIO_Read(KEYPAD_C0_PIN, KEYPAD_PORT, res);
        break;
      case 1:
        DIO_Read(KEYPAD_C1_PIN, KEYPAD_PORT, res);
        break;
      case 2:
        DIO_Read(KEYPAD_C2_PIN, KEYPAD_PORT, res);
        break;
      case 3:
        DIO_Read(KEYPAD_C3_PIN, KEYPAD_PORT, res);
        break;
    }
  }

void check_row(u8 row, u8* res) {
  switch (row) {
      case 0:
        DIO_Read(KEYPAD_R0_PIN, KEYPAD_PORT, res);
        break;
      case 1:
        DIO_Read(KEYPAD_R1_PIN, KEYPAD_PORT, res);
        break;
      case 2:
        DIO_Read(KEYPAD_R2_PIN, KEYPAD_PORT, res);
        break;
      case 3:
        DIO_Read(KEYPAD_R3_PIN, KEYPAD_PORT, res);
        break;
    }
  }

EN_KeypadStatusCode_t Keypad_getPressedKey(u8* key) {
  u8 keys[KEYPAD_ROW_NUM][KEYPAD_COL_NUM] = KEYPAD_BUTTON_VALUES;
  u8 row, col, col_state, row_state;
  // Check if the key has been depressed. If not return no presses.
  for (row = 0;row < KEYPAD_ROW_NUM; row++) {
    check_row(row, &row_state);
    if (row_state == LOW) {
      for (col = 0; col < KEYPAD_COL_NUM; col++) {
        check_col(col, &col_state);
        if (col_state == LOW) {
          return NO_KEY_PRESSED;
          }
        }
      toggle_row(row);
      }
    }
  for (row = 0; row < KEYPAD_ROW_NUM; row++) {
    toggle_row(row);
    for (col = 0; col < KEYPAD_COL_NUM; col++) {
      check_col(col, &col_state);
      if (col_state == LOW) {
        // while (col_state == LOW) {  // Wait until the key is released (busy waiting - halts the system)
        //   check_col(col, &col_state);
        //   }
        *key = keys[row][col];
        return KEY_PRESSED;
        }
      }
    toggle_row(row);
    }
  return NO_KEY_PRESSED;
  }