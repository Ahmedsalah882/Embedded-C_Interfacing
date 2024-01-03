/* 
 * File:   ecu_layer_initialize.c
 * Author: AhmedSalah
 *
 * Created on August 24, 2023, 7:21 AM
 */

#ifndef ECU_LAYER_INITIALIZE_H
#define	ECU_LAYER_INITIALIZE_H

/* Section: Includes */
#include "../ECU_Layer/LED/ecu_led.h"
#include "../ECU_Layer/PushButton/ecu_push_button.h"
#include "../ECU_Layer/RELAY/ecu_relay.h"
#include "../ECU_Layer/DC_MOTOR/ecu_dc_motor.h"
#include "../ECU_Layer/7_seg/ecu_7_seg.h"
#include "../ECU_Layer/KEYPAD/ecu_keypad.h"
#include "../ECU_Layer/LCD/ecu_lcd.h"

/* Section: Function Prototypes*/
void ecu_initialize(void);
void test_seven_seg_clock_project(void);
void keypad_test_return_value(void);
void lcd_test_number_custom_char_different_pos(void);
void lm35(void);
#endif	/* ECU_LAYER_INITIALIZE_H */

