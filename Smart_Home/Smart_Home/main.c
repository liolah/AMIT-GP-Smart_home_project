/*
 * Smart_Home.c
 *
 * Created: 3/25/2023 2:52:47 PM
 * Author : Hesham Hany
 */

#include "Application/app.h"

int main(void) {
	Remote_init(9600);
	Lamps_init();
	Door_init();
	// App_init();

	// App_start();
	while (1) {
		
		}
	}

