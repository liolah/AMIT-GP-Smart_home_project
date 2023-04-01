/*
 * eeprom.h
 *
 * Created: 3/26/2023 5:07:27 PM
 *  Author: hesha
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../MCAL/I2C/I2C.h"

void EEPROM_init();

void EEPROM_read_byte(uint8_t page, uint8_t add, uint8_t* data);

void EEPROM_read_block(uint8_t page, uint8_t add, uint8_t* data);

void EEPROM_write_byte(uint8_t page, uint8_t add, uint8_t block_size, uint8_t data);

void EEPROM_write_block(uint8_t page, uint8_t add, uint8_t block_size, uint8_t data);

#endif /* EEPROM_H_ */