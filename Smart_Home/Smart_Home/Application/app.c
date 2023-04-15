/*
 * app.c
 *
 * Created: 4/4/2023 9:31:57 AM
 *  Author: Hesham Hany
 */

#include "app.h"

 // Does all the initializations required in the app
void App_init(void) {
  EEPROM_init();
  AC_auto_control_service_start();
  Remote_init(9600);
  Lamps_init();
  Door_init();
  Local_access_init();
  // format_users_db();
  sei();

  INT0_init(RISING_EDGE_INTERRUPT_REQUEST);
  UART_RXC_INT_init();
  run_system = true;
  }

// Contains all functionalities and top level logic of the app
void App_start(void) {
  while (run_system) {
    /* code */
    }

  // If the invalid attempts are exhausted, the program will halt.
  // The program can halt by returning  and letting it reach the end of main. Or by just entering another infinite loop.
  while (1) {}
  }

