/*
 * keypad.h
 *
 * Created: 3/26/2023 5:06:30 PM
 *  Author: Hesham Hany
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../MCAL/DIO/dio.h"

#define KEYPAD_DDR        PORT_B
#define KEYPAD_PORT         PORT_B
#define KEYPAD_R0_PIN       0
#define KEYPAD_R1_PIN       1
#define KEYPAD_R2_PIN       2
#define KEYPAD_R3_PIN       3
#define KEYPAD_C0_PIN       4
#define KEYPAD_C1_PIN       5
#define KEYPAD_C2_PIN       6
#define KEYPAD_C3_PIN       7

#define KEYPAD_BUTTON_VALUES  {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'#','0','=','+'}}

#define KEYPAD_ROW_NUM  4
#define KEYPAD_COL_NUM  4

#define KEYPAD_NO_PRESSED_KEY_VALUE  0xFF

typedef enum EN_KeypadStatusCode_t
  {
  KEYPAD_INIT_OK, KEY_PRESSED, NO_KEY_PRESSED
  } EN_KeypadStatusCode_t;

EN_KeypadStatusCode_t Keypad_init(void);

EN_KeypadStatusCode_t Keypad_getPressedKey(u8* key);

#endif /* KEYPAD_H_ */