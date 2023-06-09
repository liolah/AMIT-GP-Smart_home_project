/*
 * app.c
 *
 * Created: 4/4/2023 9:31:57 AM
 *  Author: Hesham Hany
 */

#include "app.h"

 // Does all the initializations required in the app
void App_init(void) {
  Remote_init(9600);
  Local_access_init();
  Lamps_init();
  Door_init();
  AC_auto_control_service_start();
  Buzzer_init(BUZZER_PORT, BUZZER_PIN);
  sei();

  // Uncomment and use only one time to initialize the DB
  // User_DB_format();

  run_system = true;
  }

// Contains all functionalities and top level logic of the app
void App_start(void) {
  while (run_system) {
    Local_control_input_handler();
    }
  cli();
  // If the invalid attempts are exhausted, the program will halt.
  // The program can halt by returning  and letting it reach the end of main. Or by just entering another infinite loop.
    // Set the alarm
  Buzzer_on(BUZZER_PORT, BUZZER_PIN);
  while (1) {}
  }

