/* 
 * File:   mcal_timer3.c
 * Author: AhmedSalah
 *
 * Created on September 14, 2023, 5:45 PM
 */



#include "mcal_timer3.h"


static void Timer3_Reg_Select(const timer3_t * timer3);
static void Timer3_Mode_Select(const timer3_t * timer3);

static uint16 preload_value;

#if TIMER3_INTERRUPT_FEATURE == TIMER3_INTERRUPT_FEATURE_ENABLE
    void (*Timer3_Interrupt_handler)(void);
#endif    


    
    
std_ReturnType Timer3_Initialization(const timer3_t * timer3)
{
    std_ReturnType ret=E_OK;
    if(NULL==timer3)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        Timer3_Feature_Disable();
        Timer3_Mode_Select(timer3);
        Timer3_Reg_Select(timer3);
        Timer3_Prescaler_Select(timer3->timer3_prescaler);
        TMR3H=(timer3->preload_value)>>8;
        TMR3L=(uint8)(timer3->preload_value);
        preload_value=timer3->preload_value;        
        /*Configure Interrupt*/
        #if TIMER3_INTERRUPT_FEATURE == TIMER3_INTERRUPT_FEATURE_ENABLE
            Timer3_Interrupt_handler=timer3->timer3_interrupt_handler;
            Timer3_Interrupt_Enable();
            Timer3_Interrupt_Clear_Flag();
        
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
            Interrupt_priority_Enable();
            if(INTERRUPT_HIGH_PRIORITY==timer3->priority)
            {
                Timer3_High_Priority();
                Interrupt_High_Priority_Enable();
            }
            else if(INTERRUPT_LOW_PRIORITY==timer3->priority)
            {
                Timer3_Low_Priority();
                Interrupt_Low_Priority_Enable();
            }
            else{/* Nothing*/}
        #else
            Interrupt_Global_Enable();
            Interrupt_Peripheral_Enable();
        #endif    
        #endif    

        Timer3_Feature_Enable();
    }
    return ret;
}


std_ReturnType Timer3_DeInitialization(const timer3_t * timer3)
{
    std_ReturnType ret=E_OK;
    if(NULL==timer3)
    {
        ret=E_NOT_OK;
    }    
    else
    {
    Timer3_Feature_Disable();    
    #if TIMER3_INTERRUPT_FEATURE == TIMER3_INTERRUPT_FEATURE_ENABLE
        
        Timer3_Interrupt_Disable();
    #endif    

    }
    return ret; 
}


std_ReturnType Timer3_Read_Value(const timer3_t * timer3,uint16 *value)
{
    std_ReturnType ret=E_OK;
    if(NULL==timer3 ||NULL==value)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        *value=TMR3L;
        *value=(uint16)(TMR3L+ (TMR3H<<8));
    }
    return ret;
}


std_ReturnType Timer3_Write_Value(const timer3_t * timer3,uint16 value)
{
    std_ReturnType ret=E_OK;
    if(NULL==timer3)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        TMR3H=value>>8;
        TMR3L=(uint8)value;
    }
    return ret;
}







static void Timer3_Reg_Select(const timer3_t * timer3)
{
    if(TIMER3_RW_REG_16_BIT==timer3->timer3_rw_reg)
    {
        Timer3_RW_Reg_16_Bit();
    }
    else if(TIMER3_RW_REG_8_BIT==timer3->timer3_rw_reg)
    {
        Timer3_RW_Reg_8_Bit();
    }
    else{/* Nothing*/}
}

static void Timer3_Mode_Select(const timer3_t * timer3)
{
    if(TIMER3_TIMER_MODE==timer3->timer3_mode)
    {
        Timer3_Timer_Mode();
    }
    else if(TIMER3_COUNTER_MODE==timer3->timer3_mode)
    {
        Timer3_Counter_Mode();
        if(TIMER3_EXTERNAL_CLOCK_SYNCHRONIZATION_ENABLE==timer3->timer3_sync_option)
        {
            Timer3_External_Clock_Synchronization_Enable();
        }
        else if(TIMER3_EXTERNAL_CLOCK_SYNCHRONIZATION_DISABLE==timer3->timer3_sync_option)
        {
            Timer3_External_Clock_Synchronization_Disable();
        }
        else{/* Nothing*/}
    }
    else{/* Nothing*/}
}


void Timer3_ISR(void)
{
    Timer3_Interrupt_Clear_Flag();
    TMR3H=(preload_value>>8);
    TMR3L=(uint8)(preload_value);
    if(Timer3_Interrupt_handler)
    {
        Timer3_Interrupt_handler();
    }    
}

