/* 
 * File:   mcal_internal_interrupt.h
 * Author: AhmedSalah
 *
 * Created on August 31, 2023, 4:03 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H


/* Section: Includes */
#include "mcal_interrupt_config.h"


#if INTERRUPT_INTERNAL_FEATURE == INTERRUPT_INTERNAL_FEATURE_ENABLE


/* Section: Macro Functions */

/******************************************ADC Interrupt***************************/
/* Control ADC Interrupt */

#define ADC_Interrupt_Enable()                              (PIE1bits.ADIE=1)
#define ADC_Interrupt_Disable()                             (PIE1bits.ADIE=0)

/* Clear ADC Interrupt flag */
#define ADC_Interrupt_Flag_Clear()                          (PIR1bits.ADIF=0)


/****************************************Timer0 Inteerrupt***************************/
/* Control Timer0 Interrupt*/
#define Timer0_Interrupt_Enable()                           (INTCONbits.TMR0IE=1)
#define Timer0_Interrupt_Disable()                          (INTCONbits.TMR0IE=0)

/* Clear Timer0 Interrupt Flag*/
#define Timer0_Clear_Flag()                                 (INTCONbits.TMR0IF=0)        

/****************************************Timer1 Interrupt***************************/
/* Control Timer1 Interrupt*/
#define Timer1_Interrupt_Enable()                           (PIE1bits.TMR1IE=1)
#define Timer1_Interrupt_Disable()                          (PIE1bits.TMR1IE=0)

/*Clear Timer1 Interrupt Flag*/
#define Timer1_Interrupt_Clear_Flag()                       (PIR1bits.TMR1IF=0)

/****************************************Timer2 Interrupt***************************/
/* Control Timer2 Interrupt */
#define Timer2_Interrupt_Enable()                           (PIE1bits.TMR2IE=1)
#define Timer2_Interrupt_Disable()                          (PIE1bits.TMR2IE=0)

/* Clear Timer2 Interrupt Flag*/
#define Timer2_Interrupt_Clear_Flag()                       (PIR1bits.TMR2IF=0)

/****************************************Timer2 Interrupt***************************/
/****************************************Timer3 Interrupt***************************/
/* Control Timer2 Interrupt */
#define Timer3_Interrupt_Enable()                           (PIE2bits.TMR3IE=1)
#define Timer3_Interrupt_Disable()                          (PIE2bits.TMR3IE=0)

/* Clear Timer2 Interrupt Flag*/
#define Timer3_Interrupt_Clear_Flag()                       (PIR2bits.TMR3IF=0)

/****************************************CCP1 Interrupt***************************/
/* Control CCP1 Interrupt */
#define CCP1_Interrupt_Enable()                             (PIE1bits.CCP1IE=1)
#define CCP1_Interrupt_Disable()                            (PIE1bits.CCP1IE=0)

/* Clear CCP1 Interrupt Flag*/
#define CCP1_Interrupt_Clear_Flag()                         (PIR1bits.CCP1IF=0)

/****************************************CCP1 Interrupt***************************/

/****************************************CCP2 Interrupt***************************/
/* Control CCP2 Interrupt */
#define CCP2_Interrupt_Enable()                             (PIE2bits.CCP2IE=1)
#define CCP2_Interrupt_Disable()                            (PIE2bits.CCP2IE=0)

/* Clear CCP2 Interrupt Flag*/
#define CCP2_Interrupt_Clear_Flag()                         (PIR2bits.CCP2IF=0)

/****************************************CCP2 Interrupt***************************/
#endif

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE

/******************************************ADC Interrupt***************************/
#if ADC_INTERRUPT_FEATURE == ADC_INTERRUPT_FEATURE_ENABLE

#define ADC_Interrupt_High_Priority()                       (IPR1bits.ADIP=1)
#define ADC_Interrupt_Low_Priority()                        (IPR1bits.ADIP=0)

#endif
/******************************************ADC Interrupt***************************/
/******************************************Timer0 Interrupt***********************/
#if TIMER0_INTERRUPT_FEATURE == TIMER0_INTERRUPT_FEATURE_ENABLE

#define Timer0_High_Priority()                             (INTCON2bits.TMR0IP=1)
#define Timer0_Low_Priority()                              (INTCON2bits.TMR0IP=0)

#endif
/******************************************Timer0 Interrupt***********************/
/******************************************Timer1 Interrupt***********************/
#if TIMER1_INTERRUPT_FEATURE == TIMER1_INTERRUPT_FEATURE_ENABLE

#define Timer1_High_Priority()                             (IPR1bits.TMR1IP=1)
#define Timer1_Low_Priority()                              (IPR1bits.TMR1IP=0)

#endif
/******************************************Timer1 Interrupt***********************/
/******************************************Timer2 Interrupt***********************/
#if TIMER2_INTERRUPT_FEATURE == TIMER2_INTERRUPT_FEATURE_ENABLE

#define Timer2_High_Priority()                             (IPR1bits.TMR2IP=1)
#define Timer2_Low_Priority()                              (IPR1bits.TMR2IP=0)

#endif
/******************************************Timer2 Interrupt***********************/
/******************************************Timer3 Interrupt***********************/
#if TIMER3_INTERRUPT_FEATURE == TIMER3_INTERRUPT_FEATURE_ENABLE

#define Timer3_High_Priority()                             (IPR2bits.TMR3IP=1)
#define Timer3_Low_Priority()                              (IPR2bits.TMR3IP=0)

#endif
/******************************************CCP1 Interrupt***********************/
#if CCP1_INTERRUPT_FEATURE == CCP1_INTERRUPT_FEATURE_ENABLE
#define CCP1_High_Priority()                             (IPR1bits.CCP1IP=1)
#define CCP1_Low_Priority()                              (IPR1bits.CCP1IP=0)
#endif
/******************************************CCP1 Interrupt***********************/

/******************************************CCP2 Interrupt***********************/
#if CCP2_INTERRUPT_FEATURE == CCP2_INTERRUPT_FEATURE_ENABLE
#define CCP2_High_Priority()                             (IPR2bits.CCP2IP=1)
#define CCP2_Low_Priority()                              (IPR2bits.CCP2IP=0)
#endif
/******************************************CCP2 Interrupt***********************/

/****************************************** Interrupt***********************/



#endif
/* Section: Data Type Declarations */

/* Section: Function Prototypes */







#endif	/* MCAL_INTERNAL_INTERRUPT_H */


