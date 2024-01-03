/* 
 * File:   mcal_layer_initialize.c
 * Author: AhmedSalah
 *
 * Created on September 4, 2023, 3:48 AM
 */


#include "mcal_layer_initialize.h"
/*
uint8 adc_res1_txt[6];
uint8 adc_res2_txt[6];
uint8 adc_res3_txt[6];
uint8 adc_res4_txt[6];
 
volatile uint8 adc_flag=0,ADC_req=0;
uint16 adc_res1=0,adc_res2=0,adc_res3=0,adc_res4=0;


adc_t adc1={
 .ADC_Interrupt_Handler=ADC_DEFAULT_INTERRUPT_HANDLER,
  .conversion_clock=ADC_CONVERSION_CLOCK_FOSC_DIV_8,
  .input_channel=ADC_CHANNEL_AN0,
  .result_format=ADC_RESULT_FORMAT_RIGHT_JUSTIFIED,
  .time_acquisition=ADC_ACQ_TAD12,
  .voltage_ref=ADC_VOLTAGE_REF_DISABLED,
  
};

 
 void Timer0_Interrupt_Handler (void)
{   std_ReturnType ret=E_OK;
    
    led_toggle(&led1);
}


timer0_t timer0_1={
  .Timer0InterruptHandler=Timer0_Interrupt_Handler,
  .timer0_mode=TIMER0_TIMER_MODE,
  .timer0_reg_size=TIMER0_REG_SIZE_16_BIT,
  .edge_source=TIMER0_EXTERNAL_SOURCE_RISING_EDGE,
  .prescaler_option=TIMER0_PRESCALER_ACTIVATED,
  .prescalar_value=TIMER0_PRESCALER_DIV_BY_8,
  .preloaded_value=3036,
  
};

timer0_t timer0_2={
  .Timer0InterruptHandler=Timer0_Interrupt_Handler,
  .timer0_mode=TIMER0_COUNTER_MODE,
  .timer0_reg_size=TIMER0_REG_SIZE_16_BIT,
  .edge_source=TIMER0_EXTERNAL_SOURCE_RISING_EDGE,
  .prescaler_option=TIMER0_PRESCALER_DEACTIVATED,
  .preloaded_value=0,
  
};

 
        
external_interrupt_RBX_t rb4={
  .Interrupt_RBX_Handler_HIGH=RBX_Interrupt_Handler_High,
  .Interrupt_RBX_Handler_LOW=RBX_Interrupt_Handler_low,
  .priority=INTERRUPT_HIGH_PRIORITY,
  .pin.port=PORTB_INDEX,
  .pin.pin=GPIO_PIN4,
  .pin.direction=GPIO_DIRECTION_INPUT
};

external_interrupt_RBX_t rb5={
  .Interrupt_RBX_Handler_HIGH=RBX_Interrupt_Handler_High,
  .Interrupt_RBX_Handler_LOW=RBX_Interrupt_Handler_low,
  .priority=INTERRUPT_HIGH_PRIORITY,
  .pin.port=PORTB_INDEX,
  .pin.pin=GPIO_PIN5,
  .pin.direction=GPIO_DIRECTION_INPUT
};
external_interrupt_RBX_t rb6={
  .Interrupt_RBX_Handler_HIGH=RBX_Interrupt_Handler_High,
  .Interrupt_RBX_Handler_LOW=RBX_Interrupt_Handler_low,
  .priority=INTERRUPT_HIGH_PRIORITY,
  .pin.port=PORTB_INDEX,
  .pin.pin=GPIO_PIN6,
  .pin.direction=GPIO_DIRECTION_INPUT
};

external_interrupt_RBX_t rb7={
  .Interrupt_RBX_Handler_HIGH=RBX_Interrupt_Handler_High,
  .Interrupt_RBX_Handler_LOW=RBX_Interrupt_Handler_low,
  .priority=INTERRUPT_HIGH_PRIORITY,
  .pin.port=PORTB_INDEX,
  .pin.pin=GPIO_PIN7,
  .pin.direction=GPIO_DIRECTION_INPUT
};
 
  
void RBX_Interrupt_Handler_High(void)
{   
    led_turn_on(&led1);
    led_turn_off(&led2);
}
void RBX_Interrupt_Handler_low(void)
{   
    led_turn_off(&led1);
    led_turn_on(&led2);
}
 
  
  
   
*/
void eeprom_feature(void)
{ /*
     ret=EEPROM_Memory_Write(0x3ff,3);
     ret=EEPROM_Memory_Write(0x260,12);
     
    while(1)
     {  
         ret=EEPROM_Memory_Write(0x3ff,eeprom_counter++);
         ret=EEPROM_Memory_Read(0x3ff,&eeprom_data);
         __delay_ms(500);
         if(eeprom_data>15)
             led_turn_on(&led1);
         else
             led_toggle(&led1);
         */    
         
    
}

void ADC_3_POT(void)
{
    /*
     ret=lcd_4bit_send_string_specific_position(&lcd_4bit,1,1,"pot0: ");
     ret=lcd_4bit_send_string_specific_position(&lcd_4bit,2,1,"pot1: ");
     ret=lcd_4bit_send_string_specific_position(&lcd_4bit,3,1,"pot2: ");
     ret=lcd_4bit_send_string_specific_position(&lcd_4bit,4,1,"pot3: ");
     
     
     while(1)
     {      
        if(ADC_CHANNEL_AN0==ADC_req)
        {    
        ret=ADC_Select_Channel_Start_Conversion_Interrupt(&adc1 ,ADC_CHANNEL_AN0);
        }
        else if(ADC_CHANNEL_AN1==ADC_req)
        {    
        ret=ADC_Select_Channel_Start_Conversion_Interrupt(&adc1 ,ADC_CHANNEL_AN1);
        }
        else if(ADC_CHANNEL_AN2==ADC_req)
        {    
        ret=ADC_Select_Channel_Start_Conversion_Interrupt(&adc1 ,ADC_CHANNEL_AN2);
        }
        else if(ADC_CHANNEL_AN3==ADC_req)
        {    
        ret=ADC_Select_Channel_Start_Conversion_Interrupt(&adc1 ,ADC_CHANNEL_AN3);
        }
        
        ret=convert_short_to_string(adc_res1,adc_res1_txt) ;
        ret=convert_short_to_string(adc_res2,adc_res2_txt) ;
        ret=convert_short_to_string(adc_res3,adc_res3_txt) ;
        ret=convert_short_to_string(adc_res4,adc_res4_txt) ;
            
        ret=lcd_4bit_send_string_specific_position(&lcd_4bit,1,7,adc_res1_txt);
        ret=lcd_4bit_send_string_specific_position(&lcd_4bit,2,7,adc_res2_txt);
        ret=lcd_4bit_send_string_specific_position(&lcd_4bit,3,7,adc_res3_txt);
        ret=lcd_4bit_send_string_specific_position(&lcd_4bit,4,7,adc_res4_txt);  
          
     */
}


void mcal_initialize(void)
{
    
    /*
     ADC_Initialize(&adc1); 
     ret=External_Interrupt_RBX_Initialization(&rb4);
     ret=External_Interrupt_RBX_Initialization(&rb5);
     ret=External_Interrupt_RBX_Initialization(&rb6);
     ret=External_Interrupt_RBX_Initialization(&rb7);
     */ 
      
      
}






/*
void ADC_DEFAULT_INTERRUPT_HANDLER(void)
{   
   //adc_flag++; 
   std_ReturnType ret=E_NOT_OK;
   if(ADC_CHANNEL_AN0==ADC_req)
   {    
        ret=ADC_GET_RESULT(&adc1,&adc_res1);
        ADC_req=1;
   }
   else if(ADC_CHANNEL_AN1==ADC_req)
   {    
        ret=ADC_GET_RESULT(&adc1,&adc_res2);
        ADC_req=2;
   }
   else if(ADC_CHANNEL_AN2==ADC_req)
   {    
        ret=ADC_GET_RESULT(&adc1,&adc_res3);
        ADC_req=3;
   }
   else if(ADC_CHANNEL_AN3==ADC_req)
   {    
        ret=ADC_GET_RESULT(&adc1,&adc_res4);
        ADC_req=0;
   }
}


**/

void timer0_test(void)
{
    //uint16 value=ZERO_INIT;
    //ret=Timer0_Initialize(&timer0_1);
   // ret=Timer0_Initialize(&timer0_2);
    //ret=Timer0_Read_Value(&timer0_1,&value);
    
}