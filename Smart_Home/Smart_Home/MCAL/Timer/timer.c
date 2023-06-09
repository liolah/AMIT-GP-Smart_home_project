/*
 * timer.c
 *
 * Created: 3/25/2023 4:38:13 PM
 *  Author: Hesham Hany
 */

#include "timer.h"

bool isValidTimer(u8 timer) {
  if (timer == TIMER_0 || timer == TIMER_1 || timer == TIMER_2) {
    return true;
    }
  return false;
  }

// Helper function to select the prescalar 
EN_timerError_t set_prescalar(u8 timer, u16 prescalarValue) {
  // Validate the timer number
  if (!isValidTimer(timer)) {
    return WRONG_TIMER;
    }
  switch (timer) {
      case TIMER_0:
        if (prescalarValue == 0 || prescalarValue == 1 || prescalarValue == 8 || prescalarValue == 64 || prescalarValue == 256 || prescalarValue == 1024) {
          switch (prescalarValue) {
              case 0:
                // TCCR0 &= ~(1 << CS00 | CS01 | CS02);
                clear_bit(TCCR0, CS00);
                clear_bit(TCCR0, CS01);
                clear_bit(TCCR0, CS02);
                break;
              case 1:
                set_bit(TCCR0, CS00);
                clear_bit(TCCR0, CS01);
                clear_bit(TCCR0, CS02);
                break;
              case 8:
                clear_bit(TCCR0, CS00);
                set_bit(TCCR0, CS01);
                clear_bit(TCCR0, CS02);
                break;
              case 64:
                set_bit(TCCR0, CS00);
                set_bit(TCCR0, CS01);
                clear_bit(TCCR0, CS02);
                break;
              case 256:
                clear_bit(TCCR0, CS00);
                clear_bit(TCCR0, CS01);
                set_bit(TCCR0, CS02);
                break;
              case 1024:
                set_bit(TCCR0, CS00);
                clear_bit(TCCR0, CS01);
                set_bit(TCCR0, CS02);
                break;
            }
          }
        else {
          return WRONG_PRESCALAR;
          }
        break;
      case TIMER_1:
        if (prescalarValue == 0 || prescalarValue == 1 || prescalarValue == 8 || prescalarValue == 64 || prescalarValue == 256 || prescalarValue == 1024) {
          switch (prescalarValue) {
              case 0:
                // TCCR1B &= ~(1 << CS10 | CS11 | CS12);
                clear_bit(TCCR1B, CS10);
                clear_bit(TCCR1B, CS11);
                clear_bit(TCCR1B, CS12);
                break;
              case 1:
                set_bit(TCCR1B, CS10);
                clear_bit(TCCR1B, CS11);
                clear_bit(TCCR1B, CS12);
                break;
              case 8:
                clear_bit(TCCR1B, CS10);
                set_bit(TCCR1B, CS11);
                clear_bit(TCCR1B, CS12);
                break;
              case 64:
                set_bit(TCCR1B, CS10);
                set_bit(TCCR1B, CS11);
                clear_bit(TCCR1B, CS12);
                break;
              case 256:
                clear_bit(TCCR1B, CS10);
                clear_bit(TCCR1B, CS11);
                set_bit(TCCR1B, CS12);
                break;
              case 1024:
                set_bit(TCCR1B, CS10);
                clear_bit(TCCR1B, CS11);
                set_bit(TCCR1B, CS12);
                break;
            }
          }
        else {
          return WRONG_PRESCALAR;
          }
        break;
      case TIMER_2:
        if (prescalarValue == 0 || prescalarValue == 1 || prescalarValue == 8 || prescalarValue == 32 || prescalarValue == 64 || prescalarValue == 128 || prescalarValue == 256 || prescalarValue == 1024) {
          switch (prescalarValue) {
              case 0:
                // TCCR2 &= ~(1 << CS20 | CS21 | CS22);
                clear_bit(TCCR2, CS20);
                clear_bit(TCCR2, CS21);
                clear_bit(TCCR2, CS22);
                break;
              case 1:
                set_bit(TCCR2, CS20);
                clear_bit(TCCR2, CS21);
                clear_bit(TCCR2, CS22);
                break;
              case 8:
                clear_bit(TCCR2, CS20);
                set_bit(TCCR2, CS21);
                clear_bit(TCCR2, CS22);
                break;
              case 32:
                set_bit(TCCR2, CS20);
                set_bit(TCCR2, CS21);
                clear_bit(TCCR2, CS22);
                break;
              case 64:
                clear_bit(TCCR2, CS20);
                clear_bit(TCCR2, CS21);
                set_bit(TCCR2, CS22);
                break;
              case 128:
                set_bit(TCCR2, CS20);
                clear_bit(TCCR2, CS21);
                set_bit(TCCR2, CS22);
                break;
              case 256:
                clear_bit(TCCR2, CS20);
                set_bit(TCCR2, CS21);
                set_bit(TCCR2, CS22);
                break;
              case 1024:
                set_bit(TCCR2, CS20);
                set_bit(TCCR2, CS21);
                set_bit(TCCR2, CS22);
                break;
            }
          }
        else {
          return WRONG_PRESCALAR;
          }
        break;
    }
  // Everything went well
  return TIMER_OK;
  }

EN_timerError_t Timer_normal_init(u8 timerNumber, u16 initialVal) {
  // Validate the timer number
  if (!isValidTimer(timerNumber)) {
    return WRONG_TIMER;
    }
  // Check if the compare value is too large for the timer's OCR
  if (timerNumber == TIMER_0 || timerNumber == TIMER_2) {
    if (initialVal > 255)
      return WRONG_TIMER_TCNT_VALUE;
    }
  switch (timerNumber) {
      case TIMER_0:
        // Set the timer mode to normal mode
        clear_bit(TCCR0, WGM01);
        clear_bit(TCCR0, WGM00);
        // Set the initial value in the TCNT register.
        TCNT0 = (u8)initialVal;
        break;
      case TIMER_1:
        // Set the timer mode to normal mode
        clear_bit(TCCR1A, WGM10);
        clear_bit(TCCR1A, WGM11);
        clear_bit(TCCR1B, WGM12);
        clear_bit(TCCR1B, WGM13);
        // Set the initial value in the TCNT register.
        TCNT1 = initialVal;
        break;
      case TIMER_2:
        // Set the timer mode to normal mode
        clear_bit(TCCR2, WGM21);
        clear_bit(TCCR2, WGM20);
        // Set the initial value in the TCNT register.
        TCNT2 = (u8)initialVal;
        break;
    }
  // Everything went well
  return TIMER_OK;
  }

// Initialize the timers to start in CTC mode
EN_timerError_t Timer_CTC_init(u8 timerNumber, u16 compareValue) {
  // Validate the timer number
  if (!isValidTimer(timerNumber)) {
    return WRONG_TIMER;
    }
  // Check if the compare value is too large for the timer's OCR
  if (timerNumber == TIMER_0 || timerNumber == TIMER_2) {
    if (compareValue > 255)
      return WRONG_TIMER_OCR_VALUE;
    }
  switch (timerNumber) {
      case TIMER_0:
        // Set the timer mode to CTC
        set_bit(TCCR0, WGM01);
        clear_bit(TCCR0, WGM00);
        // Reset the value in TCNT register. It's probably zero but just to make sure.
        TCNT0 = 0;
        // Set the OCR to the calculated value
        OCR0 = (u8)compareValue;
        break;
      case TIMER_1:
        // Set the timer mode to CTC
        clear_bit(TCCR1A, WGM10);
        clear_bit(TCCR1A, WGM11);
        set_bit(TCCR1B, WGM12);
        clear_bit(TCCR1B, WGM13);
        // Reset the value in TCNT register.
        TCNT1 = 0;
        // Set the OCR to the calculated value
        OCR1A = compareValue;
        break;
      case TIMER_2:
        // Set the timer mode to CTC
        set_bit(TCCR2, WGM21);
        clear_bit(TCCR2, WGM20);
        // Reset the value in TCNT register.
        TCNT2 = 0;
        // Set the OCR to the calculated value
        OCR2 = (u8)compareValue;
        break;
    }
  // Everything went well
  return TIMER_OK;
  }

// Start the timer
EN_timerError_t Timer_start(u8 timerNumber, u16 prescalar) {
  // Validate the timer number
  if (!isValidTimer(timerNumber)) {
    return WRONG_TIMER;
    }
  // Select the clock source (prescaler) to start the timer 
  set_prescalar(timerNumber, prescalar);
  // Everything went well
  return TIMER_OK;
  }

// Stop the timer
EN_timerError_t Timer_stop(u8 timerNumber) {
  // Validate the timer number
  if (!isValidTimer(timerNumber)) {
    return WRONG_TIMER;
    }
  // Set the clock source to "no clock source" to stop the timer 
  set_prescalar(timerNumber, 0);
  // Everything went well
  return TIMER_OK;
  }

// Reset the timer
// The timers are reset by setting the value of TCNT to zero
EN_timerError_t Timer_reset(u8 timerNumber) {
  // Validate the timer number
  if (!isValidTimer(timerNumber)) {
    return WRONG_TIMER;
    }
  switch (timerNumber) {
      case TIMER_0:
        TCNT0 = 0;
        break;
      case TIMER_1:
        TCNT1 = 0;
        break;
      case TIMER_2:
        TCNT2 = 0;
        break;
    }
  // Everything went well
  return TIMER_OK;
  }

// *The pwm frequency can be calculated from the equation: (F_CPU/(N*256)) for fast pwm and (F_CPU/(N*510)) for phase correct pwm
// Initialize the timers to start in pwm mode
EN_timerError_t PWM_init(u8 pwmPin, double dutyCycle, u8 mode) {
  if (pwmPin != OC_0 && pwmPin != OC_1A && pwmPin != OC_1B && pwmPin != OC_2) {
    return WRONG_PWM_PIN;
    }
  if (mode != PWM_FAST && mode != PWM_PHASE_CORRECT) {
    return WRONG_PWM_MODE;
    }
  switch (pwmPin) {
      case OC_0:
        switch (mode) {
            case PWM_FAST:
              set_bit(TCCR0, WGM00);
              set_bit(TCCR0, WGM01);
              break;
            case PWM_PHASE_CORRECT:
              set_bit(TCCR0, WGM00);
              clear_bit(TCCR0, WGM01);
              break;
          }
        // The value in the OCR determines the duty cycle
        OCR0 = (u8)(dutyCycle * 255);
        break;
        //? The problem that has been occurring with OC1A (the pin was always high and no pwm signal was generated) was caused by
        //? the timer being set in pwm mode 15, which makes OCR1A the TOP and also compares it to itself, which results in the OCR register and the TOP being always equal.
        //? The behavior of the avr in that case is to generate and always high signal, which was happening.
        //? The fix for this issue is to use ICR1 as TOP instead (mode 14 in fast pwm), thus allowing OCR1A and OCR1B to be used to set the duty cycle while ICR1 is used tyo set the frequency.
        //? Mode 15 can be used at the cost of disabling PWM on OC1A, but we get more glitch-free variable frequency PWM signal on OC1B due to the double buffering of OC1A, which ICR1 doesn't have.
        //? Since I don't need a variable frequency pwm signal, ICR1 will be used as TOP by default and set to MAX.
      case OC_1A:
      case OC_1B:
        switch (mode) {
            case PWM_FAST:
#if TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_8_BIT
              set_bit(TCCR1A, WGM10);
              clear_bit(TCCR1A, WGM11);
              set_bit(TCCR1B, WGM12);
              clear_bit(TCCR1B, WGM13);
#elif TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_9_BIT
              clear_bit(TCCR1A, WGM10);
              set_bit(TCCR1A, WGM11);
              set_bit(TCCR1B, WGM12);
              clear_bit(TCCR1B, WGM13);
#elif TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_10_BIT
              set_bit(TCCR1A, WGM10);
              set_bit(TCCR1A, WGM11);
              set_bit(TCCR1B, WGM12);
              clear_bit(TCCR1B, WGM13);
#elif TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_TOP_ICR1
              clear_bit(TCCR1A, WGM10);
              set_bit(TCCR1A, WGM11);
              set_bit(TCCR1B, WGM12);
              set_bit(TCCR1B, WGM13);
              ICR1 = TIMER_1_PWM_TOP_ICR1_VALUE;
#elif TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_TOP_OCR1A
              set_bit(TCCR1A, WGM10);
              set_bit(TCCR1A, WGM11);
              set_bit(TCCR1B, WGM12);
              set_bit(TCCR1B, WGM13);
#endif
              break;
            case PWM_PHASE_CORRECT:
#if TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_8_BIT
              set_bit(TCCR1A, WGM10);
              clear_bit(TCCR1A, WGM11);
              clear_bit(TCCR1B, WGM12);
              clear_bit(TCCR1B, WGM13);
#elif TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_9_BIT
              clear_bit(TCCR1A, WGM10);
              set_bit(TCCR1A, WGM11);
              clear_bit(TCCR1B, WGM12);
              clear_bit(TCCR1B, WGM13);
#elif TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_10_BIT
              set_bit(TCCR1A, WGM10);
              set_bit(TCCR1A, WGM11);
              clear_bit(TCCR1B, WGM12);
              clear_bit(TCCR1B, WGM13);
#elif TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_TOP_ICR1
              clear_bit(TCCR1A, WGM10);
              set_bit(TCCR1A, WGM11);
              clear_bit(TCCR1B, WGM12);
              set_bit(TCCR1B, WGM13);
              ICR1 = TIMER_1_PWM_TOP_ICR1_VALUE;
#elif TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_TOP_OCR1A
              set_bit(TCCR1A, WGM10);
              set_bit(TCCR1A, WGM11);
              clear_bit(TCCR1B, WGM12);
              set_bit(TCCR1B, WGM13);
#endif
              break;
          }
        // Enable the PWM function of the OC pin.
        switch (pwmPin) {
            case OC_1A:
#if (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_8_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_8_BIT)
              OCR1A = (u16)(dutyCycle * 0x00FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_9_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_9_BIT)
              OCR1A = (u16)(dutyCycle * 0x01FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_10_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_10_BIT)
              OCR1A = (u16)(dutyCycle * 0x03FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_TOP_ICR1 || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_TOP_ICR1)
              OCR1A = (u16)(dutyCycle * TIMER_1_PWM_TOP_ICR1_VALUE);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_TOP_OCR1A || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_TOP_OCR1A)
              OCR1A = (u16)(dutyCycle * 65535);
#endif
              break;
            case OC_1B:
#if (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_8_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_8_BIT)
              OCR1B = (u16)(dutyCycle * 0x00FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_9_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_9_BIT)
              OCR1B = (u16)(dutyCycle * 0x01FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_10_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_10_BIT)
              OCR1B = (u16)(dutyCycle * 0x03FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_TOP_ICR1 || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_TOP_ICR1)
              OCR1B = (u16)(dutyCycle * TIMER_1_PWM_TOP_ICR1_VALUE);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_TOP_OCR1A || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_TOP_OCR1A)
              OCR1B = (u16)(dutyCycle * 65535);
#endif
              break;
          }
        break;
      case OC_2:
        switch (mode) {
            case PWM_FAST:
              set_bit(TCCR2, WGM20);
              set_bit(TCCR2, WGM21);
              break;
            case PWM_PHASE_CORRECT:
              set_bit(TCCR2, WGM20);
              clear_bit(TCCR2, WGM21);
              break;
          }
        // The value in the OCR determines the duty cycle
        OCR2 = (u8)(dutyCycle * 255);
        break;
    }
  PWM_OCP_connect(pwmPin);
  return TIMER_OK;
  }

// PWM stop 
// disconnects the OC pins and sets the prescalar to 0.
EN_timerError_t PWM_stop(u8 pwmPin) {
  if (pwmPin != OC_0 && pwmPin != OC_1A && pwmPin != OC_1B && pwmPin != OC_2) {
    return WRONG_PWM_PIN;
    }
  switch (pwmPin) {
      case OC_0:
        clear_bit(TCCR0, COM00);
        clear_bit(TCCR0, COM01);
        set_prescalar(TIMER_0, 0);
        break;
      case OC_1A:
        clear_bit(TCCR1A, COM1A0);
        clear_bit(TCCR1A, COM1A1);
        set_prescalar(TIMER_1, 0);
        break;
      case OC_1B:
        clear_bit(TCCR1A, COM1B0);
        clear_bit(TCCR1A, COM1B1);
        set_prescalar(TIMER_1, 0);
        break;
      case OC_2:
        clear_bit(TCCR2, COM20);
        clear_bit(TCCR2, COM21);
        set_prescalar(TIMER_2, 0);
        break;
    }
  return TIMER_OK;
  }

// disconnects the OC pins.
EN_timerError_t PWM_OCP_disconnect(u8 pwmPin) {
  if (pwmPin != OC_0 && pwmPin != OC_1A && pwmPin != OC_1B && pwmPin != OC_2) {
    return WRONG_PWM_PIN;
    }
  switch (pwmPin) {
      case OC_0:
        clear_bit(TCCR0, COM00);
        clear_bit(TCCR0, COM01);
        break;
      case OC_1A:
        clear_bit(TCCR1A, COM1A0);
        clear_bit(TCCR1A, COM1A1);
        break;
      case OC_1B:
        clear_bit(TCCR1A, COM1B0);
        clear_bit(TCCR1A, COM1B1);
        break;
      case OC_2:
        clear_bit(TCCR2, COM20);
        clear_bit(TCCR2, COM21);
        break;
    }
  return TIMER_OK;
  }

// Connects the OC pins.
EN_timerError_t PWM_OCP_connect(u8 pwmPin) {
  if (pwmPin != OC_0 && pwmPin != OC_1A && pwmPin != OC_1B && pwmPin != OC_2) {
    return WRONG_PWM_PIN;
    }
  switch (pwmPin) {
      case OC_0:
#if PWM_SIGNAL_INVERSION == PWM_NON_INVERTED_MODE
        clear_bit(TCCR0, COM00);
        set_bit(TCCR0, COM01);
#else 
        set_bit(TCCR0, COM00);
        set_bit(TCCR0, COM01);
#endif
        break;
      case OC_1A:
#if PWM_SIGNAL_INVERSION == PWM_NON_INVERTED_MODE
        clear_bit(TCCR1A, COM1A0);
        set_bit(TCCR1A, COM1A1);
#else 
        set_bit(TCCR1A, COM1A0);
        set_bit(TCCR1A, COM1A1);
#endif
        break;
      case OC_1B:
#if PWM_SIGNAL_INVERSION == PWM_NON_INVERTED_MODE
        clear_bit(TCCR1A, COM1B0);
        set_bit(TCCR1A, COM1B1);
#else 
        set_bit(TCCR1A, COM1B0);
        set_bit(TCCR1A, COM1B1);
#endif
        break;
      case OC_2:
#if PWM_SIGNAL_INVERSION == PWM_NON_INVERTED_MODE
        clear_bit(TCCR2, COM20);
        set_bit(TCCR2, COM21);
#else 
        set_bit(TCCR2, COM20);
        set_bit(TCCR2, COM21);
#endif
        break;
    }
  return TIMER_OK;
  }

// Change the duty cycle of a timer
EN_timerError_t PWM_set_DC(u8 pwmPin, double dutyCycle) {
  if (pwmPin != OC_0 && pwmPin != OC_1A && pwmPin != OC_1B && pwmPin != OC_2) {
    return WRONG_PWM_PIN;
    }
  switch (pwmPin) {
      case OC_0:
        OCR0 = (u8)(dutyCycle * 255);
        break;
      case OC_1A:
#if (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_8_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_8_BIT)
        OCR1A = (u16)(dutyCycle * 0x00FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_9_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_9_BIT)
        OCR1A = (u16)(dutyCycle * 0x01FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_10_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_10_BIT)
        OCR1A = (u16)(dutyCycle * 0x03FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_TOP_ICR1 || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_TOP_ICR1)
        OCR1A = (u16)(dutyCycle * TIMER_1_PWM_TOP_ICR1_VALUE);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_TOP_OCR1A || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_TOP_OCR1A)
        OCR1A = (u16)(dutyCycle * 65535);
#endif
        break;
      case OC_1B:
#if (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_8_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_8_BIT)
        OCR1B = (u16)(dutyCycle * 0x00FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_9_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_9_BIT)
        OCR1B = (u16)(dutyCycle * 0x01FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_10_BIT || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_10_BIT)
        OCR1B = (u16)(dutyCycle * 0x03FF);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_TOP_ICR1 || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_TOP_ICR1)
        OCR1B = (u16)(dutyCycle * TIMER_1_PWM_TOP_ICR1_VALUE);
#elif (TIMER_1_FAST_PWM_MODE == TIMER_1_FAST_PWM_TOP_OCR1A || TIMER_1_PHASE_CORRECT_PWM_MODE == TIMER_1_PHASE_CORRECT_PWM_TOP_OCR1A)
        OCR1B = (u16)(dutyCycle * 65535);
#endif
        break;
      case OC_2:
        OCR2 = (u8)(dutyCycle * 255);
        break;
    }
  return TIMER_OK;
  }

// Check if the OCR's OCF is set and reset the flag if set. Returns true if the flag is set.
EN_timerError_t Timer_read_and_reset_OCF(u8 OCRNumber, bool* flag) {
  // Validate the OCR number
  if (OCRNumber != OCR_0 && OCRNumber != OCR_1A && OCRNumber != OCR_1B && OCRNumber != OCR_2) {
    return WRONG_OCR_REGISTER;
    }
  switch (OCRNumber) {
      case OCR_0:
        // If the OCF bit is set that means a compare match has occurred. 
        if (read_bit(TIFR, OCF0)) {
          // Write one to reset the flag
          set_bit(TIFR, OCF0);
          *flag = true;
          }
        else {
          *flag = false;
          }
        break;
      case OCR_1A:
        if (read_bit(TIFR, OCF1A)) {
          set_bit(TIFR, OCF1A);
          *flag = true;
          }
        else {
          *flag = false;
          }
        break;
      case OCR_1B:
        if (read_bit(TIFR, OCF1B)) {
          set_bit(TIFR, OCF1B);
          *flag = true;
          }
        else {
          *flag = false;
          }
        break;
      case OCR_2:
        if (read_bit(TIFR, OCF2)) {
          set_bit(TIFR, OCF2);
          *flag = true;
          }
        else {
          *flag = false;
          }
        break;
    }
  // Everything went well
  return TIMER_OK;
  }

// Reset the OCF
EN_timerError_t Timer_reset_OCF(u8 OCRNumber) {
  // Validate the OCR number
  if (OCRNumber != OCR_0 && OCRNumber != OCR_1A && OCRNumber != OCR_1B && OCRNumber != OCR_2) {
    return WRONG_OCR_REGISTER;
    }
  switch (OCRNumber) {
      case OCR_0:
        set_bit(TIFR, OCF0);
        break;
      case OCR_1A:
        set_bit(TIFR, OCF1A);
        break;
      case OCR_1B:
        set_bit(TIFR, OCF1B);
        break;
      case OCR_2:
        set_bit(TIFR, OCF2);
        break;
    }
  return TIMER_OK;
  }