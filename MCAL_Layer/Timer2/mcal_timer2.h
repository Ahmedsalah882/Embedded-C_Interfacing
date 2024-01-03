/* 
 * File:   mcal_timer2.h
 * Author: AhmedSalah
 *
 * Created on September 17, 2023, 8:04 AM
 */

#ifndef MCAL_TIMER2_H
#define	MCAL_TIMER2_H


/* Section: Includes */
#include "pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
/* Section: Macro Declarations */
#define  TIMER2_POSTSCALER_DIV_1                                    0x00
#define  TIMER2_POSTSCALER_DIV_2                                    0x01
#define  TIMER2_POSTSCALER_DIV_3                                    0x02
#define  TIMER2_POSTSCALER_DIV_4                                    0x03
#define  TIMER2_POSTSCALER_DIV_5                                    0x04
#define  TIMER2_POSTSCALER_DIV_6                                    0x05
#define  TIMER2_POSTSCALER_DIV_7                                    0x06
#define  TIMER2_POSTSCALER_DIV_8                                    0x07
#define  TIMER2_POSTSCALER_DIV_9                                    0x08
#define  TIMER2_POSTSCALER_DIV_10                                   0x09
#define  TIMER2_POSTSCALER_DIV_11                                   0x0A
#define  TIMER2_POSTSCALER_DIV_12                                   0x0B
#define  TIMER2_POSTSCALER_DIV_13                                   0x0C
#define  TIMER2_POSTSCALER_DIV_14                                   0x0D
#define  TIMER2_POSTSCALER_DIV_15                                   0x0E
#define  TIMER2_POSTSCALER_DIV_16                                   0x0F
/* Section: Macro Functions */

#define Timer2_Feature_Enable()                                     (T2CONbits.TMR2ON=1)
#define Timer2_Feature_Disable()                                    (T2CONbits.TMR2ON=0)

#define Timer2_Prescaler_Select(_Prescaler)                         (T2CONbits.T2CKPS=_Prescaler)
#define Timer2_Postscaler_Select(_Postscaler)                       (T2CONbits.TOUTPS=_Postscaler)


/* Section: Data Type Declarations */
typedef enum{
    TIMER2_PRESCALER_DIV_BY_1,
    TIMER2_PRESCALER_DIV_BY_4,
    TIMER2_PRESCALER_DIV_BY_16        
}timer2_prescaler_t;

typedef struct{
    #if TIMER2_INTERRUPT_FEATURE == TIMER2_INTERRUPT_FEATURE_ENABLE
        void (*TIMER2_INTERRUPT_HANDLER)(void);
    #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
        interrupt_priority_t priority;
    #endif
    #endif
    timer2_prescaler_t timer2_prescaler;
    uint8 timer2_preload;
    uint8 timer2_postscaler  :4;
    uint8 reserved           :4;
}timer2_t;

/* Section: Function Prototype */

std_ReturnType Timer2_Init(const timer2_t* timer2);
std_ReturnType Timer2_DeInit(const timer2_t* timer2);
std_ReturnType Timer2_Read_Value(const timer2_t* timer2,uint8* value);
std_ReturnType Timer2_Write_Value(const timer2_t* timer2,uint8 value);

#endif	/* MCAL_TIMER2_H */

