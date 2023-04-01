/*
 * i2c.c
 *
 * Created: 3/25/2023 5:17:53 PM
 *  Author: hesha
 */

#include "I2C.h"

void I2C_init(void) {
  TWBR = BITRATE(TWSR = 0x00);	// Get bit rate register value by formula 
  }

EN_I2CMasterStatusCode_t I2C_start(uint8_t address) {
  // Generate start bit
  //? I tried setting each bit individually but it didn't work. For some reason the bits must be set at the same time. Probably because clearing TWINT starts the task? I don't know. 
  TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
  // set_bit(TWCR, TWSTA);
  // set_bit(TWCR, TWEN); // Enable the TWI interface
  // set_bit(TWCR, TWINT);
  while (read_bit(TWCR, TWINT) == 0);	// Wait until TWI finish its current job
  if ((TWSR & 0xF8) != 0x08)						 // check if the start condition was successful
    return START_TRANSMISSION_FAILED; // If not return error
  TWDR = address;
  TWCR = (1 << TWEN) | (1 << TWINT);
  // set_bit(TWCR, TWEN);
  // set_bit(TWCR, TWINT);
  while (read_bit(TWCR, TWINT) == 0);
  if ((TWSR & 0xF8) == 0x18)
    return SLA_W_SENT_ACK_RECEIVED;
  if ((TWSR & 0xF8) == 0x20)
    return SLA_W_SENT_NACK_RECEIVED;
  return ERROR;
  }

EN_I2CMasterStatusCode_t I2C_repeatedStart(uint8_t read_address) {
  TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
  // set_bit(TWCR, TWEN);
  // set_bit(TWCR, TWSTA);
  // set_bit(TWCR, TWINT);
  while (read_bit(TWCR, TWINT) == 0);
  if ((TWSR & 0xF8) != 0x10)						 // check if the repeated start condition was successful
    return REPEATED_START_TRANSMISSION_FAILED; // If not return error
  TWDR = read_address;
  TWCR = (1 << TWEN) | (1 << TWINT);
  // set_bit(TWCR, TWEN);
  // set_bit(TWCR, TWINT);
  while (read_bit(TWCR, TWINT) == 0);
  if ((TWSR & 0xF8) == 0x40)
    return SLA_R_SENT_ACK_RECEIVED;
  if ((TWSR & 0xF8) == 0x48)
    return SLA_R_SENT_NACK_RECEIVED;
  return ERROR;
  }

EN_I2CMasterStatusCode_t I2C_write(uint8_t data) {
  TWDR = data;
  TWCR = (1 << TWEN) | (1 << TWINT);
  // set_bit(TWCR, TWEN);
  // set_bit(TWCR, TWINT);
  while (read_bit(TWCR, TWINT) == 0);
  if ((TWSR & 0xF8) == 0x28)
    return DATA_SENT_ACK_RECEIVED;
  else if ((TWSR & 0xF8) == 0x30)
    return DATA_SENT_NACK_RECEIVED;
  return ERROR;
  }

EN_I2CMasterStatusCode_t I2C_read_Ack(uint8_t* data) {
  TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
  // set_bit(TWCR, TWEA);
  // set_bit(TWCR, TWEN);
  // set_bit(TWCR, TWINT);
  while (read_bit(TWCR, TWINT) == 0);
  *data = TWDR;
  if ((TWSR & 0xF8) == 0x50)
    return DATA_RECEIVED_ACK_SENT;
  return ERROR;
  }

EN_I2CMasterStatusCode_t I2C_read_Nack(uint8_t* data) {
  TWCR = (1 << TWEN) | (1 << TWINT);
  // set_bit(TWCR, TWEN);
  // set_bit(TWCR, TWINT);
  while (read_bit(TWCR, TWINT) == 0);
  *data = TWDR;
  if ((TWSR & 0xF8) == 0x58)
    return DATA_RECEIVED_NACK_SENT;
  return ERROR;
  }

void I2C_stop(void) {
  TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
  // set_bit(TWCR, TWSTO);
  // set_bit(TWCR, TWEN);
  // set_bit(TWCR, TWINT);
  while (read_bit(TWCR, TWSTO));	// Wait until stop condition finishes
  }

EN_I2CMasterStatusCode_t getCurrentStatus() {
  switch ((TWSR & 0xF8))
  {
  case 0x08:
    return START_CONDITION_TRANSMITTED;
    break;
  case 0x10:
    return REPEATED_START_CONDITION_TRANSMITTED;
    break;
  case 0x18:
    return SLA_W_SENT_ACK_RECEIVED;
    break;
  case 0x20:
    return SLA_W_SENT_NACK_RECEIVED;
    break;
  case 0x28:
    return DATA_SENT_ACK_RECEIVED;
    break;
  case 0x30:
    return DATA_SENT_NACK_RECEIVED;
    break;
  case 0x38:
    return ARBITRATION_LOST;
    break;
  case 0x40:
    return SLA_R_SENT_ACK_RECEIVED;
    break;
  case 0x48:
    return SLA_R_SENT_NACK_RECEIVED;
    break;
  case 0x50:
    return DATA_RECEIVED_ACK_SENT;
    break;
  case 0x58:
    return DATA_RECEIVED_NACK_SENT;
    break;
    }
  return ERROR;
  }