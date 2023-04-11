/*
 * types.h
 *
 * Created: 3/25/2023 3:15:04 PM
 *  Author: hesha
 */

#ifndef TYPES_H_
#define TYPES_H_

 // In atmega32a, int is 16 bits. long int is 32 bits.
 // u32 is defined as unsigned int, and it's supposed to be 4 bytes, which is not true for atmega32a

typedef unsigned char u8;
typedef char s8;
typedef unsigned short int u16;
typedef short int s16;
typedef unsigned long int u32;
typedef long int s32;

#endif /* TYPES_H_ */