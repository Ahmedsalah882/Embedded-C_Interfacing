/* 
 * File:   mcal_timer0.h
 * Author: AhmedSalah
 *
 * Created on September 13, 2023, 7:14 AM
 */

#ifndef MCAL_TIMER0_H
#define	MCAL_TIMER0_H


/* Section: Includes */
#include "pic18f4620.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* Section: Macro Definitions */

#define TIMER0_REG_SIZE_16_BIT                                      0x00
#define TIMER0_REG_SIZE_8_BIT                                       0x01

#define TIMER0_TIMER_MODE                                           0x00
#define TIMER0_COUNTER_MODE                                         0x01

#define TIMER0_EXTERNAL_SOURCE_RISING_EDGE                          0x00
#define TIMER0_EXTERNAL_SOURCE_FALLING_EDGE                         0x01

#define TIMER0_PRESCALER_ACTIVATED                                  0x01
#define TIMER0_PRESCALER_DEACTIVATED                                0x00            

/* Section: Macro Functions */

#define Timer0_Feature_Enable()                                     (T0CONbits.TMR0ON=1)
#define Timer0_Feature_Disable()                                    (T0CONbits.TMR0ON=0)

#define Timer0_Reg_Size_8_Bit()                                     (T0CONbits.T08BIT=1)
#define Timer0_Reg_Size_16_Bit()                                    (T0CONbits.T08BIT=0)

#define Timer0_Counter_Mode()                                       (T0CONbits.T0CS=1)
#define Timer0_Timer_Mode()                                         (T0CONbits.T0CS=0)

#define TIMER0_External_Source_Falling_Edge()                       (T0CONbits.T0SE=1)
#define TIMER0_External_Source_Rising_Edge()                        (T0CONbits.T0SE=0)

#define Timer0_Prescaler_Dectivated()                               (T0CONbits.PSA=1)
#define Timer0_Prescaler_Activated()                                (T0CONbits.PSA=0)


/* Section: Data Type Declarations*/
typedef enum{
    TIMER0_PRESCALER_DIV_BY_2,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,        
    TIMER0_PRESCALER_DIV_BY_16,        
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,        
    TIMER0_PRESCALER_DIV_BY_128,        
    TIMER0_PRESCALER_DIV_BY_256        
}timer0_prescaler_t;

typedef struct {
    #if TIMER0_INTERRUPT_FEATURE == TIMER0_INTERRUPT_FEATURE_ENABLE
        void (*Timer0InterruptHandler) (void);
    #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
        interrupt_priority_t  priority;  
    #endif
    #endif
    timer0_prescaler_t prescalar_value;
    uint16 preloaded_value;
    uint8 timer0_reg_size       :1;
    uint8 timer0_mode           :1;
    uint8 edge_source           :1;        
    uint8 prescaler_option      :1;
    uint8 reserved              :4;          
}timer0_t;

/* Section: Function Prototypes */
std_ReturnType Timer0_Initialize(const timer0_t* timer0);
std_ReturnType Timer0_Deinitialization(const timer0_t* timer0);
std_ReturnType Timer0_Read_Value(const timer0_t* timer0,uint16* value);
std_ReturnType Timer0_Write_Value(const timer0_t* timer0,uint16 value);

void Timer0_ISR(void);




#endif	/* MCAL_TIMER0_H */

