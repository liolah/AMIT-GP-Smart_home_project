/*
 * Smart_Home.c
 *
 * Created: 3/25/2023 2:52:47 PM
 * Author : Hesham Hany
 */

#include "Application/app.h"

int main(void) {
	Local_access_init();
	run_system = true;
	Lamps_init();
	// App_init();

	// App_start();
	while (run_system) {
		Local_control_input_handler();
		}
	}

