/* 
 * File:   mcal_interrupt_manager.h
 * Author: AhmedSalah
 *
 * Created on August 31, 2023, 8:52 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H


/* Section: Includes */
#include "mcal_interrupt_config.h"

/* Section: Macro Definitions */

/* Section: Macro Functions */

/* Section: Data Type Declarations */

/* Section: Function Prototypes */
/*****************************************External Interrupt*******************/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8 RB_logic_Source);
void RB5_ISR(uint8 RB_logic_Source);
void RB6_ISR(uint8 RB_logic_Source);
void RB7_ISR(uint8 RB_logic_Source);

/*****************************************Internal Interrupt*******************/
void ADC_ISR(void);
void Timer0_ISR(void);
void Timer1_ISR(void);
void Timer2_ISR(void);
void Timer3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

