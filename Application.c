/* 
 * File:   Application.c
 * Author: AhmedSalah
 *
 * Created on August 16, 2023, 1:19 PM
 */


#include "Application.h"



led_t led1={
    .port=PORTE_INDEX,
    .pin=GPIO_PIN0,
    .led_status=LED_OFF        
};


ccp1_t ccp1={
    .CCP1_Interrupt_handler=NULL,
    .ccp1_pin.port=PORTC_INDEX,
    .ccp1_pin.pin=GPIO_PIN2,
    .ccp1_pin.direction=GPIO_DIRECTION_OUTPUT,
    .ccp1_source=CCP1_MODE_PWM,
    .sub_mode=CCP1_PWM_MODE,
    .pwm_freq=20000,
    .duty_cycle=25,
    .postscaler_value=CCP1_TIMER2_POSTSCALER_DIV_1,
    .prescaler_value=CCP1_TIMER2_PRESCALER_DIV_1
};


timer2_t timer2={
  .TIMER2_INTERRUPT_HANDLER=NULL,
  .timer2_postscaler=TIMER2_POSTSCALER_DIV_1,
  .timer2_prescaler=TIMER2_PRESCALER_DIV_BY_1,
  .timer2_preload=0,
  
};

std_ReturnType ret=E_NOT_OK;
uint32 ll_duty=0,value;

int main() {
   
    application_inialize();
    Timer2_Init(&timer2);
    CCP1_Initialization(&ccp1);
    while(1)
    {      
    
      
            ll_duty+=5;
            CCP1_Set_DutyCycle(&ccp1,ll_duty);
            __delay_ms(5);
            if(ll_duty==100)
            {  
                ll_duty=0;
            }
    }     
    return (EXIT_SUCCESS);
}

void application_inialize(void)
{   
    ecu_initialize();
    mcal_initialize();
   led_initialize(&led1); 
   //ret=led_turn_on(&led1); 
}

