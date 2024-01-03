/* 
 * File:   mcal_adc.h
 * Author: AhmedSalah
 *
 * Created on August 31, 2023, 3:54 AM
 */

#ifndef MCAL_ADC_H
#define	MCAL_ADC_H

/* Section: Includes */
#include "mcal_adc_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* Section: Macro Definitions */

#define ADC_RESULT_FORMAT_LEFT_JUSTIFIED         0x00
#define ADC_RESULT_FORMAT_RIGHT_JUSTIFIED        0x01

#define ADC_VOLTAGE_REF_ENABLED                  0x01
#define ADC_VOLTAGE_REF_DISABLED                 0x00

#define ADC_CONVERSION_COMPLETED                 0x01
#define ADC_CONVERSION_IN_PROGRESS               0x00

/* Section: Macro Functions */

/* ADC Conversion Status : ADC status in progress / ADC is Idle*/
#define ADC_CONVERSION_STATUS()                 (ADCON0bits.GO_nDONE)

/* Start the ADC Conversion */
#define ADC_START_CONVERSION()                 (ADCON0bits.GO_nDONE=1)

/* Enable the ADC / Disable the ADC*/
#define ADC_CONVERTER_ENABLED()                 (ADCON0bits.ADON=1)
#define ADC_CONVERTER_DISABLED()                (ADCON0bits.ADON=0)

/* ADC Voltage Refrence Enabled  : voltage refrence is VREF+ & VREF-
 * ADC Voltage Refrence Disabled : voltage refrence is VSS   & VDD
*/
#define ADC_VOLTAGE_REFRENCE_ENABLED()          {ADCON1bits.VCFG0=1;\
                                                 ADCON1bits.VCFG0=1;\
                                                }         

#define ADC_VOLTAGE_REFRENCE_DISABLED()         {ADCON1bits.VCFG0=0;\
                                                 ADCON1bits.VCFG0=0;\
                                                }         


/* Example: ADC_ANALOG_DIGITAL_CONFIG(ADC_AN9_DIGITAL_FUNCTIONALITY) 
 * this  means AN9,AN10,AN11,AN12 will have digital functionality
 */
#define ADC_ANALOG_DIGITAL_CONFIG(_config)      (ADCON1bits.PCFG=_config)


/* Section: Data Type Declarations */
typedef enum{
    ADC_CHANNEL_AN0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,        
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,        
}adc_channel_select_t;

/* If AN11 is Selected digital this means All AN Bigger Than AN11 Will be digital --> AN11 & AN12  are digital  */
typedef enum{
    ADC_ALL_ANALOG_FUNCTIONALITY=2,
    ADC_AN12_DIGITAL_FUNCTIONALITY,
    ADC_AN11_DIGITAL_FUNCTIONALITY,
    ADC_AN10_DIGITAL_FUNCTIONALITY,
    ADC_AN9_DIGITAL_FUNCTIONALITY,
    ADC_AN8_DIGITAL_FUNCTIONALITY,
    ADC_AN7_DIGITAL_FUNCTIONALITY,        
    ADC_AN6_DIGITAL_FUNCTIONALITY,        
    ADC_AN5_DIGITAL_FUNCTIONALITY,        
    ADC_AN4_DIGITAL_FUNCTIONALITY,        
    ADC_AN3_DIGITAL_FUNCTIONALITY,
    ADC_AN2_DIGITAL_FUNCTIONALITY,        
    ADC_AN1_DIGITAL_FUNCTIONALITY,
    ADC_ALL_DIGITAL_FUNCTIONALITY        
}adc_analog_digital_functionality_t;

typedef enum{
    ADC_ACQ_TAD0,
    ADC_ACQ_TAD2,
    ADC_ACQ_TAD4,
    ADC_ACQ_TAD6,
    ADC_ACQ_TAD8,
    ADC_ACQ_TAD12,        
    ADC_ACQ_TAD16,
    ADC_ACQ_TAD20        
}adc_acquisition_time_t;

typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,        
    ADC_CONVERSION_CLOCK_FOSC_DIV_64       
}adc_conversion_clock_t;

typedef struct{
#if ADC_INTERRUPT_FEATURE == ADC_INTERRUPT_FEATURE_ENABLE
    void (* ADC_Interrupt_Handler) (void); 
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE    
    interrupt_priority_t adc_interrupt_priority ;
#endif    
#endif    
    uint8 input_channel                 :4;
    uint8 pins_functionality            :4;
    uint8 time_acquisition              :3;
    uint8 conversion_clock              :3;
    uint8 voltage_ref                   :1;
    uint8 result_format                 :1;
}adc_t;

/* Section: Function Prototypes */
std_ReturnType ADC_Initialize(const adc_t * _adc);
std_ReturnType ADC_Deinitialize(const adc_t * _adc);
std_ReturnType ADC_Select_Channel(const adc_t * _adc,adc_channel_select_t channel );
std_ReturnType ADC_Start_Conversion(const adc_t* _adc);
std_ReturnType ADC_Get_Conversion_status(const adc_t * _adc, uint8 * conversion_status);
std_ReturnType ADC_GET_RESULT(const adc_t * _adc, uint16* result);
std_ReturnType ADC_Select_Channel_Get_Result_Bolcking(const adc_t * _adc, adc_channel_select_t channel
                                                       ,uint16* result );
std_ReturnType ADC_Select_Channel_Start_Conversion_Interrupt(const adc_t * _adc, adc_channel_select_t channel);

void ADC_ISR(void);

#endif	/* MCAL_ADC_H */ 

