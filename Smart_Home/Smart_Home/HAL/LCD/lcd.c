/*
 * lcd.c
 *
 * Created: 3/26/2023 5:05:42 PM
 *  Author: Hesham Hany
 */

#include "lcd.h"

 // TODO: implement the eight bit mode

void LCD_sendEnablePulse(void) {
  DIO_write(EN, LCD_CTRL_PORT, HIGH);
  _delay_us(5);
  DIO_write(EN, LCD_CTRL_PORT, LOW);
  }

void LCD_write_4bits(u8 data) {
  DIO_write(LCD_DATA_PIN4, LCD_DATA_PORT, read_bit(data, 0));
  DIO_write(LCD_DATA_PIN5, LCD_DATA_PORT, read_bit(data, 1));
  DIO_write(LCD_DATA_PIN6, LCD_DATA_PORT, read_bit(data, 2));
  DIO_write(LCD_DATA_PIN7, LCD_DATA_PORT, read_bit(data, 3));
  }

void LCD_sendData(u8 data) {
#if LCD_MODE == FOUR_BIT_MODE
  LCD_write_4bits(data >> 4);

  DIO_write(RS, LCD_CTRL_PORT, HIGH); // To indicate that this data

  LCD_sendEnablePulse();

  // _delay_us(200); // optional wait for the data to be sent

  LCD_write_4bits(data);

  LCD_sendEnablePulse();

  _delay_us(1); // wait for the data to be processed
#else

#endif
  }

void LCD_sendCommand(u8 cmd) {
#if LCD_MODE == FOUR_BIT_MODE
  LCD_write_4bits(cmd >> 4);

  DIO_write(RS, LCD_CTRL_PORT, LOW); // To indicate that this a command

  LCD_sendEnablePulse();

  // _delay_us(200); // optional wait for the command to be sent

  LCD_write_4bits(cmd);

  LCD_sendEnablePulse();

  _delay_ms(3); // wait for the command to be executed
#else

#endif
  }

void LCD_clear_screen() {
  LCD_sendCommand(0x01);
  }

void LCD_init(void) {
  _delay_ms(20); // wait for the LCD to start up.

#if LCD_MODE == FOUR_BIT_MODE
  DIO_init(LCD_DATA_PIN4, LCD_DATA_PORT, OUT);
  DIO_init(LCD_DATA_PIN5, LCD_DATA_PORT, OUT);
  DIO_init(LCD_DATA_PIN6, LCD_DATA_PORT, OUT);
  DIO_init(LCD_DATA_PIN7, LCD_DATA_PORT, OUT);

  DIO_init(RS, LCD_CTRL_PORT, OUT);
  DIO_init(RW, LCD_CTRL_PORT, OUT);
  DIO_init(EN, LCD_CTRL_PORT, OUT);

  DIO_write(RW, LCD_CTRL_PORT, LOW);

  LCD_sendCommand(0x02);  // return home 
  LCD_sendCommand(0x28);  // 2 line  and 4 bit mode
  LCD_sendCommand(0x0C);  // display on 
  LCD_sendCommand(0x06);  // auto increment 
  LCD_clear_screen();
#else

#endif
  }

void LCD_sendString(s8* str) {
  u32 i;
  for (i = 0;str[i] != 0;i++) {
    LCD_sendData(str[i]);
    }
  }

void LCD_writeString_xy(u8 x, u8 y, s8* str) {
  switch (y) {
      case 0:
        LCD_sendCommand(0x80 + x);
        break;
      case 1:
        LCD_sendCommand(0xC0 + x);
        break;
    }
  LCD_sendString(str);
  // TODO: Input validation
  }