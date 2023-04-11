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
#include "MCAL/Timer/timer.h"
#include "Services/User/user.h"
#include "Services/Remote_access/remote.h"

int main(void) {
	u8 x = sizeof(short int);
	u8 y = sizeof(short);
	DDRA = x;
	DDRB = y;
	UART_init(y);

	while (1) {
		test();
		_delay_ms(1000);

		// int i;
		// for (i = 0; i < 185; i += 5)
		// {
		// 	servo_move_to_angle(i);
		// 	_delay_ms(100);
		// 	}
		// for (i = 180; i >= 0; i -= 5)
		// {
		// 	servo_move_to_angle(i);
		// 	_delay_ms(100);
		// }
		// servo_move_to_angle(0);
		// 	_delay_ms(500);
		// servo_move_to_angle(90);
		// 	_delay_ms(500);
		// servo_move_to_angle(180);
		// 	_delay_ms(500);
		}
	}

