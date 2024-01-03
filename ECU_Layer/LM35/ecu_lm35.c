/* 
 * File:   ecu_lm35.c
 * Author: AhmedSalah
 *
 * Created on September 11, 2023, 8:13 PM
 */

#include "ecu_lm35.h"

/**
 * 
 * @param lm35
 * @param result
 * @return 
 */
std_ReturnType Read_LM35_Temp(const adc_t* lm35, uint8* result)
{
    std_ReturnType ret= E_OK;
    if(NULL== lm35 || NULL== result)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        #if INTERRUPT_INTERNAL_FEATURE == INTERRUPT_INTERNAL_FEATURE_ENABLE
        #if ADC_INTERRUPT_FEATURE == ADC_INTERRUPT_FEATURE_DISABLE
        
                ret=ADC_Select_Channel_Start_Conversion_Interrupt(lm35, lm35->input_channel);
        #else
                ret=ADC_Select_Channel_Get_Result_Bolcking(lm35,lm35->input_channel,result);
                *result= *result *(5000/(float32)1024);
                *result/=10;
        #endif
        
        #else
                ret=ADC_Select_Channel_Get_Result_Bolcking(lm35,lm35->input_channel,result);
                *result= *result *(5000/(float32)1024);
                *result/=10;
        #endif
        
    }   
    return ret;
}