/* 
 * File:   mcal_timer2.h
 * Author: AhmedSalah
 *
 * Created on September 17, 2023, 8:04 AM
 */


#include "mcal_timer2.h"


#if TIMER2_INTERRUPT_FEATURE == TIMER2_INTERRUPT_FEATURE_ENABLE
void (*Timer_Interrupt_handler)(void);
#endif

static uint8 preload;

std_ReturnType Timer2_Init(const timer2_t* timer2)
{
    std_ReturnType ret=E_OK;
    if(NULL==timer2)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        Timer2_Feature_Disable();
        Timer2_Prescaler_Select(timer2->timer2_prescaler);
        Timer2_Postscaler_Select(timer2->timer2_postscaler);
        TMR2=timer2->timer2_preload;
        preload=timer2->timer2_preload;
        #if TIMER2_INTERRUPT_FEATURE == TIMER2_INTERRUPT_FEATURE_ENABLE
            Timer2_Interrupt_Enable();
            Timer2_Interrupt_Clear_Flag();
            Timer_Interrupt_handler=timer2->TIMER2_INTERRUPT_HANDLER;
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
            Interrupt_priority_Enable();
            if(INTERRUPT_HIGH_PRIORITY==timer2->priority)
            {
                Interrupt_High_Priority_Enable();
                Timer2_High_Priority();
            }
            else if(INTERRUPT_LOW_PRIORITY==timer2->priority)
            {
                Interrupt_Low_Priority_Enable();
                Timer2_Low_Priority();
            }
        
        #else
            Interrupt_Global_Enable();
            Interrupt_Peripheral_Enable();
        #endif
        #endif
        Timer2_Feature_Enable();
    }   
    return ret;
}


std_ReturnType Timer2_DeInit(const timer2_t* timer2)
{
    std_ReturnType ret=E_OK;
    if(NULL==timer2)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        Timer2_Feature_Disable();
        #if TIMER2_INTERRUPT_FEATURE == TIMER2_INTERRUPT_FEATURE_ENABLE
            Timer2_Interrupt_Disable();
        #endif
    }   
    return ret;
}


std_ReturnType Timer2_Read_Value(const timer2_t* timer2,uint8* value)
{
    std_ReturnType ret=E_OK;
    if(NULL==timer2 || NULL==value)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        *value=TMR2;
    }   
    return ret;
}


std_ReturnType Timer2_Write_Value(const timer2_t* timer2,uint8 value)
{
    std_ReturnType ret=E_OK;
    if(NULL==timer2)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        TMR2=value;
    }   
    return ret;
}


void Timer2_ISR(void)
{
    Timer2_Interrupt_Clear_Flag();
    TMR2=preload;
    if(Timer_Interrupt_handler)
    {
        Timer_Interrupt_handler();
    }
    
}


