/* 
 * File:   mcal_ccp1.c
 * Author: AhmedSalah
 *
 * Created on September 15, 2023, 10:44 AM
 */



#include "mcal_ccp1.h"

static void CCP_Select_Mode(const ccp1_t* ccp1);

#if CCP1_INTERRUPT_FEATURE == CCP1_INTERRUPT_FEATURE_ENABLE
    void (*CCP1_Interrupt_handler)(void);
#endif

std_ReturnType CCP1_Initialization(const ccp1_t* ccp1)
{
    std_ReturnType ret=E_OK;
    if(NULL== ccp1)
    {
        ret=E_NOT_OK;
    }
    else
    {
       /*Discale CCP_Module*/
       CCP1_Mode_Options(CCP1_MODE_DISABLED);
       /*Select CCP_mode*/
       CCP_Select_Mode(ccp1);
       /*config pin direction*/
       ret=gpio_pin_direction_inialize(&(ccp1->ccp1_pin));
       /*conffig interrupt*/
       #if CCP1_INTERRUPT_FEATURE == CCP1_INTERRUPT_FEATURE_ENABLE
            CCP1_Interrupt_Enable();
            CCP1_Interrupt_Clear_Flag();
            CCP1_Interrupt_handler=ccp1->CCP1_Interrupt_handler;
       #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
            Interrupt_priority_Enable();
            if(INTERRUPT_LOW_PRIORITY==ccp1->priority)
            {
                CCP1_Low_Priority();
                Interrupt_Low_Priority_Enable();
            }
            else if(INTERRUPT_HIGH_PRIORITY==ccp1->priority)
            {
                CCP1_High_Priority();
                Interrupt_High_Priority_Enable();
            }
            else{/*Nothing*/}
            
       #else
            Interrupt_Global_Enable();
            Interrupt_Peripheral_Enable();
       #endif     
       #endif
    } 
    return ret;
}

std_ReturnType CCP1_DeInitialization(const ccp1_t* ccp1)
{
    std_ReturnType ret=E_OK;
    if(NULL== ccp1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        CCP1_Mode_Options(CCP1_MODE_DISABLED);
        #if CCP1_INTERRUPT_FEATURE == CCP1_INTERRUPT_FEATURE_ENABLE
            CCP1_Interrupt_Disable();
        #endif
    } 
    return ret;
}

#if CCP1_Mode_Selected == CCP1_Capture_Mode_Selected
std_ReturnType CCP1_IS_Capture_Data_Ready(uint8* status)
{
    std_ReturnType ret=E_OK;
    if(NULL== status)
    {
        ret=E_NOT_OK;
    }
    else
    {
           
    } 
    return ret;
}

std_ReturnType CCP1_Read_Capture_Data(const ccp1_t* ccp1, uint16* data)
{
    std_ReturnType ret=E_OK;
    if(NULL== ccp1)
    {
        ret=E_NOT_OK;
    }
    else
    {
           
    } 
    return ret;
}


#endif


#if CCP1_Mode_Selected == CCP1_Compare_Mode_Selected

std_ReturnType CCP1_IS_Compare_Data_Ready(uint8* status)
{
    std_ReturnType ret=E_OK;
    if(NULL== status)
    {
        ret=E_NOT_OK;
    }
    else
    {
           
    } 
    return ret;
}

std_ReturnType CCP1_Write_Compare_Data(const ccp1_t* ccp1, uint16 data)
{
    std_ReturnType ret=E_OK;
    if(NULL== ccp1)
    {
        ret=E_NOT_OK;
    }
    else
    {
           
    } 
    return ret;
}

#endif


#if CCP1_Mode_Selected == CCP1_PWM_Mode_Selected


std_ReturnType CCP1_Set_DutyCycle(const ccp1_t* ccp1,const uint8 duty)
{
    std_ReturnType ret=E_OK;
    if(NULL== ccp1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        uint16 _duty;
        _duty=(uint16)( (duty/100.0) *4*(PR2+1));
        CCP1CONbits.DC1B=(uint8)(_duty & 0x0003);
        CCPR1L=(uint8)(_duty>>2);
    } 
    return ret;
}


#endif





static void CCP_Select_Mode(const ccp1_t* ccp1)
{
    if(CCP1_MODE_CAPTURE==ccp1->ccp1_source)
    {
        if(CCP1_CAPTURE_MODE_EVERY_FALLING_EDGE==ccp1->sub_mode)
        {
            CCP1_Mode_Options(CCP1_CAPTURE_MODE_EVERY_FALLING_EDGE);
        }
        else if(CCP1_CAPTURE_MODE_EVERY_RISING_EDGE==ccp1->sub_mode)
        {
            CCP1_Mode_Options(CCP1_CAPTURE_MODE_EVERY_RISING_EDGE);
        }
        else if(CCP1_CAPTURE_MODE_EVERY_4_RISING_EDGE==ccp1->sub_mode)
        {
            CCP1_Mode_Options(CCP1_CAPTURE_MODE_EVERY_4_RISING_EDGE);
        }
        else if(CCP1_CAPTURE_MODE_EVERY_16_RISING_EDGE==ccp1->sub_mode)
        {
            CCP1_Mode_Options(CCP1_CAPTURE_MODE_EVERY_16_RISING_EDGE);
        }
        else {/*Nothing*/}
    }
    else if(CCP1_MODE_COMPARE==ccp1->ccp1_source)
    {
        if(CCP1_COMPARE_MODE_TOGGLE_PIN_ON_MATCH==ccp1->sub_mode)
        {
            CCP1_Mode_Options(CCP1_COMPARE_MODE_TOGGLE_PIN_ON_MATCH);
        }
        else if(CCP1_COMPARE_MODE_HIGH_PIN_ON_MATCH==ccp1->sub_mode)
        {
            CCP1_Mode_Options(CCP1_COMPARE_MODE_HIGH_PIN_ON_MATCH);
        }
        else if(CCP1_COMPARE_MODE_LOW_PIN_ON_MATCH==ccp1->sub_mode)
        {
            CCP1_Mode_Options(CCP1_COMPARE_MODE_LOW_PIN_ON_MATCH);
        }
        else if(CCP1_COMPARE_MODE_ON_MATCH_GEN_SW_INTERRUPT==ccp1->sub_mode)
        {
            CCP1_Mode_Options(CCP1_COMPARE_MODE_ON_MATCH_GEN_SW_INTERRUPT);
        }
        else if(CCP1_COMPARE_MODE_REST_TIMER_ON_MATCH==ccp1->sub_mode)
        {
            CCP1_Mode_Options(CCP1_COMPARE_MODE_REST_TIMER_ON_MATCH);
        }
        else {/*Nothing*/}
    }
    else if(CCP1_MODE_PWM==ccp1->ccp1_source)
    {
        uint16 l_duty;
        PR2= (_XTAL_FREQ / (4*ccp1->pwm_freq*ccp1->postscaler_value*ccp1->prescaler_value))-1;
        l_duty=((ccp1->duty_cycle /100.0)*4)*(PR2+1);
        CCP1CONbits.DC1B=(uint8)(l_duty & 0x03);
        CCPR1L=(uint8)(l_duty>>2);
        CCP1_Mode_Options(CCP1_PWM_MODE);
    }
    else {/* Nothing*/}

}

void CCP1_ISR(void)
{
    CCP1_Interrupt_Clear_Flag();
    if(CCP1_Interrupt_handler)
    {
        CCP1_Interrupt_handler();
    }    
}



