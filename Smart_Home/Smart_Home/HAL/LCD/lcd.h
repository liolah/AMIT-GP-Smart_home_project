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

void LCD_sendData(uint8_t data);

void LCD_sendCommand(uint8_t cmd);

void LCD_sendString(char* str);

#endif /* LCD_H_ */