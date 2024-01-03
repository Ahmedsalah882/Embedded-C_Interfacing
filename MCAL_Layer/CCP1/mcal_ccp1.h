/* 
 * File:   mcal_ccp1.h
 * Author: AhmedSalah
 *
 * Created on September 15, 2023, 10:44 AM
 */

#ifndef MCAL_CCP_H
#define	MCAL_CCP_H


/* Section: Includes*/
#include "mcal_ccp1_config.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "pic18f4620.h"

/* Section: Macro Definitions*/
#define CCP1_MODE_DISABLED                                          0x00

#define CCP1_COMPARE_MODE_TOGGLE_PIN_ON_MATCH                       0x02
#define CCP1_COMPARE_MODE_HIGH_PIN_ON_MATCH                         0x08  // Different from him(gaphar)
#define CCP1_COMPARE_MODE_LOW_PIN_ON_MATCH                          0x09  // Different from him(gaphar)   
#define CCP1_COMPARE_MODE_ON_MATCH_GEN_SW_INTERRUPT                 0x0A
#define CCP1_COMPARE_MODE_REST_TIMER_ON_MATCH                       0x0B

#define CCP1_CAPTURE_MODE_EVERY_FALLING_EDGE                        0x04
#define CCP1_CAPTURE_MODE_EVERY_RISING_EDGE                         0x05
#define CCP1_CAPTURE_MODE_EVERY_4_RISING_EDGE                       0x06
#define CCP1_CAPTURE_MODE_EVERY_16_RISING_EDGE                      0x07

#define CCP1_PWM_MODE                                               0x0C   


#define CCP1_CAPTURE_MODE_NOT_READY                                 0x00
#define CCP1_CAPTURE_MODE_READY                                     0x01

#define CCP1_COMPARE_MODE_NOT_READY                                 0x00
#define CCP1_COMPARE_MODE_READY                                     0x01

#define  CCP1_TIMER2_POSTSCALER_DIV_1                               0x01
#define  CCP1_TIMER2_POSTSCALER_DIV_2                               0x02
#define  CCP1_TIMER2_POSTSCALER_DIV_3                               0x03
#define  CCP1_TIMER2_POSTSCALER_DIV_4                               0x04
#define  CCP1_TIMER2_POSTSCALER_DIV_5                               0x05
#define  CCP1_TIMER2_POSTSCALER_DIV_6                               0x06
#define  CCP1_TIMER2_POSTSCALER_DIV_7                               0x07
#define  CCP1_TIMER2_POSTSCALER_DIV_8                               0x08
#define  CCP1_TIMER2_POSTSCALER_DIV_9                               0x09
#define  CCP1_TIMER2_POSTSCALER_DIV_10                              0x0A
#define  CCP1_TIMER2_POSTSCALER_DIV_11                              0x0B
#define  CCP1_TIMER2_POSTSCALER_DIV_12                              0x0C
#define  CCP1_TIMER2_POSTSCALER_DIV_13                              0x0D
#define  CCP1_TIMER2_POSTSCALER_DIV_14                              0x0E
#define  CCP1_TIMER2_POSTSCALER_DIV_15                              0x0F
#define  CCP1_TIMER2_POSTSCALER_DIV_16                              0x10

#define  CCP1_TIMER2_PRESCALER_DIV_1                                0x01
#define  CCP1_TIMER2_PRESCALER_DIV_4                                0x04
#define  CCP1_TIMER2_PRESCALER_DIV_16                               0x10
/* Section: Macro Functions*/

#define CCP1_Mode_Options(_MODE)                                    (CCP1CONbits.CCP1M=_MODE)  


/* Section: Data Type Declarations*/
typedef enum{
    CCP1_MODE_CAPTURE,
    CCP1_MODE_COMPARE,
    CCP1_MODE_PWM,        
}ccp1_mode_t;

typedef union{
    struct{
        uint8 ccpr1_low;
        uint8 ccpr1_high;
    };
    struct{
        uint16 ccpr1_16Bit;
    };
}ccp1_reg_t;


typedef struct{
pin_config_t ccp1_pin;    
ccp1_mode_t ccp1_source;
uint8 sub_mode;
#if CCP1_INTERRUPT_FEATURE == CCP1_INTERRUPT_FEATURE_ENABLE
void(*CCP1_Interrupt_handler)(void);
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
interrupt_priority_t priority;
#endif
#endif
#if CCP1_Mode_Selected == CCP1_PWM_Mode_Selected
    uint32 pwm_freq;
    uint8 duty_cycle;
    uint8 prescaler_value;
    uint8 postscaler_value;
#endif

    
}ccp1_t;

/* Section: Function Prototype*/
std_ReturnType CCP1_Initialization(const ccp1_t* ccp1);
std_ReturnType CCP1_DeInitialization(const ccp1_t* ccp1);

#if CCP1_Mode_Selected == CCP1_Capture_Mode_Selected
std_ReturnType CCP1_IS_Capture_Data_Ready(uint8* status);
std_ReturnType CCP1_Read_Capture_Data(const ccp1_t* ccp1, uint16* data);

#endif


#if CCP1_Mode_Selected == CCP1_Compare_Mode_Selected

std_ReturnType CCP1_IS_Compare_Data_Ready(uint8* status);
std_ReturnType CCP1_Write_Compare_Data(const ccp1_t* ccp1, uint16 data);

#endif


#if CCP1_Mode_Selected == CCP1_PWM_Mode_Selected

std_ReturnType CCP1_Set_DutyCycle(const ccp1_t* ccp1,const uint8 duty);


#endif







#endif	/* MCAL_CCP_H */

