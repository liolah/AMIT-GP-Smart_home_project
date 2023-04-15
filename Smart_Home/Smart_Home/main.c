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

u16 temperature;
 // #include "Application/app.h"
ISR(ADC_vect) {
	temperature = (u16)ADCL;
	temperature += ((u16)ADCH << 8);
	DIO_toggle(1, 'B');
	// set_bit(TIFR, TOV1);
	set_bit(TIFR, OCF0);
	}

// ISR(TIMER1_OVF_vect) {
// 	// PORTB = PORTB - 1;
// 	DIO_toggle(7, 'D');
// 	}
ISR(TIMER0_COMP_vect) {
	// PORTB = PORTB - 1;
	DIO_toggle(7, 'D');
	}
int main(void) {
	// PWM_init(OC_1A, 0.5, PWM_PHASE_CORRECT);
	// DIO_init(5, PORT_D, OUT);
	// Timer_start(TIMER_1, 8);
	sei();
	DIO_init(7, PORT_A, IN);
	DIO_init(7, PORT_D, OUT);
	
	set_bit(TCCR0, WGM01);
	OCR0 = 255;
	set_bit(TCCR0, CS00);
	set_bit(TCCR0, CS02);
	// set_bit(TCCR1B, CS10);

	// set_bit(TIMSK, TOIE1);
	set_bit(TIMSK, OCIE0);
	
	set_bit(ADMUX, REFS0);
	set_bit(ADMUX, REFS1);

	set_bit(ADCSRA, ADPS0);
	set_bit(ADCSRA, ADPS1);
	set_bit(ADCSRA, ADPS2);
	// Enable the auto trigger mode
	set_bit(ADCSRA, ADATE);
	
	SFIOR |= (1 << ADTS0) | (1 << ADTS1);
	// SFIOR |= (1 << ADTS2) | (1 << ADTS1);
	// set_bit(SFIOR, ADTS2);

	ADMUX = (ADMUX & 0xE0) | 7;

	set_bit(ADCSRA, ADIE);
	set_bit(ADCSRA, ADEN);

	DIO_init(1, 'B', OUT);
	// AC_init();
	// Remote_init(9600);
	// DIO_init(3, PORT_D, OUT);
	// INT0_init(RISING_EDGE_INTERRUPT_REQUEST);
	// UART_RXC_INT_init();
	// App_init();

	while (1) {
		
		// App_start();
		
		}
	}

