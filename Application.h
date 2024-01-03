/* 
 * File:   Application.h
 * Author: AhmedSalah
 *
 * Created on August 16, 2023, 2:31 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section: Includes                */
#include "ECU_Layer/ecu_layer_initialize.h"
#include"MCAL_Layer/mcal_layer_initialize.h"

/* Section : Macro Definition       */
#define _XTAL_FREQ 8000000   // this is used by the __delay_ms(xx) and __delay_us(xx) functions

/* Section : Macro Functions        */

/* Section : Data Type Declaration  */
extern keypad_t keypad1 ;
extern lcd_4bit_t lcd_4bit;
extern lcd_8bit_t lcd_8bit;
extern dc_motor_t dc_motor_1;
extern dc_motor_t dc_motor_2;

/* Section : Function Prototype     */
void application_inialize(void);
void INT0_APP_Handler(void);
void RBX_Interrupt_Handler_High(void);
void RBX_Interrupt_Handler_low(void);
#endif	/* APPLICATION_H */

