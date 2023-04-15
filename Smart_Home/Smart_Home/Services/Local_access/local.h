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

void Local_access_init(void);

void Login(void);

void Show_running_devices(void);

void Show_menu(void);

#endif /* LOCAL_H_ */