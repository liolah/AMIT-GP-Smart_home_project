/*
 * interrupts.h
 *
 * Created: 3/25/2023 3:45:31 PM
 *  Author: hesha
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "../../Utilities/registers.h"
 // *********************************************************
 // Interrupt vectors
 // *********************************************************
/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect            __vector_10
#define TIMER0_COMP_vect_num        10

/* USART, Rx Complete */
#define USART_RXC_vect            __vector_13
#define USART_RXC_vect_num        13

/* USART Data Register Empty */
#define USART_UDRE_vect            __vector_14
#define USART_UDRE_vect_num        14

/* USART, Tx Complete */
#define USART_TXC_vect            __vector_15
#define USART_TXC_vect_num        15

/* ADC Conversion Complete */
#define ADC_vect            __vector_16
#define ADC_vect_num        16

#define sei() __asm__ __volatile__ ("sei" ::: "memory")
#define cli() __asm__ __volatile__ ("cli" ::: "memory")

#define ISR(INT_VECT)\
        void INT_VECT(void) __attribute__ ((signal, used));\
        void INT_VECT(void)

#endif /* INTERRUPTS_H_ */