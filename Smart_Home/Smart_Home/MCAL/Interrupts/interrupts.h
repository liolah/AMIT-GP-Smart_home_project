/*
 * interrupts.h
 *
 * Created: 3/25/2023 3:45:31 PM
 *  Author: hesha
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"
 // *********************************************************
 // Interrupt vectors
 // *********************************************************
//  TODO

#define sei() __asm__ __volatile__ ("sei" ::: "memory")
#define cli() __asm__ __volatile__ ("cli" ::: "memory")

#define ISR(INT_VECT)\
        void INT_VECT(void) __attribute__ ((signal, used));\
        void INT_VECT(void)

#endif /* INTERRUPTS_H_ */