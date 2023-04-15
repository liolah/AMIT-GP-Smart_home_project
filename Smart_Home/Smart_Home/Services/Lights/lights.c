/*
 * lights.c
 *
 * Created: 4/14/2023 6:25:38 AM
 *  Author: Hesham Hany
 */

#include "lights.h"

 // Initializes all six lamps
void Lamps_init(void) {
  LED_init(LAMP_1_PORT, LAMP_1_PIN);
  LED_init(LAMP_2_PORT, LAMP_2_PIN);
  LED_init(LAMP_3_PORT, LAMP_3_PIN);
  LED_init(LAMP_4_PORT, LAMP_4_PIN);
  LED_init(LAMP_5_PORT, LAMP_5_PIN);
  LED_init(LAMP_6_DIMMABLE_PORT, LAMP_6_DIMMABLE_PIN);
  // Initialize the pwm pin which lamp6 is on for brightness control
  PWM_init(LAMP_6_DIMMABLE_PWM_PIN, 1, PWM_FAST);
  Timer_start(TIMER_2, 1);
  }

// Turn on a lamp
void Lamp_on(u8 lampNumber) {
  switch (lampNumber) {
      case LAMP_1:
        LED_on(LAMP_1_PORT, LAMP_1_PIN);
        break;
      case LAMP_2:
        LED_on(LAMP_2_PORT, LAMP_2_PIN);
        break;
      case LAMP_3:
        LED_on(LAMP_3_PORT, LAMP_3_PIN);
        break;
      case LAMP_4:
        LED_on(LAMP_4_PORT, LAMP_4_PIN);
        break;
      case LAMP_5:
        LED_on(LAMP_5_PORT, LAMP_5_PIN);
        break;
      case LAMP_6:
        LED_on(LAMP_6_DIMMABLE_PORT, LAMP_6_DIMMABLE_PIN);
        break;
    }
  }

// Turn off a lamp
void Lamp_off(u8 lampNumber) {
  switch (lampNumber) {
      case LAMP_1:
        LED_off(LAMP_1_PORT, LAMP_1_PIN);
        break;
      case LAMP_2:
        LED_off(LAMP_2_PORT, LAMP_2_PIN);
        break;
      case LAMP_3:
        LED_off(LAMP_3_PORT, LAMP_3_PIN);
        break;
      case LAMP_4:
        LED_off(LAMP_4_PORT, LAMP_4_PIN);
        break;
      case LAMP_5:
        LED_off(LAMP_5_PORT, LAMP_5_PIN);
        break;
      case LAMP_6:
        LED_off(LAMP_6_DIMMABLE_PORT, LAMP_6_DIMMABLE_PIN);
        break;
    }
  }

// Toggle a lamp
void Lamp_toggle(u8 lampNumber) {
  switch (lampNumber) {
      case LAMP_1:
        LED_toggle(LAMP_1_PORT, LAMP_1_PIN);
        break;
      case LAMP_2:
        LED_toggle(LAMP_2_PORT, LAMP_2_PIN);
        break;
      case LAMP_3:
        LED_toggle(LAMP_3_PORT, LAMP_3_PIN);
        break;
      case LAMP_4:
        LED_toggle(LAMP_4_PORT, LAMP_4_PIN);
        break;
      case LAMP_5:
        LED_toggle(LAMP_5_PORT, LAMP_5_PIN);
        break;
      case LAMP_6:
        LED_toggle(LAMP_6_DIMMABLE_PORT, LAMP_6_DIMMABLE_PIN);
        break;
    }
  }

// Adjust the brightness of the dimmable lamp
void Lamp_dimmable_set_brightness(double brightness) {
  PWM_set_DC(LAMP_6_DIMMABLE_PWM_PIN, brightness);
  }