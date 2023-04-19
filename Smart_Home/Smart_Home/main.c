/*
 * Smart_Home.c
 *
 * Created: 3/25/2023 2:52:47 PM
 * Author : Hesham Hany
 */

#include "Application/app.h"
// #include "Services/Local_access/local.h"

int main(void) {
	// Remote_init(9600);
	Lamps_init();
	Door_init();
	Local_access_init();
	// App_init();
	sei();
	// App_start();
	
	while (1) {
		Local_control_input_handler();
		}
	}

