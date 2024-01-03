/* 
 * File:   mcal_adc.c
 * Author: AhmedSalah
 *
 * Created on August 31, 2023, 3:54 AM
 */



#include "mcal_adc.h"

static std_ReturnType ADC_Select_Voltage_Refrence(const adc_t* _adc);
static std_ReturnType ADC_Select_Result_Format(const adc_t* _adc);
static void ADC_Select_config_Channel(adc_channel_select_t channel);

#if ADC_INTERRUPT_FEATURE == ADC_INTERRUPT_FEATURE_ENABLE
static void (*ADC_Interrupt_Handler) (void)=NULL;

#endif

/**
 * @brief initialize the ADC
 * @param _adc
 * @return the status of the function:
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed  
 */
std_ReturnType ADC_Initialize(const adc_t * _adc)
{
   std_ReturnType ret=E_OK;
   if(NULL==_adc )
   {
       ret=E_NOT_OK;
   }
   else
   {
       
       ADC_CONVERTER_DISABLED();
       ADCON2bits.ACQT=_adc->time_acquisition;
       ADCON2bits.ADCS=_adc->conversion_clock;
       ADCON0bits.CHS=_adc->input_channel;
       ADC_Select_config_Channel(_adc->input_channel);
       ADC_Select_Voltage_Refrence(_adc);
       ADC_Select_Result_Format(_adc);
       
       /*config interrupt*/
       #if INTERRUPT_INTERNAL_FEATURE == INTERRUPT_INTERNAL_FEATURE_ENABLE
       #if ADC_INTERRUPT_FEATURE == ADC_INTERRUPT_FEATURE_ENABLE
            ADC_Interrupt_Enable();
            ADC_Interrupt_Flag_Clear();
            ADC_Interrupt_Handler=_adc->ADC_Interrupt_Handler;
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
            Interrupt_priority_Enable();
            if(INTERRUPT_HIGH_PRIORITY==_adc->adc_interrupt_priority)
            {
                ADC_Interrupt_High_Priority();
                Interrupt_High_Priority_Enable();
            }
            else if(INTERRUPT_LOW_PRIORITY==_adc->adc_interrupt_priority)
            {
                ADC_Interrupt_Low_Priority();
                Interrupt_Low_Priority_Enable(); 
            }
            else {/* Nothing */}
            
        #else
            
            Interrupt_Peripheral_Enable();
            Interrupt_Global_Enable() ;
        #endif    
       #endif     
       #endif
       ADC_CONVERTER_ENABLED();
   }
   return ret;
}
/**
 * 
 * @param _adc
 * @return the status of the function:
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType ADC_Deinitialize(const adc_t * _adc)
{
   std_ReturnType ret=E_OK;
   if(NULL==_adc )
   {
       ret=E_NOT_OK;
   }
   else
   {
       ADC_CONVERTER_DISABLED();
       /*Disable interrupt config*/
       #if ADC_INTERRUPT_FEATURE == ADC_INTERRUPT_FEATURE_ENABLE
            ADC_Interrupt_Disable();
       #endif
      
   }
   return ret;
}
/**
 * 
 * @param _adc
 * @param channel
 * @return the status of the function:
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType ADC_Select_Channel(const adc_t * _adc, adc_channel_select_t channel )
{
   std_ReturnType ret=E_OK;
   if(NULL==_adc )
   {
       ret=E_NOT_OK;
   }
   else
   {
       ADCON0bits.CHS=channel;
       ADC_Select_config_Channel(channel);
       
   }
   return ret;    
}
/**
 * 
 * @param _adc
 * @return the status of the function:
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType ADC_Start_Conversion(const adc_t* _adc)
{
   std_ReturnType ret=E_OK;
   if(NULL==_adc )
   {
       ret=E_NOT_OK;
   }
   else
   {
       ADC_START_CONVERSION();
   }
   return ret;    
}
/**
 * 
 * @param _adc
 * @param conversion_status
 * @return the status of the function:
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType ADC_Get_Conversion_status(const adc_t * _adc, uint8 * conversion_status)
{
   std_ReturnType ret=E_OK;
   if(NULL==_adc  || NULL==conversion_status)
   {
       ret=E_NOT_OK;
   }
   else
   {
       *conversion_status= (uint8)(!(ADCON0bits.GO_nDONE));
   }
   return ret;   
}
/**
 * 
 * @param _adc
 * @param result
 * @return the status of the function:
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType ADC_GET_RESULT(const adc_t * _adc, uint16* result)
{
   std_ReturnType ret=E_OK;
   if(NULL==_adc || NULL==result)
   {
       ret=E_NOT_OK;
   }
   else
   {
       if (ADC_RESULT_FORMAT_LEFT_JUSTIFIED==_adc->result_format)
       {
           *result=(uint16)( ((ADRESL + (ADRESH<<8) )>>6) );
       }
       else if(ADC_RESULT_FORMAT_RIGHT_JUSTIFIED==_adc->result_format)
       {
           *result= (uint16)( ADRESL + ((ADRESH << 8)) ) ;
       }  
       else
       {
           *result= (uint16)( ADRESL + ((ADRESH << 8)) ) ;
       }
   }
   return ret;    
}
/**
 * 
 * @param _adc
 * @param channel
 * @param result
 * @return the status of the function:
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType ADC_Select_Channel_Get_Result_Bolcking(const adc_t * _adc, adc_channel_select_t channel
                                              ,uint16* result )
{
   std_ReturnType ret=E_OK;
   if(NULL==_adc || NULL==result)
   {
       ret=E_NOT_OK;
   }
   else
   {   
       ret=ADC_Select_Channel(_adc,channel);
       ret=ADC_Start_Conversion(_adc);
       while(ADCON0bits.GO_nDONE);
       ret=ADC_GET_RESULT(_adc,result);
       
   }
   return ret;    
}   
/**
 * 
 * @param _adc
 * @param channel
 * @return the status of the function:
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType ADC_Select_Channel_Start_Conversion_Interrupt(const adc_t * _adc, adc_channel_select_t channel )
{
   std_ReturnType ret=E_OK;
   if(NULL==_adc )
   {
       ret=E_NOT_OK;
   }
   else
   {   
       ret=ADC_Select_Channel(_adc,channel);
       ret=ADC_Start_Conversion(_adc);
      
   }
   return ret;    
}   


static std_ReturnType ADC_Select_Voltage_Refrence(const adc_t* _adc)
{
   std_ReturnType ret=E_OK;
   if(NULL==_adc )
   {
       ret=E_NOT_OK;
   }
   else
   {
    switch (_adc->voltage_ref)
        {    
            case ADC_VOLTAGE_REF_ENABLED  :ADC_VOLTAGE_REFRENCE_ENABLED()  ; break;
            case ADC_VOLTAGE_REF_DISABLED :ADC_VOLTAGE_REFRENCE_DISABLED() ; break; 
            default: ADC_VOLTAGE_REFRENCE_DISABLED()                       ; break;
        }    
    }
   return ret;
    
}

static std_ReturnType ADC_Select_Result_Format(const adc_t* _adc)
{
   std_ReturnType ret=E_OK;
   if(NULL==_adc )
   {
       ret=E_NOT_OK;
   }
   else
   {
       if (ADC_RESULT_FORMAT_LEFT_JUSTIFIED==_adc->result_format)
       {
           ADCON2bits.ADFM=ADC_RESULT_FORMAT_LEFT_JUSTIFIED;
       }
       else if(ADC_RESULT_FORMAT_RIGHT_JUSTIFIED==_adc->result_format)
       {
           ADCON2bits.ADFM=ADC_RESULT_FORMAT_RIGHT_JUSTIFIED;
       }  
       else
       {
           ADCON2bits.ADFM=ADC_RESULT_FORMAT_RIGHT_JUSTIFIED;
       }
   }
   return ret;
}

static void ADC_Select_config_Channel(adc_channel_select_t channel)
{

    switch (channel)
        {    
            case ADC_CHANNEL_AN0 :SET_BIT(TRISA, _TRISA_RA0_POSN); break;
            case ADC_CHANNEL_AN1 :SET_BIT(TRISA, _TRISA_RA1_POSN); break;
            case ADC_CHANNEL_AN2 :SET_BIT(TRISA, _TRISA_RA2_POSN); break;
            case ADC_CHANNEL_AN3 :SET_BIT(TRISA, _TRISA_RA3_POSN); break;
            case ADC_CHANNEL_AN4 :SET_BIT(TRISA, _TRISA_RA5_POSN); break;
            case ADC_CHANNEL_AN5 :SET_BIT(TRISE, _TRISE_RE0_POSN); break;
            case ADC_CHANNEL_AN6 :SET_BIT(TRISE, _TRISE_RE1_POSN); break;
            case ADC_CHANNEL_AN7 :SET_BIT(TRISE, _TRISE_RE2_POSN); break;
            case ADC_CHANNEL_AN8 :SET_BIT(TRISB, _TRISB_RB2_POSN); break;
            case ADC_CHANNEL_AN9 :SET_BIT(TRISB, _TRISB_RB3_POSN); break;
            case ADC_CHANNEL_AN10 :SET_BIT(TRISB,_TRISB_RB1_POSN); break;
            case ADC_CHANNEL_AN11 :SET_BIT(TRISB,_TRISB_RB4_POSN); break;
            case ADC_CHANNEL_AN12 :SET_BIT(TRISB,_TRISB_RB0_POSN); break;
        }    
    
  
}


void ADC_ISR(void)
{
    /* Clear Flag*/
    ADC_Interrupt_Flag_Clear();
    /*some code*/
    /*ADC Handler*/
#if ADC_INTERRUPT_FEATURE == ADC_INTERRUPT_FEATURE_ENABLE    
    if (ADC_Interrupt_Handler)
    { 
        ADC_Interrupt_Handler();
    }
#endif        
}



