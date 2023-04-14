/*
 * Smart_Home.c
 *
 * Created: 3/25/2023 2:52:47 PM
 * Author : hesha
 */

#include <string.h>
#include <stdio.h>
#include "HAL/LCD/lcd.h"
#include "HAL/Keypad/keypad.h"
#include "HAL/EEPROM/eeprom.h"
#include "HAL/Servo/servo.h"
#include "MCAL/ADC/adc.h"
#include "MCAL/UART/uart.h"
#include "MCAL/Timer/timer.h"
#include "Services/User/user.h"
#include "Services/AC/ac.h"
#include "Services/User/user.h"
#include "Services/Remote_access/remote.h"

// #include "Application/app.h"

int main(void) {
	PWM_init(OC_1A, 0.5, PWM_PHASE_CORRECT);
	Timer_start(TIMER_1, 8);
	Timer_CTC_init(TIMER_0, 230);
	Timer_start(TIMER_0, 1024);
	DDRB = 0xff;
	AC_init();
	// Remote_init(9600);
	// DIO_init(3, PORT_D, OUT);
	// INT0_init(RISING_EDGE_INTERRUPT_REQUEST);
	// UART_RXC_INT_init();
	sei();
	// App_init();

	while (1) {

		// App_start();
		
		}
	}

