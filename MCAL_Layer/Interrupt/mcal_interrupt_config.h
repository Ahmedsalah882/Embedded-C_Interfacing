/* 
 * File:   mcal_interrupt_config.h
 * Author: AhmedSalah
 *
 * Created on August 31, 2023, 8:16 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H


/* Section: Includes */
#include "pic18f4620.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/mcal_std_types.h"
/* Section: Macro Definitions */
#define INTERRUPT_FEATURE                                   INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_FEATURE_ENABLE                            0x01
#define INTERRUPT_FEATURE_DISABLE                           0x00

#define INTERRUPT_OCCUR                                     0x01               
#define INTERRUPT_NOT_OCCUR                                 0x00

#define INTERRUPT_PRIORITY_FEATURE                          INTERRUPT_PRIORITY_FEAUTURE_DISABLE
#define INTERRUPT_PRIORITY_FEAUTURE_ENABLE                  0x01
#define INTERRUPT_PRIORITY_FEAUTURE_DISABLE                 0x00

#define INTERRUPT_EXTERNAL_FEATURE                          INTERRUPT_EXTERNAL_FEATURE_ENABLE    
#define INTERRUPT_EXTERNAL_FEATURE_ENABLE                   0x01
#define INTERRUPT_EXTERNAL_FEATURE_DISABLE                  0x00

#define INTERRUPT_INTERNAL_FEATURE                          INTERRUPT_INTERNAL_FEATURE_ENABLE
#define INTERRUPT_INTERNAL_FEATURE_ENABLE                   0x01
#define INTERRUPT_INTERNAL_FEATURE_DISABLE                  0x00


#define ADC_INTERRUPT_FEATURE                               ADC_INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_FEATURE_ENABLE                        0x01
#define ADC_INTERRUPT_FEATURE_DISABLE                       0x00

#define TIMER0_INTERRUPT_FEATURE                            TIMER0_INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_FEATURE_ENABLE                     0x01
#define TIMER0_INTERRUPT_FEATURE_DISABLE                    0x00

#define TIMER1_INTERRUPT_FEATURE                            TIMER1_INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEATURE_ENABLE                     0x01
#define TIMER1_INTERRUPT_FEATURE_DISABLE                    0x00

#define TIMER2_INTERRUPT_FEATURE                            TIMER2_INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEATURE_ENABLE                     0x01
#define TIMER2_INTERRUPT_FEATURE_DISABLE                    0x00


#define TIMER3_INTERRUPT_FEATURE                            TIMER3_INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEATURE_ENABLE                     0x01
#define TIMER3_INTERRUPT_FEATURE_DISABLE                    0x00

#define CCP1_INTERRUPT_FEATURE                              CCP1_INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUPT_FEATURE_ENABLE                       0x01
#define CCP1_INTERRUPT_FEATURE_DISABLE                      0x00

#define CCP2_INTERRUPT_FEATURE                              CCP2_INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE_ENABLE                       0x01
#define CCP2_INTERRUPT_FEATURE_DISABLE                      0x00

/* Section: Macro Functions */
#if INTERRUPT_FEATURE==INTERRUPT_FEATURE_ENABLE 

/* Control Priority Feature */
#define Interrupt_priority_Enable()                          (RCONbits.IPEN=1)
#define Interrupt_priority_Disable()                         (RCONbits.IPEN=0)

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
/* Priority Feature Enabled */

/* Control High Priority Feature */
#define Interrupt_High_Priority_Enable()                     (INTCONbits.GIEH=1)
#define Interrupt_High_Priority_Disable()                    (INTCONbits.GIEH=0)

/* Control Low Priority Feature */
#define Interrupt_Low_Priority_Enable()                      (INTCONbits.GIEL=1)
#define Interrupt_Low_Priority_Disable()                     (INTCONbits.GIEL=0)

#else 
/* Priority Feature Disabled */

/* Control Global Interrupt Feature */
#define Interrupt_Global_Enable()                            (INTCONbits.GIE=1)
#define Interrupt_Global_Disable()                           (INTCONbits.GIE=0)

/* Control Peripheral Interrupt Feature */
#define Interrupt_Peripheral_Enable()                        (INTCONbits.PEIE=1)
#define Interrupt_Peripheral_Disable()                       (INTCONbits.PEIE=0)


#endif

#endif

/* Section: Data Type Declarations */
typedef enum{
    INTERRUPT_LOW_PRIORITY,
    INTERRUPT_HIGH_PRIORITY        
}interrupt_priority_t;
/* Section: Function Prototypes */



#endif	/* MCAL_INTERRUPT_CONFIG_H */

