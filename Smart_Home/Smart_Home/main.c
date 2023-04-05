/*
 * Smart_Home.c
 *
 * Created: 3/25/2023 2:52:47 PM
 * Author : hesha
 */

#include "HAL/LCD/lcd.h"
#include "HAL/Keypad/keypad.h"
#include "HAL/EEPROM/eeprom.h"

int main(void) {
	char* x = "Hesham";
	uint8_t y[7];
	EEPROM_init();
	EEPROM_write_block(0, 0, 7, x);
	DDRD = 0xff;
			EEPROM_read_block(0, 0, 7, y);
	while (1) {
		int i;
		for (i = 0; i < 7; i++) {
			PORTD = y[i];
			_delay_ms(500);
			}

		}
	}

