/*
 * lcd.h
 *
 * Created: 3/26/2023 5:05:29 PM
 *  Author: hesha
 */


#ifndef LCD_H_
#define LCD_H_

#include "lcd_config.h"

void LCD_init(void);

void LCD_sendData(u8 data);

void LCD_sendCommand(u8 cmd);

void LCD_sendString(char* str);

void LCD_writeString_xy(u8 x, u8 y, char* str);

void LCD_clear_screen();

#endif /* LCD_H_ */