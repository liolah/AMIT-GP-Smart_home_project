/*
 * eeprom.c
 *
 * Created: 3/26/2023 5:07:33 PM
 *  Author: hesha
 */

#include "eeprom.h"

void EEPROM_init() {
  I2C_init();
  }

void EEPROM_read_byte(uint8_t page, uint8_t address, uint8_t* data) {
  I2C_start();
  // I2C_write(0b10100000 + (page << 1));
  I2C_write(0xA0 + (page << 1)); // EEPROM address first part + page number
  I2C_write(address);
  I2C_start();
  I2C_write(0xA0 + (page << 1) + 1);
  // read_Ack will halt the reading here, because it will send the next byte, which will not be received and wait for ack, which will not be sent. 
  // Nack must be sent after the arrival of the last requested byte. It's used basically to indicate that no further data transmission is required and then the stop condition is sent
  I2C_read_Nack(data);
  I2C_stop();
  }

void EEPROM_read_block(uint8_t page, uint8_t address, uint8_t bytes_number, uint8_t* data) {
#if READ_BLOCK_METHOD == BYTE_BY_BYTE
  int i;
  for (i = 0;i < bytes_number;i++) {
    EEPROM_read_byte(page, address + i, &data[i]);
    }
#elif READ_BLOCK_METHOD == MULTIBYTE
  I2C_start();
  I2C_write(0xA0 + (page << 1));
  I2C_write(address);
  I2C_start();
  I2C_write(0xA0 + (page << 1) + 1);
  int i;
  for (i = 0;i < bytes_number - 1;i++) {
    I2C_read_Ack(&data[i]);
    }
  I2C_read_Nack(&data[i]);
  I2C_stop();
#endif
  }

void EEPROM_write_byte(uint8_t page, uint8_t address, int8_t data) {
  I2C_start();
  // I2C_write(0b10100000 + (page << 1));
  I2C_write(0xA0 + (page << 1)); // EEPROM address first part + page number
  I2C_write(address);
  I2C_write(data);
  I2C_stop();

#if EEPROM_WRITE_DELAY_MS
  _delay_ms(EEPROM_WRITE_DELAY_MS);
#endif
  }

// bytes_number must be less than 16
void EEPROM_write_block(uint8_t page, uint8_t address, uint8_t bytes_number, int8_t* data) {
#if WRITE_BLOCK_METHOD == BYTE_BY_BYTE
  int i;
  for (i = 0;i < bytes_number;i++) {
    EEPROM_write_byte(page, address + i, data[i]);
    }
#elif WRITE_BLOCK_METHOD == MULTIBYTE
  int i;
  I2C_start();
  I2C_write(0xA0 + (page << 1));
  I2C_write(address);

  for (i = 0;i < bytes_number;i++) {
    I2C_write(data[i]);
    }
  I2C_stop();

#if EEPROM_WRITE_DELAY_MS
  _delay_ms(EEPROM_WRITE_DELAY_MS);
#endif
#endif
  }