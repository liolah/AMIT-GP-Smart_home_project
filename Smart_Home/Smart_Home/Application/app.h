/*
 * app.h
 *
 * Created: 4/4/2023 9:31:45 AM
 *  Author: Hesham Hany
 */

#ifndef APP_H_
#define APP_H_

#include "../Services/AC/ac.h"
#include "../Services/Lights/lights.h"
#include "../Services/Door/door.h"
#include "../Services/User/user.h"
#include "../Services/Local_access/local.h"
#include "../Services/Remote_access/remote.h"

 // Does all the initializations required in the app
void App_init(void);

// Contains all functionalities and top level logic of the app
void App_start(void);

#endif /* APP_H_ */