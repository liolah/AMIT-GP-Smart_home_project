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

int main(void) {
	servo_init();
	while (1) {
		int i;
		for (i = 0; i < 185; i += 5)
		{
			servo_move_to_angle(i);
			_delay_ms(20);
			}
		for (i = 180; i >= 0; i -= 5)
		{
			servo_move_to_angle(i);
			_delay_ms(20);
		}
		}
	}

