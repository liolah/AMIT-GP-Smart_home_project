/*
 * eeprom.h
 *
 * Created: 3/26/2023 5:07:27 PM
 *  Author: hesha
 */


#ifndef EEPROM_H_
#define EEPROM_H_

#define F_CPU 16000000ul
#include <util/delay.h>
#include "../../MCAL/I2C/I2C.h"

#define EEPROM_WRITE_DELAY_MS 10 

#define BYTE_BY_BYTE 0 
#define MULTIBYTE 1 

#define WRITE_BLOCK_METHOD MULTIBYTE 
#define READ_BLOCK_METHOD MULTIBYTE 

// Initialize the EEPROM
void EEPROM_init();

// Read a byte on the EEPROM, given the address and the page number
void EEPROM_read_byte(uint8_t page, uint8_t add, uint8_t* data);

// Read a block on the EEPROM, given the address and the page number. 
void EEPROM_read_block(uint8_t page, uint8_t address, uint8_t bytes_number, uint8_t* data);

// Write a byte on the EEPROM, given the address and the page number
void EEPROM_write_byte(uint8_t page, uint8_t address, int8_t data);

// Write a block on the EEPROM, given the address and the page number. The block size shouldn't be larger than 16 bytes. 
void EEPROM_write_block(uint8_t page, uint8_t add, uint8_t block_size, int8_t* data);

#endif /* EEPROM_H_ */