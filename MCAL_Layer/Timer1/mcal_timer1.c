/* 
 * File:   mcal_timer1.c
 * Author: AhmedSalah
 *
 * Created on September 14, 2023, 4:44 AM
 */



#include "mcal_timer1.h"

static void Timer1_Mode_Select(const timer1_t* timer1);
static void Timer1_OSC_Select(const timer1_t* timer1);
static void Timer1_RW_Mode(const timer1_t* timer1);

static uint16 preload_value=ZERO_INIT;

#if TIMER1_INTERRUPT_FEATURE == TIMER1_INTERRUPT_FEATURE_ENABLE
void (*TIMER1_INTERRUT_HANDLER)(void)=NULL;
#endif 


/**
 * @brief Init the timer1 feature
 * @param timer1
 * @return status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed   
 */
std_ReturnType Timer1_Initialization(const timer1_t* timer1 )
{
    std_ReturnType ret=E_OK;
    if(NULL== timer1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        Timer1_Feature_Disable();
        Timer1_Mode_Select(timer1);
        Timer1_OSC_Select(timer1);
        Timer1_RW_Mode(timer1);
        Timer1_Prescaler_Value(timer1->prescaler_value);
        TMR1H=(timer1->preload_value >>8);
        TMR1L=(uint8)(timer1->preload_value);
        preload_value=timer1->preload_value;
        /*CONFIG TIMER1 Interrupt*/
        #if TIMER1_INTERRUPT_FEATURE == TIMER1_INTERRUPT_FEATURE_ENABLE
            TIMER1_INTERRUT_HANDLER=timer1->Timer1_Interrupt_Handler;
            Timer1_Interrupt_Enable();
            Timer1_Interrupt_Clear_Flag();
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
            Interrupt_priority_Enable();
            if(INTERRUPT_LOW_PRIORITY=timer1->priority)
            {
                 Timer1_Low_Priority();
                 Interrupt_High_Priority_Enable();
            }
            else if(INTERRUPT_HIGH_PRIORITY=timer1->priority)
            {
                 Timer1_High_Priority();
                 Interrupt_Low_Priority_Enable();
            }
            else{ /* Nothing */}
         
        #else   
            Interrupt_Global_Enable();
            Interrupt_Peripheral_Enable();
        #endif
        #endif 
        Timer1_Feature_Enable();
    } 
    return ret;
}

/**
 * @brief Deinit the timer1 feature 
 * @param timer1
 * @return status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed   
 */
std_ReturnType Timer1_DeInitialization(const timer1_t* timer1)
{
    std_ReturnType ret=E_OK;
    if(NULL== timer1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        Timer1_Feature_Disable();
        #if TIMER1_INTERRUPT_FEATURE == TIMER1_INTERRUPT_FEATURE_ENABLE
            
            Timer1_Interrupt_Disable();
        
        #endif        
    } 
    return ret;
}

/**
 * @brief reading the value inside the timer1 reg and store it in a varable through pointer 
 * @param timer1
 * @param value
 * @return status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed    
 */
std_ReturnType Timer1_Read_Value(const timer1_t* timer1, uint16* value)
{
    std_ReturnType ret=E_OK;
    if(NULL== timer1 || NULL== value)
    {
        ret=E_NOT_OK;
    }
    else
    {
        *value=TMR1L;
        *value= (uint16 )(TMR1L + (TMR1H<<8));
    } 
    return ret;
}

/**
 * @brief writing a value in the timer1 reg
 * @param timer1
 * @param value
 * @return status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed   
 */
std_ReturnType Timer1_Write_Value(const timer1_t* timer1, uint16 value)
{
    std_ReturnType ret=E_OK;
    if(NULL== timer1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        TMR1H= value>>8;
        TMR1L= (uint8)value;
    } 
    return ret;
}        
        
        
        
 static void Timer1_Mode_Select(const timer1_t* timer1)
 {
     if(TIMER1_TIMER_MODE==timer1->timer1_mode)
     {
         Timer1_Timer_Mode();
     }
     else if(TIMER1_COUNTER_MODE==timer1->timer1_mode)
     {
         Timer1_Counter_Mode();
         if(TIMER1_EXTERNAL_CLOCK_SYNCHRONIZATION_ENABLE==timer1->timer1_sync)
         {
             Timer1_External_Clock_Synchronization_Enable();
         }
         else if(TIMER1_EXTERNAL_CLOCK_SYNCHRONIZATION_DISABLE==timer1->timer1_sync)
         {
             Timer1_External_Clock_Synchronization_Disable();
         }  
         else { /* Nothing*/}        
     }
     else{ /* Nothing */}
 }
        
        
static void Timer1_OSC_Select(const timer1_t* timer1)
{
    if(TIMER1_OSC_ENABLE==timer1->timer1_osc_option)
     {
         Timer1_OSC_Enable();
     }
     else if(TIMER1_OSC_DISABLE==timer1->timer1_mode)
     {
         Timer1_OSC_Disable();
                 
     }
     else{ /* Nothing */}
}
        

static void Timer1_RW_Mode(const timer1_t* timer1)
{
    if(TIMER1_REG_READWRITE_16_BIT_MODE==timer1->timer1_rw_reg_mode)
     {
         Timer1_Reg_ReadWrite_16_Bit_Mode();
     }
     else if(TIMER1_REG_READWRITE_8_BIT_MODE==timer1->timer1_mode)
     {
         Timer1_Reg_ReadWrite_8_Bit_Mode();
                 
     }
     else{ /* Nothing */}
}
        
        


void Timer1_ISR(void)
{
    Timer1_Interrupt_Clear_Flag();
    TMR1H=(preload_value >>8);
    TMR1L=(uint8)(preload_value);        
    if(TIMER1_INTERRUT_HANDLER)
    {
        TIMER1_INTERRUT_HANDLER();
    }
    else{/* Nothing */}
}




