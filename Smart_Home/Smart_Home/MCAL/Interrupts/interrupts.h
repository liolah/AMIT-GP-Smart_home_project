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
/* Interrupt vectors */
/* Vector 0 is the reset vector */

/* External Interrupt Request 0 */
#define INT0_vect            __vector_1
#define INT0_vect_num        1

/* External Interrupt Request 1 */
#define INT1_vect            __vector_2
#define INT1_vect_num        2

/* External Interrupt Request 2 */
#define INT2_vect            __vector_3
#define INT2_vect_num        3

/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect            __vector_4
#define TIMER2_COMP_vect_num        4

/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect            __vector_5
#define TIMER2_OVF_vect_num        5

/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect            __vector_6
#define TIMER1_CAPT_vect_num        6

/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect            __vector_7
#define TIMER1_COMPA_vect_num        7

/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB_vect            __vector_8
#define TIMER1_COMPB_vect_num        8

/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect            __vector_9
#define TIMER1_OVF_vect_num        9

/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect            __vector_10
#define TIMER0_COMP_vect_num        10

/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect            __vector_11
#define TIMER0_OVF_vect_num        11

/* Serial Transfer Complete */
#define SPI_STC_vect            __vector_12
#define SPI_STC_vect_num        12

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

/* EEPROM Ready */
#define EE_RDY_vect            __vector_17
#define EE_RDY_vect_num        17

/* Analog Comparator */
#define ANA_COMP_vect            __vector_18
#define ANA_COMP_vect_num        18

/* 2-wire Serial Interface */
#define TWI_vect            __vector_19
#define TWI_vect_num        19

#define sei() __asm__ __volatile__ ("sei" ::: "memory")
#define cli() __asm__ __volatile__ ("cli" ::: "memory")

#define ISR(INT_VECT)\
        void INT_VECT(void) __attribute__ ((signal, used));\
        void INT_VECT(void)

//*******************************************************************
// Initialization functions
//*******************************************************************

#define LOW_LEVEL_INTERRUPT_REQUEST            0
#define LOGICAL_CHANGE_INTERRUPT_REQUEST       1
#define FALLING_EDGE_INTERRUPT_REQUEST         2
#define RISING_EDGE_INTERRUPT_REQUEST          3

typedef enum EN_INT_init_Status_t
        {
        INTERRUPT_INIT_OK, WRONG_TRIGGER
        } EN_INT_init_Status_t;

// Initialize the INT0 interrupt given the trigger event
EN_INT_init_Status_t INT0_init(u8 trigger);

// Initialize the INT1 interrupt given the trigger event
EN_INT_init_Status_t INT1_init(u8 trigger);

// Initialize the INT2 interrupt given the trigger event
EN_INT_init_Status_t INT2_init(u8 trigger);

// Initialize the ADC conversion complete interrupt
EN_INT_init_Status_t ADC_INT_init(void);

// Initialize the UART RX complete interrupt
EN_INT_init_Status_t UART_RXC_INT_init(void);

#endif /* INTERRUPTS_H_ */