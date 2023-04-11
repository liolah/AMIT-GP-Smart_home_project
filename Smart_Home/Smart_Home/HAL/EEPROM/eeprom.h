/*
 * eeprom.h
 *
 * Created: 3/26/2023 5:07:27 PM
 *  Author: hesha
 */


#ifndef EEPROM_H_
#define EEPROM_H_

#ifndef	F_CPU
#define F_CPU 16000000ul
#endif

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
void EEPROM_read_byte(u8 page, u8 address, s8* data);

// Read a block on the EEPROM, given the address and the page number. 
void EEPROM_read_block(u8 page, u8 address, u16 bytes_number, s8* data);

// Write a byte on the EEPROM, given the address and the page number
void EEPROM_write_byte(u8 page, u8 address, s8 data);

// Write a block on the EEPROM, given the address and the page number. Block_size must be within page size (256 bytes)
void EEPROM_write_block(u8 page, u8 address, u16 block_size, s8* data);

#endif /* EEPROM_H_ */