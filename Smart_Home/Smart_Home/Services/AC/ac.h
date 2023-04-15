/*
 * ac.h
 *
 * Created: 4/14/2023 6:24:38 AM
 *  Author: Hesham Hany
 */

 //? According to the specifications and requirements, the temperature control has to be automatic only, a manual mode is not required.
 //? In other words, the system doesn't have to include a manual control option for the user to turn the AC on and off(Like the lamps for example).

 // TODO: Add manual control option

#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include "../../HAL/LM35/lm35.h"
#include "../../MCAL/Timer/timer.h"
#include "../../MCAL/Interrupts/interrupts.h"

#define AMBIENT_HIGH_TEMP  28
#define AMBIENT_LOW_TEMP   21

#define AMBIENT_HIGH_TEMP_ADC_VAL  112
#define AMBIENT_LOW_TEMP_ADC_VAL   84

//  The temperature sensor has to be on port A, since it must be connected to the ADC
#define TEMPERATURE_SENSOR_PIN   7

#define AC_PIN   7
#define AC_PORT  PORT_C

#define AC_ADC_TRIGGER TIMER_0_OVF_TRIGGER

#define TIMER_0_TOV_RESET_METHOD TIMER_0_TOV_RESET_VIA_ADC_COMPLETE_INTERRUPT
#define TIMER_0_TOV_RESET_VIA_ADC_COMPLETE_INTERRUPT    0
#define TIMER_0_TOV_RESET_BY_ACTIVATING_TIMER0_OVF_INT  1

void AC_auto_control_service_start(void);

void AC_auto_control_service_stop(void);

#endif /* TEMPERATURE_H_ */