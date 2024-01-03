/* 
 * File:   mcal_timer3.h
 * Author: AhmedSalah
 *
 * Created on September 14, 2023, 5:45 PM
 */

#ifndef MCAL_TIMER3_H
#define	MCAL_TIMER3_H

/* Section: Includes*/
#include "pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
/* Section: Macro Definitions */
#define TIMER3_TIMER_MODE                                             0x00
#define TIMER3_COUNTER_MODE                                           0x01

#define TIMER3_EXTERNAL_CLOCK_SYNCHRONIZATION_ENABLE                  0x00
#define TIMER3_EXTERNAL_CLOCK_SYNCHRONIZATION_DISABLE                 0x01

#define TIMER3_RW_REG_8_BIT                                           0x00
#define TIMER3_RW_REG_16_BIT                                          0x01


/* Section: Macro Function */
#define Timer3_Feature_Enable()                                       (T3CONbits.TMR3ON=1)
#define Timer3_Feature_Disable()                                      (T3CONbits.TMR3ON=0)

#define Timer3_Counter_Mode()                                         (T3CONbits.TMR3CS=1)
#define Timer3_Timer_Mode()                                           (T3CONbits.TMR3CS=0)  

#define Timer3_External_Clock_Synchronization_Disable()               (T3CONbits.T3SYNC=1)
#define Timer3_External_Clock_Synchronization_Enable()                (T3CONbits.T3SYNC=0) 

#define Timer3_RW_Reg_16_Bit()                                        (T3CONbits.RD16=1)  
#define Timer3_RW_Reg_8_Bit()                                         (T3CONbits.RD16=0)


#define Timer3_Prescaler_Select(_Prescaler)                           (T3CONbits.T3CKPS=_Prescaler)  



/* Section: Data Type Declaration */
typedef enum{
    TIMER3_PRESCALER_DIV_BY_1,
    TIMER3_PRESCALER_DIV_BY_2,
    TIMER3_PRESCALER_DIV_BY_4,
    TIMER3_PRESCALER_DIV_BY_8,        
}timer3_prescaler_t;


typedef struct{
#if TIMER3_INTERRUPT_FEATURE == TIMER3_INTERRUPT_FEATURE_ENABLE
    void (*timer3_interrupt_handler)(void);
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE  
    interrupt_priority_t   priority;
#endif
#endif    
    timer3_prescaler_t timer3_prescaler;
    uint16 preload_value;

    uint8 timer3_rw_reg      :1;
    uint8 timer3_mode        :1;
    uint8 timer3_sync_option :1;
    uint8 reserved           :5;
}timer3_t;

/* Section: Function Prototype */
std_ReturnType Timer3_Initialization(const timer3_t * timer3);
std_ReturnType Timer3_DeInitialization(const timer3_t * timer3);
std_ReturnType Timer3_Read_Value(const timer3_t * timer3,uint16 *value);
std_ReturnType Timer3_Write_Value(const timer3_t * timer3,uint16 value);


void Timer3_ISR(void);


#endif	/* MCAL_TIMER3_H */

