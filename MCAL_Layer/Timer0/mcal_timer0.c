/* 
 * File:   mcal_timer0.h
 * Author: AhmedSalah
 *
 * Created on September 13, 2023, 7:14 AM
 */

#include "mcal_timer0.h"

static std_ReturnType Timer0_Select_Mode(const timer0_t* timer0);
static std_ReturnType Timer0_Select_Prescaler_Value(const timer0_t* timer0);
static std_ReturnType Timer0_Select_Reg_Size(const timer0_t* timer0);
static std_ReturnType Timer0_Select_Edge_Source(const timer0_t* timer0);

static uint16 timer0_preload=ZERO_INIT;

#if TIMER0_INTERRUPT_FEATURE == TIMER0_INTERRUPT_FEATURE_ENABLE
static void (*Timer0_Interrupt_Handler) (void)=NULL;
#endif

/**
 * @brief initialize timer0
 * @param timer0
 * @return status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed   
 */
std_ReturnType Timer0_Initialize(const timer0_t* timer0)
{
    std_ReturnType ret=E_OK;
    if(NULL== timer0)
    {
        ret=E_NOT_OK;
    }
    else
    {
        Timer0_Feature_Disable();
        ret=Timer0_Select_Mode(timer0);
        ret=Timer0_Select_Prescaler_Value(timer0);
        ret=Timer0_Select_Reg_Size(timer0); 
        ret=Timer0_Write_Value(timer0,timer0->preloaded_value);
        timer0_preload=timer0->preloaded_value;
        /*configure interrupt*/ 
        #if TIMER0_INTERRUPT_FEATURE == TIMER0_INTERRUPT_FEATURE_ENABLE
            Timer0_Interrupt_Enable();
            Timer0_Clear_Flag();
            Timer0_Interrupt_Handler=timer0->Timer0InterruptHandler;
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
            Interrupt_priority_Enable();
            if(INTERRUPT_HIGH_PRIORITY==timer0->priority)
            {
                Timer0_High_Priority()
                Interrupt_High_Priority_Enable();
            }
            else if(INTERRUPT_LOW_PRIORITY==timer0->priority)
            {
                Timer0_Low_Priority();
                Interrupt_Low_Priority_Enable();
            }
            else {/* Nothing*/}
        #else
            Interrupt_Global_Enable();
            Interrupt_Peripheral_Enable();  
        #endif
        #endif    
        Timer0_Feature_Enable();
    }
    return ret;
}

/**
 * @brief Deinitialize Timer0
 * @param timer0
 * @return status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed  
 */
std_ReturnType Timer0_Deinitialization(const timer0_t* timer0)
{
   std_ReturnType ret=E_OK;
    if(NULL== timer0)
    {
        ret=E_NOT_OK;
    }
    else
    {
        Timer0_Feature_Disable();
        #if TIMER0_INTERRUPT_FEATURE == TIMER0_INTERRUPT_FEATURE_ENABLE
                
            Timer0_Interrupt_Disable();
        
        #endif
    }
    return ret; 
}

/**
 * @brief Reading the value inside Timer0
 * @param timer0
 * @param value
 * @return status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed  
 */
std_ReturnType Timer0_Read_Value(const timer0_t* timer0,uint16* value)
{
    std_ReturnType ret=E_OK;
    if(NULL== timer0 || NULL== value)
    {
        ret=E_NOT_OK;
    }
    else
    {
        *value=TMR0L;
        *value=(uint16)(TMR0L+ (TMR0H <<8));
    }
    return ret;
}

/**
 * @brief Writing  value inside Timer0 
 * @param timer0
 * @param value
 * @return status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed  
 */
std_ReturnType Timer0_Write_Value(const timer0_t* timer0,uint16 value)
{
    std_ReturnType ret=E_OK;
    if(NULL== timer0)
    {
        ret=E_NOT_OK;
    }
    else
    {
        TMR0H=(value>>8);
        TMR0L=(uint8)(value);
    }
    return ret;
}



static std_ReturnType Timer0_Select_Mode(const timer0_t* timer0)
{
    std_ReturnType ret=E_OK;
    if(NULL== timer0)
    {
        ret=E_NOT_OK;
    }
    else
    {
        if(TIMER0_TIMER_MODE==timer0->timer0_mode)
        {
            Timer0_Timer_Mode();
        }
        else if(TIMER0_COUNTER_MODE==timer0->timer0_mode)
        {
            Timer0_Counter_Mode();
            ret=Timer0_Select_Edge_Source(timer0);
        }
        else {/* No thing*/}
    }
    return ret;
}

static std_ReturnType Timer0_Select_Prescaler_Value(const timer0_t* timer0)
{
    std_ReturnType ret=E_OK;
    if(NULL== timer0)
    {
        ret=E_NOT_OK;
    }
    else
    {
        if(TIMER0_PRESCALER_ACTIVATED==timer0->prescaler_option)
        {
            Timer0_Prescaler_Activated();
            T0CONbits.T0PS=timer0->prescalar_value;
        }
        
        else 
        {
         Timer0_Prescaler_Dectivated();   
        }
    }
    return ret;
}


static std_ReturnType Timer0_Select_Reg_Size(const timer0_t* timer0)
{
    std_ReturnType ret=E_OK;
    if(NULL== timer0)
    {
        ret=E_NOT_OK;
    }
    else
    {
        if(TIMER0_REG_SIZE_8_BIT==timer0->timer0_reg_size)
        {
            Timer0_Reg_Size_8_Bit();
        }
        else if(TIMER0_REG_SIZE_16_BIT==timer0->timer0_reg_size)
        {
            Timer0_Reg_Size_16_Bit();
        }
        else {/* No thing*/}
    }
    return ret;
}




static std_ReturnType Timer0_Select_Edge_Source(const timer0_t* timer0)
{
    std_ReturnType ret=E_OK;
    if(NULL== timer0)
    {
        ret=E_NOT_OK;
    }
    else
    {
        if(TIMER0_EXTERNAL_SOURCE_RISING_EDGE==timer0->edge_source)
        {
            TIMER0_External_Source_Rising_Edge();
        }
        else if(TIMER0_EXTERNAL_SOURCE_FALLING_EDGE==timer0->edge_source)
        {
            TIMER0_External_Source_Falling_Edge();
        }
        else {/* No thing*/}
    }
    return ret;
}

void Timer0_ISR(void)
{
    Timer0_Clear_Flag();
    TMR0H=(timer0_preload >>8);
    TMR0L=(uint8)timer0_preload;
    if(Timer0_Interrupt_Handler)
    {
        Timer0_Interrupt_Handler();
    }  
}




