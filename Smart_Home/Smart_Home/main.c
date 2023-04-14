/*
 * Smart_Home.c
 *
 * Created: 3/25/2023 2:52:47 PM
 * Author : hesha
 */

#include <string.h>
#include <stdio.h>
// #include "HAL/LCD/lcd.h"
// #include "HAL/Keypad/keypad.h"
// #include "HAL/EEPROM/eeprom.h"
// #include "HAL/Servo/servo.h"
// #include "MCAL/ADC/adc.h"
// #include "MCAL/UART/uart.h"
#include "MCAL/DIO/dio.h"
#include "MCAL/Interrupts/interrupts.h"
// #include "MCAL/Timer/timer.h"
// #include "Services/User/user.h"
// #include "Services/Remote_access/remote.h"
// #include "Services/User/user.h"
// #include "Services/Remote_access/remote.h"

// #include "Application/app.h"
ISR(INT0_vect) {
	// Initialize communication with the user
	// Request user login credentials
	// remote_login_prompt();
	DIO_toggle(3, PORT_D);
	}

int main(void) {
	// set_bit(MCUCR, ISC00);
	// set_bit(MCUCR, ISC01);
	// // Enabling interrupts on INT0
	// set_bit(GICR, INT0);

	INT0_init(RISING_EDGE_INTERRUPT_REQUEST);
	
	DIO_init(2, PORT_D, IN);
	DIO_init(3, PORT_D, OUT);
	// INT0_init(RISING_EDGE_INTERRUPT_REQUEST);
	// UART_RXC_INT_init();
	sei();
	// App_init();

	while (1) {

		// App_start();
		
		}
	}

