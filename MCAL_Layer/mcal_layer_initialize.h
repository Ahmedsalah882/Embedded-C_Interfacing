/* 
 * File:   mcal_layer_initialize.h
 * Author: AhmedSalah
 *
 * Created on September 4, 2023, 3:48 AM
 */

#ifndef MCAL_LAYER_INITIALIZE_H
#define	MCAL_LAYER_INITIALIZE_H

/* Section: Includes */
#include "Interrupt/mcal_external_interrupt.h"
#include "ADC/mcal_adc.h"
#include"EEPROM/mcal_eeprom.h"
#include "Timer0/mcal_timer0.h"
#include "Timer1/mcal_timer1.h"
#include "Timer2/mcal_timer2.h"
#include "Timer3/mcal_timer3.h"
#include "CCP1/mcal_ccp1.h"
/* Section: Function Prototypes */
void mcal_initialize(void);
//ADC_Initialize(&adc1);
void eeprom_feature(void);

void ADC_DEFAULT_INTERRUPT_HANDLER(void);
void ADC_3_POT(void);

void timer0_test(void);

#endif	/* MCAL_LAYER_INITIALIZE_H */

