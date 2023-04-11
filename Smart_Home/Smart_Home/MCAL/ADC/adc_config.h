/*
 * adc_config.h
 *
 * Created: 3/28/2023 9:53:54 PM
 *  Author: hesha
 */ 


#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#define ADC_VREF INTERNAL_VREF

#define AREF 0
#define AVCC 1
#define INTERNAL_VREF 2

#define FREE_RUNNING_MODE_TRIGGER         0
#define ANALOG_COMPARATOR_TRIGGER         1
#define INT0_TRIGGER                      2
#define TIMER_0_COMPARE_MATCH_TRIGGER     3
#define TIMER_0_OVF_TRIGGER               4
#define TIMER_1_COMPARE_MATCH_B_TRIGGER   5
#define TIMER_1_OVF_TRIGGER               6

#endif /* ADC_CONFIG_H_ */