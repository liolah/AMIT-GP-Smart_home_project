/*
 * i2c.c
 *
 * Created: 3/25/2023 5:17:53 PM
 *  Author: hesha
 */

#include "I2C.h"

EN_I2CMasterStatusCode_t getCurrentStatus() {
  switch ((TWSR & 0xF8)) {
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

void I2C_init(void) {
  TWBR = BITRATE(TWSR = 0x00);	// Get bit rate register value by formula 
  }

EN_I2CMasterStatusCode_t I2C_start() {
  // Generate start bit
  //? I tried setting each bit individually but it didn't work. For some reason the bits must be set at the same time. Probably because clearing TWINT starts the task? I don't know. 
  TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
  while (read_bit(TWCR, TWINT) == 0);	// Wait until TWI finish its current job
  return getCurrentStatus();
  }

EN_I2CMasterStatusCode_t I2C_repeatedStart() {   // Same as start, just a different name
  TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
  while (read_bit(TWCR, TWINT) == 0);
  return getCurrentStatus();
  }

EN_I2CMasterStatusCode_t I2C_write(u8 data) {
  TWDR = data;
  TWCR = (1 << TWEN) | (1 << TWINT);
  while (read_bit(TWCR, TWINT) == 0);
  return getCurrentStatus();
  }

EN_I2CMasterStatusCode_t I2C_read_Ack(u8* data) {
  TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
  while (read_bit(TWCR, TWINT) == 0);
  *data = TWDR;
  return getCurrentStatus();
  }

EN_I2CMasterStatusCode_t I2C_read_Nack(u8* data) {
  TWCR = (1 << TWEN) | (1 << TWINT);
  while (read_bit(TWCR, TWINT) == 0);
  *data = TWDR;
  return getCurrentStatus();
  }

void I2C_stop(void) {
  TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
  while (read_bit(TWCR, TWSTO));	// Wait until stop condition finishes
  }
