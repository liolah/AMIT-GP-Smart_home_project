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
#include "MCAL/ADC/adc.h"
#include "MCAL/Timer/timer.h"

int main(void) {
	set_bit(DDRB, 3);
	PWM_init(OC_0, 0.9, PWM_FAST);
	Timer_start(TIMER_0, 8);
	while (1) {
		// int i;
		// for (i = 0; i < 65535; i++) {
		// 	OCR1A = i;
		// 	_delay_us(10);
		// 	}
		// for (i = 65535; i > 0; i--) {
		// 	OCR1A = i;
		// 	_delay_us(10);
		// 	}

		}
	}

