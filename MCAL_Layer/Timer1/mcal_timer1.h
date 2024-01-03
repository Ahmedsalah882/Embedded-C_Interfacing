/* 
 * File:   mcal_timer1.h
 * Author: AhmedSalah
 *
 * Created on September 14, 2023, 4:44 AM
 */

#ifndef MCAL_TIMER1_H
#define	MCAL_TIMER1_H


/* Section :Includes */
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
/* Section: Macro Definitions */

#define TIMER1_COUNTER_MODE                                             0x01
#define TIMER1_TIMER_MODE                                               0x00

#define TIMER1_EXTERNAL_CLOCK_SYNCHRONIZATION_DISABLE                   0x01
#define TIMER1_EXTERNAL_CLOCK_SYNCHRONIZATION_ENABLE                    0x00

#define TIMER1_OSC_ENABLE                                               0X01
#define TIMER1_OSC_DISABLE                                              0X00


#define TIMER1_REG_READWRITE_16_BIT_MODE                                0x01
#define TIMER1_REG_READWRITE_8_BIT_MODE                                 0x00

/* Section: Macro Functions */

#define Timer1_Feature_Enable()                                         (T1CONbits.TMR1ON=1)
#define Timer1_Feature_Disable()                                        (T1CONbits.TMR1ON=0)

#define Timer1_Counter_Mode()                                           (T1CONbits.TMR1CS=1)
#define Timer1_Timer_Mode()                                             (T1CONbits.TMR1CS=0)

#define Timer1_External_Clock_Synchronization_Disable()                 (T1CONbits.T1SYNC=1)
#define Timer1_External_Clock_Synchronization_Enable()                  (T1CONbits.T1SYNC=0)


#define Timer1_OSC_Enable()                                             (T1CONbits.T1OSCEN=1)
#define Timer1_OSC_Disable()                                            (T1CONbits.T1OSCEN=0)

#define Timer1_Read_Clock_System_Status()                               (T1CONbits.T1RUN)

#define Timer1_Reg_ReadWrite_16_Bit_Mode()                              (T1CONbits.T1RD16=1)
#define Timer1_Reg_ReadWrite_8_Bit_Mode()                               (T1CONbits.T1RD16=0)    

#define Timer1_Prescaler_Value(_Prescaler)                              (T1CONbits.T1CKPS=_Prescaler)

/* Section: Data Type Declarations */
typedef enum{
    TIMER1_PRESCALER_DIV_BY_1,
    TIMER1_PRESCALER_DIV_BY_2,
    TIMER1_PRESCALER_DIV_BY_4,
    TIMER1_PRESCALER_DIV_BY_8,        
}timer1_prescalar_t;

typedef struct{
#if TIMER1_INTERRUPT_FEATURE == TIMER1_INTERRUPT_FEATURE_ENABLE    
    void (*Timer1_Interrupt_Handler)(void);
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE    
    interrupt_priority_t priority;
#endif    
#endif    
    timer1_prescalar_t prescaler_value;
    uint16 preload_value;
    uint8 timer1_mode           :1;
    uint8 timer1_sync           :1;
    uint8 timer1_osc_option     :1;
    uint8 timer1_rw_reg_mode    :1;
    uint8 reserved              :4;
}timer1_t;

/* Section: Function Prototype */
std_ReturnType Timer1_Initialization(const timer1_t* timer1 );
std_ReturnType Timer1_DeInitialization(const timer1_t* timer1);
std_ReturnType Timer1_Read_Value(const timer1_t* timer1, uint16* value);
std_ReturnType Timer1_Write_Value(const timer1_t* timer1, uint16 value);

void Timer1_ISR(void);
#endif	/* MCAL_TIMER1_H */

