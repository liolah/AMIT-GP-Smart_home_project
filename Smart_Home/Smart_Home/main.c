/*
 * Smart_Home.c
 *
 * Created: 3/25/2023 2:52:47 PM
 * Author : hesha
 */ 

#include "HAL/LCD/lcd.h"
#include "HAL/Keypad/keypad.h"
#include "MCAL/I2C/I2C.h"

int main(void)
{
	I2C_init();
	DDRD = 0xff;
	while (1)
	{
		I2C_start(0x20);
		I2C_write(0x55);
		I2C_repeatedStart(0x22);
		I2C_write(0xBB);
		I2C_stop();
		PORTD = 0;
		_delay_ms(500);
		PORTD = 0xff;
		_delay_ms(500);
	}
}

