/*
 * types.h
 *
 * Created: 3/25/2023 3:15:04 PM
 *  Author: Hesham Hany
 */

#ifndef TYPES_H_
#define TYPES_H_

 // In atmega32a, int is 16 bits. long int is 32 bits.
 // uint32_t is defined as unsigned int in stdin.h, and it's supposed to be 4 bytes, which is not true for atmega32a
 // Therefore, this typedefs are needed

// Note: short int and short and int are the same for atmega32a, all of them are 16 bits integer datatypes

typedef unsigned char u8;
typedef char s8;
typedef unsigned short int u16;
typedef short int s16;
typedef unsigned long int u32;
typedef long int s32;

#endif /* TYPES_H_ */