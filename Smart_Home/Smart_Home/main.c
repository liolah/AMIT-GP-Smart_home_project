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
	set_bit(DDRD, 5);
	set_bit(DDRD, 4);

	PWM_init(OC_1A, 0.3, PWM_PHASE_CORRECT);
	PWM_init(OC_1B, 0.7, PWM_PHASE_CORRECT);

	Timer_start(TIMER_1, 8);
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

