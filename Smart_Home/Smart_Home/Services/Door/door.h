/*
 * door.h
 *
 * Created: 4/14/2023 6:26:56 AM
 *  Author: Hesham Hany
 */


#ifndef DOOR_H_
#define DOOR_H_

#include "../../HAL/Servo/servo.h"

#define DOOR_OPEN_ANGLE   180
#define DOOR_CLOSE_ANGLE  0

 // Initialize the servo for the door
void Door_init(void);

// Open the door by moving the servo to the open angle
void Door_open(void);

// Close the door by moving the servo to the close angle
void Door_close(void);

#endif /* DOOR_H_ */