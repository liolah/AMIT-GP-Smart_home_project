/*
 * lcd_config.h
 *
 * Created: 3/26/2023 5:06:15 PM
 *  Author: hesha
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#ifndef F_CPU
#define F_CPU 16000000ul
#endif

#include "util/delay.h"

#include "../../MCAL/DIO/dio.h"

#define FOUR_BIT_MODE   0
#define EIGHT_BIT_MODE  1

#define LCD_MODE FOUR_BIT_MODE

#define LCD_DATA_PORT PORT_A
#define LCD_CTRL_PORT PORT_A

#define RS 4
#define RW 5
#define EN 6

#if LCD_MODE == FOUR_BIT_MODE

#define LCD_DATA_PIN4 0
#define LCD_DATA_PIN5 1
#define LCD_DATA_PIN6 2
#define LCD_DATA_PIN7 3

#endif

#endif /* LCD_CONFIG_H_ */