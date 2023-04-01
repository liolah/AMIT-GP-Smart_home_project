/*
 * eeprom.c
 *
 * Created: 3/26/2023 5:07:33 PM
 *  Author: hesha
 */ 

#include "eeprom.h"

void EEPROM_init(){
  I2C_init();
}

void EEPROM_read_byte(uint8_t page, uint8_t add, uint8_t* data){
  
}

void EEPROM_read_block(uint8_t page, uint8_t add, uint8_t* data){
  
}

void EEPROM_write_byte(uint8_t page, uint8_t add, uint8_t block_size, uint8_t data){
  
}

void EEPROM_write_block(uint8_t page, uint8_t add, uint8_t block_size, uint8_t data){
  
}