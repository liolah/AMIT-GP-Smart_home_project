/*
 * app.h
 *
 * Created: 4/4/2023 9:31:45 AM
 *  Author: hesha
 */ 


#ifndef APP_H_
#define APP_H_

#include "../Services/User/user.h"
#include "../Services/Remote_access/remote.h"
#include "../Services/Local_control/local.h"

// Does all the initializations required in the app
void App_init(void);

// Contains all functionalities and top level logic of the app
void App_start(void);

#endif /* APP_H_ */