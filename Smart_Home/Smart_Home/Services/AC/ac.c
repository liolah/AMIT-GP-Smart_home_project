/*
 * ac.c
 *
 * Created: 4/14/2023 6:24:50 AM
 *  Author: hesha
 */ 

#include "ac.h"

u8 temperature;

void AC_init(void) {
  LM35_init_INT(TEMPERATURE_SENSOR_PIN, AC_ADC_TRIGGER);
  DIO_init(AC_PIN, AC_PORT, OUT);
  ADC_INT_init();
  }

ISR(ADC_vect){
  temperature = (u16)ADCL + ((u16)ADCH << 8);
  // Since the ADC is set to use the internal VREF of 2.56 V, the resolution of the ADC is 2.5 mV. This resolution allows to measure the temperature
  // out of the LM35 with a resolution of 0.25 degree celsius, since each 10mV  increment on the LM35 output is 1 degree C.
  // We divide the ADC reading by 10 to get the temperature in C. 
  PORTB = temperature;
  temperature /= 10;
  // If the temperature is higher than the maximum specified temperature, turn on the AC.
  if (temperature > AMBIENT_HIGH_TEMP) DIO_write(AC_PIN, AC_PORT, HIGH);
  // If the temperature became below the minimum specified temperature turn off the AC.
  if (temperature < AMBIENT_LOW_TEMP) DIO_write(AC_PIN, AC_PORT, LOW);
  }