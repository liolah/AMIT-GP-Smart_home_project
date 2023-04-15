/*
 * bit_manipulation.h
 *
 * Created: 3/25/2023 3:13:26 PM
 *  Author: Hesham Hany
 */


#ifndef BIT_MANIPULATION_H_
#define BIT_MANIPULATION_H_

#define set_bit(port, pinNumber) port |= (1 << pinNumber)
#define clear_bit(port, pinNumber)  port &= ~(1 << pinNumber)
#define toggle_bit(port, pinNumber) port ^= (1 << pinNumber)
#define read_bit(port, pinNumber) ((port >> pinNumber) & 1)
 // #define read_bit(port, pinNumber) ((port & (1 << pinNumber)) >> pinNumber)

#endif /* BIT_MANIPULATION_H_ */