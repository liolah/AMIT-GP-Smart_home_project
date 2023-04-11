/*
 * interrupts.c
 *
 * Created: 4/9/2023 6:43:02 PM
 *  Author: hesha
 */

#include "interrupts.h"


 // Initialize the INT0 interrupt given the trigger event
EN_INT_init_Status_t INT0_init(u8 trigger) {
  if (trigger != LOW_LEVEL_INTERRUPT_REQUEST && trigger != LOGICAL_CHANGE_INTERRUPT_REQUEST && trigger != FALLING_EDGE_INTERRUPT_REQUEST && trigger != RISING_EDGE_INTERRUPT_REQUEST) {
    return WRONG_TRIGGER;
    }
  // Enable the external interrupt 
  set_bit(GICR, INT0);
  switch (trigger) {
      case LOW_LEVEL_INTERRUPT_REQUEST:
        // Default trigger mode
        // clear_bit(MCUCR, ISC00);
        // clear_bit(MCUCR, ISC01);
        break;
      case LOGICAL_CHANGE_INTERRUPT_REQUEST:
        set_bit(MCUCR, ISC00);
        break;
      case FALLING_EDGE_INTERRUPT_REQUEST:
        set_bit(MCUCR, ISC01);
        break;
      case RISING_EDGE_INTERRUPT_REQUEST:
        set_bit(MCUCR, ISC00);
        set_bit(MCUCR, ISC01);
        break;
    }
  return INTERRUPT_INIT_OK;
  }

// Initialize the INT1 interrupt given the trigger event
EN_INT_init_Status_t INT1_init(u8 trigger) {
  if (trigger != LOW_LEVEL_INTERRUPT_REQUEST && trigger != LOGICAL_CHANGE_INTERRUPT_REQUEST && trigger != FALLING_EDGE_INTERRUPT_REQUEST && trigger != RISING_EDGE_INTERRUPT_REQUEST) {
    return WRONG_TRIGGER;
    }
  // Enable the external interrupt 
  set_bit(GICR, INT1);
  switch (trigger) {
      case LOW_LEVEL_INTERRUPT_REQUEST:
        // Default trigger mode
        // clear_bit(MCUCR, ISC10);
        // clear_bit(MCUCR, ISC11);
        break;
      case LOGICAL_CHANGE_INTERRUPT_REQUEST:
        set_bit(MCUCR, ISC10);
        break;
      case FALLING_EDGE_INTERRUPT_REQUEST:
        set_bit(MCUCR, ISC11);
        break;
      case RISING_EDGE_INTERRUPT_REQUEST:
        set_bit(MCUCR, ISC10);
        set_bit(MCUCR, ISC11);
        break;
    }
  return INTERRUPT_INIT_OK;
  }

// Initialize the INT2 interrupt given the trigger event
EN_INT_init_Status_t INT2_init(u8 trigger) {
  if (trigger != FALLING_EDGE_INTERRUPT_REQUEST && trigger != RISING_EDGE_INTERRUPT_REQUEST) {
    return WRONG_TRIGGER;
    }
  // Enable the external interrupt 
  set_bit(GICR, INT2);
  switch (trigger) {
      case FALLING_EDGE_INTERRUPT_REQUEST:
        break;
      case RISING_EDGE_INTERRUPT_REQUEST:
        set_bit(MCUCSR, ISC2);
        break;
    }
  return INTERRUPT_INIT_OK;
  }

// Initialize the ADC conversion complete interrupt
EN_INT_init_Status_t ADC_INT_init(void) {
  // Enable the ADC conversion complete interrupt
  set_bit(ADCSRA, ADIE);
  return INTERRUPT_INIT_OK;
  }

// Initialize the UART RX complete interrupt
EN_INT_init_Status_t UART_RXC_INT_init(void) {
  // Enable the UART RX complete interrupt
  set_bit(UCSRB, RXCIE);
  return INTERRUPT_INIT_OK;
  }