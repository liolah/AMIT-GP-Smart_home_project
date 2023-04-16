/*
 * local.h
 *
 * Created: 4/12/2023 7:25:19 AM
 *  Author: Hesham Hany
 */ 


#ifndef LOCAL_H_
#define LOCAL_H_

#include "../../HAL/LCD/lcd.h"
#include "../../HAL/Keypad/keypad.h"
#include "../../Services/User/user.h"

#define MENU_NUMBERED_OPTIONS_SEPARATOR_STYLE ')'

#define OPTIONS_MENU_1 "1)\x7F 2)Login  3)\x7E"
#define OPTIONS_MENU_2 "1)\x7F      2)Login"
#define OPTIONS_MENU_3 "1)Login      2)\x7E"
#define OPTIONS_MENU_4 "1)\x7F 2)Toggle 3)\x7E"
#define OPTIONS_MENU_5 "1)\x7F   2)On   3)\x7E"
#define OPTIONS_MENU_6 "1)\x7F  2)Off   3)\x7E"
#define OPTIONS_MENU_7 "1)On         2)\x7E"
#define OPTIONS_MENU_8 "1)Off        2)\x7E"
#define OPTIONS_MENU_9 "1)\x7F   2)+    3)-"

#define BACKSPACE_OPTION "1)<x"
#define ENTER_OPTION "2)Ok"




void Local_access_init(void);

bool running_devices[7];

void Login(void);

void Show_running_devices(u8 screen);

void Get_running_devices(void);

void Show_LCD_menu(void);

#endif /* LOCAL_H_ */