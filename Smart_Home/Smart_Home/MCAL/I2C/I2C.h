/*
 * i2c.h
 *
 * Created: 3/25/2023 5:17:31 PM
 *  Author: hesha
 */


#ifndef I2C_H_
#define I2C_H_

#include <stdbool.h>
#include <math.h>

#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"

 // *************************************************
  // Master Mode
 // *************************************************

#define F_CPU 16000000
#define SCL_CLK 10000
 //SCL frequency =  (CPU CLK frequency)/(16+2(TWBR)*4^TWPS )
 /* Define bit rate */
#define BITRATE(TWSR)	((F_CPU / SCL_CLK) - 16) / (2 * pow(4, (TWSR & (( 1 << TWPS0) | (1 << TWPS1)))))

typedef enum EN_I2CMasterStatusCode_t
  {
  START_TRANSMITTED, START_TRANSMISSION_FAILED, REPEATED_START_TRANSMITTED, REPEATED_START_TRANSMISSION_FAILED, SLA_W_SENT_ACK_RECEIVED, SLA_W_SENT_NACK_RECEIVED, DATA_SENT_ACK_RECEIVED, DATA_SENT_NACK_RECEIVED, SLA_R_SENT_ACK_RECEIVED, SLA_R_SENT_NACK_RECEIVED, DATA_RECEIVED_ACK_SENT, DATA_RECEIVED_NACK_SENT, ERROR
  } EN_I2CMasterStatusCode_t;

void I2C_init(void);

EN_I2CMasterStatusCode_t I2C_start(uint8_t address);

EN_I2CMasterStatusCode_t I2C_repeatedStart(uint8_t read_address);

EN_I2CMasterStatusCode_t I2C_write(uint8_t data);

EN_I2CMasterStatusCode_t I2C_read_Ack(uint8_t* data);

EN_I2CMasterStatusCode_t I2C_read_Nack(uint8_t* data);

void I2C_stop(void);


// *************************************************
 // Slave Mode
// *************************************************
// TODO
#endif /* I2C_H_ */