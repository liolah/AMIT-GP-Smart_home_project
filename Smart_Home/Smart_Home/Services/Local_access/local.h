/*
 * local.h
 *
 * Created: 4/12/2023 7:25:19 AM
 *  Author: Hesham Hany
 */


#ifndef LOCAL_H_
#define LOCAL_H_

#include "../../HAL/LCD/lcd.h"
#include <stdio.h>
#include "../../HAL/Keypad/keypad.h"
#include "../../Services/User/user.h"
#include "../../Services/Lights/lights.h"
#include "../../Services/Remote_access/remote.h"

#define OPTIONS_MENU_1 "1)\x7F 2)Login  3)\x7E"
#define OPTIONS_MENU_2 "1)\x7F      2)Login"
#define OPTIONS_MENU_3 "2)Login      3)\x7E"
#define OPTIONS_MENU_4 "1)\x7F 2)Toggle 3)\x7E"
#define OPTIONS_MENU_5 "1)\x7F   2)On   3)\x7E"
#define OPTIONS_MENU_6 "1)\x7F  2)Off   3)\x7E"
#define OPTIONS_MENU_7 "2)On         3)\x7E"
#define OPTIONS_MENU_8 "2)Off        3)\x7E"
#define OPTIONS_MENU_9 "1)\x7F   2)+    3)-"

#define BACKSPACE_OPTION "-)<X"
#define ENTER_OPTION "=)Ok"

#define LAMP_6_BRIGHTNESS_PERCENTAGE_STEP 10

bool running_devices[7];

// Initialize the local control system
void Local_access_init(void);

// Used in the super loop for getting the user input and handling it.
void Local_control_input_handler(void);

// Updates the logical states (in/off) of the running devices' array 
void Get_running_devices(void);

// Updates the device status array, which has lamp 6 brightness level 
void Get_devices_status(void);

// Shows the bottom line options on the LCD
void Show_bottom_options_menu(u8 menu);

// Shows the side options list on the LCD
void Show_side_options_menu(void);

// Shows the currently running devices with the appropriate control menu appended (Screen controls and login- no device controls)
void Show_running_devices(u8 screen);

// Shows the currently running devices with the appropriate control menu appended (Devices' controls)
void Show_devices_controls(u8 screen);

// Handles setting the alarm and halting the system when the user enters invalid credentials during login
void invalid_local_login_attempt(void);

#endif /* LOCAL_H_ */