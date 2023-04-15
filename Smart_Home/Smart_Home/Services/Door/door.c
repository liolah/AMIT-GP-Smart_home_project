/*
 * door.c
 *
 * Created: 4/14/2023 6:27:13 AM
 *  Author: hesha
 */

#include "door.h"

 // Initialize the servo for the door
void Door_init(void) {
  Servo_init();
  }

// Open the door by moving the servo to the open angle
void Door_open(void) {
  Servo_move_to_angle(DOOR_OPEN_ANGLE);
  }

// Close the door by moving the servo to the close angle
void Door_close(void) {
  Servo_move_to_angle(DOOR_CLOSE_ANGLE);
  }