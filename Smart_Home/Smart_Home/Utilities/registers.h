/*
 * registers.h
 *
 * Created: 3/25/2023 3:16:48 PM
 *  Author: hesha
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "types.h"

// *********************************************************
// DIO Registers
// *********************************************************
// PORTA registers
#define PORTA *((volatile uint8_t*)0x3B)  // 8-bit register
#define PORTA7  7
#define PORTA6  6
#define PORTA5  5
#define PORTA4  4
#define PORTA3  3
#define PORTA2  2
#define PORTA1  1
#define PORTA0  0

#define DDRA *((volatile uint8_t*)0x3A)  // 8-bit register
#define DDRA7   7
#define DDRA6   6
#define DDRA5   5
#define DDRA4   4
#define DDRA3   3
#define DDRA2   2
#define DDRA1   1
#define DDRA0   0

#define PINA *((volatile uint8_t*)0x39)  // 8-bit register
#define PINA7   7
#define PINA6   6
#define PINA5   5
#define PINA4   4
#define PINA3   3
#define PINA2   2
#define PINA1   1
#define PINA0   0

// PORTB registers
#define PORTB *((volatile uint8_t*)0x38)  // 8-bit register
#define PORTB7  7
#define PORTB6  6
#define PORTB5  5
#define PORTB4  4
#define PORTB3  3
#define PORTB2  2
#define PORTB1  1
#define PORTB0  0

#define DDRB *((volatile uint8_t*)0x37)  // 8-bit register
#define DDRB7   7
#define DDRB6   6
#define DDRB5   5
#define DDRB4   4
#define DDRB3   3
#define DDRB2   2
#define DDRB1   1
#define DDRB0   0

#define PINB *((volatile uint8_t*)0x36)  // 8-bit register
#define PINB7   7
#define PINB6   6
#define PINB5   5
#define PINB4   4
#define PINB3   3
#define PINB2   2
#define PINB1   1
#define PINB0   0

// PORTC registers
#define PORTC *((volatile uint8_t*)0x35)  // 8-bit register
#define PORTC7  7
#define PORTC6  6
#define PORTC5  5
#define PORTC4  4
#define PORTC3  3
#define PORTC2  2
#define PORTC1  1
#define PORTC0  0

#define DDRC *((volatile uint8_t*)0x34)  // 8-bit register
#define DDRC7   7
#define DDRC6   6
#define DDRC5   5
#define DDRC4   4
#define DDRC3   3
#define DDRC2   2
#define DDRC1   1
#define DDRC0   0

#define PINC *((volatile uint8_t*)0x33)  // 8-bit register
#define PINC7   7
#define PINC6   6
#define PINC5   5
#define PINC4   4
#define PINC3   3
#define PINC2   2
#define PINC1   1
#define PINC0   0

// PORTD registers
#define PORTD *((volatile uint8_t*)0x32)  // 8-bit register
#define PORTD7  7
#define PORTD6  6
#define PORTD5  5
#define PORTD4  4
#define PORTD3  3
#define PORTD2  2
#define PORTD1  1
#define PORTD0  0

#define DDRD *((volatile uint8_t*)0x31)  // 8-bit register
#define DDRD7   7
#define DDRD6   6
#define DDRD5   5
#define DDRD4   4
#define DDRD3   3
#define DDRD2   2
#define DDRD1   1
#define DDRD0   0

#define PIND *((volatile uint8_t*)0x30)  // 8-bit register
#define PIND7   7
#define PIND6   6
#define PIND5   5
#define PIND4   4
#define PIND3   3
#define PIND2   2
#define PIND1   1
#define PIND0   0

// *********************************************************
// Timer Registers
// *********************************************************
// Output compare registers
#define OCR0    *((volatile uint8_t*)0x5C)  // 8-bit register
#define OCR1A   *((volatile uint16_t*)0x4A)  // 16-bit register
#define OCR1B   *((volatile uint16_t*)0x48)  // 16-bit register
#define OCR2    *((volatile uint8_t*)0x43)  // 8-bit register

// Timer/Counter registers
#define TCNT0   *((volatile uint8_t*)0x52)  // 8-bit register
#define TCNT1   *((volatile uint16_t*)0x4C)  // 16-bit register
#define TCNT2   *((volatile uint8_t*)0x44)  // 8-bit register

// Timer/Counter control registers
#define TCCR0   *((volatile uint8_t*)0x53)  // 8-bit register
#define CS00    0
#define CS01    1
#define CS02    2
#define WGM01   3
#define COM00   4
#define COM01   5
#define WGM00   6
#define FOC0    7

#define TCCR1A  *((volatile uint8_t*)0x4F)  // 8-bit register
#define WGM10   0
#define WGM11   1
#define FOC1B   2
#define FOC1A   3
#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7

#define TCCR1B  *((volatile uint8_t*)0x4E)  // 8-bit register
#define CS10    0
#define CS11    1
#define CS12    2
#define WGM12   3
#define WGM13   4
#define ICES1   6
#define ICNC1   7

#define TCCR2   *((volatile uint8_t*)0x45)  // 8-bit register
#define CS20    0
#define CS21    1
#define CS22    2
#define WGM21   3
#define COM20   4
#define COM21   5
#define WGM20   6
#define FOC2    7

// Timer interrupts mask register
#define TIMSK   *((volatile uint8_t*)0x59)  // 8-bit register
#define TOIE0   0
#define OCIE0   1
#define TOIE2   6
#define OCIE2   7
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5

// Timer interrupts flag register
#define TIFR    *((volatile uint8_t*)0x58)  // 8-bit register
#define TOV0    0
#define OCF0    1
#define TOV2    6
#define OCF2    7
#define TOV1    2
#define OCF1B   3
#define OCF1A   4
#define ICF1    5
// *********************************************************
// Interrupts Registers
// *********************************************************
// MCU control register
#define MCUCR *((volatile uint8_t*)0x55)  // 8-bit register
#define ISC00   0
#define ISC01   1

// General interrupt control register
#define GICR *((volatile uint8_t*)0x5B)  // 8-bit register
#define INT2    5
#define INT0    6
#define INT1    7

// General interrupt flag register
#define GIFR    *((volatile uint8_t*)0x5A)  // 8-bit register
#define INTF2   5
#define INTF0   6
#define INTF1   7

// *********************************************************
// ADC Registers
// *********************************************************
#define ADCW    *((volatile uint16_t*)0x24)  // 16-bit register

#define ADCL    *((volatile uint8_t*)0x24)  // 8-bit register
#define ADCH    *((volatile uint8_t*)0x25)  // 8-bit register

#define ADCSRA  *((volatile uint8_t*)0x26)  // 8-bit register
#define ADPS0   0
#define ADPS1   1
#define ADPS2   2
#define ADIE    3
#define ADIF    4
#define ADATE   5
#define ADSC    6
#define ADEN    7

#define ADMUX   *((volatile uint8_t*)0x27)  // 8-bit register
#define MUX0    0
#define MUX1    1
#define MUX2    2
#define MUX3    3
#define MUX4    4
#define ADLAR   5
#define REFS0   6
#define REFS1   7

#define ACSR    *((volatile uint8_t*)0x28)  // 8-bit register
#define ACIS0   0
#define ACIS1   1
#define ACIC    2
#define ACIE    3
#define ACI     4
#define ACO     5
#define ACBG    6
#define ACD     7

// *********************************************************
// USART Registers
// *********************************************************
#define UDR     *((volatile uint8_t*)0x2C)  // 8-bit register

#define UCSRA   *((volatile uint8_t*)0x2B)  // 8-bit register
#define MPCM    0
#define U2X     1
#define UPE     2
#define DOR     3
#define FE      4
#define UDRE    5
#define TXC     6
#define RXC     7

#define UCSRB   *((volatile uint8_t*)0x2A)  // 8-bit register
#define TXB8    0
#define RXB8    1
#define UCSZ2   2
#define TXEN    3
#define RXEN    4
#define UDRIE   5
#define TXCIE   6
#define RXCIE   7

#define UCSRC   *((volatile uint8_t*)0x40)  // 8-bit register
#define UCPOL   0
#define UCSZ0   1
#define UCSZ1   2
#define USBS    3
#define UPM0    4
#define UPM1    5
#define UMSEL   6
#define URSEL   7

#define UBRRL   *((volatile uint8_t*)0x29)  // 8-bit register
#define UBRRH   *((volatile uint8_t*)0x40)  // 8-bit register

// *********************************************************
// TWI (I2C) Registers
// *********************************************************
#define TWBR    *((volatile uint8_t*)0x20)  // 8-bit register

#define TWSR    *((volatile uint8_t*)0x21)  // 8-bit register
#define TWPS0   0
#define TWPS1   1
#define TWS3    3
#define TWS4    4
#define TWS5    5
#define TWS6    6
#define TWS7    7

#define TWAR    *((volatile uint8_t*)0x22)  // 8-bit register

#define TWDR    *((volatile uint8_t*)0x23)  // 8-bit register

#define TWCR    *((volatile uint8_t*)0x56)  // 8-bit register
#define TWIE    0
#define TWEN    2
#define TWWC    3
#define TWSTO   4
#define TWSTA   5
#define TWEA    6
#define TWINT   7

#endif /* REGISTERS_H_ */