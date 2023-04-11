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

void EEPROM_read_byte(u8 page, u8 address, char* data) {
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

void EEPROM_read_block(u8 page, u8 address, u16 bytes_number, char* data) {
#if READ_BLOCK_METHOD == BYTE_BY_BYTE
  u16 i;
  for (i = 0;i < bytes_number;i++) {
    EEPROM_read_byte(page, address + i, &data[i]);
    }
#elif READ_BLOCK_METHOD == MULTIBYTE
  I2C_start();
  I2C_write(0xA0 + (page << 1));
  I2C_write(address);
  I2C_start();
  I2C_write(0xA0 + (page << 1) + 1);
  u16 i;
  for (i = 0;i < bytes_number - 1;i++) {
    I2C_read_Ack(&data[i]);
    }
  I2C_read_Nack(&data[i]);
  I2C_stop();
#endif
  }

void EEPROM_write_byte(u8 page, u8 address, char data) {
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

// bytes_number must be within page size (256 bytes)
void EEPROM_write_block(u8 page, u8 address, u16 bytes_number, char* data) {
#if WRITE_BLOCK_METHOD == BYTE_BY_BYTE
  u16 i;
  for (i = 0;i < bytes_number;i++) {
    EEPROM_write_byte(page, address + i, data[i]);
    }
#elif WRITE_BLOCK_METHOD == MULTIBYTE
  //! In multibyte write, the bytes are first saved in a 16 bytes buffer then written to the EEPROM in the write cycle after the stop condition. 
  //! The buffer is a row of 16 bytes in the EEPROM, Each consecutive 16 bytes in each page is the buffer for the multibyte write operation
  //! done starting from a byte within these 16 bytes. As an example: 0x00 is the start of the first row and the first buffer. 0x10 is the start of the second row and the second buffer.
  //! If data is required to be written in the first 16 bytes starting from byte 10 for example, the data will be stored starting from bytes 10, 
  //! and if the data exceeds the row limit ** IT WILL ROLL OVER AND OVERWRITE THE ROW **. Therefore, in a single multibyte write cycle, we can't write more than 16 bytes at maximum if starting from the first byte in the row
  //! or the remaining bytes till the end of the row from the starting position. The remaining bytes must be written in another write cycle to avoind the roll over problem.

  u16 dataIndex, blockNumber, i;
  u16 first_block_size = 16 - (address % 16);
  if (16 - (address % 16) > bytes_number) first_block_size = bytes_number;
  
  // Write the first part of the data in the remaining space in the starting row
  I2C_start();
  I2C_write(0xA0 + (page << 1));
  I2C_write(address);
  for (dataIndex = 0;dataIndex < first_block_size;dataIndex++) {
    I2C_write(data[dataIndex]);
    }
  I2C_stop();
#if EEPROM_WRITE_DELAY_MS
  _delay_ms(EEPROM_WRITE_DELAY_MS);
#endif

  // Return if the data fits in the row (data fits in a single row or the remaining part of it after the address)
  if (first_block_size == bytes_number) return;
  
  u16 last_block_size = (address + bytes_number) % 16;
  u16 blocks_number = (bytes_number - first_block_size - last_block_size) / 16;
  // Write the remaining whole rows if any
  for (blockNumber = 0;blockNumber < blocks_number;blockNumber++) {
    I2C_start();
    I2C_write(0xA0 + (page << 1));
    I2C_write(address + dataIndex);
    for (i = 0;i < 16;i++) {
      I2C_write(data[dataIndex + i]);
      }
    dataIndex += 16;
    I2C_stop();
#if EEPROM_WRITE_DELAY_MS
    _delay_ms(EEPROM_WRITE_DELAY_MS);
#endif
    }

  // Write the last part of the data
  I2C_start();
  I2C_write(0xA0 + (page << 1));
  I2C_write(address + dataIndex);
  for (i = 0;i < last_block_size;i++) {
    I2C_write(data[dataIndex + i]);
    }
  I2C_stop();
#if EEPROM_WRITE_DELAY_MS
  _delay_ms(EEPROM_WRITE_DELAY_MS);
#endif
#endif
  }