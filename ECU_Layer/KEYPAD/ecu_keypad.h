/* 
 * File:   ecu_keypad.h
 * Author: AhmedSalah
 *
 * Created on August 24, 2023, 4:12 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section: Includes */
#include "ecu_keypad_config.h"
#include "../../ECU_Layer/PushButton/ecu_push_button.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Definitions  */

/* Section: Macro Functions */

/* Section: Data Type Declarations */
typedef struct {
    pin_config_t keypad_row_pins[KEYPAD_MAX_ROWS];
    pin_config_t keypad_column_pins[KEYPAD_MAX_COLUMNS];
}keypad_t;

/* Section: Function Prototypes */
std_ReturnType keypad_initialize(const keypad_t * _keypad);
std_ReturnType keypad_get_value(const keypad_t* _keypad, uint8 * value );

#endif	/* ECU_KEYPAD_H */

